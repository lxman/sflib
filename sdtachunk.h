#ifndef SDTACHUNK_H
#define SDTACHUNK_H

#include <QByteArray>
#include <QList>
#include <QMap>
#include "sflib_global.h"

class SdtaChunk {
public:
	SdtaChunk(QByteArray ba);
	QList<int32_t> subSample(int start, int end);
	QByteArray sample(int start, int end);
	int count(void) { return _data16.length() / 2; }
private:
	QString _tag;
	QByteArray _data16;
	QByteArray _data24;
	QMap<int, QList<int32_t> > _samples;
	QList<int32_t> _retvalue;
};

#endif // SDTACHUNK_H
