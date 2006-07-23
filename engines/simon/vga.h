/* ScummVM - Scumm Interpreter
 * Copyright (C) 2001  Ludvig Strigeus
 * Copyright (C) 2002-2006 The ScummVM project
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

#ifndef SIMON_VGA_H
#define SIMON_VGA_H

namespace Simon {

#include "common/pack-start.h"	// START STRUCT PACKING

// Feeble Files
struct VgaFileHeader_Feeble {
	uint16 x_1;
	uint16 hdr2_start;
	uint16 x_2, x_3;
};

struct VgaFileHeader2_Feeble {
	uint16 imageCount;
	uint16 x_2;
	uint16 animationCount;
	uint16 x_3;
	uint16 imageTable;
	uint16 x_4;
	uint16 animationTable;
	uint16 x_5;
};

struct ImageHeader_Feeble {
	uint16 id;
	uint16 x_1;
	uint16 scriptOffs;
	uint16 x_2;
};

struct AnimationHeader_Feeble {
	uint16 scriptOffs;
	uint16 x_2;
	uint16 id;
};

// Simon 1/2
struct VgaFileHeader_Simon {
	uint16 x_1, x_2;
	uint16 hdr2_start;
	uint16 x_3, x_4;
};

struct VgaFileHeader2_Simon {
	uint16 x_1;
	uint16 imageCount;
	uint16 x_2;
	uint16 animationCount;
	uint16 x_3;
	uint16 imageTable;
	uint16 x_4;
	uint16 animationTable;
	uint16 x_5;
};

struct ImageHeader_Simon {
	uint16 id;
	uint16 x_1;
	uint16 x_2;
	uint16 scriptOffs;
};

struct AnimationHeader_Simon {
	uint16 id;
	uint16 x_2;
	uint16 scriptOffs;
};


#include "common/pack-end.h"	// END STRUCT PACKING

enum DrawFlags {
	kDFFlip           = 0x1,
	kDFNonTrans       = 0x2,
	kDFUseFrontBuf    = 0x4,
	kDFCompressed     = 0x8,
	kDFCompressedFlip = 0x10,
	kDFMasked         = 0x20,

	// Feeble specific
	kDFOverlayed      = 0x10,
	kDFScaled         = 0x40,
	kDFShaded         = 0x80
};

struct VC10_state {
	int image;
	uint16 flags;
	byte palette;

	int x, y;
	int width, height;
	uint draw_width, draw_height;
	uint x_skip, y_skip;

	byte *surf2_addr;
	uint surf2_pitch;

	byte *surf_addr;
	uint surf_pitch;

	uint16 dl, dh;

	const byte *depack_src;
	int8 depack_cont;

	byte depack_dest[480];
};

byte *vc10_depackColumn(VC10_state *vs);

} // End of namespace Simon

#endif
