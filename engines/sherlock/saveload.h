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
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef SHERLOCK_SAVELOAD_H
#define SHERLOCK_SAVELOAD_H

#include "common/scummsys.h"
#include "common/savefile.h"
#include "common/serializer.h"
#include "common/str-array.h"
#include "engines/savestate.h"
#include "graphics/surface.h"

namespace Sherlock {

#define MAX_SAVEGAME_SLOTS 99
#define ONSCREEN_FILES_COUNT 5
#define SHERLOCK_SAVEGAME_VERSION 1

enum SaveMode { SAVEMODE_NONE = 0, SAVEMODE_LOAD = 1, SAVEMODE_SAVE = 2 };

extern const int ENV_POINTS[6][3];

struct SherlockSavegameHeader {
	uint8 _version;
	Common::String _saveName;
	Graphics::Surface *_thumbnail;
	int _year, _month, _day;
	int _hour, _minute;
	int _totalFrames;
};

class SherlockEngine;

class SaveManager {
private:
	SherlockEngine *_vm;
	Common::String _target;
	Graphics::Surface *_saveThumb;

	/**
	 * Build up a savegame list, with empty slots given an explicit Empty message
	 */
	void createSavegameList();

	/**
	 * Synchronize the data for a savegame
	 */
	void synchronize(Common::Serializer &s);
public:
	Common::StringArray _savegames;
	int _savegameIndex;
	SaveMode _envMode;
	bool _justLoaded;
public:
	SaveManager(SherlockEngine *vm, const Common::String &target);
	~SaveManager();

	/**
	 * Shows the in-game dialog interface for loading and saving games
	 */
	void drawInterface();

	/**
	 * Creates a thumbnail for the current on-screen contents
	 */
	void createThumbnail();

	/**
	 * Load a list of savegames
	 */
	static SaveStateList getSavegameList(const Common::String &target);

	/**
	 * Support method that generates a savegame name
	 * @param slot		Slot number
	 */
	Common::String generateSaveName(int slot);

	/**
	 * Write out the header information for a savegame
	 */
	void writeSavegameHeader(Common::OutSaveFile *out, SherlockSavegameHeader &header);

	/**
	 * Read in the header information for a savegame
	 */
	static bool readSavegameHeader(Common::InSaveFile *in, SherlockSavegameHeader &header);

	/**
	 * Return the index of the button the mouse is over, if any
	 */
	int getHighlightedButton() const;

	/**
	 * Handle highlighting buttons
	 */
	void highlightButtons(int btnIndex);

	/**
	 * Load the game in the specified slot
	 */
	void loadGame(int slot);
	
	/**
	 * Save the game in the specified slot with the given name
	 */
	void saveGame(int slot, const Common::String &name);

	/**
	 * Make sure that the selected savegame is on-screen
	 */
	bool checkGameOnScreen(int slot);

	/**
	 * Prompts the user to enter a description in a given slot
	 */
	bool promptForDescription(int slot);

	/**
	 * Returns true if the given save slot is empty
	 */
	bool isSlotEmpty(int slot) const;
};

} // End of namespace Sherlock

#endif
