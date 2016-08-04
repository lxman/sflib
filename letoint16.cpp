#include "letoint16.h"

LEtoINT16::LEtoINT16(QByteArray ba) {
	_val = (char)ba.at(0);
	_val += ((char)ba.at(1) * 0x100);
}

