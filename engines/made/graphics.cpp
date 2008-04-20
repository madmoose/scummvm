/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#include "common/endian.h"

#include "made/graphics.h"

namespace Made {

void decompressImage(byte *source, Graphics::Surface &surface, uint16 cmdOffs, uint16 pixelOffs, uint16 maskOffs, uint16 lineSize, bool deltaFrame) {

    const int offsets[] = {
        0, 1, 2, 3,
        320, 321, 322, 323,
        640, 641, 642, 643,
        960, 961, 962, 963
    };

	uint16 width = surface.w;
    uint16 height = surface.h;

    byte *cmdBuffer = source + cmdOffs;
    byte *maskBuffer = source + maskOffs;
    byte *pixelBuffer = source + pixelOffs;

    byte *destPtr = (byte*)surface.getBasePtr(0, 0);

    //byte lineBuf[320 * 4];
    byte lineBuf[640 * 4];
    byte bitBuf[40];

    int bitBufLastOfs = (((lineSize + 1) >> 1) << 1) - 2;
    int bitBufLastCount = ((width + 3) >> 2) & 7;
    if (bitBufLastCount == 0)
        bitBufLastCount = 8;

    while (height > 0) {

        int drawDestOfs = 0;

    	memset(lineBuf, 0, sizeof(lineBuf));

        memcpy(bitBuf, cmdBuffer, lineSize);
        cmdBuffer += lineSize;

        for (uint16 bitBufOfs = 0; bitBufOfs < lineSize; bitBufOfs += 2) {

            uint16 bits = READ_LE_UINT16(&bitBuf[bitBufOfs]);

            int bitCount;
            if (bitBufOfs == bitBufLastOfs)
                bitCount = bitBufLastCount;
            else
                bitCount = 8;

            for (int curCmd = 0; curCmd < bitCount; curCmd++) {
                int cmd = bits & 3;
                bits >>= 2;

                byte pixels[4];
                uint32 mask;

                switch (cmd) {

                case 0:
                    pixels[0] = *pixelBuffer++;
                    for (int i = 0; i < 16; i++)
                        lineBuf[drawDestOfs + offsets[i]] = pixels[0];
                    break;

                case 1:
                    pixels[0] = *pixelBuffer++;
                    pixels[1] = *pixelBuffer++;
                    mask = READ_LE_UINT16(maskBuffer);
                    maskBuffer += 2;
                    for (int i = 0; i < 16; i++) {
                        lineBuf[drawDestOfs + offsets[i]] = pixels[mask & 1];
                        mask >>= 1;
                    }
                    break;

                case 2:
                    pixels[0] = *pixelBuffer++;
                    pixels[1] = *pixelBuffer++;
                    pixels[2] = *pixelBuffer++;
                    pixels[3] = *pixelBuffer++;
                    mask = READ_LE_UINT32(maskBuffer);
                    maskBuffer += 4;
                    for (int i = 0; i < 16; i++) {
                        lineBuf[drawDestOfs + offsets[i]] = pixels[mask & 3];
                        mask >>= 2;
                    }
                    break;

                case 3:
                    if (!deltaFrame) {
                        // Yes, it reads from maskBuffer here
                        for (int i = 0; i < 16; i++)
                            lineBuf[drawDestOfs + offsets[i]] = *maskBuffer++;
                    }
                    break;

                }

                drawDestOfs += 4;

            }

        }

        if (deltaFrame) {
    		for (int y = 0; y < 4 && height > 0; y++, height--) {
                for (int x = 0; x < width; x++) {
                    if (lineBuf[x + y * 320] != 0)
                        *destPtr = lineBuf[x + y * 320];
                    destPtr++;
                }
    		}
        } else {
    		for (int y = 0; y < 4 && height > 0; y++, height--) {
    		    memcpy(destPtr, &lineBuf[y * 320], width);
    		    destPtr += width;
    		}
        }

    }

}

} // End of namespace Made
