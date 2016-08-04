#ifndef PMODPARSE_H
#define PMODPARSE_H

#include <QByteArray>
#include <QList>
#include "moditem.h"
#include "sflib_global.h"

class ModParse {
public:
	ModParse(QByteArray ba);
	ModItem *pmod(int index) { return _mods.at(index); }
	ModItem *imod(int index) { return _mods.at(index); }
	int count(void) { return _mods.count(); }
private:
	QList<ModItem *> _mods;
};

#endif // PMODPARSE_H
