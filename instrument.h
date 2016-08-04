#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <QList>
#include "zone.h"
#include "sflib_global.h"

class Instrument {
public:
	Instrument() {}
	void setIndex(int index) { _index = index; }
	void setName(QByteArray name) { _name = name; }
	void addZone(Zone *z) { _zones.append(z); }
	int count(void) { return _zones.count(); }
	Zone *thisZone(int index) { return _zones.at(index); }
	QList<Zone *> zones(void) { return _zones; }
	int index(void) { return _index; }
	QByteArray name(void) { return _name; }
private:
	QList<Zone *> _zones;
	QByteArray _name;
	int _index;
};

#endif // INSTRUMENT_H
