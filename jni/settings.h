/* gen/settings.h.  Generated from settings.h.in by configure.  */
/* gen/settings.h.in.  Generated from configure.ac by autoheader.  */

#ifndef ASPELL_SETTINGS__H
#define ASPELL_SETTINGS__H

/* Defined if filters should be compiled in */
/* #undef COMPILE_IN_FILTER */

/* Defined to curses header file */
/* #undef CURSES_HEADER */

/* Defined if no special Workarounds are needed for Curses headers */
/* #undef CURSES_INCLUDE_STANDARD */

/* Defined if special Wordaround I is need for Curses headers */
/* #undef CURSES_INCLUDE_WORKAROUND_1 */

/* Defined if curses like POSIX Functions should be used */
/* #undef CURSES_ONLY */

/* Defined if _XOPEN_SOURCE_EXTENDED needs to be defined. (Can't define
   globally as that will cause problems with some systems) */
/* #undef DEFINE_XOPEN_SOURCE_EXTENDED */

/* Define to 1 if translation of program messages to the user's native
   language is requested. */
//#define ENABLE_NLS 1

/* Defined if win32 relocation should be used */
/* #undef ENABLE_WIN32_RELOCATABLE */

/* Defined if filter version control should be used */
#define FILTER_VERSION_CONTROL 1

/* Define to 1 if you have the MacOS X function CFLocaleCopyCurrent in the
   CoreFoundation framework. */
/* #undef HAVE_CFLOCALECOPYCURRENT */

/* Define to 1 if you have the MacOS X function CFPreferencesCopyAppValue in
   the CoreFoundation framework. */
/* #undef HAVE_CFPREFERENCESCOPYAPPVALUE */

/* Define if the GNU dcgettext() function is already present or preinstalled.
   */
#define HAVE_DCGETTEXT 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Defined if msdos getch is supported */
/* #undef HAVE_GETCH */

/* Define if the GNU gettext() function is already present or preinstalled. */
#define HAVE_GETTEXT 1

/* Define if you have the iconv() function. */
/* #undef HAVE_ICONV */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define if you have <langinfo.h> and nl_langinfo(CODESET). */
//#define HAVE_LANGINFO_CODESET 1

/* Defined if the curses library is available */
/* #undef HAVE_LIBCURSES */

/* Define to 1 if you have the `dl' library (-ldl). */
#define HAVE_LIBDL 1

/* Defined if mblen is supported */
#define HAVE_MBLEN 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Defined if mmap and friends is supported */
#define HAVE_MMAP 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Defined if curses libraray includes wide character support */
/* #undef HAVE_WIDE_CURSES */

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Define to 1 if your C compiler doesn't accept -c and -o together. */
/* #undef NO_MINUS_C_MINUS_O */

/* Name of package */
#define PACKAGE "aspell"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME "GNU Aspell"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "GNU Aspell 0.60.6.1"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "aspell"

/* Define to the version of this package. */
#define PACKAGE_VERSION "0.60.6.1"

/* Defined if Posix Termios is Supported */
#define POSIX_TERMIOS 1

/* Defined if STL rel_ops pollute the global namespace */
/* #undef REL_OPS_POLLUTION */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Defined to term header file */
/* #undef TERM_HEADER */

/* Defined if file ino is supported */
#define USE_FILE_INO 1

/* Defined if file locking and truncating is supported */
#define USE_FILE_LOCKS 1

/* Defined if Posix locales are supported */
#define USE_LOCALE 1

/* Defined if Posix mutexes are supported */
#define USE_POSIX_MUTEX 1

/* Defined if Posix regex are supported */
#define USE_POSIX_REGEX 1

/* Version number of package */
#define VERSION "0.60.6.1"

#define C_EXPORT extern "C"

#endif /* ASPELL_SETTINGS__H */
