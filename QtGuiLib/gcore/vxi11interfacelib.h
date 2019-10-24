#ifndef VXI11INTERFACELIB_H
#define VXI11INTERFACELIB_H


#ifdef WIN32
    #ifdef STATIC_LIB
        #define VXI_API         extern
    #else
        #ifdef VXI11INTERFACELIB_LIB
            #define VXI_API     __declspec(dllexport)
        #else
            #define VXI_API     __declspec(dllimport)
        #endif
    #endif
#else
    #define VXI_API             extern
#endif


#ifdef _WIN32
    #include <Windows.h>

    #ifdef __MINGW32__
        extern "C"
        {
            #include <rpc/types.h>
            #include <rpc/rpc.h>
            #include <rpc/xdr.h>
            #include <rpc/auth.h>
            #include <rpc/auth_uni.h>
            #include <rpc/clnt.h>
            #include <rpc/pmap_cln.h>
            #include <rpc/pmap_pro.h>
        }
    #endif
#else
    #include <rpc/clnt.h>
#endif

#include <QtCore\QStringList>
#include <QtCore\QMap>
#include <QtCore\QHash>

#include "vxi11_hdr.h"


#define VXI_IO_TIMEOUT                  30000       // Timeout for VXI11 I/O operations
#define VXI_LOCK_TIMEOUT                1500        // Timeout for VXI11 lock operations

#define VXI11_FLAG_SHOULD_WAIT          0x00000001  // If the flag is set to one(1), then the network instrument server suspends (blocks) the
                                                    // requested operation for at least lock_timeout milliseconds if it cannot be performed due to a lock held 
                                                    // by another link. If the flag is reset to zero(0), then the network instrument server sets the
                                                    // error value to 11 and returns if the operation cannot be performed due to a lock held by another link
#define VXI11_FLAG_END_DATA             0x00000008  // If the flag is set to one(1) then the last byte in the buffer is sent with an END indicator.
                                                    // This flag is only valid for device_write
#define VXI11_FLAG_TERM_CHAR_PRESENT    0x00000080  // This flag is set to one(1) if a termination character is specified on a read. The
                                                    // actual termination character itself is passed in the termchr parameter.This flag is only valid for device_read
#define VXI11_REASON_END_BIT	        0x04	    // An end indicator has been read
#define VXI11_REASON_CHR_BIT	        0x02	    // A termchr is set in flags and a character which matches termChar is transferred
#define VXI11_REASON_REQCNT_BIT	        0x01	    // requestSize bytes have been transferred.  This includes a request size of zero.

#define VXI_MAX_SRQ_DATA_SIZE           (40-sizeof(qint32))    // Max size for user data in interrupt call

#define VXI11_IOCTRL_READ_STB           1           // Execute VXI11 device_readstb()
#define VXI11_IOCTRL_TRIGGER            2           // Execute VXI11 device_trigger()
#define VXI11_IOCTRL_CLEAR              3           // Execute VXI11 device_clear()
#define VXI11_IOCTRL_REMOTE             4           // Execute VXI11 device_remote()
#define VXI11_IOCTRL_LOCAL              5           // Execute VXI11 device_local()
#define VXI11_IOCTRL_LOCK               6           // Execute VXI11 device_lock()
#define VXI11_IOCTRL_UNLOCK             7           // Execute VXI11 device_unlock()
#define VXI11_IOCTRL_DO_CMD             8           // Execute VXI11 device_docmd()

#define VXI11_IOCTRL_GET_TIMEOUT        257         // Get timeout for network operations (parameter: long *timeout)
#define VXI11_IOCTRL_SET_TIMEOUT        258         // Set timeout to network operations (parameter: long timeout)
#define VXI11_IOCTRL_GET_SERVER_ADDRESS 259         // Get Server address as sockaddr structure (parameter: sockaddr *address)


// For description of VXI11 errors see VXI11 standard
typedef enum _vxi11stat
{
    VXI11_NO_ERROR                      = 0,
    VXI11_SYNTAX_ERROR                  = 1,
    VXI11_DEVICE_NOT_ACCESSIBLE         = 3,
    VXI11_INVALID_LINK                  = 4,
    VXI11_PARAMETER_ERROR               = 5,
    VXI11_CHANNEL_NOT_ESTABLISHED       = 6,
    VXI11_OPERATION_NOT_SUPPORTED       = 8,
    VXI11_OUT_OF_RESOURCES              = 9,
    VXI11_DEVICE_LOCKED                 = 11,
    VXI11_NO_LOCK_HELD                  = 12,
    VXI11_IO_TIMEOUT                    = 15,
    VXI11_IO_ERROR                      = 17,
    VXI11_INVALID_ADDRESS               = 21,
    VXI11_ABORT                         = 23,
    VXI11_CHANNEL_ALREADY_ESTABLISHED   = 29
} vxi11stat;

typedef quint64                 SESSION, *PSESSION;
typedef struct svc_req          ServiceRequest;

// This handlers are used to process VXI11 calls from clients of VXI11 server.
// For descriptions of VXI11 calls see VXI11 standard.
typedef struct _VxiHandlers
{
    Device_Error        (*pDeviceAbort)(Device_Link, SESSION, ServiceRequest *);            // Handler for device_abort call.

    Create_LinkResp     (*pCreateLink)(Create_LinkParms, SESSION, ServiceRequest *);        // Handler for create_link call.
                                                                                            // Create_LinkResp.lid is ignored by the library. Created Link ID is supplied in SESSION argument.
                                                                                            // If user refuses Link ID creation by setting up Create_LinkResp.error to any error code
                                                                                            // than Link ID created by the library will be freed.
                                                                                            // Create_LinkResp.abortPort filled by the library automatically.
    Device_WriteResp    (*pDeviceWrite)(Device_WriteParms, SESSION, ServiceRequest *);      // Handler for device_write call.
    Device_ReadResp     (*pDeviceRead)(Device_ReadParms, SESSION, ServiceRequest *);        // Handler for device_read call.
    Device_ReadStbResp  (*pDeviceReadstb)(Device_GenericParms, SESSION, ServiceRequest *);  // Handler for device_readstb call.
    Device_Error        (*pDeviceTrigger)(Device_GenericParms, SESSION, ServiceRequest *);  // Handler for device_trigger call.
    Device_Error        (*pDeviceClear)(Device_GenericParms, SESSION, ServiceRequest *);    // Handler for device_clear call.
    Device_Error        (*pDeviceRemote)(Device_GenericParms, SESSION, ServiceRequest *);   // Handler for device_remote call.
    Device_Error        (*pDeviceLocal)(Device_GenericParms, SESSION, ServiceRequest *);    // Handler for device_local call.
    Device_Error        (*pDeviceLock)(Device_LockParms, SESSION, ServiceRequest *);        // Handler for device_lock call.
    Device_Error        (*pDeviceUnlock)(Device_Link, SESSION, ServiceRequest *);           // Handler for device_unlock call.
    Device_Error        (*pDeviceEnableInterrupts)(Device_EnableSrqParms, SESSION, ServiceRequest *);// Handler for device_enable_srq call.
    Device_DocmdResp    (*pDeviceDoCmd)(Device_DocmdParms, SESSION, ServiceRequest *);      // Handler for device_docmd call.
    Device_Error        (*pDestroyLink)(Device_Link, SESSION, ServiceRequest *);            // Handler for destroy_link call.

    _VxiHandlers() : pDeviceAbort(NULL), pCreateLink(NULL), pDeviceWrite(NULL), pDeviceRead(NULL), pDeviceReadstb(NULL), pDeviceTrigger(NULL), pDeviceClear(NULL), 
                     pDeviceRemote(NULL), pDeviceLocal(NULL),pDeviceLock(NULL),pDeviceUnlock(NULL),pDeviceEnableInterrupts(NULL),pDeviceDoCmd(NULL),pDestroyLink(NULL)
    {}
}VxiHandlers;

typedef enum _SrvProtocolType
{
    UndefinedProtocol   = 0,
    TcpProtocol         = IPPROTO_TCP,
    UdpProtocol         = IPPROTO_UDP
}SrvProtocolType;

// Do not do any call to library methods (except for vxiGetLinkForClient(), vxiGetCommonIdForClient(), vxiMakeSessionId()) during call to user handler with any code of VxiNotifySignals!
typedef enum _VxiNotifySignals
{
    NewClientOfServer           = 1,    // notifier is called as VxiNotifierMethod(NewClientOfServer, iClientId, ServiceRequest *)
    ClientOfServerDied          = 2,    // notifier is called as VxiNotifierMethod(ClientOfServerDied, iClientId, SVCXPRT *)
    InterruptChannelEstablished = 16,   // notifier is called as VxiNotifierMethod(InterruptChannelEstablished, iClientId, VXI11_CLIENT *pCreatedClient)
    InterruptChannelDestroyed   = 17    // notifier is called as VxiNotifierMethod(InterruptChannelDestroyed, iClientId, void *pDestroyedClient)
}VxiNotifySignals;

// Type for notifier method for VXI11 server. iClientId is common ID of client of Server. See description of vxiGetCommonIdForClient() for details.
typedef void            (*VxiNotifierMethod)(VxiNotifySignals Signal, int iClientId, void *pArg);

// This structure used to supply Handler's arguments AND raw service request data to Service Request Handler.
// This type is used when bAllowRawAccessToSrqData == true in call to vxiSetupInterruptChannel(), 
// otherwise (bAllowRawAccessToSrqData == false) Handler's arguments pointer is supplied tdirectly o Service Request Handler.
typedef struct _SrqComplexData
{
    void        *pvArgs;            // Handler's arguments pointer
    QByteArray  qbaSrqRawData;      // Represents raw data in Service Request
}SrqComplexData;


// Initializes Vxi11 Interface library
VXI_API int  vxiInitialize(void);
// Cleans up Vxi11 Interface library
VXI_API void vxiCleanup(void);

// Returns link associated with Client parameter. If bCheckLink is true checks Client parameter for correctness
VXI_API int  vxiGetLinkForClient(SESSION Client,long &lLink, bool bCheckLink=true);
// Returns an ID associated with Client parameter (or common ID). This ID is an entity describing all links for particular TCP/IP client
VXI_API int  vxiGetCommonIdForClient(SESSION Client, int &iId);
// Returns a SESSION built on supplied ID and link. If bNoLinkInSession is true makes common SESSION for all links for particular TCP/IP client
VXI_API int  vxiMakeSessionId(int iClientId, long lLink, SESSION &s, bool bSkipCheck = false);

// Creates VXI11 server for CORE and ASYNC programs.
// All fields in Handlers must be initialized.
// If qslInterfacesToListenOn is not empty listen sockets are created only on these interfaces, otherwise any available interface will be used for listening.
// Format of qslInterfacesToListenOn: ip_for_interface:port_to_listen_on. For multiple interfaces their ports must be equal.
// If bPublishServer is true register created server with portmap service. If portmap service does not exist this method creates local one.
VXI_API int  vxiCreateVXI11server(const VxiHandlers &Handlers, VxiNotifierMethod pNotifier=NULL, QStringList qslInterfacesToListenOn = QStringList(), bool bPublishServer = true);
// Deletes listening sockets on interfaces pointed by qslInterfacesToDelete, if this parameter is empty, deletes all listening sockets.
// If bDestroyClients is true deletes connected clients of server also.
VXI_API int  vxiDeleteVXI11server(const QStringList &qslInterfacesToDelete = QStringList(), bool bDestroyClients=true);
// Deletes clients of VXI11 server. IDs are ones returned by vxiGetCommonIdForClient().
VXI_API int  vxiDeleteClientsOfServer(const QList<int> &qlClientIDs = QList<int>());

// Executes device_intr_srq for all links for common ID associated with Client. If bExactLink is true device_intr_srq executed only for link associated with Client.
// If qbaData is not empty it will be passed in arguments to device_intr_srq. Size of qbaData must not be greater than VXI_MAX_SRQ_DATA_SIZE.
// If piReason is not NULL result of call to device_intr_srq will be stored in *piReason.
// WARNING! This call must be used in methods pointed by VxiHandlers ONLY!
VXI_API int  vxiGenerateInterruptsInHandler(SESSION Client, bool bExactLink = false, const QByteArray &qbaData = QByteArray(), int *piReason = NULL);
// This call is identical to vxiGenerateInterruptsInHandler() except it must not be used in in methods pointed by VxiHandlers.
VXI_API int  vxiGenerateInterrupts(SESSION Client, bool bExactLink = false, const QByteArray &qbaData = QByteArray(), int *piReason = NULL);

// Finds all available in local network segment VXI11 servers and returns them in FoundDevices in format "ip_addr_of_server":QList("instrument_name")
VXI_API int  vxiFindAvailableServers(QHash<QString, QStringList> &FoundDevices, int iTimeToWaitForResponsesMs=10000);

// Opens device at IP address in qsInterface with VXI11.3 name in qsDevice and returns SESSION for it.
VXI_API int vxiOpenDevice(const QString &qsInterface, QString qsDevice, SESSION &Client, bool bIndependentTransport=true);
// Closes given SESSION and resets it to 0. If bIgnoreRpcErrors is true ignores errors in RPC calls. If bDestroyWholeClient is true deletes all links 
// for common ID associated with Client.
VXI_API int  vxiCloseDevice(SESSION &Client, bool bIgnoreRpcErrors = false, bool bDestroyWholeClient = false);

// Locks device for given SESSION
VXI_API int  vxiLockDevice(SESSION &Client, bool bWaitForFree = false, quint32 dwTimeout = VXI_IO_TIMEOUT);
// Unlocks device for given SESSION
VXI_API int  vxiUnlockDevice(SESSION &Client);

// Reads data from device in qbaBuffer. If puiBytesReturned is not NULL size of received data is written to *puiBytesReturned, otherwise qbaBuffer is resized to data size.
// if plFlags is not NULL flags which caused this method to return are written an this address.
VXI_API int  vxiRead(SESSION Client, QByteArray &qbaBuffer, quint32 *puiBytesReturned=NULL, quint32 uiTimeout = VXI_IO_TIMEOUT, long *plFlags = NULL);
// Writes data to device from qbaBuffer
VXI_API int  vxiWrite(SESSION Client, const QByteArray &qbaBuffer, quint32 uiTimeout = VXI_IO_TIMEOUT, long lFlags = VXI11_FLAG_END_DATA);
// Writes data from qsCommand to device and if qsCommand contains '?' reads response from device. Other parameters are same as for vxiRead()
VXI_API int  vxiQuery(SESSION Client, const QString &qsCommand, QByteArray &qbaBuffer, quint32 *puiBytesReturned = NULL, quint32 uiTimeout = VXI_IO_TIMEOUT, long *plFlags = NULL);

// Sets up abort channel for ID associated with Client parameter
VXI_API int  vxiSetupAbortChannel(SESSION Client);
// Destroys existing abort channel for ID associated with Client parameter
VXI_API int  vxiDestroyAbortChannel(SESSION Client);
// executes device_abort for link associated with Client
VXI_API int  vxiAbortOperation(SESSION Client);

// Sets up interrupt Channel for ID associated with Client parameter, set bAllowRawAccessToSrqData to true for UI clients (see description of SrqComplexData structure above)
VXI_API int vxiSetupInterruptChannel(SESSION Client, bool bAllowRawAccessToSrqData = false);
// Destroys interrupt Channel for ID associated with Client parameter
VXI_API int  vxiDestroyInterruptChannel(SESSION Client);
// Sets interrupt handler which will be called when VXI11 server executes device_intr_srq.
// If there is no link associated with SESSION in Client parameter, supplied handler is set for ID associated with Client
VXI_API int  vxiSetInterruptHandler(SESSION Client, void (*IntrFunc)(SESSION, void*), void *pArgs);
// Enables or disables interrupts from server for link associated with Client parameter.
// If qbaData is not empty it will be transferred to server as interrupt data for mentioned link. See VXI11 standard for details.
// Size of qbaData must not be greater than VXI_MAX_SRQ_DATA_SIZE.
VXI_API int  vxiEnableInterrupts(SESSION Client, bool bEnable, const QByteArray &qbaData=QByteArray());

// Used to do calls to VXI11 methods described by macros VXI11_IOCTRL_*. For parameters of these methods see vxi11_hdr.h file.
VXI_API int  vxiIOcontrol(SESSION Client, int iOperation, ...);

// Convenience method to get answer for command as integer value.
VXI_API int  vxiGetInt(SESSION Client, const QString &qsCommand, int &iValue, quint32 uiTimeout = VXI_IO_TIMEOUT);
// Convenience method to get answer for command as double value.
VXI_API int  vxiGetDouble(SESSION Client, const QString &qsCommand, double &dValue, quint32 uiTimeout = VXI_IO_TIMEOUT);

// Returns human readable description of error.
VXI_API QString vxiGetErrorDescription(int iErrorCode);


#endif // VXI11INTERFACELIB_H
