#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([tinyscheme],[1.41],[dsouflis@acm.org])
AC_PREREQ([2.61])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_SRCDIR([scheme.c])
AC_CONFIG_HEADERS([schemeconfig.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_HEADER_DIRENT
AC_HEADER_STDC
AC_CHECK_HEADERS([stdio.h stdlib.h string.h stdint.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_HEADER_TIME

# Checks for library functions.
AC_FUNC_CLOSEDIR_VOID
AC_FUNC_MEMCMP
AC_FUNC_SELECT_ARGTYPES
AC_TYPE_SIGNAL
AC_FUNC_STAT
AC_PROG_LIBTOOL
AC_CHECK_FUNCS([memset])


AC_ARG_ENABLE([standalone],
[  --enable-standalone	Define this to produce a standalone interpreter],
[enable_standalone=${enableval}], [enable_standalone=no])

if test "x${enable_standalone}" = xyes; then
   AC_DEFINE([STANDALONE], 1, [standalone enabled])
   AC_MSG_NOTICE([standalone enabled])
else
   AC_DEFINE([STANDALONE], 0, [standalone disabled])
   AC_MSG_NOTICE([standalone disabled])
fi

AC_ARG_ENABLE([math],
[  --enable-math	Includes math routines],
[enable_math=${enableval}], [enable_math=yes])

if test "x${enable_math}" = xyes; then
   AC_DEFINE([USE_MATH], 1, [math enabled])
   AC_MSG_NOTICE([math enabled])
else
   AC_DEFINE([USE_MATH], 0, [math disabled])
   AC_MSG_NOTICE([math disabled])
fi

AC_ARG_ENABLE([character-classifiers],
[  --enable-character-classifiers	 Includes character classifier procedures],
[enable_character_classifiers=${enableval}], [enable_character_classifiers=yes])

if test "x${enable_character_classifiers}" = xyes; then
   AC_DEFINE([USE_CHAR_CLASSIFIERS], 1, [character classifiers enabled])
   AC_MSG_NOTICE([character classifiers enabled])
else
   AC_DEFINE([USE_CHAR_CLASSIFIERS], 0, [character classifiers disabled])
   AC_MSG_NOTICE([character classifiers disabled])
fi

AC_ARG_ENABLE([ascii-names],
[  --enable-ascii-names	Enable extended character notation based on ASCII names],
[enable_ascii_names=${enableval}], [enable_ascii_names=yes])

if test "x${enable_ascii_names}" = xyes; then
   AC_DEFINE([USE_ASCII_NAMES], 1, [ascii name enabled])
   AC_MSG_NOTICE([ascii name enabled])
else
   AC_DEFINE([USE_ASCII_NAMES], 0, [ascii name disabled])
   AC_MSG_NOTICE([ascii name disabled])
fi

AC_ARG_ENABLE([string-ports],
[  --enable-string-ports	Enables string ports],
[enable_string_ports=${enableval}], [enable_string_ports=yes])

if test "x${enable_string_ports}" = xyes; then
   AC_DEFINE([USE_STRING_PORTS], 1, [string ports enabled])
   AC_MSG_NOTICE([string ports enabled])
else
   AC_DEFINE([USE_STRING_PORTS], 0, [ascii name disabled])
   AC_MSG_NOTICE([string ports disabled])
fi

AC_ARG_ENABLE([error-hook],
[  --enable-error-hook	To force system errors through user-defined error handling],
[enable_error_hook=${enableval}], [enable_error_hook=yes])

if test "x${enable_error_hook}" = xyes; then
   AC_DEFINE([USE_ERROR_HOOK], 1, [error hook enabled])
   AC_MSG_NOTICE([error hook enabled])
else
   AC_DEFINE([USE_ERROR_HOOK], 0, [error hook disabled])
   AC_MSG_NOTICE([error hook disabled])
fi

AC_ARG_ENABLE([tracing],
[  --enable-tracing	To enable use of TRACING],
[enable_tracing=${enableval}], [enable_tracing=yes])

if test "x${enable_tracing}" = xyes; then
   AC_DEFINE([USE_TRACING], 1, [tracing enabled])
   AC_MSG_NOTICE([error hook enabled])
else
   AC_DEFINE([USE_TRACING], 0, [tracing disabled])
   AC_MSG_NOTICE([error hook disabled])
fi

AC_ARG_ENABLE([colon-hook],
[  --enable-colon-hook	Enable use of qualified identifiers. (see "Colon Qualifiers - Packages")],
[enable_colon_hook=${enableval}], [enable_colon_hook=yes])

if test "x${enablenable_colon_hook}" = xyes; then
   AC_DEFINE([USE_COLON_HOOK], 1, [colon hook enabled])
   AC_MSG_NOTICE([colon hook enabled])
else
   AC_DEFINE([USE_COLON_HOOK], 0, [colon hook disabled])
   AC_MSG_NOTICE([colon hook disabled])
fi

AC_ARG_ENABLE([strcasecmp],
[  --enable-strcasecmp	Defines stricmp as strcasecmp, for Unix")],
[enable_strcasecmp=${enableval}], [enable_strcasecmp=yes])

if test "x${enable_strcasecmp}" = xyes; then
   AC_DEFINE([USE_STRCASECMP], 1, [strcasecmp enabled])
   AC_MSG_NOTICE([strcasecmp enabled])
else
   AC_DEFINE([USE_STRCASECMP], 0, [strcasecmp disabled])
   AC_MSG_NOTICE([strcasecmp disabled])
fi

AC_ARG_ENABLE([stdio-adds-cr],
[  --enable-stdio-adds-cr	Informs TinyScheme that stdio translates cr to crlf for DOS/Windows")],
[enable_stdio_adds_cr=${enableval}], [enable_stdio_adds_cr=no])

if test "x${enable_stdio_adds_cr}" = xyes; then
   AC_DEFINE([STDIO_ADDS_CR], 1, [stdio adds cr enabled])
   AC_MSG_NOTICE([stdio adds cr enabled])
else
   AC_DEFINE([STDIO_ADDS_CR], 0, [stdio adds cr disabled])
   AC_MSG_NOTICE([stdio adds cr disabled])
fi

AC_ARG_ENABLE([dl],
[  --enable-dl	Enables dynamically loaded routines.")],
[enable_dl=${enableval}], [enable_dl=yes])

if test "x${enable_dl}" = xyes; then
   AC_DEFINE([USE_DL], 1, [dynamically loaded routines enabled])
   AC_MSG_NOTICE([dynamically loaded routines enabled])
else
   AC_DEFINE([USE_DL], 0, [dynamically loaded routines disabled])
   AC_MSG_NOTICE([dynamically loaded routines disabled])
fi

AC_ARG_ENABLE([plist],
[  --enable-plist	Enables property lists (not Standard Scheme stuff). Off by default.")],
[enable_plist=${enableval}], [enable_plist=no])

if test "x${enable_plist}" = xyes; then
   AC_DEFINE([USE_PLIST], 1, [property lists enabled])
   AC_MSG_NOTICE([property lists enabled])
else
   AC_DEFINE([USE_PLIST], 0, [property lists disabled])
   AC_MSG_NOTICE([property lists disabled])
fi

AC_ARG_ENABLE([scheme-stack],
[  --enable-scheme-stack	Enables 'cons' stack (the alternative is a faster calling scheme, which breaks continuations).")],
[enable_scheme_stack=${enableval}], [enable_scheme_stack=yes])

if test "x${enable_scheme_stack}" = xyes; then
   AC_DEFINE([USE_SCHEME_STACK], 1, [scheme stack enabled])
   AC_MSG_NOTICE([scheme stack enabled])
else
   AC_MSG_NOTICE([scheme stack disabled])
fi

AC_ARG_ENABLE([no-features],
[  --enable-no-features	Shortcut to disable USE_MATH, USE_CHAR_CLASSIFIERS, USE_ASCII_NAMES, USE_STRING_PORTS, USE_ERROR_HOOK, USE_TRACING, USE_COLON_HOOK, USE_DL.")],
[enable_no_features=${enableval}], [enable_no_features=no])

if test "x${enable_no_features}" = xyes; then
   AC_DEFINE([USE_NO_FEATURES], 1, [no features enabled])
   AC_MSG_NOTICE([no features enabled])
else
   AC_DEFINE([USE_NO_FEATURES], 0, [no features disabled])
   AC_MSG_NOTICE([no features disabled])
fi


AC_CONFIG_FILES([Makefile tinyscheme.pc])
AC_OUTPUT
