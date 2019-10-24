#ifndef CM_COMMAND_IDS_BY_LEVEL_H
#define CM_COMMAND_IDS_BY_LEVEL_H


#ifdef DEFINE_COMMAND_SET


    #include "scpi/scpi.h"
    #include "_CmdExec.h"

    #define BEGIN_COMMAND_LIST(cmd_list_name)           int                             COMMAND_COUNTER;            \
                                                        extern "C" const scpi_command_t cmd_list_name [] = {

        #define SCPI_ITEM(pattern,handler,counter,query)    { pattern, handler, ++ counter, query},

        #define COMMAND_ITEM(pattern,handler)               SCPI_ITEM(pattern,    handler,COMMAND_COUNTER,FALSE)
        #define QUERY_ITEM(pattern,handler)                 SCPI_ITEM(pattern "?",handler,COMMAND_COUNTER,TRUE)
        #define COMMAND_AND_QUERY_ITEM(pattern,handler)     COMMAND_ITEM(pattern,handler)                           \
                                                            QUERY_ITEM  (pattern,handler)
    #define END_COMMAND_LIST                            SCPI_CMD_LIST_END };

#else

    typedef struct _scpi_command_t
    {
        const char  *szPattern;
        qint32      iCommandId;
        qint32      iReserved;
    }scpi_command_t;

    #define BEGIN_COMMAND_LIST(cmd_list_name)           int                             COMMAND_COUNTER;            \
                                                        extern "C" const scpi_command_t cmd_list_name [] = {

        #define SCPI_ITEM(pattern,handler,counter,query)    { pattern, ++ counter, query},

        #define COMMAND_ITEM(pattern,handler)               SCPI_ITEM(pattern,    handler,COMMAND_COUNTER,FALSE)
        #define QUERY_ITEM(pattern,handler)                 SCPI_ITEM(pattern "?",handler,COMMAND_COUNTER,TRUE)
        #define COMMAND_AND_QUERY_ITEM(pattern,handler)     COMMAND_ITEM(pattern,handler)                           \
                                                            QUERY_ITEM  (pattern,handler)
    #define END_COMMAND_LIST                            {NULL, 0, 0} };


#endif


#endif  // CM_COMMAND_IDS_BY_LEVEL_H



