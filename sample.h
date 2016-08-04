#ifndef SAMPLE_H
#define SAMPLE_H

#include <QByteArray>
#include "sflib_global.h"

class Sample {
public:
	Sample() {}
	void setSample(QByteArray ba) { _sample = ba; }
	void setHeader(sfSample *s) { _header = s; }
	QByteArray sample(void) { return _sample; }
	sfSample *header(void) { return _header; }
private:
	QByteArray _sample;
	sfSample *_header;
};

#endif // SAMPLE_H
