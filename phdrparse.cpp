#include "phdrparse.h"

PHDRParse::PHDRParse(QByteArray ba) {
	while(ba.length() > 0) {
		sfPresetHeader *tmp = new sfPresetHeader();
		QString tmp_str(ba.left(20).trimmed());
		for(int x = 0; x < tmp_str.length(); x++) tmp->achPresetName[x] = tmp_str.at(x).toLatin1();
		tmp->achPresetName[tmp_str.length()] = '\0';
		tmp->wPreset = (uchar)ba.at(20) + ((uchar)ba.at(21) * 0x100);
		tmp->wBank = (uchar)ba.at(22) + ((uchar)ba.at(23) * 0x100);
		tmp->wPresetBagNdx = (uchar)ba.at(24) + ((uchar)ba.at(25) * 0x100);
		tmp->dwLibrary = (uchar)ba.at(26) + ((uchar)ba.at(27) * 0x100) + ((uchar)ba.at(28) * 0x10000) + ((uchar)ba.at(29) * 0x1000000);
		tmp->dwGenre = (uchar)ba.at(30) + ((uchar)ba.at(31) * 0x100) + ((uchar)ba.at(32) * 0x10000) + ((uchar)ba.at(33) * 0x1000000);
		tmp->dwMorphology = (uchar)ba.at(34) + ((uchar)ba.at(35) * 0x100) + ((uchar)ba.at(36) * 0x10000) + ((uchar)ba.at(37) * 0x1000000);
		_phdrs.append(tmp);
		ba.remove(0, 38);
	}
}
