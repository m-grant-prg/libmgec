/**
 * @file src/prg/c/src/libmgec/buf-msg/buffer.c
 *
 * Buffer processing functions.
 *
 * All buffer manipulation support functions.
 *
 * @author Copyright (C) 2017-2023  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.1.0 ==== 02/11/2023_
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "internal.h"
#include <libmgec/mge-buffer.h>
#include <libmgec/mge-errno.h>

/**
 * Concatenate the used portion of a flat buffer into a buffer object.
 * On failure NULL is returned, the function arguments are unchanged and
 * mge_errno will be set.
 * @param s_buf Source buffer.
 * @param s_buf_os Offset into source buffer ie extent of used portion.
 * @param m_buf The buffer object to use.
 * @return The processed buffer object. NULL on error.
 */
struct mgebuffer *concat_buf(const char *s_buf, const size_t s_buf_os,
			     struct mgebuffer *m_buf)
{
	size_t t;
	size_t x = 0;
	char *m_buf_tmp;

	if ((m_buf->next_free + s_buf_os) > m_buf->size) {
		t = m_buf->size + (s_buf_os - (m_buf->size - m_buf->next_free));
		if (t < DEF_BUF_SIZE)
			t = DEF_BUF_SIZE;
		m_buf_tmp = realloc(m_buf->buffer, t);
		if (m_buf_tmp == NULL) {
			sav_errno = errno;
			mge_errno = MGE_ERRNO;
			return NULL;
		}
		m_buf->buffer = m_buf_tmp;
		m_buf->size = t;
	}
	while (x < s_buf_os)
		*(m_buf->buffer + (m_buf->next_free)++) = *(s_buf + x++);
	return m_buf;
}

/**
 * Remove processed data from a buffer object if deemed necessary.
 * Re-sizing the buffer every time this function is called would not be
 * efficient. So, the function first tests whether the buffer has a defined
 * multiple of the default buffer size (BUF_UNUSED_DEF_SIZE_MULT) free, and if
 * so shrinks the buffer and relocates valid data to the start of the buffer.
 * If that test does not result in action, the second test determines if the
 * percentage of unreachable portion of the buffer to the size of the buffer
 * exceeds a defined value (BUF_MAX_UNREACH_PERCENT), and if so, it relocates
 * data to the start of the buffer.
 * On failure NULL is returned, the function argument is unchanged and
 * mge_errno will be set.
 * @param m_buf Pointer to the buffer object to process.
 * @return Pointer to the processed buffer object or NULL on error.
 */
struct mgebuffer *trim_buf(struct mgebuffer *m_buf)
{
	char *t_buf = NULL;
	size_t unreachable, used, unused;

	used = m_buf->next_free - m_buf->proc_next;
	unused = m_buf->size - m_buf->next_free;

	/* Shrink buffer by a default buffer size and compact. */
	if (unused > (BUF_UNUSED_DEF_SIZE_MULT * DEF_BUF_SIZE)) {
		t_buf = realloc(m_buf->buffer, (m_buf->size - DEF_BUF_SIZE));
		if (t_buf == NULL) {
			sav_errno = errno;
			mge_errno = MGE_ERRNO;
			return NULL;
		}
		t_buf = memcpy(t_buf, (m_buf->buffer + m_buf->proc_next), used);
		m_buf->buffer = t_buf;
		m_buf->size -= DEF_BUF_SIZE;
		m_buf->next_free -= m_buf->proc_next;
		m_buf->proc_next = 0;
		return m_buf;
	}

	/* Compact buffer area. */
	unreachable = (size_t)((m_buf->proc_next * 100) / m_buf->size);
	if (unreachable >= BUF_MAX_UNREACH_PERCENT) {
		m_buf->buffer = memmove(m_buf->buffer,
					(m_buf->buffer + m_buf->proc_next),
					used);
		m_buf->next_free -= m_buf->proc_next;
		m_buf->proc_next = 0;
	}

	return m_buf;
}

/**
 * Print a buffer object to stdout, (for debugging).
 * @param m_buf Buffer to print.
 */
void print_buf(struct mgebuffer *m_buf)
{
	printf("Print buffer struct:-\n");
	printf("\tEntire buffer:\t%.*s\n", (int)m_buf->next_free,
	       m_buf->buffer);
	printf("\tSize:\t\t%zu\n", m_buf->size);
	printf("\tproc_next:\t\t%zu\n", m_buf->proc_next);
	printf("\tnext_free:\t\t%zu\n", m_buf->next_free);
}

/**
 * Print the key default values to stdout, (for debugging).
 */
void print_def_buf_values(void)
{
	printf("DEF_BUF_SIZE - %i\n", DEF_BUF_SIZE);
	printf("BUF_UNUSED_DEF_SIZE_MULT - %i\n", BUF_UNUSED_DEF_SIZE_MULT);
	printf("BUF_MAX_UNREACH_PERCENT - %i\n", BUF_MAX_UNREACH_PERCENT);
}
