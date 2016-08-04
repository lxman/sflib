#ifndef BAGASSEMBLE_H
#define BAGASSEMBLE_H

#include <QByteArray>
#include "uint16tole.h"
#include "sflib_global.h"

class BagAssemble {
public:
	BagAssemble(sfBag *b);
	QByteArray assembled(void) { return _assembled; }
private:
	QByteArray _assembled;
};

#endif // BAGASSEMBLE_H
