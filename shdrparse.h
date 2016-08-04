#ifndef SHDRPARSE_H
#define SHDRPARSE_H

#include <QByteArray>
#include <QList>
#include "sflib_global.h"

class SHDRParse {
public:
	SHDRParse(QByteArray ba);
	void removeOne(sfSample *s) { _shdrs.removeOne(s); }
	sfSample *shdr(int index) { return _shdrs.at(index); }
	int count(void) { return _shdrs.count(); }
private:
	QList<sfSample *> _shdrs;
};

#endif // SHDRPARSE_H
