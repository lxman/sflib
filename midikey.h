#ifndef MIDIKEY_H
#define MIDIKEY_H

#include <QString>
#include <QMap>
#include "sflib_global.h"

class MidiKey {
public:
	MidiKey(u_int8_t i);
	QString translated(void) { return _translated; }
private:
	QMap<int, QString> _root_keys;
	QString _translated;
};

#endif // MIDIKEY_H
