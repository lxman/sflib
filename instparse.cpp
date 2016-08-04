#include "instparse.h"

INSTParse::INSTParse(QByteArray ba) {
	while(ba.length() > 0) {
		sfInst *i = new sfInst();
		i->achInstName = ba.left(20).trimmed();
		i->wInstBagNdx = (uchar)ba.at(20) + ((uchar)ba.at(21) * 0x100);
		_insts.append(i);
		ba.remove(0, 22);
	}
}

