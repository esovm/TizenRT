/****************************************************************************
 *
 * Copyright 2019 NXP Semiconductors All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/
/****************************************************************************
 * os/arch/arm/src/imxrt/imxrt_clrpend.c
 *
 *   Copyright (C) 2018 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <tinyara/config.h>

#include <arch/irq.h>

#include "nvic.h"
#include "up_arch.h"

#include "imxrt_irq.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: imxrt_clrpend
 *
 * Description:
 *   Clear a pending interrupt at the NVIC.  This does not seem to be required
 *   for most interrupts.  Don't know why... but the LPC54xx Ethernet EMAC
 *   interrupt definitely needs it!
 *
 *   This function is logically a part of imxrt_irq.c, but I will keep it in
 *   a separate file so that it will not increase the footprint on LPC54xx
 *   platforms that do not need this function.
 *
 ****************************************************************************/

void imxrt_clrpend(int irq)
{
	/* Check for external interrupt */

	if (irq >= IMXRT_IRQ_EXTINT) {
		if (irq < (IMXRT_IRQ_EXTINT + 32)) {
			putreg32(1 << (irq - IMXRT_IRQ_EXTINT), NVIC_IRQ0_31_CLRPEND);
		}
#if IMXRT_IRQ_NEXTINT >= 64
		else if (irq < (IMXRT_IRQ_EXTINT + 64)) {
			putreg32(1 << (irq - IMXRT_IRQ_EXTINT - 32), NVIC_IRQ32_63_CLRPEND);
		}
#endif
#if IMXRT_IRQ_NEXTINT >= 96
		else if (irq < (IMXRT_IRQ_EXTINT + 96)) {
			putreg32(1 << (irq - IMXRT_IRQ_EXTINT - 64), NVIC_IRQ64_95_CLRPEND);
		}
#endif
#if IMXRT_IRQ_NEXTINT >= 128
		else if (irq < (IMXRT_IRQ_EXTINT + 128)) {
			putreg32(1 << (irq - IMXRT_IRQ_EXTINT - 96), NVIC_IRQ96_127_CLRPEND);
		}
#endif
#if IMXRT_IRQ_NEXTINT >= 160
		else if (irq < (IMXRT_IRQ_EXTINT + 160)) {
			putreg32(1 << (irq - IMXRT_IRQ_EXTINT - 128), NVIC_IRQ128_159_CLRPEND);
		}
#endif
		else {
			DEBUGPANIC();
		}
	}
}
