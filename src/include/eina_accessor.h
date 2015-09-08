/* EINA - EFL data type library
 * Copyright (C) 2008 Cedric Bail
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

#ifndef EINA_ACCESSOR_H__
#define EINA_ACCESSOR_H__

#include "eina_config.h"

#include "eina_types.h"
#include "eina_magic.h"

/**
 * @defgroup Eina_Accessor_Group Accessor Functions
 * @ingroup Eina_Content_Access_Group
 *
 * @brief This group discusses the functions to manage an accessor on containers.
 *
 * These functions allow to access elements of a container in a
 * generic way, without knowing which container is used (a bit like
 * iterators in the C++ STL). Accessors allows random access (that is, any
 * element in the container). For sequential access, see
 * @ref Eina_Iterator_Group.
 *
 * Getting an accessor to access elements of a given container is done through
 * the functions of that particular container. There is no function to create
 * a generic accessor as accessors absolutely depend on the container. This
 * means you won't find an accessor creation function here, those can be found on
 * the documentation of the container type you're using. Though created with
 * container specific functions, accessors are always deleted by the same
 * function: eina_accessor_free().
 *
 * To get the data of an element at a given
 * position, use eina_accessor_data_get(). To call a function on
 * chosen elements of a container, use eina_accessor_over().
 *
 * @{
 */

/**
 * @typedef Eina_Accessor
 * @brief The structure type containing the abstract type for accessors.
 */
typedef struct _Eina_Accessor Eina_Accessor;

/**
 * @typedef Eina_Accessor_Get_At_Callback
 * @brief The boolean type for a callback that returns the data of a container as the given index.
 */
typedef Eina_Bool (*Eina_Accessor_Get_At_Callback)(Eina_Accessor *it,
                                                   unsigned int   idx,
                                                   void         **data);

/**
 * @typedef Eina_Accessor_Get_Container_Callback
 * @brief Called to return the container.
 */
typedef void *(*Eina_Accessor_Get_Container_Callback)(Eina_Accessor *it);

/**
 * @typedef Eina_Accessor_Free_Callback
 * @brief Called to free the container.
 */
typedef void (*Eina_Accessor_Free_Callback)(Eina_Accessor *it);

/**
 * @typedef Eina_Accessor_Lock_Callback
 * @brief The boolean type for a callback that locks the container.
 */
typedef Eina_Bool (*Eina_Accessor_Lock_Callback)(Eina_Accessor *it);

/**
 * @struct _Eina_Accessor
 * @brief The structure type to provide random access to data structures.
 *
 * @internal
 * @remarks When creating an accessor remember to set the type using #EINA_MAGIC_SET
 * @endinternal
 */
struct _Eina_Accessor
{
#define EINA_ACCESSOR_VERSION 1
   int                                  version; /**< Version of the Accessor API */

   Eina_Accessor_Get_At_Callback        get_at        EINA_ARG_NONNULL(1, 3) EINA_WARN_UNUSED_RESULT; /**< Callback called when a data element is requested */
   Eina_Accessor_Get_Container_Callback get_container EINA_ARG_NONNULL(1) EINA_WARN_UNUSED_RESULT; /**< Callback called when the container is requested */
   Eina_Accessor_Free_Callback          free          EINA_ARG_NONNULL(1); /**< Callback called when the container is freed */

   Eina_Accessor_Lock_Callback          lock          EINA_WARN_UNUSED_RESULT; /**< Callback called when the container is locked */
   Eina_Accessor_Lock_Callback          unlock        EINA_WARN_UNUSED_RESULT; /**< Callback called when the container is unlocked */

#define EINA_MAGIC_ACCESSOR 0x98761232
   EINA_MAGIC
};

/**
 * @def FUNC_ACCESSOR_GET_AT(Function)
 * @brief Definition of a helper macro to cast @a Function to a Eina_Accessor_Get_At_Callback.
 */
#define FUNC_ACCESSOR_GET_AT(Function)        ((Eina_Accessor_Get_At_Callback)Function)

/**
 * @def FUNC_ACCESSOR_GET_CONTAINER(Function)
 * @brief Definition of a helper macro to cast @a Function to a Eina_Accessor_Get_Container_Callback.
 */
#define FUNC_ACCESSOR_GET_CONTAINER(Function) ((Eina_Accessor_Get_Container_Callback)Function)

/**
 * @def FUNC_ACCESSOR_FREE(Function)
 * @brief Definition of a helper macro to cast @a Function to a Eina_Accessor_Free_Callback.
 */
#define FUNC_ACCESSOR_FREE(Function)          ((Eina_Accessor_Free_Callback)Function)

/**
 * @def FUNC_ACCESSOR_LOCK(Function)
 * @brief Definition of a helper macro to cast @a Function to a Eina_Iterator_Lock_Callback.
 */
#define FUNC_ACCESSOR_LOCK(Function)          ((Eina_Accessor_Lock_Callback)Function)


/**
 * @brief Frees an accessor.
 *
 * @details This function frees @a accessor if it is not @c NULL.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param[in] accessor The accessor to free
 *
 */
EAPI void      eina_accessor_free(Eina_Accessor *accessor);

/**
 * @brief Gets the data of an accessor at the given position.
 *
 * @details This function retrieves the data of the element pointed by
 *          @a accessor at the position @a position, and stores it in
 *          @a data. If @a accessor is @c NULL or if an error occurs, @c EINA_FALSE
 *          is returned, otherwise @c EINA_TRUE is returned.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param[in] accessor The accessor
 * @param[in] position The position of the element
 * @param[in] data The pointer that stores the data to retrieve
 * @return @c EINA_TRUE on success, otherwise @c EINA_FALSE
 *
 */
EAPI Eina_Bool eina_accessor_data_get(Eina_Accessor *accessor,
                                      unsigned int   position,
                                      void         **data) EINA_ARG_NONNULL(1);

/**
 * @brief Gets the container of an accessor.
 *
 * @details This function returns the container that created @a accessor. If
 *          @a accessor is @c NULL, this function returns @c NULL.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param[in] accessor The accessor
 * @return The container that created the accessor
 *
 */
EAPI void *eina_accessor_container_get(Eina_Accessor *accessor) EINA_ARG_NONNULL(1) EINA_PURE;

/**
 * @brief Iterates over the container and executes a callback on the chosen elements.
 *
 * @details This function iterates over the elements pointed by @a accessor,
 *          starting from the element at position @a start and ending at the
 *          element at position @a end. For each element, the callback
 *          @a cb is called with the data @a fdata. If @a accessor is @c NULL
 *          or if @a start is greater than or equal to @a end, the function returns
 *          immediately.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param[in] accessor The accessor
 * @param[in] cb The callback called on the chosen elements
 * @param[in] start The position of the first element
 * @param[in] end The position of the last element
 * @param[in] fdata The data passed to the callback
 *
 */
EAPI void  eina_accessor_over(Eina_Accessor *accessor,
                              Eina_Each_Cb   cb,
                              unsigned int   start,
                              unsigned int   end,
                              const void    *fdata) EINA_ARG_NONNULL(2);

/**
 * @brief Locks the container of the accessor.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @remarks If the container of the @a accessor permits it, it is locked. When a
 *          container is locked by calling eina_accessor_over() on it, it returns
 *          immediately. If @a accessor is @c NULL or if a problem occurs, @c EINA_FALSE
 *          is returned, otherwise @c EINA_TRUE is returned. If the container isn't
 *          lockable, it returns @c EINA_TRUE.
 *
 * @remarks None of the existing eina data structures are lockable.
 *
 * @param[in] accessor The accessor
 * @return @c EINA_TRUE on success, otherwise @c EINA_FALSE
 *
 */
EAPI Eina_Bool eina_accessor_lock(Eina_Accessor *accessor) EINA_ARG_NONNULL(1);

/**
 * @brief Unlocks the container of the accessor.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @remarks If the container of the @a accessor permits it and is previously
 *          locked, it is unlocked. If @a accessor is @c NULL or if a
 *          problem occurs, @c EINA_FALSE is returned, otherwise @c EINA_TRUE
 *          is returned. If the container is not lockable, it
 *          returns @c EINA_TRUE.
 *
 * @remarks None of the existing eina data structures are lockable.
 *
 * @param[in] accessor The accessor
 * @return @c EINA_TRUE on success, otherwise @c EINA_FALSE
 *
 */
EAPI Eina_Bool eina_accessor_unlock(Eina_Accessor *accessor) EINA_ARG_NONNULL(1);

/**
 * @def EINA_ACCESSOR_FOREACH
 * @brief Definition of the macro to iterate over all the elements easily.
 *
 * @details This macro allows a convenient way to loop over all elements in an
 *          accessor, very similar to EINA_LIST_FOREACH().
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @remarks This macro can be used for freeing the data of a list, like in the
 *          following example. It has the same goal as the one documented in
 *          EINA_LIST_FOREACH(), but using accessors:
 *
 * @code
 * Eina_List     *list;
 * Eina_Accessor *accessor;
 * unsigned int   i;
 * char          *data;
 *
 * // list is already filled,
 * // its elements are just duplicated strings
 *
 * accessor = eina_list_accessor_new(list);
 * EINA_ACCESSOR_FOREACH(accessor, i, data)
 *   free(data);
 * eina_accessor_free(accessor);
 * eina_list_free(list);
 * @endcode
 *
 * @remarks If the data type provides both iterators and accessors, prefer
 *          to use iterators to iterate over, as they're likely to be more
 *          optimized for such a task.
 *
 * @remarks This example is not an optimal algorithm to release a list as
 *          it walks through the list twice, but it serves as an example. For an
 *          optimized version use EINA_LIST_FREE().
 *
 * @remarks Unless explicitly stated in the function's returning accessors,
 *          do not modify the accessed object while you walk through it. In this
 *          example using lists, do not remove list nodes or the program might
 *          crash. This is not a limitation of the accessors themselves,
 *          but a limitation in the accessors implementations to keep them as simple
 *          and fast as possible.
 *
 * @param accessor The accessor to use
 * @param counter A counter used by eina_accessor_data_get() when
 *                iterating over the container.
 * @param data A pointer to store the data \n
 *             It must be a pointer to support getting
 *             its address since eina_accessor_data_get() requires a pointer.
 *
 */
#define EINA_ACCESSOR_FOREACH(accessor, counter, data)                  \
  for ((counter) = 0;                                                   \
       eina_accessor_data_get((accessor), (counter), (void **)(void *)&(data)); \
       (counter)++)

/**
 * @}
 */

#endif
