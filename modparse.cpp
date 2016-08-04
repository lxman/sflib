#include "modparse.h"

ModParse::ModParse(QByteArray ba) {
	while(ba.length() > 0) {
		sfModItem *ml = new sfModItem();
		ModItem *mi = new ModItem();
		ml->sfModSrcOper = (uchar)ba.at(0) + ((uchar)ba.at(1) * 0x100);
		ml->sfModDestOper = (SFGenerator)((uchar)ba.at(2) + ((uchar)ba.at(3) * 0x100));
		ml->modAmount = (uchar)ba.at(4) + ((uchar)ba.at(5) * 0x100);
		ml->sfModAmtSrcOper = (uchar)ba.at(6) + ((uchar)ba.at(7) * 0x100);
		ml->sfModTransOper = (uchar)ba.at(8) + ((uchar)ba.at(9) * 0x100);
		mi->addModulator(ml);
		_mods.append(mi);
		ba.remove(0, 10);
	}
}

