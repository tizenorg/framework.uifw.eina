/* EINA - EFL data type library
 * Copyright (C) 2007-2008 Jorge Luis Zapata Muga
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

#ifndef EINA_LALLOC_H_
#define EINA_LALLOC_H_

#include "eina_types.h"

/**
 * @defgroup Eina_Lalloc_Group Lazy allocator
 * @ingroup Eina_Tools_Group
 *
 * @brief This group provides lazy allocator functions.
 *
 * @{
 */

/**
 * @typedef Eina_Lalloc_Alloc
 * Type definition for the callback used to allocate new items in a lazy allocator.
 */
typedef Eina_Bool (*Eina_Lalloc_Alloc)(void *user_data, int num);

/**
 * @def EINA_LALLOC_ALLOC
 *
 * @since_tizen 2.3
 *
 * @param function The function to allocate
 */
#define EINA_LALLOC_ALLOC(function) ((Eina_Lalloc_Alloc)function)

/**
 * @typedef Eina_Lalloc_Free
 *
 * @brief Type definition for the callback used to allocate new items in a lazy allocator.
 */
typedef void      (*Eina_Lalloc_Free)(void *user_data);
/**
 * @def EINA_LALLOC_FREE
 * @param function The function to free
 */
#define EINA_LALLOC_FREE(function)  ((Eina_Lalloc_Free)function)

/** 
 * @typedef Eina_Lalloc
 * Public type definition for a lazy allocator.
 * 
 */
typedef struct _Eina_Lalloc Eina_Lalloc;

/**
 * @brief Create a new lazy allocator.
 *
 * @since_tizen 2.3
 *
 * @param[in] data The data for which memory will be allocated.
 * @param[in] alloc_cb The callback to allocate memory for @p data items.
 * @param[in] free_cb The callback to free memory for @p data items. 
 * @param[in] num_init The number of @p data items to initally allocate space for.
 * @return A new lazy allocator.
 *
 */
EAPI Eina_Lalloc *eina_lalloc_new(void             *data,
                                  Eina_Lalloc_Alloc alloc_cb,
                                  Eina_Lalloc_Free  free_cb,
                                  int               num_init) EINA_ARG_NONNULL(2, 3);

/**
 * @brief Free the resources for a lazy allocator.
 *
 * @since_tizen 2.3
 *
 * @param[in] a The lazy allocator to free.
 */
EAPI void      eina_lalloc_free(Eina_Lalloc *a) EINA_ARG_NONNULL(1);

/**
 * @brief Add several elements to a lazy allocator.
 *
 * @since_tizen 2.3
 *
 * @param[in] a The lazy allocater to add items to.
 * @param[in] num The number of elements to add.
 * @return EINA_TRUE on success, else EINA_FALSE.
 */
EAPI Eina_Bool eina_lalloc_elements_add(Eina_Lalloc *a,
                                        int          num) EINA_ARG_NONNULL(1);

/**
 * @brief Allocate one more of whatever the lazy allocator is allocating.
 *
 * @since_tizen 2.3
 *
 * @param[in] a The lazy allocator to add an item to.
 *
 * @return EINA_TRUE on success, else EINA_FALSE.
 */
EAPI Eina_Bool eina_lalloc_element_add(Eina_Lalloc *a) EINA_ARG_NONNULL(1);

/**
 * @}
 */

#endif /* EINA_LALLOC_H_ */