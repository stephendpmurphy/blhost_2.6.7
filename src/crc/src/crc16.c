/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "crc/crc16.h"
#include <assert.h>

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////
void crc16_init(crc16_data_t *crc16Config)
{
    assert(crc16Config);

    // initialize running crc and byte count
    crc16Config->currentCrc = 0;
}

void crc16_update(crc16_data_t *crc16Config, const uint8_t *src, uint32_t lengthInBytes)
{
    assert(crc16Config);
    assert(src);

    uint32_t crc = crc16Config->currentCrc;

    uint32_t j;
    for (j = 0; j < lengthInBytes; ++j)
    {
        uint32_t i;
        uint32_t byte = src[j];
        crc ^= byte << 8;
        for (i = 0; i < 8; ++i)
        {
            uint32_t temp = crc << 1;
            if (crc & 0x8000)
            {
                temp ^= 0x1021;
            }
            crc = temp;
        }
    }

    crc16Config->currentCrc = crc;
}

void crc16_finalize(crc16_data_t *crc16Config, uint16_t *hash)
{
    assert(crc16Config);
    assert(hash);

    *hash = crc16Config->currentCrc;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
