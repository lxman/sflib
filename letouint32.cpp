#include "letouint32.h"

LEtoUINT32::LEtoUINT32(QByteArray ba) {
	_val = (uchar)ba.at(0);
	_val += ((uchar)ba.at(1) * 0x100);
	_val += ((uchar)ba.at(2) * 0x10000);
	_val += ((uchar)ba.at(3) * 0x1000000);
}

