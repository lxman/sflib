#ifndef GENPARSE_H
#define GENPARSE_H

#include <QByteArray>
#include <QList>
#include "genitem.h"
#include "sflib_global.h"

class GenParse {
public:
	GenParse(QByteArray ba);
	void removeOne(int index) { _gens.removeAt(index); }
	GenItem *gen(int index) { return _gens.at(index); }
	int count(void) { return _gens.count(); }
private:
	QList<GenItem *> _gens;
};

#endif // GENPARSE_H
