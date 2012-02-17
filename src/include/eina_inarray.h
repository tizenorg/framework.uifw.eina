/* EINA - EFL data type library
 * Copyright (C) 2012 ProFUSION embedded systems
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library;
 * if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EINA_INARRAY_H_
#define EINA_INARRAY_H_

#include "eina_types.h"
#include "eina_iterator.h"
#include "eina_accessor.h"

/**
 * @addtogroup Eina_Data_Types_Group Data Types
 *
 * @since 1.2
 *
 * @{
 */

/**
 * @addtogroup Eina_Containers_Group Containers
 *
 * @{
 */

/**
 * @defgroup Eina_Inline_Array_Group Inline Array
 *
 * @{
 */


/**
 * @typedef Eina_Inarray
 * Inlined array type.
 *
 * @since 1.2
 */
typedef struct _Eina_Inarray Eina_Inarray;

/**
 * Inline array structure, use #Eina_Inarray typedef instead.
 *
 * Do not modify these fields directly, use eina_inarray_setup() or
 * eina_inarray_new() instead.
 *
 * @since 1.2
 */
struct _Eina_Inarray
{
   unsigned int member_size; /**< byte size of each entry in members */
   unsigned int len; /**< number of elements used in members */
   unsigned int max; /**< number of elements allocated in members */
   unsigned int step; /**< amount to grow number of members allocated */
   void *members; /**< actual array of elements */
   EINA_MAGIC
};

/**
 * @brief Create new inline array.
 *
 * @param member_size size of each member in the array.
 * @param step when resizing the array, do this using the following
 *        extra amount.
 * @return The new inline array table or @c NULL on failure.
 *
 * Create a new array where members are inlined in a sequence. Each
 * member has @a member_size bytes.
 *
 * If the @a step is 0, then a safe default is chosen.
 *
 * On failure, @c NULL is returned and #EINA_ERROR_OUT_OF_MEMORY is
 * set. If @a member_size is zero, then @c NULL is returned.
 *
 * @see eina_inarray_free()
 *
 * @since 1.2
 */
EAPI Eina_Inarray *eina_inarray_new(unsigned int member_size,
                                    unsigned int step) EINA_MALLOC EINA_WARN_UNUSED_RESULT;

/**
 * @brief Free array and its members.
 * @param array array object
 *
 * @see eina_inarray_flush()
 *
 * @since 1.2
 */
EAPI void eina_inarray_free(Eina_Inarray *array) EINA_ARG_NONNULL(1);

/**
 * @brief Initialize inline array.
 * @param array array object to initialize.
 * @param member_size size of each member in the array.
 * @param step when resizing the array, do this using the following
 *        extra amount.
 *
 * Initialize array. If the @a step is 0, then a safe default is
 * chosen.
 *
 * This is useful for arrays inlined into other structures or
 * allocated at stack.
 *
 * @see eina_inarray_flush()
 *
 * @since 1.2
 */
EAPI void eina_inarray_setup(Eina_Inarray *array,
                             unsigned int member_size,
                             unsigned int step) EINA_ARG_NONNULL(1);

/**
 * @brief Remove every member from array.
 * @param array array object
 *
 * @since 1.2
 */
EAPI void eina_inarray_flush(Eina_Inarray *array) EINA_ARG_NONNULL(1);

/**
 * @brief Copy the data as the last member of the array.
 * @param array array object
 * @param data data to be copied at the end
 * @return the index of the new member or -1 on errors.
 *
 * Copies the given pointer contents at the end of the array. The
 * pointer is not referenced, instead it's contents is copied to the
 * members array using the previously defined @c member_size.
 *
 * @see eina_inarray_insert_at().
 *
 * @since 1.2
 */
EAPI int eina_inarray_append(Eina_Inarray *array,
                             const void *data) EINA_ARG_NONNULL(1, 2);

/**
 * @brief Copy the data to array at position found by comparison function
 * @param array array object
 * @param data data to be copied
 * @param compare compare function
 * @return the index of the new member or -1 on errors.
 *
 * Copies the given pointer contents at the array position defined by
 * given @a compare function. The pointer is not referenced, instead
 * it's contents is copied to the members array using the previously
 * defined @c member_size.
 *
 * The data given to @a compare function are the pointer to member
 * memory itself, do no change it.
 *
 * @see eina_inarray_insert_sorted()
 * @see eina_inarray_insert_at()
 * @see eina_inarray_append()
 *
 * @since 1.2
 */
EAPI int eina_inarray_insert(Eina_Inarray *array,
                             const void *data,
                             Eina_Compare_Cb compare) EINA_ARG_NONNULL(1, 2, 3);

/**
 * @brief Copy the data to array at position found by comparison function
 * @param array array object
 * @param data data to be copied
 * @param compare compare function
 * @return the index of the new member or -1 on errors.
 *
 * Copies the given pointer contents at the array position defined by
 * given @a compare function. The pointer is not referenced, instead
 * it's contents is copied to the members array using the previously
 * defined @c member_size.
 *
 * The data given to @a compare function are the pointer to member
 * memory itself, do no change it.
 *
 * This variation will optimize insertion position assuming the array
 * is already sorted by doing binary search.
 *
 * @see eina_inarray_sort()
 *
 * @since 1.2
 */
EAPI int eina_inarray_insert_sorted(Eina_Inarray *array,
                                    const void *data,
                                    Eina_Compare_Cb compare) EINA_ARG_NONNULL(1, 2, 3);

/**
 * @brief Find data and remove matching member
 * @param array array object
 * @param data data to be found and removed
 * @return the index of the removed member or -1 on errors.
 *
 * Find data in the array and remove it. Data may be an existing
 * member of array (then optimized) or the contents will be matched
 * using memcmp().
 *
 * @see eina_inarray_pop()
 * @see eina_inarray_remove_at()
 *
 * @since 1.2
 */
EAPI int eina_inarray_remove(Eina_Inarray *array,
                             const void *data) EINA_ARG_NONNULL(1, 2);

/**
 * @brief Removes the last member of the array
 * @param array array object
 * @return the index of the removed member or -1 on errors.
 *
 * @since 1.2
 */
EAPI int eina_inarray_pop(Eina_Inarray *array) EINA_ARG_NONNULL(1);

/**
 * @brief Get the member at given position
 * @param array array object
 * @param position member position
 * @return pointer to current member memory.
 *
 * Gets the member given its position in the array. It is a pointer to
 * its current memory, then it can be invalidated with functions that
 * changes the array such as eina_inarray_append(),
 * eina_inarray_insert_at() or eina_inarray_remove_at() or variants.
 *
 * See also eina_inarray_lookup() and eina_inarray_lookup_sorted().
 *
 * @since 1.2
 */
EAPI void *eina_inarray_nth(const Eina_Inarray *array,
                            unsigned int position) EINA_ARG_NONNULL(1) EINA_WARN_UNUSED_RESULT;

/**
 * @brief Copy the data at given position in the array
 * @param array array object
 * @param position where to insert the member
 * @param data data to be copied at position
 * @return #EINA_TRUE on success, #EINA_FALSE on failure.
 *
 * Copies the given pointer contents at the given @a position in the
 * array. The pointer is not referenced, instead it's contents is
 * copied to the members array using the previously defined
 * @c member_size.
 *
 * All the members from @a position to the end of the array are
 * shifted to the end.
 *
 * If @a position is equal to the end of the array (equals to
 * eina_inarray_count()), then the member is appended.
 *
 * If @a position is bigger than the array length, it will fail.
 *
 * @since 1.2
 */
EAPI Eina_Bool eina_inarray_insert_at(Eina_Inarray *array,
                                      unsigned int position,
                                      const void *data) EINA_ARG_NONNULL(1, 3);

/**
 * @brief Opens a space at given position, returning its pointer.
 * @param array array object
 * @param position where to insert first member (open/allocate space)
 * @param member_count how many times member_size bytes will be allocated.
 * @return pointer to first member memory allocated or @c NULL on errors.
 *
 * This is similar to eina_inarray_insert_at(), but useful if the
 * members contents are still unknown or unallocated. It will make
 * room for the required number of items and return the pointer to the
 * first item, similar to malloc(member_count * member_size), with the
 * guarantee all memory is within members array.
 *
 * The new member memory is undefined, it's not automatically zeroed.
 *
 * All the members from @a position to the end of the array are
 * shifted to the end.
 *
 * If @a position is equal to the end of the array (equals to
 * eina_inarray_count()), then the member is appended.
 *
 * If @a position is bigger than the array length, it will fail.
 *
 * @since 1.2
 */
EAPI void *eina_inarray_alloc_at(Eina_Inarray *array,
                                 unsigned int position,
                                 unsigned int member_count) EINA_ARG_NONNULL(1) EINA_WARN_UNUSED_RESULT;

/**
 * @brief Copy the data over the given position.
 * @param array array object
 * @param position where to replace the member
 * @param data data to be copied at position
 * @return #EINA_TRUE on success, #EINA_FALSE on failure.
 *
 * Copies the given pointer contents at the given @a position in the
 * array. The pointer is not referenced, instead it's contents is
 * copied to the members array using the previously defined
 * @c member_size.
 *
 * If @a position does not exist, it will fail.
 *
 * @since 1.2
 */
EAPI Eina_Bool eina_inarray_replace_at(Eina_Inarray *array,
                                       unsigned int position,
                                       const void *data) EINA_ARG_NONNULL(1, 3);

/**
 * @brief Remove member at given position
 * @param array array object
 * @param position position to be removed
 * @return #EINA_TRUE on success, #EINA_FALSE on failure.
 *
 * The member is removed from array and any members after it are moved
 * towards the array head.
 *
 * See also eina_inarray_pop() and eina_inarray_remove().
 *
 * @since 1.2
 */
EAPI Eina_Bool eina_inarray_remove_at(Eina_Inarray *array,
                                      unsigned int position) EINA_ARG_NONNULL(1);

/**
 * @brief Reverse members in the array.
 * @param array array object
 *
 * If you do not want to change the array, just walk its elements
 * backwards, then use EINA_INARRAY_REVERSE_FOREACH() macro.
 *
 * @see EINA_INARRAY_REVERSE_FOREACH()
 *
 * @since 1.2
 */
EAPI void eina_inarray_reverse(Eina_Inarray *array) EINA_ARG_NONNULL(1);

/**
 * @brief Applies quick sort to array
 * @param array array object
 * @param compare compare function
 *
 * Applies quick sort to the @a array.
 *
 * The data given to @a compare function are the pointer to member
 * memory itself, do no change it.
 *
 * @see eina_inarray_insert_sorted()
 *
 * @since 1.2
 */
EAPI void eina_inarray_sort(Eina_Inarray *array,
                            Eina_Compare_Cb compare) EINA_ARG_NONNULL(1, 2);

/**
 * @brief Search member (linear walk)
 * @param array array object
 * @param data member to search using @a compare function.
 * @param compare compare function
 * @return the member index or -1 if not found.
 *
 * Walks array linearly looking for given data as compared by
 * @a compare function.
 *
 * The data given to @a compare function are the pointer to member
 * memory itself, do no change it.
 *
 * See also eina_inarray_lookup_sorted().
 *
 * @since 1.2
 */
EAPI int eina_inarray_search(const Eina_Inarray *array,
                             const void *data,
                             Eina_Compare_Cb compare) EINA_ARG_NONNULL(1, 2, 3);

/**
 * @brief Search member (binary search walk)
 * @param array array object
 * @param data member to search using @a compare function.
 * @param compare compare function
 * @return the member index or -1 if not found.
 *
 * Uses binary search for given data as compared by @a compare function.
 *
 * The data given to @a compare function are the pointer to member
 * memory itself, do no change it.
 *
 * @since 1.2
 */
EAPI int eina_inarray_search_sorted(const Eina_Inarray *array,
                                    const void *data,
                                    Eina_Compare_Cb compare) EINA_ARG_NONNULL(1, 2, 3);

/**
 * @brief Call function for each array member
 * @param array array object
 * @param function callback function
 * @param user_data user data given to callback @a function
 * @return #EINA_TRUE if it successfully iterate all items of the array.
 *
 * Call @a function for every given data in @a array.
 *
 * Safe way to iterate over an array. @p function should return
 * #EINA_TRUE as long as you want the function to continue iterating,
 * by returning #EINA_FALSE it will stop and return #EINA_FALSE as a
 * result.
 *
 * The data given to @a function are the pointer to member memory
 * itself.
 *
 * @see EINA_INARRAY_FOREACH()
 *
 * @since 1.2
 */
EAPI Eina_Bool eina_inarray_foreach(const Eina_Inarray *array,
                                    Eina_Each_Cb function,
                                    const void *user_data) EINA_ARG_NONNULL(1, 2);

/**
 * @brief Remove all members that matched.
 * @param array array object
 * @param match match function
 * @param user_data user data given to callback @a match.
 * @return number of removed entries or -1 on error.
 *
 * Remove all entries in the @a array where @a match function
 * returns #EINA_TRUE.
 *
 * @since 1.2
 */
EAPI int eina_inarray_foreach_remove(Eina_Inarray *array,
                                     Eina_Each_Cb match,
                                     const void *user_data) EINA_ARG_NONNULL(1, 2);

/**
 * @brief number of members in array.
 * @param array array object
 * @return number of members in array.
 *
 * @since 1.2
 */
EAPI unsigned int eina_inarray_count(const Eina_Inarray *array) EINA_ARG_NONNULL(1) EINA_WARN_UNUSED_RESULT;

/**
 * @brief Returned a new iterator associated to an array.
 * @param array array object
 * @return A new iterator.
 *
 * This function returns a newly allocated iterator associated to
 * @p array.
 *
 * If the memory can not be allocated, NULL is returned and
 * #EINA_ERROR_OUT_OF_MEMORY is set. Otherwise, a valid iterator is
 * returned.
 *
 * @warning if the array structure changes then the iterator becomes
 *          invalid! That is, if you add or remove members this
 *          iterator behavior is undefined and your program may crash!
 *
 * @since 1.2
 */
EAPI Eina_Iterator *eina_inarray_iterator_new(const Eina_Inarray *array) EINA_MALLOC EINA_WARN_UNUSED_RESULT EINA_ARG_NONNULL(1);

/**
 * @brief Returned a new reversed iterator associated to an array.
 * @param array array object
 * @return A new iterator.
 *
 * This function returns a newly allocated iterator associated to
 * @p array.
 *
 * Unlike eina_inarray_iterator_new(), this will walk the array backwards.
 *
 * If the memory can not be allocated, NULL is returned and
 * #EINA_ERROR_OUT_OF_MEMORY is set. Otherwise, a valid iterator is
 * returned.
 *
 * @warning if the array structure changes then the iterator becomes
 *          invalid! That is, if you add or remove nodes this iterator
 *          behavior is undefined and your program may crash!
 *
 * @since 1.2
 */
EAPI Eina_Iterator *eina_inarray_iterator_reversed_new(const Eina_Inarray *array) EINA_MALLOC EINA_WARN_UNUSED_RESULT EINA_ARG_NONNULL(1);

/**
 * @brief Returned a new accessor associated to an array.
 * @param array array object
 * @return A new accessor.
 *
 * This function returns a newly allocated accessor associated to
 * @p array.
 *
 * If the memory can not be allocated, NULL is returned and
 * #EINA_ERROR_OUT_OF_MEMORY is set. Otherwise, a valid accessor is
 * returned.
 *
 * @since 1.2
 */
EAPI Eina_Accessor *eina_inarray_accessor_new(const Eina_Inarray *array) EINA_MALLOC EINA_WARN_UNUSED_RESULT EINA_ARG_NONNULL(1);

/**
 * @def EINA_INARRAY_FOREACH
 * @brief walks array linearly from head to tail
 * @param array array object
 * @param itr the iterator pointer
 *
 * @a itr must be a pointer with sizeof(itr*) == array->member_size.
 *
 * @warning This is fast as it does direct pointer access, but it will
 *          not check for @c NULL pointers or invalid array object!
 *          See eina_inarray_foreach() to do that.
 *
 * @warning Do not modify array as you walk it! If that is desired,
 *          then use eina_inarray_foreach_remove()
 *
 * @since 1.2
 */
#define EINA_INARRAY_FOREACH(array, itr)                                \
  for ((itr) = (array)->members;					\
       (itr) < (((typeof(*itr)*)(array)->members) + (array)->len);	\
       (itr)++)

/**
 * @def EINA_INARRAY_REVERSE_FOREACH
 * @brief walks array linearly from tail to head
 * @param array array object
 * @param itr the iterator pointer
 *
 * @a itr must be a pointer with sizeof(itr*) == array->member_size.
 *
 * @warning This is fast as it does direct pointer access, but it will
 *          not check for @c NULL pointers or invalid array object!
 *
 * @warning Do not modify array as you walk it! If that is desired,
 *          then use eina_inarray_foreach_remove()
 *
 * @since 1.2
 */
#define EINA_INARRAY_REVERSE_FOREACH(array, itr)                        \
  for ((itr) = ((((typeof(*(itr))*)(array)->members) + (array)->len) - 1); \
       (((itr) >= (typeof(*(itr))*)(array)->members)			\
        && ((array)->members != NULL));					\
       (itr)--)

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#endif /*EINA_INARRAY_H_*/
