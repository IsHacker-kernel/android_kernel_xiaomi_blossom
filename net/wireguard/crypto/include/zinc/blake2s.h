/* SPDX-License-Identifier: GPL-2.0 OR MIT */
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#ifndef _ZINC_BLAKE2S_H
#define _ZINC_BLAKE2S_H

#include <linux/types.h>
#include <linux/kernel.h>
#include <asm/bug.h>
#include <wg-custom/wgcustom.h>

enum blake2s_lengths {
	BLAKE2S_BLOCK_SIZE = 64,
	BLAKE2S_HASH_SIZE = 32,
	BLAKE2S_KEY_SIZE = 32
};

void blake2s_init(struct blake2s_state *state, const size_t outlen);
void blake2s_init_key(struct blake2s_state *state, const size_t outlen,
		      const void *key, const size_t keylen);

void blake2s_hmac(u8 *out, const u8 *in, const u8 *key, const size_t outlen,
		  const size_t inlen, const size_t keylen);

#endif /* _ZINC_BLAKE2S_H */
