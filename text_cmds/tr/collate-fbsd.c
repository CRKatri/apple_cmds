/*-
 * Copyright (c) 1995 Alex Tatmanjants <alex@elvisti.kiev.ua>
 *		at Electronni Visti IA, Kiev, Ukraine.
 *			All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: src/lib/libc/locale/collate.c,v 1.33 2004/09/22 16:56:48 stefanf Exp $");

#include "xlocale_private.h"
#define __collate_chain_equiv_table	(loc->__lc_collate->__chain_equiv_table)
#define __collate_chain_pri_table	(loc->__lc_collate->__chain_pri_table)
#define __collate_char_pri_table	(loc->__lc_collate->__char_pri_table)
#define __collate_info			(&loc->__lc_collate->__info)
#define __collate_large_char_pri_table	(loc->__lc_collate->__large_char_pri_table)
#define __collate_substitute_table	(loc->__lc_collate->__substitute_table)

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <wchar.h>
#include <errno.h>
#include <unistd.h>
#include <sysexits.h>
#include <ctype.h>

#if __DARWIN_BYTE_ORDER == __DARWIN_LITTLE_ENDIAN
static void wntohl(wchar_t *, int);
#endif /* __DARWIN_BYTE_ORDER == __DARWIN_LITTLE_ENDIAN */
void __collate_err(int ex, const char *f) __dead2;

/*
 * Normally, the __collate_* routines should all be __private_extern__,
 * but grep is using them (3715846).  Until we can provide an alternative,
 * we leave them public, and provide a read-only __collate_load_error variable
 */
#undef __collate_load_error
int __collate_load_error = 1;

static int
__collate_wcsnlen(const wchar_t *s, int len)
{
	int n = 0;
	while (*s && n < len) {
		s++;
		n++;
	}
	return n;
}

static struct __collate_st_chain_pri *
chainsearch(const wchar_t *key, int *len, locale_t loc)
{
	int low = 0;
	int high = __collate_info->chain_count - 1;
	int next, compar, l;
	struct __collate_st_chain_pri *p;
	struct __collate_st_chain_pri *tab = __collate_chain_pri_table;

	while (low <= high) {
		next = (low + high) / 2;
		p = tab + next;
		compar = *key - *p->str;
		if (compar == 0) {
			l = __collate_wcsnlen(p->str, STR_LEN);
			compar = wcsncmp(key, p->str, l);
			if (compar == 0) {
				*len = l;
				return p;
			}
		}
		if (compar > 0)
			low = next + 1;
		else
			high = next - 1;
	}
	return NULL;
}

static struct __collate_st_large_char_pri *
largesearch(const wchar_t key, locale_t loc)
{
	int low = 0;
	int high = __collate_info->large_pri_count - 1;
	int next, compar;
	struct __collate_st_large_char_pri *p;
	struct __collate_st_large_char_pri *tab = __collate_large_char_pri_table;

	while (low <= high) {
		next = (low + high) / 2;
		p = tab + next;
		compar = key - p->val;
		if (compar == 0)
			return p;
		if (compar > 0)
			low = next + 1;
		else
			high = next - 1;
	}
	return NULL;
}

void
__collate_lookup_l(const wchar_t *t, int *len, int *prim, int *sec, locale_t loc)
{
	struct __collate_st_chain_pri *p2;
	int l;

	*len = 1;
	*prim = *sec = 0;
	p2 = chainsearch(t, &l, loc);
	/* use the chain if prim >= 0 */
	if (p2 && p2->pri[0] >= 0) {
		*len = l;
		*prim = p2->pri[0];
		*sec = p2->pri[1];
		return;
	}
	if (*t <= UCHAR_MAX) {
		*prim = __collate_char_pri_table[*t].pri[0];
		*sec = __collate_char_pri_table[*t].pri[1];
		return;
	}
	if (__collate_info->large_pri_count > 0) {
		struct __collate_st_large_char_pri *match;
		match = largesearch(*t, loc);
		if (match) {
			*prim = match->pri.pri[0];
			*sec = match->pri.pri[1];
			return;
		}
	}
	*prim = (l = __collate_info->undef_pri[0]) >= 0 ? l : *t - l;
	*sec = (l = __collate_info->undef_pri[1]) >= 0 ? l : *t - l;
}
