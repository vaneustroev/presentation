#ifndef CM_CLIENT_UI_DATA_DEFINITIONS_H
#define CM_CLIENT_UI_DATA_DEFINITIONS_H

#include <qglobal.h>

//#include "ClientUiCmdDefinitions.h"

#pragma pack(push,1)

//////////////////////////////////////////////////////////////////////////
// Authentication data definitions
//////////////////////////////////////////////////////////////////////////

namespace TG
{

typedef enum _ClientCategories : qint32
{
    NoCategory              = -1,
    OrdinaryClientCategory  = 0,
    InterfaceClientCategory = 1,
    UIclientCategory        = 2
}ClientCategories;

typedef struct _AuthenticationStepOne
{
    union MagicSignatureStepOne
    {
        quint8  AsBytes[16];
        quint32 AsDWords[4];
    } SignatureStepOne;       // string "NPP Gamma FAZA-B" XORed with Create_LinkParms.clientId

    ClientCategories    ClientCategory;         // Request of category for client
    quint32             dwFlags;
    qint32              lReversedClientId;      // ~Create_LinkParms.clientId 
}AuthenticationStepOne;

typedef struct _AuthenticationStepTwo
{
    union MagicSignatureStepTwo
    {
        quint8 AsBytes[16];
        quint32 AsDWords[4];
    } SignatureStepTwo;       // string "Auth.Login\0\0\0\0\0\0" XORed with Create_LinkParms.clientId

    quint8 bLogin[16];             // bLogin is MD5 hash of login string
}AuthenticationStepTwo;

typedef struct _AuthenticationStepThree
{
    union MagicSignatureStepThree
    {
        quint8   AsBytes[16];
        quint32 AsDWords[4];
    } SignatureStepThree;     // string "Auth.Password\0\0\0" XORed with Create_LinkParms.clientId

    quint8              bPassword[16];          // bPassword is MD5 hash of password string
}AuthenticationStepThree;

typedef struct _AuthenticationDataOnClient
{
    qint32          lLink;

    union AuthenticationSteps
    {
        AuthenticationStepOne   One;
        AuthenticationStepTwo   Two;
        AuthenticationStepThree Three;
    }Steps;
}AuthenticationDataOnClient;

typedef struct _AuthenticationDataOnServer
{
    qint32          lLink;

    struct AuthenticationSteps
    {
        AuthenticationStepOne   One;
        AuthenticationStepTwo   Two;
        AuthenticationStepThree Three;
    }Steps;
}AuthenticationDataOnServer;

//////////////////////////////////////////////////////////////////////////
// Service Request data definitions for UI client
//////////////////////////////////////////////////////////////////////////

// Organization of data with ScpiChangedSubsystem structures:
//  Firstly field wCommandId must contain valid command id. 
//  Secondly if command contains numbers it's counter must present in NumbersCounter field, numbers will be places directly after header as BYTES if they are ALL fit in BYTE
//  (bUseBigNumbers is 0) OR as WORDs if ANY of them does not fit in BYTE (bUseBigNumbers is 1).
//  Thirdly if command has data field Data Size must not be equal to 0 and data will be placed after numbers of command or directly after Header if there is no numbers.
// It is prohibited to break command represented by ScpiPackedCommand structure to different service requests. 
//
// Example 1: SENSe<1|2>:DETector<1...6>:FUNCtion:AUTO
//  NumbersCounter is 2, one for SENSE and one for DETector. Numbers ALL fit in BYTE so bUseBigNumbers is 0. DataSize and bDataToBig are 0.
//  So ScpiChangedSubsystem structure will be: {cmd_id, header={2,0,0,0}, wData[1]=1|2, wData[2]=1...6}
//  and sizeof (ScpiChangedSubsystem) - is 6 bytes.
//
// Example 2: ESPectrum:RANGe<1...300>:BANDwidth:RESolution data
//  NumbersCounter is 1, Number does not fit in BYTE so bUseBigNumbers is 1. Let data can fit in one service request so bDataToBig is 0. DataSize is sizeof(data)
//  So ScpiChangedSubsystem structure will be: {cmd_id, header={1, 1, sizeof(data), 0}, wData[1]=1|2, bData[4,...]=data}
//  and sizeof (ScpiChangedSubsystem) - is 6 + sizeof(data) bytes.
//
// Example 3: TRACe:DATA data
//  NumbersCounter is 0, bUseBigNumbers is 0. Data can not fit in service request do bDataToBig is 1. DataSize is sizeof(data)
//  So ScpiChangedSubsystem structure will be: {cmd_id, header={0, 0, sizeof(data), 1} }
//  and sizeof (ScpiChangedSubsystem) - is 4 bytes.
//
typedef struct _ScpiChangedSubsystem
{
    quint16     wCommandId;

    union ScpiPackedCommand
    {
        struct ScpiCommandLevelHeader
        {
            quint16 NumbersCounter      : 4;
            quint16 bUseBigNumbers      : 1;
            quint16 DataSize            : 5;
            quint16 bDataToBig          : 1;
            quint16                     : 0;
        }
                    Header;
        quint16     wData[1];
        quint8      bData[1];
    }
                CommandBody;
}ScpiChangedSubsystem;

typedef struct _ClientUiServiceRequestData
{
    struct _Flags
    {
        quint32     bInternalDataPresent        : 1;
        quint32     InternalDataLastByteIndex   : 5;    // if bInternalDataPresent != 0 than InternalDataLastByteIndex + 1 is sizeof(InternalData)
        quint32     ChangedSubSyssInRequest     : 4;    // if all commands in ChangedSubsystems contain NO numbers than only 8 commands are possible
        quint32     STBregister                 : 8;    // copy of Status Byte Register for the moment, if no data present AND no other changes 
                                                        //   since previous request this request is caused by new value of STB
        quint32     ESRregister                 : 8;    // copy of Event Status Register for the moment, if no data present AND no other changes 
                                                        //   since previous request this request is caused by new value of ESR
        quint32     bSlaveModeActive            : 1;    // if 1 UI client is in slave mode, if no data present AND no other changes 
                                                        //   since previous request this request is caused by new UI client mode (bit == 0 => marter, otherwise - slave)
        quint32     bErrorExecCmdInSlaveMode    : 1;    // if 1 than UI client being in slave mode tried to execute a command (this is a error case)
        quint32                                 : 0;
    }
                        Flags;
    union _Data
    {
        quint8                  bInternalData    [32];
        ScpiChangedSubsystem    ChangedSubsystems[8];
    }
                        Data;
}ClientUiServiceRequestData;

} // namespace TG

#pragma pack(pop)

#endif  // CM_CLIENT_UI_DATA_DEFINITIONS_H

