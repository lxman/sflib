#-------------------------------------------------
#
# Project created by QtCreator 2015-11-04T08:55:03
#
#-------------------------------------------------

QT       -= gui

TARGET = sflib
TEMPLATE = lib

CONFIG += staticlib

QMAKE_CXXFLAGS += --std=gnu++11

DEFINES += SFLIB_LIBRARY

SOURCES += sflib.cpp \
	sfmodulator.cpp \
	sfmodulatortranslate.cpp \
	shdrassemble.cpp \
	shdrparse.cpp \
	sltranslator.cpp \
	uint16tole.cpp \
	uint32tole.cpp \
	bagassemble.cpp \
	bagparse.cpp \
	genassemble.cpp \
	genitem.cpp \
	genlisttranslator.cpp \
	genparse.cpp \
	infoassemble.cpp \
	infolist.cpp \
	instassemble.cpp \
	instparse.cpp \
	mainchunk.cpp \
	midikey.cpp \
	modassemble.cpp \
	modparse.cpp \
	pdtachunk.cpp \
	pgenselector.cpp \
	phdrassemble.cpp \
	phdrparse.cpp \
	sdtachunk.cpp \
    preset.cpp \
    sfont.cpp \
    letouint32.cpp \
    letouint16.cpp \
    letoint16.cpp \
    sfliberror.cpp

HEADERS += sflib.h\
		sflib_global.h \
	sfmodulator.h \
	sfmodulatortranslate.h \
	shdrassemble.h \
	shdrparse.h \
	sltranslator.h \
	uint16tole.h \
	uint32tole.h \
	zone.h \
	bagassemble.h \
	bagparse.h \
	bagzone.h \
	genassemble.h \
	genitem.h \
	genlisttranslator.h \
	genparse.h \
	igenlist.h \
	infoassemble.h \
	infolist.h \
	instassemble.h \
	instmapper.h \
	instparse.h \
	instrument.h \
	mainchunk.h \
	midikey.h \
	modassemble.h \
	moditem.h \
	modparse.h \
	pdtachunk.h \
	pgenselector.h \
	phdrassemble.h \
	phdrparse.h \
	sdtachunk.h \
    preset.h \
    sfont.h \
    sample.h \
    letouint32.h \
    letouint16.h \
    letoint16.h \
    sfliberror.h

unix {
	target.path = /usr/lib
	INSTALLS += target
}
