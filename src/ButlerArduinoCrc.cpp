/*
 *******************************************************************************
 *
 * Purpose: CRC implementation.
 *
 *******************************************************************************
 * Copyright Oleg Kovalenko 2017.
 *
 * Distributed under the MIT License.
 * (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)
 *******************************************************************************
 */

/* System Includes */
#include "Arduino.h"
#ifdef __AVR__
//	#include <avr/pgmspace.h>
	typedef uint32_t prog_uint32_t;
#else
//	#include <pgmspace.h>
#endif
/* Internal Includes */
#include "ButlerArduinoCrc.h"


namespace Butler {
namespace Arduino {

namespace CrcPrivate {

const prog_uint32_t crc32_table[16] PROGMEM = {
	0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
	0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
	0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
	0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
};

uint32_t crc32_update(uint32_t crc, uint8_t data) {
	uint8_t tbl_idx;
	tbl_idx = crc ^ (data >> (0 * 4));
	crc = pgm_read_dword_near(crc32_table + (tbl_idx & 0x0f)) ^ (crc >> 4);
	tbl_idx = crc ^ (data >> (1 * 4));
	crc = pgm_read_dword_near(crc32_table + (tbl_idx & 0x0f)) ^ (crc >> 4);
	return crc;
}

} // CrcPrivate

namespace Crc {

uint32_t crc32Begin() {
	uint32_t crc = ~0L;
	return crc;
}

uint32_t crc32Continue(uint32_t crc, const uint8_t b[], uint32_t len) {
	for (uint32_t i = 0; i < len; i++) {
		crc = CrcPrivate::crc32_update(crc, b[i]);
	}
	return crc;
}

uint32_t crc32End(uint32_t crc) {
	crc = ~crc;
	return crc;
}

uint32_t crc32(const char *s) {
	uint32_t crc = crc32Begin();
	while (*s) {
		crc = CrcPrivate::crc32_update(crc, *s++);
	}
	return crc32End(crc);
}

uint32_t crc32(const uint8_t b[], uint32_t len) {
	return crc32End(crc32Continue(crc32Begin(), b, len));
}

} // Crc

}}
