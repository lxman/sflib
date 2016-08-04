#ifndef INFOASSEMBLE_H
#define INFOASSEMBLE_H

#include <QByteArray>
#include <QString>
#include "uint16tole.h"
#include "uint32tole.h"
#include "sflib_global.h"

class INFOAssemble {
public:
	INFOAssemble();
	void setIfil(sfVersionTag ifil) { _ifil = ifil; }
	void setIsng(QString isng) { _isng = isng; }
	void setINAM(QString inam) { _inam = inam; }
	void setIrom(QString irom) { _irom = irom; }
	void setIver(sfVersionTag iver) { _iver = iver; }
	void setICRD(QString icrd) { _icrd = icrd; }
	void setIENG(QString ieng) { _ieng = ieng; }
	void setICOP(QString icop) { _icop = icop; }
	void setISFT(QString isft) { _isft = isft; }
	void setICMT(QString icmt) { _icmt = icmt; }
	void setIPRD(QString iprd) { _iprd = iprd; }
	QByteArray &assembled(void);
private:
	QByteArray &_appendString(QByteArray &ba, QString val, QString header);
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
	QByteArray _assembled;
};

#endif // INFOASSEMBLE_H
