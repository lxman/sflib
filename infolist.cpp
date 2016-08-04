#include "infolist.h"
#include "letouint32.h"
#include <QDebug>

InfoList::InfoList(QByteArray ba) {
	_ifil.wMajor = 0;
	_ifil.wMinor = 0;
	int index;
	index = ba.indexOf("ifil");
	if(index != -1) {
		_ifil.wMajor = (uchar)ba.at(index + 8) + ((uchar)ba.at(index + 9));
		_ifil.wMinor = (uchar)ba.at(index + 10) + ((uchar)ba.at(index + 11));
	} else {
		index = ba.indexOf("IFIL");
		if(index != -1) {
			_ifil.wMajor = (uchar)ba.at(index + 8) + ((uchar)ba.at(index + 9));
			_ifil.wMinor = (uchar)ba.at(index + 10) + ((uchar)ba.at(index + 11));
		}
	}
	_isng = _getString("isng", ba);
	_inam = _getString("inam", ba);
	_inam = _getString("irom", ba);
	_inam = _getString("icrd", ba);
	_inam = _getString("ieng", ba);
	_inam = _getString("icmt", ba);
	_inam = _getString("iprd", ba);
	_inam = _getString("icop", ba);
	_inam = _getString("isft", ba);
	index = ba.indexOf("iver");
	if(index != -1) {
		_iver.wMajor = (uchar)ba.at(index + 8) + ((uchar)ba.at(index + 9) * 0x100);
		_iver.wMinor = (uchar)ba.at(index + 10) + ((uchar)ba.at(index + 11) * 0x100);
	}
	if(_isng.endsWith("\0")) _isng = _isng.left(_isng.length() - 1);
	if(_irom.endsWith("\0")) _irom = _irom.left(_irom.length() - 1);
	if(_inam.endsWith("\0")) _inam = _inam.left(_inam.length() - 1);
	if(_icrd.endsWith("\0")) _icrd = _icrd.left(_icrd.length() - 1);
	if(_ieng.endsWith("\0")) _ieng = _ieng.left(_ieng.length() - 1);
	if(_iprd.endsWith("\0")) _iprd = _iprd.left(_iprd.length() - 1);
	if(_icop.endsWith("\0")) _icop = _icop.left(_icop.length() - 1);
	if(_icmt.endsWith("\0")) _icmt = _icmt.left(_icmt.length() - 1);
	if(_isft.endsWith("\0")) _isft = _isft.left(_isft.length() - 1);
	if((_ifil.wMajor == 0) && (_ifil.wMinor == 0)) _error = ifilMissing;
	if(_isng.length() == 0) _error = isngMissing;
	if(_inam.length() == 0) _error = INAMMissing;
}

QString InfoList::_getString(QString tag, QByteArray ba) {
	QString retvalue;
	int index = 0;
	while(index < (ba.length() - 7)) {
		QString tmp = QString(ba.mid(index++, 4));
		if(tmp.toLower() == tag.toLower()) break;
	}
	if(index >= (ba.length() - 7)) index = -1;
	else index -= 1;
	if(index != -1) {
		int offset = index + 8;
		for(uint x = 0; x < LEtoUINT32(ba.mid(index + 4, 4)).uint32(); x++) {
			retvalue.append((uchar)ba.at(x + offset));
			if(retvalue[x] == 0) break;
		}
	}
	return retvalue;
}
