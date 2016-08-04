#ifndef MAINCHUNK_H
#define MAINCHUNK_H

#include <QByteArray>
#include <QString>
#include "sflib_global.h"

class MainChunk {
public:
	MainChunk(QByteArray ba);
	QByteArray info(void) { return _list1; }
	QByteArray sdta(void) { return _list2; }
	QByteArray pdta(void) { return _list3; }
	QByteArray leftover(void) { return _leftover; }
	void clear(void);
	violations error(void) { return _error; }

private:
	violations _error = success;
	u_int32_t _littleEndianToUInt(QByteArray ba);
	QString _ID, _tag;
	QByteArray _leftover, _main, _list1, _list2, _list3;
};

#endif // MAINCHUNK_H
