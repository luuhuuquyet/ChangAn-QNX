/*
 * $QNXLicenseC:
 * Copyright 2014, QNX Software Systems.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You
 * may not reproduce, modify or distribute this software except in
 * compliance with the License. You may obtain a copy of the License
 * at: http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as
 * contributors under the License or as licensors under other terms.
 * Please review this entire file for other proprietary rights or license
 * notices, as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

#include "f3s_qspi.h"

/*
 * This is the page callout for SPI serial NOR flash.
 */
uint8_t *f3s_qspi_page(f3s_socket_t *socket, uint32_t flags, uint32_t offset, int32_t *size)
{
	// check if offset does not fit in array
	if (offset >= socket->window_size && socket->window_size > 0) {
		errno = ERANGE;
		return NULL;
	}

	// always zero since there is only 1 window for this device
	socket->window_offset = 0;

	// ensure that offset + size is not out of bounds
	if (size)
		*size = min(*size, socket->window_size - offset);

	// memory pointers are not applicable to this device
	// so we just return ~NULL every time the offset is within bounds
	return (uint8_t*)~NULL;
}


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/6.6.0/trunk/hardware/flash/boards/ti_qspi/f3s_qspi_page.c $ $Rev: 744783 $")
#endif
