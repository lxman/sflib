#ifndef SFMODULATORTRANSLATE_H
#define SFMODULATORTRANSLATE_H

#include <QBitArray>
#include "sflib_global.h"

class SFModulatorTranslate {
public:
	SFModulatorTranslate(SFModulator sfm);
private:
	u_int8_t _type;
	QBitArray _P = QBitArray(1);
	QBitArray _D = QBitArray(1);
	QBitArray _CC = QBitArray(1);
	u_int8_t _index;
};

#endif // SFMODULATORTRANSLATE_H
