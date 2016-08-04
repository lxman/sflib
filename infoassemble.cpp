#include "infoassemble.h"

INFOAssemble::INFOAssemble() {}

QByteArray &INFOAssemble::assembled(void) {
	_assembled.clear();
	_assembled.append("ifil");
	_assembled.append(UINT32toLE(4).parsed());
	_assembled.append(UINT16toLE(_ifil.wMajor).parsed());
	_assembled.append(UINT16toLE(_ifil.wMinor).parsed());
	if(_isng.length() > 256) _isng.truncate(256);
	_assembled = _appendString(_assembled, _isng, "isng");
	if(_inam.length() > 256) _inam.truncate(256);
	_assembled = _appendString(_assembled, _inam, "INAM");
	if(_irom.length() > 256) _irom.truncate(256);
	if(_irom.length() > 0) _assembled = _appendString(_assembled, _irom, "irom");
	_assembled.append("iver");
	_assembled.append(UINT32toLE(4).parsed());
	_assembled.append(UINT16toLE(_iver.wMajor).parsed());
	_assembled.append(UINT16toLE(_iver.wMinor).parsed());
	if(_icrd.length() > 256) _icrd.truncate(256);
	if(_icrd.length() > 0) _assembled = _appendString(_assembled, _icrd, "ICRD");
	if(_ieng.length() > 256) _ieng.truncate(256);
	if(_ieng.length() > 0) _assembled = _appendString(_assembled, _ieng, "IENG");
	if(_iprd.length() > 256) _iprd.truncate(256);
	if(_iprd.length() > 0) _assembled = _appendString(_assembled, _iprd, "IPRD");
	if(_icop.length() > 256) _icop.truncate(256);
	if(_icop.length() > 0) _assembled = _appendString(_assembled, _icop, "ICOP");
	if(_icmt.length() > 65536) _icmt.truncate(65536);
	if(_icmt.length() > 0) _assembled = _appendString(_assembled, _icmt, "ICMT");
	if(_isft.length() > 256) _isft.truncate(256);
	if(_isft.length() > 0) _assembled = _appendString(_assembled, _isft, "ISFT");
	return _assembled;
}

QByteArray &INFOAssemble::_appendString(QByteArray &ba, QString val, QString header) {
	QByteArray tmp;
	ba.append(header);
	tmp.append(val);
	if(tmp.length() == 0) {
		tmp.append('\0');
		tmp.append('\0');
	}
	if((tmp.length() % 2) != 0) tmp.append('\0');
	ba.append(UINT32toLE(tmp.length()).parsed());
	return ba.append(tmp);
}
