/* EINA - EFL data type library
 * Copyright (C) 2007-2008 Jorge Luis Zapata Muga, Cedric Bail
 *
 * This library is a free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library;
 * if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EINA_ERROR_H_
#define EINA_ERROR_H_

#include <stdarg.h>

#include "eina_types.h"

/**
 * @defgroup Eina_Error_Group Error
 * @ingroup Eina_Tools_Group
 *
 * @brief This group discusses the functions that provide error management for projects.
 *
 * The Eina error module provides a way to manage errors in a simple but
 * powerful way in libraries and modules. It is also used in Eina itself.
 * Similar to libC's @c errno and strerror() facilities, this is extensible and
 * recommended for other libraries and applications as well.
 *
 * @{
 */

/**
 * @typedef Eina_Error
 * @brief The integer type containing the error type.
 */
typedef int Eina_Error;

/**
 * @var EINA_ERROR_OUT_OF_MEMORY
 * @brief The error identifier corresponding to lack of memory.
 */

EAPI extern Eina_Error EINA_ERROR_OUT_OF_MEMORY;

/**
 * @internal
 * @brief Registers a new error type.
 *
 * @details This function stores the error message described by
 *          @a msg in a list. The returned value is a unique identifier greater than or equal
 *          to @c 1. The description can be retrieved later by passing
 *          the returned value to eina_error_msg_get().
 *
 * @since_tizen 2.3
 *
 * @param[in] msg The description of the error \n
 *            It is duplicated using eina_stringshare_add().
 * @return The unique number identifier for this error
 *
 * @see eina_error_msg_static_register()
 */
EAPI Eina_Error  eina_error_msg_register(const char *msg) EINA_ARG_NONNULL(1) EINA_WARN_UNUSED_RESULT;

/**
 * @internal
 * @brief Registers a new error type, statically allocated message.
 *
 * @details This function stores the error message described by
 *          @a msg in a list. The returned value is a unique identifier greater than or equal
 *          to @c 1. The description can be retrieved later by passing
 *          the returned value to eina_error_msg_get().
 *
 * @since_tizen 2.3
 *
 * @param[in] msg The description of the error \n
 *            This string is not duplicated and thus
 *            the given pointer should live during the usage of eina_error.
 * @return The unique number identifier for this error
 *
 * @see eina_error_msg_register()
 */
EAPI Eina_Error  eina_error_msg_static_register(const char *msg) EINA_ARG_NONNULL(1) EINA_WARN_UNUSED_RESULT;

/**
 * @internal
 * @brief Changes the message of an already registered message.
 *
 * @details This function modifies the message associated with @a error and changes
 *          it to @a msg. If the error is previously registered by @ref eina_error_msg_static_register
 *          then the string is not duplicated, otherwise the previous message
 *          is unrefed and @a msg is copied.
 *
 * @since_tizen 2.3
 *
 * @param[in] error The Eina_Error to change the message of
 * @param[in] msg The description of the error \n
 *            This string is duplicated only if the error is registered with @ref eina_error_msg_register,
 *            otherwise it must remain intact for the duration.
 * @return @c EINA_TRUE if successful, otherwise @c EINA_FALSE on error
 *
 * @see eina_error_msg_register()
 */
EAPI Eina_Bool   eina_error_msg_modify(Eina_Error  error,
                                       const char *msg) EINA_ARG_NONNULL(2);

/**
 * @internal
 * @brief Returns the last set error.
 *
 * @details This function returns the last error set by eina_error_set(). The
 *          description of the message is returned by eina_error_msg_get().
 *
 * @since_tizen 2.3
 *
 * @return The last error
 *
 */
EAPI Eina_Error  eina_error_get(void);

/**
 * @internal
 * @brief Sets the last error.
 *
 * @details This function sets the last error identifier. The last error can be
 *          retrieved by eina_error_get().
 *
 * @since_tizen 2.3
 *
 * @remarks This is also used to clear previous errors, in which case @a err should
 *          be @c 0.
 *
 * @param[in] err The error identifier
 *
 */
EAPI void        eina_error_set(Eina_Error err);

/**
 * @internal
 * @brief Returns the description of the given error number.
 *
 * @details This function returns the description of an error that has been
 *          registered by eina_error_msg_register(). If an incorrect error is
 *          given, then @c NULL is returned.
 *
 * @since_tizen 2.3
 *
 * @param[in] error The error number
 * @return The description of the error
 *
 */
EAPI const char *eina_error_msg_get(Eina_Error error) EINA_PURE;

/**
 * @internal
 * @brief Finds the #Eina_Error corresponding to a message string.
 *
 * @details This function attempts to match @a msg with its corresponding #Eina_Error value.
 *          If no such value is found, @c 0 is returned.
 *
 * @since_tizen 2.3
 *
 * @param[in] msg The error message string to match (NOT @c NULL)
 * @return The #Eina_Error matching @a msg, otherwise @c 0 on failure
 *
 */
EAPI Eina_Error  eina_error_find(const char *msg) EINA_ARG_NONNULL(1) EINA_PURE;

/**
 * @}
 */

#endif /* EINA_ERROR_H_ */
