#ifndef PHDRASSEMBLE_H
#define PHDRASSEMBLE_H

#include <QByteArray>
#include "uint16tole.h"
#include "uint32tole.h"
#include "sflib_global.h"

class PHDRAssemble {
public:
	PHDRAssemble(sfPresetHeader *p);
	QByteArray assembled(void) { return _assembled; }
private:
	QByteArray _assembled;
};

#endif // PHDRASSEMBLE_H
