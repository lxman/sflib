#ifndef INSTPARSE_H
#define INSTPARSE_H

#include <QByteArray>
#include <QList>
#include "sflib_global.h"

class INSTParse {
public:
	INSTParse(QByteArray ba);
	sfInst *inst(int index) { return _insts.at(index); }
	int count(void) { return _insts.count(); }
private:
	QList<sfInst *> _insts;
};

#endif // INSTPARSE_H
