#include "genparse.h"

GenParse::GenParse(QByteArray ba) {
	while(ba.length() > 0) {
		GenItem *gl = new GenItem();
		genAmountType tmp;
		gl->setGenerator((SFGenerator)((uchar)ba.at(0) + ((uchar)ba.at(1) * 0x100)));
		tmp.ranges.byLo = (uchar)ba.at(2);
		tmp.ranges.byHi = (uchar)ba.at(3);
		gl->setGenAmount(tmp);
		_gens.append(gl);
		ba.remove(0, 4);
	}
}

