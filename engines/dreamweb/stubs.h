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
 */
	uint16 allocatemem(uint16 paragraphs);
	uint8 *workspace();
	void allocatework();
	void clearwork();
	void multidump();
	void multidump(uint16 x, uint16 y, uint8 width, uint8 height);
	void frameoutv(uint8 *dst, const uint8 *src, uint16 pitch, uint16 width, uint16 height, uint16 x, uint16 y);
	void frameoutnm(uint8 *dst, const uint8 *src, uint16 pitch, uint16 width, uint16 height, uint16 x, uint16 y);
	void frameoutbh(uint8 *dst, const uint8 *src, uint16 pitch, uint16 width, uint16 height, uint16 x, uint16 y);
	void frameoutfx(uint8 *dst, const uint8 *src, uint16 pitch, uint16 width, uint16 height, uint16 x, uint16 y);
	void worktoscreen();
	void multiget();
	void multiget(uint8 *dst, uint16 x, uint16 y, uint8 width, uint8 height);
	void convertkey();
	void cls();
	void printsprites();
	void quickquit();
	void readoneblock();
	void printundermon();
	void seecommandtail();
	void randomnumber();
	void quickquit2();
	uint8 getnextword(const Frame *charSet, const uint8 *string, uint8 *totalWidth, uint8 *charCount);
	void printboth(const Frame* charSet, uint16 *x, uint16 y, uint8 c, uint8 nextChar);
	void printchar();
	void printchar(const Frame* charSet, uint16 *x, uint16 y, uint8 c, uint8 nextChar, uint8 *width, uint8 *height);
	void printdirect();
	void printdirect(const uint8** string, uint16 x, uint16 *y, uint8 maxWidth, bool centered);
	void printmessage(uint16 x, uint16 y, uint8 index, uint8 maxWidth, bool centered);
	void printmessage();
	void usetimedtext();
	void dumptimedtext();
	void setuptimedtemp();
	void setuptimedtemp(uint8 textIndex, uint8 voiceIndex, uint8 x, uint8 y, uint16 countToTimed, uint16 timeCount);
	void getundertimed();
	void putundertimed();
	uint8 printslow(const uint8 *string, uint16 x, uint16 y, uint8 maxWidth, bool centered);
	void printslow();
	void dumptextline();
	void getnumber();
	uint8 getnumber(const Frame *charSet, const uint8 *string, uint16 maxWidth, bool centered, uint16 *offset);
	uint8 kernchars(uint8 firstChar, uint8 secondChar, uint8 width);
	void getroomdata();
	void readheader();
	void fillspace();
	void startloading();
	void startloading(const Room *room);
	Sprite *spritetable();
	void showframe();
	void showframe(const Frame *frameData, uint16 x, uint16 y, uint16 frameNumber, uint8 effectsFlag, uint8 *width, uint8 *height);
	void showframe(const Frame *frameData, uint16 x, uint16 y, uint16 frameNumber, uint8 effectsFlag);
	void printasprite(const Sprite *sprite);
	void width160();
	void multiput(const uint8 *src, uint16 x, uint16 y, uint8 width, uint8 height);
	void multiput();
	void eraseoldobs();
	void clearsprites();
	void makesprite();
	Sprite *makesprite(uint8 x, uint8 y, uint16 updateCallback, uint16 frameData, uint16 somethingInDi);
	void spriteupdate();
	void initman();
	void mainman(Sprite *sprite);
	void facerightway();
	void walking(Sprite *sprite);
	void autosetwalk();
	void checkdest(const uint8 *roomsPaths);
	void aboutturn(Sprite *sprite);
	void backobject(Sprite *sprite);
	void constant(Sprite *sprite, SetObject *objData);
	void steady(Sprite *sprite, SetObject *objData);
	void random(Sprite *sprite, SetObject *objData);
	void dodoor();
	void dodoor(Sprite *sprite, SetObject *objData);
	void doorway(Sprite *sprite, SetObject *objData);
	void widedoor(Sprite *sprite, SetObject *objData);
	void lockeddoorway(Sprite *sprite, SetObject *objData);
	void liftsprite(Sprite *sprite, SetObject *objData);
	void findsource();
	Frame *findsourceCPP();
	void showgamereel();
	void showgamereel(ReelRoutine *routine);
	void showreelframe();
	void showreelframe(Reel *reel);
	const Frame *getreelframeax(uint16 frame);
	void turnpathonCPP(uint8 param);
	void turnpathoffCPP(uint8 param);
	void getroomspaths();
	uint8 *getroomspathsCPP();
	void makebackob(SetObject *objData);
	void modifychar();
	void lockmon();
	void cancelch0();
	void cancelch1();
	void plotreel();
	Reel *getreelstart();
	void dealwithspecial(uint8 firstParam, uint8 secondParam);
	void zoom();
	void crosshair();
	void showrain();
	void deltextline();
	void commandonly();
	void commandonly(uint8 command);
	void doblocks();
	void checkifperson();
	bool checkifperson(uint8 x, uint8 y);
	void checkiffree();
	bool checkiffree(uint8 x, uint8 y);
	void checkifex();
	bool checkifex(uint8 x, uint8 y);
	const uint8 *findobname(uint8 type, uint8 index);
	void copyname();
	void copyname(uint8 type, uint8 index, uint8 *dst);
	void commandwithob();
	void commandwithob(uint8 command, uint8 type, uint8 index);
	void showpanel();
	void updatepeople();
	void madmantext();
	void madmode();
	void movemap(uint8 param);
	bool addalong(const uint8 *mapFlags);
	bool addlength(const uint8 *mapFlags);
	void getdimension();
	void getdimension(uint8 *mapXstart, uint8 *mapYstart, uint8 *mapXsize, uint8 *mapYsize);
	void getmapad();
	void calcmapad();
	uint8 getmapad(const uint8 *setData);
	uint8 getxad(const uint8 *setData, uint8 *result);
	uint8 getyad(const uint8 *setData, uint8 *result);
	void calcfrframe();
	void calcfrframe(uint8* width, uint8* height);
	void finalframe();
	void finalframe(uint16 *x, uint16 *y);
	void showallobs();
	void blocknametext();
	void walktotext();
	void personnametext();
	void findxyfrompath();
	void findormake();
	void findormake(uint8 index, uint8 value, uint8 type);
	DynObject *getfreead(uint8 index);
	DynObject *getexad(uint8 index);
	DynObject *geteitheradCPP();
	SetObject *getsetad(uint8 index);
	void setallchanges();
	void dochange();
	void dochange(uint8 index, uint8 value, uint8 type);
	void deletetaken();
	bool isCD();
	void placesetobject();
	void placesetobject(uint8 index);
	void removesetobject();
	void removesetobject(uint8 index);
	void showallfree();
	void showallex();
	bool finishedwalkingCPP();
	void finishedwalking();
	void checkone();
	void checkone(uint8 x, uint8 y, uint8 *flag, uint8 *flagEx, uint8 *type, uint8 *flagX, uint8 *flagY);
	void getflagunderp();
	void getflagunderp(uint8 *flag, uint8 *flagEx);
	void walkandexamine();
	void obname();
	void obname(uint8 command, uint8 commandType);
	void delpointer();
	void showblink();
	void dumpblink();
	void dumppointer();
	void showpointer();
	void animpointer();
	void checkcoords();
	void checkcoords(const RectWithCallback *rectWithCallbacks);
	void readmouse();
	void readmouse1();
	void readmouse2();
	void readmouse3();
	void readmouse4();
	uint16 waitframes();
	void drawflags();
	void addtopeoplelist();
	void addtopeoplelist(ReelRoutine *routine);
	void getexpos();
	void paneltomap();
	void obpicture();
	void transferinv();

