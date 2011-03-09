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

#ifndef RING_ACCESSIBILITY_H
#define RING_ACCESSIBILITY_H

#include "ring/shared.h"

#include "common/rect.h"
#include "common/serializer.h"

namespace Ring {

class Hotspot;
class Object;

class Accessibility : public Common::Serializable {
public:
	Accessibility(Object *object);
	~Accessibility();

	void setHotspot(const Common::Rect &rect, bool enabled, CursorId cursorId, uint32 a4);
	Hotspot *getHotspot();
	void enableHotspot();
	void disableHotspot();

	// Serializable
	void saveLoadWithSerializer(Common::Serializer &s);

	Object *getObject() { return _object; }

private:
	Object  *_object;
	Hotspot *_hotspot;
};

} // End of namespace Ring

#endif // RING_ACCESSIBILITY_H
