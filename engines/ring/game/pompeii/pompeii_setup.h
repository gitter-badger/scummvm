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
 */

#ifndef RING_POMPEII_SETUP_H
#define RING_POMPEII_SETUP_H

#include "ring/shared.h"

namespace Ring {

class ApplicationPompeii;

class EventSetupPompeii {
public:
	EventSetupPompeii(ApplicationPompeii *application);
	~EventSetupPompeii();

	void onSetupZone2(SetupType type);
	void onSetupZone3(SetupType type);
	void onSetupZone4(SetupType type);

private:
	ApplicationPompeii *_app;
};

} // End of namespace Ring

#endif // RING_POMPEII_SETUP_H
