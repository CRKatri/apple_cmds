/*
 * Copyright (c) 2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _XLOCALE_PRIVATE_H_
#define _XLOCALE_PRIVATE_H_

#include <sys/cdefs.h>
#define __DARWIN_XLOCALE_PRIVATE
#include <xlocale.h>
#undef __DARWIN_XLOCALE_PRIVATE
#include <stdlib.h>
#include <locale.h>
#include <libkern/OSAtomic.h>
#include <pthread.h>
#include <limits.h>
#include "setlocale.h"
#include "collate.h"

typedef void (*__free_extra_t)(void *);

#define	__STRUCT_COMMON	\
	int32_t __refcount; \
	__free_extra_t __free_extra;

struct __xlocale_st_collate {
	__STRUCT_COMMON
	char __encoding[ENCODING_LEN + 1];
	struct __collate_st_info __info;
	struct __collate_st_subst *__substitute_table[COLL_WEIGHTS_MAX];
	struct __collate_st_chain_pri *__chain_pri_table;
	struct __collate_st_large_char_pri *__large_char_pri_table;
	struct __collate_st_char_pri __char_pri_table[UCHAR_MAX + 1];
};
struct _xlocale {
/* The item(s) before __magic are not copied when duplicating locale_t's */
	__STRUCT_COMMON	/* only used for locale_t's in __lc_numeric_loc */
	/* 10 independent mbstate_t buffers! */
	__darwin_mbstate_t __mbs_mblen;
	__darwin_mbstate_t __mbs_mbrlen;
	__darwin_mbstate_t __mbs_mbrtowc;
	__darwin_mbstate_t __mbs_mbsnrtowcs;
	__darwin_mbstate_t __mbs_mbsrtowcs;
	__darwin_mbstate_t __mbs_mbtowc;
	__darwin_mbstate_t __mbs_wcrtomb;
	__darwin_mbstate_t __mbs_wcsnrtombs;
	__darwin_mbstate_t __mbs_wcsrtombs;
	__darwin_mbstate_t __mbs_wctomb;
/* magic (Here up to the end is copied when duplicating locale_t's) */
	int64_t __magic;
/* flags */
	unsigned char __collate_load_error;
	unsigned char __collate_substitute_nontrivial;
	unsigned char _messages_using_locale;
	unsigned char _monetary_using_locale;
	unsigned char _numeric_using_locale;
	unsigned char _time_using_locale;
	unsigned char __mlocale_changed;
	unsigned char __nlocale_changed;
	unsigned char __numeric_fp_cvt;
/* collate */
	struct __xlocale_st_collate *__lc_collate;
/* ctype */
	struct __xlocale_st_runelocale *__lc_ctype;
/* messages */
	struct __xlocale_st_messages *__lc_messages;
/* monetary */
	struct __xlocale_st_monetary *__lc_monetary;
/* numeric */
	struct __xlocale_st_numeric *__lc_numeric;
	struct _xlocale *__lc_numeric_loc;
/* time */
	struct __xlocale_st_time *__lc_time;
/* localeconv */
	struct __xlocale_st_localeconv *__lc_localeconv;
};

#endif /* _XLOCALE_PRIVATE_H_ */
