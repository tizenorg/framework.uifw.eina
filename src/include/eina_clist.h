/*
 * Linked lists support
 *
 * Copyright (C) 2002 Alexandre Julliard
 * Copyright (C) 2011 Mike McCormack (adapted for Eina)
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
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef __EINA_CLIST_H__
#define __EINA_CLIST_H__

/**
 * @defgroup Eina_CList_Group Compact List
 * @ingroup Eina_Containers_Group
 *
 * @{
 *
 * @brief Eina_Clist is a compact (inline) list implementation.
 *
 * Elements of this list are members of the structs stored in the list.
 *
 * Advantages over @ref Eina_List and @ref Eina_Inlist :
 * - Uses less memory (two machine words per item).
 * - Allows removing items without knowing which list they're in while using O(1) time.
 * - Doesn't need to keep updating the head pointer as the list is changed.
 *
 * Disadvantages:
 * - O(N) time to calculate the list length.
 * - Requires one list entry in a struct per list (i.e. it's an inlist).
 * - Requires a head/tail pointer.
 * - Needs to know the list head when moving to the next or previous pointer.
 *
 * There's no @c NULL at the end of the list, the last item points to the head.
 *
 * List heads must be initialized with EINA_CLIST_INIT or by calling eina_clist_element_init.
 *
 * Define a list as follows:
 *
 * @code
 *   struct gadget
 *   {
 *       struct Eina_Clist  entry;   <-- doesn't have to be the first item in the struct
 *       int                a, b;
 *   };
 *
 *   static Eina_Clist global_gadgets = EINA_CLIST_INIT( global_gadgets );
 * @endcode
 *
 * or
 *
 * @code
 *   struct some_global_thing
 *   {
 *       Eina_Clist gadgets;
 *   };
 *
 *   eina_clist_init( &some_global_thing->gadgets );
 * @endcode
 *
 * Manipulate it like this:
 *
 * @code
 *   eina_clist_add_head( &global_gadgets, &new_gadget->entry );
 *   eina_clist_remove( &new_gadget->entry );
 *   eina_clist_add_after( &some_random_gadget->entry, &new_gadget->entry );
 * @endcode
 *
 * And to iterate over it:
 *
 * @code
 *   struct gadget *gadget;
 *   EINA_CLIST_FOR_EACH_ENTRY( gadget, &global_gadgets, struct gadget, entry )
 *   {
 *       ...
 *   }
 * @endcode
 *
 */

/**
 * @typedef Eina_Clist
 * @brief The structure type containing the list head and the list entry.
 * @since 1.1.0
 */
typedef struct _Eina_Clist Eina_Clist;

/**
 * @struct _Eina_Clist
 * @brief The structure type for a compact list type.
 *
 * @since 1.1.0
 *
 * @remarks This structure is used as both the list head and the list entry.
 */
struct _Eina_Clist
{
   Eina_Clist *next;
   Eina_Clist *prev;
};

/**
 * @brief Adds an element after the specified one.
 *
 * @since 1.1.0
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @remarks There is no need to initialize an element before adding it to the list.
 *
 * @param[in] elem An element in the list
 * @param[in] to_add The element to add to the list
 * @pre The list head must be initialized once before adding anything.
 * @pre The element is not in any list.
 *
 */
static inline void eina_clist_add_after(Eina_Clist *elem, Eina_Clist *to_add);

/**
 * @brief Adds an element before the specified one.
 *
 * @since 1.1.0
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @remarks There is no need to initialize an element before adding it to the list.
 *
 * @param[in] elem An element in the list
 * @param[in] to_add The element to add to the list
 * @pre The list head must be initialized once before adding anything.
 * @pre The element is not in any list.
 *
 */
static inline void eina_clist_add_before(Eina_Clist *elem, Eina_Clist *to_add);

/**
 * @brief Adds an element to the head of the list.
 *
 * @since 1.1.0
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @remarks There is no need to initialize an element before adding it to the list.
 *
 * @param[in] list The list
 * @param[in] elem An element
 * @pre The list head must be initialized once before adding anything.
 * @pre The element is not in any list.
 */
static inline void eina_clist_add_head(Eina_Clist *list, Eina_Clist *elem);

/**
 * @brief Adds an element at the tail of the list.
 *
 * @since 1.1.0
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @remarks There is no need to initialize an element before adding it to the list.
 *
 * @param[in] list The list
 * @param[in] elem An element
 * @pre The list head must be initialized once before adding anything.
 * @pre The element is not in any list.
 */
static inline void eina_clist_add_tail(Eina_Clist *list, Eina_Clist *elem);

/**
 * @brief Inits an (unlinked) element.
 *
 * @details This function is called on elements that have not been added to the list
 *          so that eina_clist_element_init() works correctly.
 *
 * @since 1.1.0
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @remarks It is not necessary to call this before adding an element to this list.
 *
 * @param[in] elem An element
 * @pre The element is not in any list.
 * @post The element is marked as not being in any list.
 */
static inline void eina_clist_element_init(Eina_Clist *elem);

/**
 * @brief Checks whether an element is in a list.
 *
 * @since 1.1.0
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param[in] elem An element
 * @return 1 if it is in a list, otherwise 0
 *
 * @pre Either eina_clist_element_init() has been called on @a elem,
 *      or it has been added to a list or removed from a list.
 */
static inline int eina_clist_element_is_linked(Eina_Clist *elem);

/**
 * @brief Removes an element from its list.
 *
 * @since 1.1.0
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param[in] elem An element
 * @pre The element is already in a list.
 * @post The element is marked as not being in any list.
 */
static inline void eina_clist_remove(Eina_Clist *elem);

/**
 * @brief Gets the next element.
 *
 * @since 1.1.0
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param[in] list The list
 * @param[in] elem An element
 * @return The element after @a elem in @a list, otherwise @c NULL if @a elem is last in @a list
 * @pre @a elem is in @a list.
 */
static inline Eina_Clist *eina_clist_next(const Eina_Clist *list, const Eina_Clist *elem);

/**
 * @brief Gets the previous element.
 *
 * @since 1.1.0
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param[in] list The list
 * @param[in] elem An element
 *
 * @return The element before @a elem, otherwise @c NULL if @a elem is first in @a list
 */
static inline Eina_Clist *eina_clist_prev(const Eina_Clist *list, const Eina_Clist *elem);

/**
 * @brief Gets the first element.
 *
 * @since 1.1.0
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param[in] list The list
 * @return The first element in @a list, otherwise @c NULL if @a list is empty
 */
static inline Eina_Clist *eina_clist_head(const Eina_Clist *list);

/**
 * @brief Gets the last element.
 *
 * @since 1.1.0
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param[in] list The list
 * @return The last element in @a list, otherwise @c NULL if @a list is empty
 */
static inline Eina_Clist *eina_clist_tail(const Eina_Clist *list);

/**
 * @brief Checks whether a list is empty.
 *
 * @since 1.1.0
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param[in] list The list
 * @return A non-zero value if @a list is empty, otherwise zero if it is not
 */
static inline int eina_clist_empty(const Eina_Clist *list);

/**
 * @brief Initializes a list.
 *
 * @since 1.1.0
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @remarks Don't call this function on a list with items
 * @remarks This function must be called. Don't try to
 *          initialize the list by zeroing out the list head.
 *
 * @param[in] list The list
 * @pre The list is uninitialized
 * @post The list contains no items
 *
 */
static inline void eina_clist_init(Eina_Clist *list);

/**
 * @brief Counts the elements of a list.
 *
 * @since 1.1.0
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param[in] list The list
 * @return The number of items in the list
 */
static inline unsigned int eina_clist_count(const Eina_Clist *list);

/**
 * @brief Moves all elements from @a src to the tail of @a dst.
 *
 * @since 1.1.0
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param[in] dst The list to be appended to
 * @param[in] src The list to append
 *
 * @post @a src is initialized, but is empty after this operation.
 */
static inline void eina_clist_move_tail(Eina_Clist *dst, Eina_Clist *src);

/**
 * @brief Moves all elements from @a src to the head of @a dst.
 *
 * @since 1.1.0
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param[in] dst The list to be prepended to
 * @param[in] src The list to prepend
 *
 * @post @a src is initialized, but is empty after this operation.
 */
static inline void eina_clist_move_head(Eina_Clist *dst, Eina_Clist *src);

/**
 * @def EINA_CLIST_FOR_EACH
 * @brief Iterates through the list.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param cursor The pointer to be used during the interaction
 * @param list The list to be interacted with
 */
#define EINA_CLIST_FOR_EACH(cursor,list) \
    for ((cursor) = (list)->next; (cursor) != (list); (cursor) = (cursor)->next)

/**
 * @def EINA_CLIST_FOR_EACH_SAFE
 * @brief Iterates through the list, with safety against removal.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param cursor The pointer to be used during the interaction
 * @param cursor2 The auxiliar pointer to be used during the interaction
 * @param list The list to be interacted with
 */
#define EINA_CLIST_FOR_EACH_SAFE(cursor, cursor2, list) \
    for ((cursor) = (list)->next, (cursor2) = (cursor)->next; \
         (cursor) != (list); \
         (cursor) = (cursor2), (cursor2) = (cursor)->next)

/**
 * @def EINA_CLIST_FOR_EACH_ENTRY
 * @brief Iterates through the list using a list entry.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param elem The element to be used
 * @param list The list to be iterated
 * @param type The type of the list
 * @param field The field of the element
 */
#define EINA_CLIST_FOR_EACH_ENTRY(elem, list, type, field) \
    for ((elem) = EINA_CLIST_ENTRY((list)->next, type, field); \
         &(elem)->field != (list); \
         (elem) = EINA_CLIST_ENTRY((elem)->field.next, type, field))

/**
 * @def EINA_CLIST_FOR_EACH_ENTRY_SAFE
 * @brief Iterates through the list using a list entry, with safety against removal.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param cursor The pointer to be used during the interaction
 * @param cursor2 The auxiliar pointer to be used during the interaction
 * @param list The list to be interacted with
 * @param type The type of the list
 * @param field The field of the element
*/
#define EINA_CLIST_FOR_EACH_ENTRY_SAFE(cursor, cursor2, list, type, field) \
    for ((cursor) = EINA_CLIST_ENTRY((list)->next, type, field), \
         (cursor2) = EINA_CLIST_ENTRY((cursor)->field.next, type, field); \
         &(cursor)->field != (list); \
         (cursor) = (cursor2), \
         (cursor2) = EINA_CLIST_ENTRY((cursor)->field.next, type, field))

/**
 * @def EINA_CLIST_FOR_EACH_REV
 * @brief Iterates through the list in the reverse order.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param cursor The pointer to be used during the interaction
 * @param list The list to be interacted with
 */
#define EINA_CLIST_FOR_EACH_REV(cursor,list) \
    for ((cursor) = (list)->prev; (cursor) != (list); (cursor) = (cursor)->prev)

/**
 * @def EINA_CLIST_FOR_EACH_SAFE_REV
 * @brief Iterates through the list in the reverse order, with safety against removal.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param cursor The pointer to be used during the interaction
 * @param cursor2 The auxiliar pointer to be used during the interaction
 * @param list The list to be interacted with
 */
#define EINA_CLIST_FOR_EACH_SAFE_REV(cursor, cursor2, list) \
    for ((cursor) = (list)->prev, (cursor2) = (cursor)->prev; \
         (cursor) != (list); \
         (cursor) = (cursor2), (cursor2) = (cursor)->prev)

/**
 * @def EINA_CLIST_FOR_EACH_ENTRY_REV
 * @brief Iterates through the list in the reverse order using a list entry.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param elem The element to be used
 * @param list The list to be iterated
 * @param type The type of the list
 * @param field The field of the element
 */
#define EINA_CLIST_FOR_EACH_ENTRY_REV(elem, list, type, field) \
    for ((elem) = EINA_CLIST_ENTRY((list)->prev, type, field); \
         &(elem)->field != (list); \
         (elem) = EINA_CLIST_ENTRY((elem)->field.prev, type, field))

/**
 * @def EINA_CLIST_FOR_EACH_ENTRY_SAFE_REV
 * @brief Iterates through the list in the reverse order using a list entry, with safety against
 *        removal.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param cursor The pointer to be used during the interaction
 * @param cursor2 The auxiliar pointer to be used during the interaction
 * @param list The list to be interacted with
 * @param type The type of the list
 * @param field The field of the element
 */
#define EINA_CLIST_FOR_EACH_ENTRY_SAFE_REV(cursor, cursor2, list, type, field) \
    for ((cursor) = EINA_CLIST_ENTRY((list)->prev, type, field), \
         (cursor2) = EINA_CLIST_ENTRY((cursor)->field.prev, type, field); \
         &(cursor)->field != (list); \
         (cursor) = (cursor2), \
         (cursor2) = EINA_CLIST_ENTRY((cursor)->field.prev, type, field))

/**
 * @def EINA_CLIST_INIT
 * @brief Provides macros for statically initialized lists.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param list The list to be used
 */
#undef EINA_CLIST_INIT
#define EINA_CLIST_INIT(list)  { &(list), &(list) }

/**
 * @def EINA_CLIST_ENTRY
 * @brief Gets a pointer to the object containing the list element.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param elem The element to be used
 * @param type The type of the element
 * @param field The field of the element
 */
#undef EINA_CLIST_ENTRY
#define EINA_CLIST_ENTRY(elem, type, field) \
    ((type *)((char *)(elem) - (unsigned long)(&((type *)0)->field)))

#include "eina_inline_clist.x"

/**
 * @}
 */

#endif /* __EINA_CLIST_H__ */
