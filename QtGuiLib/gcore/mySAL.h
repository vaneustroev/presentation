#ifndef SOFTWARE_ABSTRACTION_LAYER_H
#define SOFTWARE_ABSTRACTION_LAYER_H

#ifdef _WIN32

#define rpcInit             rpc_nt_init
#define getdtablesize()     0
#define getpid              _getpid

#define S_addr              S_un.S_addr

#define PORT(p)             p

typedef int                 socklen_t;

#else   //if defined linux

#define _getch              getchar
#define putch               putchar
#define _stricmp            strcasecmp
#define closesocket         close
#define ioctlsocket         ioctl

#define __stdcall           __attribute__((stdcall))
#define _countof(_Array)    (sizeof(_Array) / sizeof(_Array[0]))

#define S_addr              s_addr

#define PORT(p)             htons(p)
#define SOCKET              int
#define INVALID_SOCKET      (SOCKET)(~0)
#define SOCKET_ERROR                (-1)
#define WSAGetLastError()   errno
#define WSAerrno            errno
#define WSAEWOULDBLOCK      EINPROGRESS

#define rpcInit()           0


#endif // WINDOWS




#endif  // SOFTWARE_ABSTRACTION_LAYER_H
