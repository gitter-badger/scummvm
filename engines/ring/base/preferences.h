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

#ifndef RING_PREFERENCES_H
#define RING_PREFERENCES_H

#include "ring/shared.h"

namespace Ring {

class Application;

class PreferenceHandler {
public:
	PreferenceHandler(Application *application);
	~PreferenceHandler();

	void load();
	void save(int32 volume, int32 volumeDialog, int32 reverseStereo, bool showSubtitles);

	// Accessors
	int32 getVolume() { return _volume; }
	int32 getVolumeDialog() { return _volumeDialog; }
	int32 getReverseStereo() { return _reverseStereo; }
	bool getShowSubtitles() { return _showSubtitles; }

private:
	Application *_app;

	int32 _volume;
	int32 _volumeDialog;
	int32 _reverseStereo;
	bool  _showSubtitles;

	void loadDefaults();
	void set(int32 volume, int32 volumeDialog, int32 reverseStereo, bool showSubtitles);
	void setup();
};

} // End of namespace Ring

#endif // RING_PREFERENCES_H
