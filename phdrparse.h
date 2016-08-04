#ifndef PHDRPARSE_H
#define PHDRPARSE_H

#include <QByteArray>
#include <QList>
#include "sflib_global.h"

class PHDRParse {
public:
	PHDRParse(QByteArray ba);
	sfPresetHeader * phdr(int index) { return _phdrs.at(index); }
	int count(void) { return _phdrs.count(); }
private:
	QList<sfPresetHeader *> _phdrs;
};

#endif // PHDRPARSE_H
