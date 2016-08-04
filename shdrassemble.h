#ifndef SHDRASSEMBLE_H
#define SHDRASSEMBLE_H

#include <QByteArray>
#include "uint32tole.h"
#include "uint16tole.h"
#include "sflib_global.h"

class SHDRAssemble {
public:
	SHDRAssemble(sfSample *s);
	QByteArray assembled(void) { return _assembled; }
private:
	QByteArray _assembled;
};

#endif // SHDRASSEMBLE_H
