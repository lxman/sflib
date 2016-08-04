#include "bagparse.h"

BagParse::BagParse(QByteArray ba) {
	while(ba.length() > 0) {
		sfBag *pb = new sfBag();
		pb->wGenNdx = (uchar)ba.at(0) + ((uchar)ba.at(1) * 0x100);
		pb->wModNdx = (uchar)ba.at(2) + ((uchar)ba.at(3) * 0x100);
		_bags.append(pb);
		ba.remove(0, 4);
	}
}

