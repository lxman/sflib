#ifndef INFOLIST_H
#define INFOLIST_H

#include <QByteArray>
#include <QString>
#include "sflib_global.h"

class InfoList {
public:
	InfoList(QByteArray ba);
	sfVersionTag ifil(void) { return _ifil; }
	QString isng(void) { return _isng; }
	QString INAM(void) { return _inam; }
	QString irom(void) { return _irom; }
	sfVersionTag iver(void) { return _iver; }
	QString ICRD(void) { return _icrd; }
	QString IENG(void) { return _ieng; }
	QString ICOP(void) { return _icop; }
	QString ISFT(void) { return _isft; }
	QString ICMT(void) { return _icmt; }
	QString IPRD(void) { return _iprd; }
	violations error(void) { return _error; }
private:
	QString _getString(QString tag, QByteArray ba);
	violations _error = success;
	sfVersionTag _ifil, _iver;
	QString _isng;
	QString _inam;
	QString _irom;
	QString _icrd;
	QString _ieng;
	QString _icmt;
	QString _iprd;
	QString _icop;
	QString _isft;
};

#endif // INFOLIST_H
