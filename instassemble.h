#ifndef INSTASSEMBLE_H
#define INSTASSEMBLE_H

#include <QByteArray>
#include "uint16tole.h"
#include "sflib_global.h"

class InstAssemble {
public:
	InstAssemble(sfInst *i);
	QByteArray assembled(void) { return _assembled; }
private:
	QByteArray _assembled;
};

#endif // INSTASSEMBLE_H
