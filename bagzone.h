#ifndef BAGZONE_H
#define BAGZONE_H

#include <QList>
#include "sflib_global.h"

class BagZone {
public:
	BagZone() {}
	void addBag(sfBag *b) { _bag_ptrs.append(b); }
	void setSource(sfInst *source) { _source = source; }
	QList<sfBag *> bags(void) { return _bag_ptrs; }
	sfInst *source(void) { return _source; }
	int count(void) { return _bag_ptrs.count(); }
private:
	QList<sfBag *> _bag_ptrs;
	sfInst *_source;
};

#endif // BAGZONE_H
