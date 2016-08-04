#include "letouint16.h"

LEtoUINT16::LEtoUINT16(QByteArray ba) {
	_val = (uchar)ba.at(0);
	_val += ((uchar)ba.at(1) * 0x100);
}

