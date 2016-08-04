#ifndef BAGPARSE_H
#define BAGPARSE_H

#include <QByteArray>
#include <QList>
#include "sflib_global.h"

class BagParse {
public:
	BagParse(QByteArray ba);
	sfBag *bag(int index) { return _bags.at(index); }
	int count(void) { return _bags.count(); }
private:
	QList<sfBag *> _bags;
};

#endif // BAGPARSE_H
