#ifndef MODASSEMBLE_H
#define MODASSEMBLE_H

#include <QByteArray>
#include "moditem.h"
#include "uint16tole.h"
#include "sflib_global.h"

class ModAssemble {
public:
	ModAssemble(sfModItem *m);
	QByteArray assembled(void) { return _assembled; }
private:
	QByteArray _assembled;
};

#endif // MODASSEMBLE_H
