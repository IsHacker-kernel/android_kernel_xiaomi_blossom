#ifndef WGCUSTOM_H_
#define WGCUSTOM_H_

#include <crypto/internal/blake2s.h>

void blake2s_update(struct blake2s_state *state, const u8 *in, size_t inlen);
void blake2s_final(struct blake2s_state *state, u8 *out);

#endif
