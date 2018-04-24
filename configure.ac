# Initialize
AC_INIT([ChocAn-DataProcessing], [0.01], [paustin@cecs.pdx.edu], [chocan], [https://github.com/Gilmore-PDX-CS/Group7])

# Force autoconf to be at least this version number:
AC_PREREQ([2.68])

# Safety check - list a source file that shouldn't be in any other directory
AC_CONFIG_SRCDIR([src/main.cpp])

# Put configuration results here, so we can #include them
AC_CONFIG_HEADERS([config.h])

# Put autotools auxiliary files in a subdir
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

# Enable "automake"
AM_INIT_AUTOMAKE([1.11 subdir-objects -Wall -Werror])
AC_CONFIG_FILES([Makefile])

# Look for a C++ compiler:
AC_PROG_CXX

# Check that C++11 is supported (and enable it):
AX_CXX_COMPILE_STDCXX_11

# Output results
AC_OUTPUT
