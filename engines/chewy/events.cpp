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

#include "common/system.h"
#include "common/events.h"

#include "chewy/chewy.h"
#include "chewy/console.h"
#include "chewy/events.h"
#include "chewy/graphics.h"

namespace Chewy {

Events::Events(ChewyEngine *vm, Graphics *graphics, Console *console) :
	_vm(vm), _graphics(graphics), _console(console) {

	_eventManager = g_system->getEventManager();
}

void Events::processEvents() {
	while (_eventManager->pollEvent(_event)) {
		if (_event.type == Common::EVENT_KEYDOWN) {
			switch (_event.kbd.keycode) {
			case Common::KEYCODE_ESCAPE:
				_vm->quitGame();
				break;
			case Common::KEYCODE_SPACE:
				_graphics->nextCursor();
				break;
			case Common::KEYCODE_d:
				if (_event.kbd.flags & Common::KBD_CTRL)
					_console->attach();
				break;
			default:
				break;
			}
		} else if (_event.type == Common::EVENT_RBUTTONUP) {
			_graphics->nextCursor();
		}
	}
}

} // End of namespace Chewy
