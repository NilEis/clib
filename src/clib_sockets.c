#include "clib_sockets.h"
#include <stdlib.h>

/**
 * No modifications were made
 * @see https://stackoverflow.com/a/28031039 
 */
#ifdef _WIN32
/* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501 /* Windows XP. */
#endif
#include <winsock2.h>
#include <Ws2tcpip.h>
#else
/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */
#endif

struct _clib_socket
{
#ifdef _WIN32
#else
#endif
    clib_socket_t *self;
};

clib_error_code_t clib_sockets_init(void)
{
#ifdef _WIN32
    WSADATA wsaData;
    switch (WSAStartup(MAKEWORD(2, 2), &wsaData))
    {
    case WSASYSNOTREADY:
        clib_errno = CLIB_ERRNO_SOCKET_WSASYSNOTREADY;
        return CLIB_ERRNO_SOCKET_WSASYSNOTREADY;
    case WSAVERNOTSUPPORTED:
        clib_errno = CLIB_ERRNO_SOCKET_WSAVERNOTSUPPORTED;
        return CLIB_ERRNO_SOCKET_WSAVERNOTSUPPORTED;
    case WSAEINPROGRESS:
        clib_errno = CLIB_ERRNO_SOCKET_WSAEINPROGRESS;
        return CLIB_ERRNO_SOCKET_WSAEINPROGRESS;
    case WSAEPROCLIM:
        clib_errno = CLIB_ERRNO_SOCKET_WSAEPROCLIM;
        return CLIB_ERRNO_SOCKET_WSAEPROCLIM;
    case WSAEFAULT:
        clib_errno = CLIB_ERRNO_SOCKET_WSAEFAULT;
        return CLIB_ERRNO_SOCKET_WSAEFAULT;
        break;
    default:
        return CLIB_ERRNO_NO_ERROR;
    }
#else
    return CLIB_ERRNO_NO_ERROR;
#endif
}
