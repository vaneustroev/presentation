#ifndef MY_ERRORS_H
#define MY_ERRORS_H

//#include "common.h"

#define ERROR_NONE                          0x00
                                            
#define ERROR_NOT_INITIALIZED               0x01
#define ERROR_WRONG_PARAMETER               0x03
#define ERROR_DATA_TOO_BIG                  0x06
#define ERROR_WRONG_DATA                    0x07
#define ERROR_CALL_NOT_REALIZED             0x09
#define ERROR_WAITING_TIMEOUT               0x0D
#define ERROR_CANT_EXECUTE_COMMAND          0x12
#define ERROR_WRONG_ADDRESS                 0x1D
#define ERROR_CREATE_TCP_SERVER             0x40
#define ERROR_CREATE_TCP_CLIENT             0x41
#define ERROR_CREATE_UDP_SERVER             0x42
#define ERROR_CREATE_TASK                   0x47
#define ERROR_TERMINATE_TASK                0x48
#define ERROR_NET_SELECT_ERROR              0x61
#define ERROR_CONNECTION_NOT_ESTABLISHED    0x64
#define ERROR_CANT_CREATE_SOCKET            0x66
#define ERROR_CANT_BIND_SOCKET              0x67
#define ERROR_IOCTL                         0x68
#define ERROR_COMMON                        0xFF


#endif // MY_ERRORS_H
