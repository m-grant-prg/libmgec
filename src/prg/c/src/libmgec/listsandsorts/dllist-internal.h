/**
 * @file src/prg/c/src/libmgec/listsandsorts/dllist-internal.h
 *
 * Non-public header file for double linked lists in the libmgec shared library.
 * No distribution required.
 *
 * @author Copyright (C) 2015-2019  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0
 *
 * @version _v1.0.9 ==== 12/07/2019_
 */

/* **********************************************************************
 *									*
 * Changelog								*
 *									*
 * Date		Author	Version	Description				*
 *									*
 * 04/11/2017	MG	1.0.1	Started ChangeLog.			*
 * 09/11/2017	MG	1.0.2	Add SPDX license tag.			*
 * 02/01/2018	MG	1.0.3	Move to new source directory structure.	*
 * 19/05/2018	MG	1.0.4	Include dllist and sllist prototypes.	*
 * 20/05/2018	MG	1.0.5	Add re-inclusion prevention #defines.	*
 * 20/05/2018	MG	1.0.6	Standardise on define name format.	*
 * 02/06/2018	MG	1.0.7	Add support for counter and node totals	*
 *				for a tree.				*
 * 09/06/2019	MG	1.0.8	clang-format coding style changes.	*
 * 12/07/2019	MG	1.0.9	Separate combined header file into	*
 *				specific individual files.		*
 *									*
 ************************************************************************
 */

#ifndef DLLIST_INTERNAL_H
#define DLLIST_INTERNAL_H

#include <portability.h>

#include <dllist.h>

BEGIN_C_DECLS

static void free_dll_node(struct dllistnode *currentnode);

END_C_DECLS

#endif /* ndef DLLIST_INTERNAL_H */

