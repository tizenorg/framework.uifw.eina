/* EINA - EFL data type library
 * Copyright (C) 2007-2008 Jorge Luis Zapata Muga
 *                    2011 Cedric Bail
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

#ifndef EINA_FILE_H_
#define EINA_FILE_H_

#include <limits.h>
#include <time.h>
#include <sys/stat.h>

#include "eina_types.h"
#include "eina_array.h"
#include "eina_iterator.h"


/**
 * @internal
 * @defgroup Eina_File_Group File
 * @ingroup Eina_Tools_Group
 *
 * @brief This group discusses the functions to handle files and directories.
 *
 * @details This function makes it easier to do a number of file and directory operations
 *          such as getting the list of files in a directory, spliting paths, and finding
 *          out file size and type.
 *
 * @remarks All functions in this group are @b blocking, which means they may
 *          take a long time to return, use them carefully.
 *
 * @{
 */

/**
 * @typedef Eina_File_Direct_Info
 * @brief The structure type for a typedef to #_Eina_File_Direct_Info.
 */
typedef struct _Eina_File_Direct_Info Eina_File_Direct_Info;

/**
 * @typedef Eina_Stat
 * @brief The structure type for a typedef to #_Eina_Stat.
 * @since 1.2
 */
typedef struct _Eina_Stat Eina_Stat;

/**
 * @typedef Eina_File_Line
 * @brief The structure type for a typedef to #_Eina_File_Line.
 */
typedef struct _Eina_File_Line Eina_File_Line;

/**
 * @typedef Eina_File_Dir_List_Cb
 * @brief Called when iterating over the files of a directory.
 * 
 * @param The file name EXCLUDING the path
 * @param path The path passed to eina_file_dir_list()
 * @param data The data passed to eina_file_dir_list()
 */
typedef void (*Eina_File_Dir_List_Cb)(const char *name, const char *path, void *data);

/**
 * @typedef Eina_File_Type
 * @brief Enumeration of a file type in Eina_File_Direct_Info.
 */
typedef enum {
  EINA_FILE_UNKNOWN, /**< Unknown file type */
  EINA_FILE_FIFO,    /**< Named pipe (FIFO) type (unused on Windows) */
  EINA_FILE_CHR,     /**< Character device type (unused on Windows) */
  EINA_FILE_DIR,     /**< Directory type */
  EINA_FILE_BLK,     /**< Block device type (unused on Windows) */
  EINA_FILE_REG,     /**< Regular file type */
  EINA_FILE_LNK,     /**< Symbolic link type */
  EINA_FILE_SOCK,    /**< UNIX domain socket type (unused on Windows) */
  EINA_FILE_WHT      /**< Whiteout file type (unused on Windows) */
} Eina_File_Type;

typedef struct _Eina_File Eina_File;
/**
 * @typedef Eina_File_Populate
 * @brief Enumeration of a file access type used in Eina_File_Direct_info.
 */
typedef enum {
  EINA_FILE_RANDOM,     /**< Advise random memory access to the mapped memory */
  EINA_FILE_SEQUENTIAL, /**< Advise sequential memory access to the mapped memory */
  EINA_FILE_WILLNEED,   /**< Advise need for all the mapped memory */
  EINA_FILE_POPULATE    /**< Request for all the mapped memory */
} Eina_File_Populate;

/* Why do this? Well PATH_MAX may vary from when eina itself is compiled
 * to when the app using eina is compiled. Exposing the path buffer below
 * can't safely and portably vary based on how/when you compile. It should
 * always be the same for both eina inside AND for apps outside that use eina,
 * so define this to 8192 - most PATH_MAX values are like 4096 or 1024 (with
 * Windows I think being 260), so 8192 should cover almost all the cases. There
 * is a possibility that PATH_MAX could be more than 8192. If anyone spots
 * a path_max that is bigger - let us know, but, for now we assume that
 * it never happens */
/**
 * @def EINA_PATH_MAX
 * @brief The constant defined as the highest value for PATH_MAX.
 */
#define EINA_PATH_MAX 8192
/**
 * @struct _Eina_File_Direct_Info
 * @brief The structure type to store information of a path.
 */
struct _Eina_File_Direct_Info
{
   size_t               path_length; /**< Size of the whole path */
   size_t               name_length; /**< Size of the filename/basename component */
   size_t               name_start; /**< Start position of the filename/basename component */
   Eina_File_Type       type; /**< File type */
   char                 path[EINA_PATH_MAX]; /**< The path */
};

/**
 * @struct _Eina_Stat
 * @brief The structure type to store information of a path.
 * @since 1.2
 */
struct _Eina_Stat
{
   unsigned long int    dev;
   unsigned long int    ino;
   unsigned int         mode;
   unsigned int         nlink;
   unsigned int         uid;
   unsigned int         gid;
   unsigned long int    rdev;
   unsigned long int    size;
   unsigned long int    blksize;
   unsigned long int    blocks;
   unsigned long int    atime;
   unsigned long int    atimensec;
   unsigned long int    mtime;
   unsigned long int    mtimensec;
   unsigned long int    ctime;
   unsigned long int    ctimensec;
};

/**
 * @struct _Eina_File_Line
 * @brief The structure type to store information of a line.
 * @since 1.3
 */
struct _Eina_File_Line
{
  const char *start;
  const char *end;
  unsigned int index;
  unsigned long long length;
};

/**
 * @def EINA_FILE_DIR_LIST_CB
 * @brief Definition of the macro to cast to an #Eina_File_Dir_List_Cb.
 *
 * @details This macro casts @a function to Eina_File_Dir_List_Cb.
 *
 * @param function The function to cast
 *
 */
#define EINA_FILE_DIR_LIST_CB(function) ((Eina_File_Dir_List_Cb)function)


/**
 * @brief Lists all the files on the directory by calling the function for every file found.
 *
 * @details This function calls @a cb for each file that is in @a dir. To have @a cb
 *          called on the files that are in subdirectories of @a dir, @a recursive should
 *          be @c EINA_TRUE. In other words, if @a recursive is @c EINA_FALSE, only direct children
 *          of @a dir are operated on, if @a recursive is @c EINA_TRUE the entire tree
 *          of files that is below @a dir is operated on.
 *
 *          If @a cb or @a dir is @c NULL or if @a dir is a string of size 0,
 *          or if @a dir cannot be opened, this function returns @c EINA_FALSE
 *          immediately. Otherwise, it returns @c EINA_TRUE.
 *
 * @since_tizen 2.3
 *
 * @param[in] dir The directory name
 * @param[in] recursive Iterate recursively in the directory
 * @param[in] cb The callback to be called
 * @param[in] data The data to pass to the callback
 * @return @c EINA_TRUE on success, otherwise @c EINA_FALSE
 *
 */
EAPI Eina_Bool eina_file_dir_list(const char           *dir,
                                  Eina_Bool             recursive,
                                  Eina_File_Dir_List_Cb cb,
                                  void                 *data) EINA_ARG_NONNULL(1, 3);

/**
 * @brief Splits a path according to the delimiter of the filesystem.
 *
 * @details This function splits @a path according to the delimiter of the used
 *          filesystem. If  @a path is @c NULL or if the array cannot be
 *          created, @c NULL is returned, otherwise an array with each part of @a path
 *          is returned.
 *
 * @since_tizen 2.3
 *
 * @param[in] path The path to split
 * @return An array of the parts of the path to split
 *
 */
EAPI Eina_Array    *eina_file_split(char *path) EINA_WARN_UNUSED_RESULT EINA_ARG_NONNULL(1) EINA_MALLOC;

/**
 * @brief Gets an iterator to list the content of a directory.
 *
 * @details This returns an iterator for shared strings, the name of each file in @a dir is
 *          only fetched when advancing the iterator, which means there is very little
 *          cost associated with creating the list and stopping halfway through it.
 *
 * @since_tizen 2.3
 *
 * @remarks The iterator hands the user a stringshared value with the full
 *          path. The user must free the string using eina_stringshare_del() on it.
 *
 * @remarks The container for the iterator is of type DIR*.
 * @remarks The iterator walks over '.' and '..' without returning them.
 *
 * @param [in] dir The name of the directory to list
 * @return An Eina_Iterator that walks over the files and directories
 *         in @a dir. On failure, it returns @c NULL.
 *
 * @see eina_file_direct_ls()
 */
EAPI Eina_Iterator *eina_file_ls(const char *dir) EINA_WARN_UNUSED_RESULT EINA_ARG_NONNULL(1) EINA_MALLOC;

/**
 * @brief Gets an iterator to list the content of a directory, with direct
 *        information.
 *
 * @details This returns an iterator for Eina_File_Direct_Info, the name of each file in @a
 *          dir is only fetched when advancing the iterator, which means there is
 *          cost associated with creating the list and stopping halfway through it.
 *
 * @since_tizen 2.3
 *
 * @remarks The container for the iterator is of type DIR*.
 * @remarks The iterator walks over '.' and '..' without returning them.
 * @remarks The difference between this function and eina_file_direct_ls() is that
 *          it guarantees the file type information to be correct by incurring a
 *          possible performance penalty.
 *
 * @remarks The Eina_File_Direct_Info returned by the iterator <b>must not</b>
 *          be modified in any way.
 * @remarks When the iterator is advanced or deleted the Eina_File_Direct_Info
 *          returned is no longer valid.
 *
 * @param [in] dir The name of the directory to list
 *
 * @return An Eina_Iterator that walks over the files and
 *         directories in @a dir. On failure, it returns @c NULL.
 *
 * @see eina_file_direct_ls()
 */
EAPI Eina_Iterator *eina_file_stat_ls(const char *dir) EINA_WARN_UNUSED_RESULT EINA_ARG_NONNULL(1) EINA_MALLOC;

/**
 * @brief Uses information provided by Eina_Iterator of eina_file_stat_ls or eina_file_direct_ls
 *        to call stat in the most efficient way on your system.
 *
 * @details This function calls fstatat or stat depending on what your system supports. This makes it efficient and simple
 *          to use on your side without complex detection already done inside Eina on what the system can do.
 *
 * @since 1.2
 *
 * @since_tizen 2.3
 *
 * @param[in] container The container returned by Eina_Iterator using eina_iterator_container_get()
 * @param[in] info The content of the current Eina_File_Direct_Info provided by Eina_Iterator
 * @param[in] buf The location put the result of the stat
 * @return @c 0 is returnedon success, otherwise @c -1 is returned on error and errno is set appropriately
 *
 * @see eina_file_direct_ls()
 * @see eina_file_stat_ls()
 */
EAPI int eina_file_statat(void *container, Eina_File_Direct_Info *info, Eina_Stat *buf) EINA_WARN_UNUSED_RESULT EINA_ARG_NONNULL(1, 2, 3);

/**
 * @brief Gets an iterator to list the content of a directory, with direct
 *        information.
 *
 * @details This returns an iterator for Eina_File_Direct_Info, the name of each file in
 *          @a dir is only fetched when advancing the iterator, which means there is
 *          cost associated with creating the list and stopping halfway through it.
 *
 * @since_tizen 2.3
 *
 * @remarks The container for the iterator is of type DIR*.
 * @remarks The iterator walks over '.' and '..' without returning them.
 * @remarks The difference between this function and eina_file_stat_ls() is that
 *          it may not get the file type information however it is likely to be
 *          faster.
 *
 * @remarks If readdir_r doesn't contain file type information, file type is
 *          DT_UNKNOW.
 * @remarks The Eina_File_Direct_Info returned by the iterator <b>must not</b>
 *          be modified in any way.
 * @remarks When the iterator is advanced or deleted the Eina_File_Direct_Info
 *          returned is no longer valid.
 *
 * @param [in] dir The name of the directory to list
 *
 * @return An Eina_Iterator that walks over the files and
 *         directories in @a dir. On failure, it returns @c NULL.
 *
 * @see eina_file_ls()
 */
EAPI Eina_Iterator *eina_file_direct_ls(const char *dir) EINA_WARN_UNUSED_RESULT EINA_ARG_NONNULL(1) EINA_MALLOC;

/**
 * @brief Sanitizes the file path.
 *
 * @details This function takes care of adding the current working directory if its a
 *          relative path and also removes all '..' and '//' references in the original
 *          path.
 *
 * @since 1.1
 *
 * @since_tizen 2.3
 *
 * @param[in] path The path to sanitize
 *
 * @return An allocated string with the sanitized path
 *
 */
EAPI char *eina_file_path_sanitize(const char *path);

/**
 * @brief Gets a read-only handler to a file.
 *
 * @details This opens a file in the read-only mode. @a name should be an absolute path. An
 *          Eina_File handle can be shared among multiple instances if @a shared
 *          is @c EINA_TRUE.
 *
 * @since 1.1
 *
 * @since_tizen 2.3
 *
 * @param[in] name The filename to open
 * @param[in] shared  If @c EINA_TRUE the handle can be shared, 
 *                otherwise @c EINA_FALSE
 * @return An Eina_File handle to the file
 *
 */
EAPI Eina_File *eina_file_open(const char *name, Eina_Bool shared) EINA_WARN_UNUSED_RESULT EINA_ARG_NONNULL(1) EINA_MALLOC;

/**
 * @brief Unrefs the file handler.
 *
 * @details This decrements the file's reference count and if it reaches zero it closes the file.
 *
 * @since 1.1
 *
 * @since_tizen 2.3
 *
 * @param[in] file The file handler to unref
 *
 */
EAPI void eina_file_close(Eina_File *file);

/**
 * @brief Gets the file size at open time.
 *
 * @since 1.1
 *
 * @since_tizen 2.3
 *
 * @param[in] file The file handler to request the size from
 * @return The length of the file
 *
 */
EAPI size_t eina_file_size_get(Eina_File *file);

/**
 * @brief Gets the last modification time of an open file.
 *
 * @since 1.1
 *
 * @since_tizen 2.3
 *
 * @param[in] file The file handler to request the modification time from
 * @return The last modification time
 *
 */
EAPI time_t eina_file_mtime_get(Eina_File *file);

/**
 * @brief Gets the filename of an open file.
 *
 * @since 1.1
 *
 * @since_tizen 2.3
 *
 * @param[in] file The file handler to request the name from
 * @return The stringshared filename of the file
 *
 */
EAPI const char *eina_file_filename_get(Eina_File *file);

/**
 * @brief Gets the extended attribute of an open file.
 *
 * @since 1.2
 *
 * @since_tizen 2.3
 *
 * @remarks The iterator lists all the extended attribute names without allocating
 *          them, so you need to copy them yourself if needed.
 *
 * @param[in] file The file handler to request the extended attribute from
 * @return An iterator
 *
 */
EAPI Eina_Iterator *eina_file_xattr_get(Eina_File *file);

/**
 * @brief Gets the extended attribute of an open file.
 *
 * @since 1.2
 *
 * @remarks The iterator lists all the extended attribute names without allocating
 *          them, so you need to copy them yourself if needed. It returns the
 *          Eina_Xattr structure.
 *
 * @since_tizen 2.3
 *
 * @param[in] file The file handler to request the extended attribute from
 * @return An iterator
 *
 */
EAPI Eina_Iterator *eina_file_xattr_value_get(Eina_File *file);

/**
 * @brief Maps all the files to a buffer.
 *
 * @since 1.1
 *
 * @since_tizen 2.3
 *
 * @param[in] file The file handler to map in the memory
 * @param[in] rule The rule to apply to the mapped memory
 * @return A pointer to a buffer that maps all the file content \n
 *         @c NULL if it fails
 *
 */
EAPI void *eina_file_map_all(Eina_File *file, Eina_File_Populate rule);

/**
 * @brief Maps a part of the file.
 *
 * @since 1.1
 *
 * @since_tizen 2.3
 *
 * @remarks This does handle reference counting so it can share the same memory area.
 *
 * @param[in] file The file handler to map in the memory
 * @param[in] rule The rule to apply to the mapped memory
 * @param[in] offset The offset inside the file
 * @param[in] length The length of the memory to map
 * @return A valid pointer to the system memory with @a length valid bytes in it \n
 *         And @c NULL if not inside the file or anything else goes wrong.
 *
 */
EAPI void *eina_file_map_new(Eina_File *file, Eina_File_Populate rule,
                             unsigned long int offset, unsigned long int length);

/**
 * @brief Unrefs and unmaps memory if possible.
 *
 * @since 1.1
 *
 * @since_tizen 2.3
 *
 * @param[in] file The file handler to unmap memory from
 * @param[in] map The memory map to unref and unmap
 *
 */
EAPI void eina_file_map_free(Eina_File *file, void *map);

/**
 * @brief Maps line by line in the memory efficiently using an Eina_Iterator.
 *
 * @details This function returns an iterator that acts like fgets without
 *          useless memcpy. Be aware that once eina_iterator_next has been called,
 *          nothing can guarantee that the memory is still going to be mapped.
 *
 * @since 1.3
 *
 * @since_tizen 2.3
 *
 * @param[in] file The file to run over
 * @return An Eina_Iterator that produces #Eina_File_Line
 */
EAPI Eina_Iterator *eina_file_map_lines(Eina_File *file);

/**
 * @brief Tells whether there has been an IO error during the life of a mmaped file,
 *
 * @since 1.2
 *
 * @since_tizen 2.3
 *
 * @param[in] file The file handler to the mmaped file
 * @param[in] map The memory map to check if an error occurred on it
 * @return @c EINA_TRUE if there has been an IO error, otherwise @c EINA_FALSE
 *
 */
EAPI Eina_Bool eina_file_map_faulted(Eina_File *file, void *map);

/**
 * @}
 */

#endif /* EINA_FILE_H_ */
