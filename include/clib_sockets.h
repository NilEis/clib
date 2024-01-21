/** @file
 * @brief functions for working with sockets
 */
#ifndef CLIB_SOCKETS_H
#define CLIB_SOCKETS_H

#include "clib_c90_support.h"
#include "clib_error.h"
#include <stdbool.h>

/**
 * @brief typedef for a clib_socket
 */
typedef struct _clib_socket clib_socket_t;

/**
 * @brief initialises the socket systems and sets the appropriate clib_errno if an error occurs
 * @return the clib_error_code_t that occured
 */
clib_error_code_t clib_sockets_init(void);

#endif /* CLIB_SOCKETS_H */
