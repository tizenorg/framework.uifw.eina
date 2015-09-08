/* EINA - EFL data type library
 * Copyright (C) 2011 Vincent Torri
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

#ifndef EINA_LOCK_H_
#define EINA_LOCK_H_

#include "eina_config.h"
#include "eina_types.h"
#include "eina_error.h"

/**
 * @internal
 * @defgroup Eina_Lock_Group Lock
 * @ingroup Eina_Tools_Group
 *
 * @{
 */

typedef enum
{
   EINA_LOCK_FAIL     = EINA_FALSE,
   EINA_LOCK_SUCCEED  = EINA_TRUE,
   EINA_LOCK_DEADLOCK
} Eina_Lock_Result;

#ifdef EINA_HAVE_THREADS
# ifdef _WIN32_WCE
#  include "eina_inline_lock_wince.x"
# elif defined(_WIN32)
#  include "eina_inline_lock_win32.x"
# else
#  include "eina_inline_lock_posix.x"
# endif
#else
# include "eina_inline_lock_void.x"
#endif

EAPI extern Eina_Error EINA_ERROR_NOT_MAIN_LOOP;

/**
 * @brief Create a new #Eina_Lock.
 *
 * @details This function creates a new #Eina_Lock object and stores it in the
 *          @p mutex buffer. On success, this function returns #EINA_TRUE
 *          and #EINA_FALSE otherwise. To free the resources allocated by this
 *          function, use eina_lock_free(). For performance reasons, no check
 *          is done on @p mutex.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param[in] mutex A pointer to the lock object.
 * @return #EINA_TRUE on success, #EINA_FALSE otherwise.
 */
static inline Eina_Bool eina_lock_new(Eina_Lock *mutex);

/**
 * @brief Free the ressources of the given lock object.
 *
 * @details This function frees the resources of @p mutex allocated by
 *          eina_lock_new(). For performance reasons, no check is done on
 *          @p mutex.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param[in] mutex The lock object to free.
 */
static inline void eina_lock_free(Eina_Lock *mutex);

/**
 * @brief Lock the given mutual exclusion object.
 *
 * @details This function locks @p mutex. @p mutex must have been created by
 *          eina_lock_new(). On success, this function returns #EINA_TRUE
 *          and #EINA_FALSE otherwise. For performance reasons, no check is done on
 *          @p mutex.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param[in] mutex The lock object to lock.
 * @return #EINA_TRUE on success, #EINA_FALSE otherwise.
 */
static inline Eina_Lock_Result eina_lock_take(Eina_Lock *mutex);

/**
 * @brief Try to lock the given mutual exclusion object.
 *
 * @details This function tries to lock @p mutex. @p mutex must have been created by
 *          eina_lock_new(). If @p mutex can be locked, this function returns #EINA_TRUE;
 *          if @p mutex can not be locked, or is already locked, it
 *          returns #EINA_FALSE. This function does not block and returns
 *          immediately. For performance reasons, no check is done on
 *          @p mutex.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @remarks On Windows CE, this function is actually eina_lock_take().
 *
 * @param[in] mutex The lock object to try to lock.
 * @return #EINA_TRUE on success, #EINA_FALSE otherwise.
 */
static inline Eina_Lock_Result eina_lock_take_try(Eina_Lock *mutex);

/**
 * @brief Unlock the given mutual exclusion object.
 *
 * @details This function unlocks @p mutex. @p mutex must have been created by
 *          eina_lock_new(). On success, this function returns #EINA_TRUE
 *          and #EINA_FALSE otherwise. For performance reasons, no check is
 *          done on @p mutex.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param[in] mutex The lock object to unlock.
 * @return #EINA_TRUE on success, #EINA_FALSE otherwise.
 */
static inline Eina_Lock_Result eina_lock_release(Eina_Lock *mutex);

static inline void eina_lock_debug(const Eina_Lock *mutex);
static inline Eina_Bool eina_condition_new(Eina_Condition *cond, Eina_Lock *mutex);
static inline void eina_condition_free(Eina_Condition *cond);
static inline Eina_Bool eina_condition_wait(Eina_Condition *cond);
static inline Eina_Bool eina_condition_timedwait(Eina_Condition *cond, double t);
static inline Eina_Bool eina_condition_broadcast(Eina_Condition *cond);
static inline Eina_Bool eina_condition_signal(Eina_Condition *cond);

static inline Eina_Bool eina_rwlock_new(Eina_RWLock *mutex);
static inline void eina_rwlock_free(Eina_RWLock *mutex);
static inline Eina_Lock_Result eina_rwlock_take_read(Eina_RWLock *mutex);
static inline Eina_Lock_Result eina_rwlock_take_write(Eina_RWLock *mutex);
static inline Eina_Lock_Result eina_rwlock_release(Eina_RWLock *mutex);

static inline Eina_Bool eina_tls_new(Eina_TLS *key);
static inline void eina_tls_free(Eina_TLS key);
static inline void *eina_tls_get(Eina_TLS key);
static inline Eina_Bool eina_tls_set(Eina_TLS key, const void *data);
static inline Eina_Bool eina_semaphore_new(Eina_Semaphore *sem, int count_init);
static inline Eina_Bool eina_semaphore_free(Eina_Semaphore *sem);
static inline Eina_Bool eina_semaphore_lock(Eina_Semaphore *sem);
static inline Eina_Bool eina_semaphore_release(Eina_Semaphore *sem, int count_release);

#ifdef EINA_HAVE_DEBUG_THREADS
# define EINA_MAIN_LOOP_CHECK_RETURN_VAL(val)				\
  do {									\
    if (EINA_UNLIKELY(!eina_main_loop_is()))				\
      {									\
	eina_error_set(EINA_ERROR_NOT_MAIN_LOOP);			\
	EINA_LOG_ERR("You are calling %s from outside"			\
		     "of the main loop threads in %s at line %i",	\
		     __FUNCTION__,					\
		     __FILE__,						\
		     __LINE__);						\
	return val;							\
      }									\
  } while (0)
# define EINA_MAIN_LOOP_CHECK_RETURN					\
  do {									\
    if (EINA_UNLIKELY(!eina_main_loop_is()))				\
      {									\
	eina_error_set(EINA_ERROR_NOT_MAIN_LOOP);			\
	EINA_LOG_ERR("You are calling %s from outside"			\
		     "of the main loop threads in %s at line %i",	\
		     __FUNCTION__,					\
		     __FILE__,						\
		     __LINE__);						\
	return ;							\
      }									\
  } while (0)
#else
/**
 * @def EINA_MAIN_LOOP_CHECK_RETURN_VAL
 * @brief Definition of the macro that doesn't do anything unless EINA_HAVE_DEBUG_THREADS is defined.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 * @param val The value to be returned
 */
# define EINA_MAIN_LOOP_CHECK_RETURN_VAL(val)
/**
 * @def EINA_MAIN_LOOP_CHECK_RETURN
 * @brief Definition of the macro that doesn't do anything unless EINA_HAVE_DEBUG_THREADS is defined.
 *
 * @if MOBILE @since_tizen 2.3
 * @elseif WEARABLE @since_tizen 2.3.1
 * @endif
 *
 */
# define EINA_MAIN_LOOP_CHECK_RETURN
#endif

/**
 * @}
 */

#endif
