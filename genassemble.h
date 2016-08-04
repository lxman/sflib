#ifndef GENASSEMBLE_H
#define GENASSEMBLE_H

#include <QByteArray>
#include "genitem.h"
#include "uint16tole.h"
#include "sflib_global.h"

class GenAssemble {
public:
	GenAssemble(GenItem *gen);
	QByteArray assembled(void) { return _assembled; }
private:
	QByteArray _assembled;
};

#endif // GENASSEMBLE_H
