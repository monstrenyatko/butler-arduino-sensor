/*
 *******************************************************************************
 *
 * Purpose: Buffer interface declaration.
 *    Usually used to print logs.
 *
 *******************************************************************************
 * Copyright Oleg Kovalenko 2017.
 *
 * Distributed under the MIT License.
 * (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)
 *******************************************************************************
 */

#ifndef BUTLER_ARDUINO_BUFFER_H_
#define BUTLER_ARDUINO_BUFFER_H_

/* System Includes */
#include <stddef.h>
/* Internal Includes */


namespace Butler {
namespace Arduino {

struct Buffer {
	/** Gets pointer to array */
	virtual unsigned char* get() = 0;
	/** Gets the array size */
	virtual int size() const = 0;
};

}}

#endif // BUTLER_ARDUINO_BUFFER_H_

