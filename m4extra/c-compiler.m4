#! /usr/bin/env bash
#########################################################################
#									#
# Macro ID: m4extra/c-compiler.m4					#
# Author: Copyright (C) 2019  Mark Grant				#
#									#
# Released under the GPLv3 or later.					#
# SPDX-License-Identifier: GPL-3.0-or-later				#
#									#
# Purpose:								#
# Build a variable containing CFLAGS depending on compiler version.	#
#									#
# Check gcc version changes here:-					#
#	https://www.gnu.org/software/gcc/				#
#			and check under Changes and C-Family.		#
#									#
#########################################################################

#########################################################################
#									#
# Changelog								#
#									#
# Date		Author	Version	Description				#
#									#
# 10/02/2019	MG	1.0.1	Initial release. Checked up to gcc v8.2	#
# 02/03/2019	MG	1.0.2	Change file name to c-compiler.m4	#
# 05/05/2019	MG	1.0.3	Remove manual specification of implicit	#
#				fallthrough from v7 as it is included	#
#				in Wextra.				#
#				Establish baseline warnings as of	#
#				gcc v6.3				#
#				Checked up to v9.1			#
# 16/06/2019	MG	1.0.4	Backported to gcc v5 to facilitate use	#
#				with xenial build VMs on Travis CI.	#
#									#
#########################################################################


# BUILD_COMPILER_VERSION_CFLAGS(CFLAGS_Variable)
# ----------------------------------------------
AC_DEFUN([BUILD_COMPILER_VERSION_CFLAGS],
[AC_MSG_NOTICE(placing compiler-dependent CFLAGS in $1 - starting ...)
AC_SUBST($1)
AX_COMPILER_VENDOR
AX_COMPILER_VERSION
# The following 2 options seem fairly universal.
$1="-Wall -Wextra"
if [[ $ax_cv_c_compiler_vendor == gnu ]]; then
	# The following non version specific inclusions form the baseline for
	# this macro from gcc v5.4
	$1+=" -Wbad-function-cast -Wconversion -Wmissing-include-dirs"
	$1+=" -Wmissing-prototypes -Wredundant-decls"
	$1+=" -Wshadow -Wstrict-prototypes"
	AX_COMPARE_VERSION($ax_cv_c_compiler_version, ge, "6")
	if [[ x${ax_compare_version} == xtrue ]]; then
		$1+=" -Wduplicated-cond -Wnull-dereference"
	fi
	AX_COMPARE_VERSION($ax_cv_c_compiler_version, ge, "8")
	if [[ x${ax_compare_version} == xtrue ]]; then
		$1+=" -Wmultistatement-macros"
	fi
fi
AC_MSG_NOTICE(CFLAGS to be used are $$1)
AC_MSG_NOTICE(placing compiler-dependent CFLAGS in $1 ... done)
])

