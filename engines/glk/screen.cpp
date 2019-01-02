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

#include "glk/screen.h"
#include "glk/conf.h"
#include "common/unzip.h"
#include "image/bmp.h"
#include "graphics/fonts/ttf.h"
#include "graphics/fontman.h"

namespace Glk {


#define FONTS_VERSION 1.0
#define FONTS_FILENAME "fonts.dat"

Screen::~Screen() {
	for (int idx = 0; idx < FONTS_TOTAL; ++idx)
		delete _fonts[idx];
}

void Screen::initialize() {
	if (!loadFonts())
		error("Could not load fonts.dat");

	for (int idx = 0; idx < 2; ++idx) {
		FontInfo *i = (idx == 0) ? &g_conf->_monoInfo : &g_conf->_propInfo;
		const Graphics::Font *f = (idx == 0) ? _fonts[0] : _fonts[7];

		// TODO: See if there's any better way for getting the leading and baseline
		Common::Rect r1 = f->getBoundingBox('o');
		Common::Rect r2 = f->getBoundingBox('y');
		double baseLine = (double)r1.bottom;
		double leading = (double)((idx == 0) ? r2.bottom : r2.bottom + 2);

		i->_leading = static_cast<int>(MAX((double)i->_leading, leading));
		i->_baseLine = static_cast<int>(MAX((double)i->_baseLine, baseLine));
		i->_cellW = _fonts[0]->getStringWidth("0");
		i->_cellH = i->_leading;
	}
}

void Screen::fill(const byte *rgb) {
	uint color = format.RGBToColor(rgb[0], rgb[1], rgb[2]);
	clear(color);
}

void Screen::fillRect(const Rect &box, const byte *rgb) {
	uint color = format.RGBToColor(rgb[0], rgb[1], rgb[2]);
	Graphics::Screen::fillRect(box, color);
}

bool Screen::loadFonts() {
	Common::Archive *archive = nullptr;

	if (!Common::File::exists(FONTS_FILENAME) || (archive = Common::makeZipArchive(FONTS_FILENAME)) == nullptr)
		return false;

	// Open the version.txt file within it to validate the version
	Common::File f;
	if (!f.open("version.txt", *archive)) {
		delete archive;
		return false;
	}

	// Validate the version
	char buffer[4];
	f.read(buffer, 3);
	buffer[3] = '\0';

	if (Common::String(buffer) != "1.1") {
		delete archive;
		return false;
	}

	loadFonts(archive);

	delete archive;
	return true;
}

void Screen::loadFonts(Common::Archive *archive) {
	// R ead in the fonts
	double monoAspect = g_conf->_monoInfo._aspect;
	double propAspect = g_conf->_propInfo._aspect;
	double monoSize = g_conf->_monoInfo._size;
	double propSize = g_conf->_propInfo._size;

	_fonts.resize(FONTS_TOTAL);
	_fonts[0] = loadFont(MONOR, archive, monoSize, monoAspect, FONTR);
	_fonts[1] = loadFont(MONOB, archive, monoSize, monoAspect, FONTB);
	_fonts[2] = loadFont(MONOI, archive, monoSize, monoAspect, FONTI);
	_fonts[3] = loadFont(MONOZ, archive, monoSize, monoAspect, FONTZ);

	_fonts[4] = loadFont(PROPR, archive, propSize, propAspect, FONTR);
	_fonts[5] = loadFont(PROPB, archive, propSize, propAspect, FONTB);
	_fonts[6] = loadFont(PROPI, archive, propSize, propAspect, FONTI);
	_fonts[7] = loadFont(PROPZ, archive, propSize, propAspect, FONTZ);
}

const Graphics::Font *Screen::loadFont(FACES face, Common::Archive *archive, double size, double aspect, int style) {
	Common::File f;
	const char *const FILENAMES[8] = {
		"GoMono-Regular.ttf", "GoMono-Bold.ttf", "GoMono-Italic.ttf", "GoMono-Bold-Italic.ttf",
		"NotoSerif-Regular.ttf", "NotoSerif-Bold.ttf", "NotoSerif-Italic.ttf", "NotoSerif-Bold-Italic.ttf"
	};

	if (!f.open(FILENAMES[face], *archive))
		error("Could not load %s from fonts file", FILENAMES[face]);

	return Graphics::loadTTFFont(f, (int)size, Graphics::kTTFSizeModeCharacter);
}

FACES Screen::getFontId(const Common::String &name) {
	if (name == "monor") return MONOR;
	if (name == "monob") return MONOB;
	if (name == "monoi") return MONOI;
	if (name == "monoz") return MONOZ;
	if (name == "propr") return PROPR;
	if (name == "propb") return PROPB;
	if (name == "propi") return PROPI;
	if (name == "propz") return PROPZ;
	return MONOR;
}

int Screen::drawString(const Point &pos, int fontIdx, const byte *rgb, const Common::String &text, int spw) {
	int baseLine = (fontIdx >= PROPR) ? g_conf->_propInfo._baseLine : g_conf->_monoInfo._baseLine;
	Point pt(pos.x / GLI_SUBPIX, pos.y - baseLine);
	const Graphics::Font *font = _fonts[fontIdx];
	const uint32 color = format.RGBToColor(rgb[0], rgb[1], rgb[2]);
	font->drawString(this, text, pt.x, pt.y, w - pt.x, color);

	pt.x += font->getStringWidth(text);
	return MIN((int)pt.x, (int)w) * GLI_SUBPIX;
}

int Screen::drawStringUni(const Point &pos, int fontIdx, const byte *rgb, const Common::U32String &text, int spw) {
	int baseLine = (fontIdx >= PROPR) ? g_conf->_propInfo._baseLine : g_conf->_monoInfo._baseLine;
	Point pt(pos.x / GLI_SUBPIX, pos.y - baseLine);
	const Graphics::Font *font = _fonts[fontIdx];
	const uint32 color = format.RGBToColor(rgb[0], rgb[1], rgb[2]);
	font->drawString(this, text, pt.x, pt.y, w - pt.x, color);

	pt.x += font->getStringWidth(text);
	return MIN((int)pt.x, (int)w) * GLI_SUBPIX;
}

size_t Screen::stringWidth(int fontIdx, const Common::String &text, int spw) {
	const Graphics::Font *font = _fonts[fontIdx];
	return font->getStringWidth(text) * GLI_SUBPIX;
}

size_t Screen::stringWidthUni(int fontIdx, const Common::U32String &text, int spw) {
	const Graphics::Font *font = _fonts[fontIdx];
	return font->getStringWidth(text) * GLI_SUBPIX;
}

} // End of namespace Glk