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
#include "clib_string.h"
#include <Ws2tcpip.h>
#include <winsock2.h>
#else
/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <arpa/inet.h>
#include <netdb.h> /* Needed for getaddrinfo() and freeaddrinfo() */
#include <sys/socket.h>
#include <unistd.h> /* Needed for close() */
#endif

static int internal_family_to_native_family (clib_socket_family_t family);
static int internal_type_to_native_type (clib_socket_type_t type);

struct clib_internal_socket
{
    clib_socket_type_t t;
#ifdef _WIN32
    SOCKET sock;
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

clib_socket_t *clib_sockets_create_client (const char *address,
    int port,
    clib_socket_type_t type,
    clib_socket_family_t family)
{
    clib_socket_t *res = calloc (1, sizeof (clib_socket_t));
    if (res == NULL)
    {
        clib_errno CLIB_ERRNO_ALLOCATION_ZEROED_ERROR;
        return NULL;
    }
    res->self = res;
#ifdef _WIN32
    {
        char port_str[6] = { 0 };
        int call_res = 0;
        struct addrinfo *result = NULL, *ptr = NULL, hints;

        if (clib_string_from_int (port_str, port, CLIB_RADIX_DEC) == NULL)
        {
            return NULL;
        }
        ZeroMemory (&hints, sizeof (hints));
        hints.ai_family = internal_family_to_native_family (family);
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = internal_type_to_native_type (type);
        call_res = getaddrinfo (address, port_str, &hints, &result);
        if (call_res != 0)
        {
            clib_extern_errno = call_res;
            clib_errno = CLIB_ERRNO_SOCKET_EXT_GETADDRINFO;
        }
        res->sock = INVALID_SOCKET;
        res->sock = socket (
            result->ai_family, result->ai_socktype, result->ai_protocol);
        if (res->sock == INVALID_SOCKET)
        {
            clib_extern_errno = WSAGetLastError ();
            clib_errno = CLIB_ERRNO_SOCKET_EXT_SOCKET;
            freeaddrinfo (result);
            return NULL;
        }
        call_res
            = connect (res->sock, result->ai_addr, (int)result->ai_addrlen);
        if (call_res == SOCKET_ERROR)
        {
            clib_extern_errno = call_res;
            clib_errno = CLIB_ERRNO_SOCKET_EXT_CONNECT;
            res->sock = INVALID_SOCKET;
            closesocket (res->sock);
            freeaddrinfo (result);
            return NULL;
        }
        freeaddrinfo (result);
        return res;
    }
#else

#endif
}

void clib_sockets_free (clib_socket_t *sock)
{
#ifdef _WIN32
    closesocket (sock->sock);
#else

#endif
    free (sock);
}

static int internal_family_to_native_family (clib_socket_family_t family)
{
    switch (family)
    {
    case CLIB_SOCKET_FAMILY_UNSPEC:
#ifdef _WIN32
        return AF_UNSPEC;
#else
        return 0;
#endif
        break;
    case CLIB_SOCKET_FAMILY_INET:
#ifdef _WIN32
        return AF_INET;
#else
        return 0;
#endif
        break;
    case CLIB_SOCKET_FAMILY_NETBIOS:
#ifdef _WIN32
        return AF_NETBIOS;
#else
        return 0;
#endif
        break;
    case CLIB_SOCKET_FAMILY_INET6:
#ifdef _WIN32
        return AF_INET6;
#else
        return 0;
#endif
        break;
    case CLIB_SOCKET_FAMILY_IRDA:
#ifdef _WIN32
        return AF_IRDA;
#else
        return 0;
#endif
        break;
    case CLIB_SOCKET_FAMILY_BTH:
#ifdef _WIN32
        return AF_BTH;
#else
        return 0;
#endif
        break;
    default:
#ifdef _WIN32
        return AF_UNSPEC;
#else
        return 0;
#endif
        break;
    }
}

static int internal_type_to_native_type (clib_socket_type_t type)
{
    switch (type)
    {
    case CLIB_SOCKET_TYPE_TCP:
#ifdef _WIN32
        return IPPROTO_TCP;
#else
        return 0;
#endif
        break;
    case CLIB_SOCKET_TYPE_UDP:
#ifdef _WIN32
        return IPPROTO_UDP;
#else
        return 0;
#endif
        break;
    default:
#ifdef _WIN32
        return IPPROTO_TCP;
#else
        return 0;
#endif
        break;
    }
}
