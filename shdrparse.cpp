#include "shdrparse.h"

SHDRParse::SHDRParse(QByteArray ba) {
	while(ba.length() > 0) {
		sfSample *s = new sfSample();
		s->achSampleName = ba.left(20).trimmed();
		s->dwStart = (uchar)ba.at(20) + ((uchar)ba.at(21) * 0x100) + ((uchar)ba.at(22) * 0x10000) + ((uchar)ba.at(23) * 0x1000000);
		s->dwEnd = (uchar)ba.at(24) + ((uchar)ba.at(25) * 0x100) + ((uchar)ba.at(26) * 0x10000) + ((uchar)ba.at(27) * 0x1000000);
		s->dwStartLoop = (uchar)ba.at(28) + ((uchar)ba.at(29) * 0x100) + ((uchar)ba.at(30) * 0x10000) + ((uchar)ba.at(31) * 0x1000000);
		s->dwEndLoop = (uchar)ba.at(32) + ((uchar)ba.at(33) * 0x100) + ((uchar)ba.at(34) * 0x10000) + ((uchar)ba.at(35) * 0x1000000);
		s->dwSampleRate = (uchar)ba.at(36) + ((uchar)ba.at(37) * 0x100) + ((uchar)ba.at(38) * 0x10000) + ((uchar)ba.at(39) * 0x1000000);
		s->byOriginalPitch = (uchar)ba.at(40);
		s->chPitchCorrection = (uchar)ba.at(41);
		s->wSampleLink = (uchar)ba.at(42) + ((uchar)ba.at(43) * 0x100);
		s->sfSampleType = (SFSampleLink)((uchar)ba.at(44) + ((uchar)ba.at(45)));
		_shdrs.append(s);
		ba.remove(0, 46);
	}
}

