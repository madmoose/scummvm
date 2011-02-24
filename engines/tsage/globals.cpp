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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL: https://scummvm-misc.svn.sourceforge.net/svnroot/scummvm-misc/trunk/engines/tsage/globals.cpp $
 * $Id: globals.cpp 229 2011-02-12 06:50:14Z dreammaster $
 *
 */

#include "tsage/globals.h"

namespace tSage {

Globals *_globals = NULL;

/*--------------------------------------------------------------------------*/

/**
 * Instantiates a saved object that can be instantiated
 */
static SavedObject *classFactoryProc(const Common::String &className) {
	if (className == "ObjectMover") return new ObjectMover();
	if (className == "NpcMover") return new NpcMover();
	if (className == "ObjectMover2") return new ObjectMover2();
	if (className == "ObjectMover3") return new ObjectMover3();
	if (className == "PlayerMover") return new PlayerMover();
	
	return NULL;
}

/*--------------------------------------------------------------------------*/

Globals::Globals(): 
		_dialogCentre(160, 140),
		_gfxManagerInstance(_screenSurface) {
	reset();
	_stripNum = 0;
	_gfxFontNumber = 50;
	_gfxColours.background = 53;
	_gfxColours.foreground = 18;
	_fontColours.background = 51;
	_fontColours.foreground = 54;
	
	_screenSurface.setScreenSurface();
	_gfxManagers.push_back(&_gfxManagerInstance);

	_sceneObjects = &_sceneObjectsInstance;
	_sceneObjects_queue.push_front(_sceneObjects);

	_stru_4642E = Common::Point(-1, -1);
	_sceneListeners.push_back(&_soundHandler);
	_sceneListeners.push_back(&_sequenceManager._soundHandler);
}

Globals::~Globals() {
	_globals = NULL;
}

void Globals::reset() {
	Common::set_to(&_flags[0], &_flags[MAX_FLAGS], false);
	_saver->addFactory(classFactoryProc);
}

void Globals::synchronise(Serialiser &s) {
	assert(_gfxManagers.size() == 1);

	_sceneItems.synchronise(s);
	SYNC_POINTER(_sceneObjects);
	_sceneObjects_queue.synchronise(s);
	s.syncAsSint32LE(_gfxFontNumber);
	s.syncAsSint32LE(_gfxColours.background);
	s.syncAsSint32LE(_gfxColours.foreground);
	s.syncAsSint32LE(_fontColours.background);
	s.syncAsSint32LE(_fontColours.foreground);

	s.syncAsSint16LE(_dialogCentre.x); s.syncAsSint16LE(_dialogCentre.y);
	_sceneListeners.synchronise(s);
	for (int i = 0; i < 256; ++i)
		s.syncAsByte(_flags[i]);

	s.syncAsSint16LE(_sceneOffset.x); s.syncAsSint16LE(_sceneOffset.y);
	s.syncAsSint16LE(_stru_4642E.x); s.syncAsSint16LE(_stru_4642E.y);
	SYNC_POINTER(_scrollFollower);
	s.syncAsSint32LE(_stripNum);
}

} // end of namespace tSage
