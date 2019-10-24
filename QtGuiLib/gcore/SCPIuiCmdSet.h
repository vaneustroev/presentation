#ifndef CM_SCPI_COMMAND_SET_FOR_UI_CLIENTS_H
#define CM_SCPI_COMMAND_SET_FOR_UI_CLIENTS_H

#define COMMAND_COUNTER     iUiCommandSetCounter

#include "CmdSet.h"

BEGIN_COMMAND_LIST(g_ScpiUiCmdSet)
    // IEEE Mandated Commands (SCPI std V1999.0 4.1.1)
    COMMAND_ITEM            ("*CLS",                        ceCoreCls_C)
    COMMAND_AND_QUERY_ITEM  ("*ESE",                        SCPI_CoreEseBoth)
    QUERY_ITEM              ("*ESR",                        SCPI_CoreEsrQ)
    QUERY_ITEM              ("*IDN",                        SCPI_CoreIdnQ)
    COMMAND_AND_QUERY_ITEM  ("*OPC",                        ceCoreOpc_CQ)
    COMMAND_ITEM            ("*RST",                        ceCoreRst_C)
    COMMAND_AND_QUERY_ITEM  ("*SRE",                        SCPI_CoreSreBoth)
    QUERY_ITEM              ("*STB",                        SCPI_CoreStbQ)
    QUERY_ITEM              ("*TST",                        ceCoreTst_Q)
    COMMAND_ITEM            ("*WAI",                        ceCoreWai_C)

    // Required SCPI commands (SCPI std V1999.0 4.2.1)
    QUERY_ITEM              ("SYSTem:ERRor[:NEXT]",         SCPI_SystemErrorNextQ)
    QUERY_ITEM              ("SYSTem:ERRor:COUNt",          SCPI_SystemErrorCountQ)
    QUERY_ITEM              ("SYSTem:VERSion",              SCPI_SystemVersionQ)
    
    QUERY_ITEM              ("STATus:OPERation[:EVENt]",    scpi_stub_callback)
    QUERY_ITEM              ("STATus:OPERation:CONDition",  scpi_stub_callback)
    COMMAND_AND_QUERY_ITEM  ("STATus:OPERation:ENABle",     scpi_stub_callback)
    
    QUERY_ITEM              ("STATus:QUEStionable[:EVENt]", SCPI_StatusQuestionableEventQ)
    QUERY_ITEM              ("STATus:QUEStionable:CONDition", scpi_stub_callback)
    COMMAND_AND_QUERY_ITEM  ("STATus:QUEStionable:ENABle",  SCPI_StatusQuestionableEnableBoth)

    COMMAND_ITEM            ("STATus:PRESet",               SCPI_StatusPreset)

    //////////////////////////////////////////////////////////////////////////
    // Real device commands
    //////////////////////////////////////////////////////////////////////////
    // SCPI CALCULATE subsystem
    COMMAND_AND_QUERY_ITEM  ("CALCulate#:UNIT:POWer",       ceCalculateUnitPower_CQ)
    COMMAND_AND_QUERY_ITEM  ("CALCulate#:DLINe#",           ceCalculateDLine_CQ)
    COMMAND_AND_QUERY_ITEM  ("CALCulate#:DLINe#:STATe",     ceCalculateDLineState_CQ)
    COMMAND_AND_QUERY_ITEM  ("CALCulate#:MARKer#[:STATe]",  ceCalculateMarkerState_CQ)
    COMMAND_AND_QUERY_ITEM  ("CALCulate#:MARKer#:X",        ceCalculateMarkerX__CQ)

    // SCPI SENSE subsystem
    //    SCPI SENSE:SWEEP subsystem
    COMMAND_AND_QUERY_ITEM  ("[SENSe#]:SWEep:TIME",         ceSenseSweepTime_CQ)
    COMMAND_AND_QUERY_ITEM  ("[SENSe#]:SWEep:TIME:AUTO",    ceSenseSweepTimeAuto_CQ)
    COMMAND_AND_QUERY_ITEM  ("[SENSe#]:SWEep:POINts",       ceSenseSweepPoints_CQ)
    //    SCPI SENSE:FREQUENCY subsystem
    COMMAND_AND_QUERY_ITEM  ("[SENSe#]:FREQuency:CENTer",   ceSenseFrequencyCenter_CQ)
    COMMAND_AND_QUERY_ITEM  ("[SENSe#]:FREQuency:CENTer:STEP", ceSenseFrequencyCenterStep_CQ)
    COMMAND_AND_QUERY_ITEM  ("[SENSe#]:FREQuency:SPAN",     ceSenseFrequencySpan_CQ)
    COMMAND_ITEM            ("[SENSe#]:FREQuency:SPAN:FULL",ceSenseFrequencySpanFull_C)
    COMMAND_AND_QUERY_ITEM  ("[SENSe#]:FREQuency:STARt",    ceSenseFrequencyStart_CQ)
    COMMAND_AND_QUERY_ITEM  ("[SENSe#]:FREQuency:STOP",     ceSenseFrequencyStop_CQ)
    //    SCPI SENSE:BANDWIDTH subsystem
    COMMAND_AND_QUERY_ITEM  ("[SENSe#]:BANDwidth[:RESolution]", ceSenseBandwidthResolution_CQ)
    COMMAND_AND_QUERY_ITEM  ("[SENSe#]:BWIDth[:RESolution]",    ceSenseBandwidthResolution_CQ)
    COMMAND_AND_QUERY_ITEM  ("[SENSe#]:BANDwidth[:RESolution]:AUTO", ceSenseBandwidthResolutionAuto_CQ)
    COMMAND_AND_QUERY_ITEM  ("[SENSe#]:BWIDth[:RESolution]:AUTO",    ceSenseBandwidthResolutionAuto_CQ)
    COMMAND_AND_QUERY_ITEM  ("[SENSe#]:BANDwidth:VIDeo", ceSenseBandwidthVideo_CQ)
    COMMAND_AND_QUERY_ITEM  ("[SENSe#]:BWIDth:VIDeo",    ceSenseBandwidthVideo_CQ)
    COMMAND_AND_QUERY_ITEM  ("[SENSe#]:BANDwidth:VIDeo:AUTO", ceSenseBandwidthVideoAuto_CQ)
    COMMAND_AND_QUERY_ITEM  ("[SENSe#]:BWIDth:VIDeo:AUTO",    ceSenseBandwidthVideoAuto_CQ)
    //    SCPI SENSE:DETECTOR subsystem
    COMMAND_AND_QUERY_ITEM  ("[SENSe#]:DETector#[:FUNCtion]", ceSenseDetectorFunction_CQ)
    COMMAND_AND_QUERY_ITEM  ("[SENSe#]:DETector#[:FUNCtion]:AUTO", ceSenseDetectorFunctionAuto_CQ)

    // SCPI INITIATE subsystem
    COMMAND_ITEM            ("INITiate#[:IMMediate]",       ceInitiateImmediate_C)
    COMMAND_AND_QUERY_ITEM  ("INITiate#:CONTinuous",        ceInitiateContinuous_CQ)

    // SCPI DISPLAY subsystem
    COMMAND_AND_QUERY_ITEM  ("DISPlay[:WINDow#]:TRACe#[:STATe]", ceDisplayWindowTraceState_CQ)
    COMMAND_AND_QUERY_ITEM  ("DISPlay[:WINDow#]:TRACe#:Y[:SCALe]", ceDisplayWindowTraceYScale_CQ)
    COMMAND_AND_QUERY_ITEM  ("DISPlay[:WINDow#]:TRACe#:Y[:SCALe]:RLEVel", ceDisplayWindowTraceYScaleRLevel_CQ)

    // SCPI TRACE subsystem
    QUERY_ITEM              ("TRACe#[:DATA]",               ceTraceData_Q)

    // SCPI UNIT subsystem
    COMMAND_AND_QUERY_ITEM  ("UNIT#:POWer",                 ceUnitPower_CQ)
    //////////////////////////////////////////////////////////////////////////
    // End of real device commands
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // Extended command set for UI clients
    //////////////////////////////////////////////////////////////////////////
    COMMAND_AND_QUERY_ITEM  ("DEVICEPROXY",                 ceDeviceProxyActivate_CQ)
    COMMAND_AND_QUERY_ITEM  ("DEVICEPROXY:ADDRESS",         ceDeviceProxySetAddress_CQ)

    //////////////////////////////////////////////////////////////////////////
    // Commands for Testing
    //////////////////////////////////////////////////////////////////////////
    COMMAND_ITEM            ("TEST:BOOL",                   TEST_Bool)
    QUERY_ITEM              ("TEST:BOOL",                   TEST_BoolQ)

END_COMMAND_LIST

#undef COMMAND_COUNTER

#endif  // CM_SCPI_COMMAND_SET_FOR_UI_CLIENTS_H

