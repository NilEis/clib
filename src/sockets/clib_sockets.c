#include "clib_sockets.h"

const char *clib_sockets_module_name (void) { return "clib_sockets"; }

/**
 * No modifications were made
 * @see https://stackoverflow.com/a/28031039
 */
#ifdef _WIN32
/* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501 /* Windows XP. */
#endif
#include <Ws2tcpip.h>
#include <winsock2.h>
#else
/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <arpa/inet.h>
#include <netdb.h> /* Needed for getaddrinfo() and freeaddrinfo() */
#include <sys/socket.h>
#include <unistd.h> /* Needed for close() */
#endif

struct clib_internal_socket
{
#ifdef _WIN32
#else
#endif
    clib_socket_t *self;
};

clib_error_code_t clib_sockets_init (void)
{
#ifdef _WIN32
    WSADATA wsaData;
    switch (WSAStartup (MAKEWORD (2, 2), &wsaData))
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
