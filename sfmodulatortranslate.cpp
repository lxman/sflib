#include "sfmodulatortranslate.h"

SFModulatorTranslate::SFModulatorTranslate(SFModulator sfm) {
	_type = (sfm & 0xFC00) >> 10;
	_P = (QBitArray)((sfm & 0x200) >> 9);
	_D = (QBitArray)((sfm & 0x100) >> 8);
	_CC = (QBitArray)((sfm & 0x80) >> 7);
	_index = (sfm & 0x7F);
}

