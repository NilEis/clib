/** @file
 * @brief functions for working with sockets
 */
#if !defined(CLIB_SOCKETS_H) && defined(CLIB_INCLUDE_SOCKETS)
#define CLIB_SOCKETS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "clib_error.h"
#include <stdint.h>

/**
 * @brief typedef for a clib_socket
 */
typedef struct clib_internal_socket clib_socket_t;

/**
 * @brief The supported types for the socket connection
 */
typedef enum
{
    CLIB_SOCKET_TYPE_TCP,
    CLIB_SOCKET_TYPE_UDP
} clib_socket_type_t;

typedef enum
{
    CLIB_SOCKET_FAMILY_UNSPEC,
    CLIB_SOCKET_FAMILY_INET,
    CLIB_SOCKET_FAMILY_NETBIOS,
    CLIB_SOCKET_FAMILY_INET6,
    CLIB_SOCKET_FAMILY_IRDA,
    CLIB_SOCKET_FAMILY_BTH
} clib_socket_family_t;

/**
 * @brief initialises the socket systems and sets the appropriate clib_errno if
 * an error occurs
 * @return the clib_error_code_t that occured
 */
clib_error_code_t clib_sockets_init (void);

/**
 * @brief creates a client socket and connects to given address and port
 *
 * @param address
 * @param port
 * @param type
 * @param family
 * @return clib_socket_t*
 */
clib_socket_t *clib_sockets_client_create (const char *address,
    int port,
    clib_socket_type_t type,
    clib_socket_family_t family);

int clib_sockets_client_send (
    const clib_socket_t *socket, const char *data, size_t data_len);

int clib_sockets_client_recv (
    const clib_socket_t *socket, char *data, size_t data_len);

void clib_sockets_free (clib_socket_t *sock);

#ifdef __cplusplus
}
#endif

#endif /* CLIB_SOCKETS_H */
