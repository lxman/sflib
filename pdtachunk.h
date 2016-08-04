#ifndef PDTACHUNK_H
#define PDTACHUNK_H

#include <QByteArray>
#include "sflib_global.h"
#include "sfliberror.h"

class PdtaChunk {
public:
	PdtaChunk(QByteArray ba);
	QByteArray phdr(void) { return _phdr_chunk; }
	QByteArray pbag(void) { return _pbag_chunk; }
	QByteArray pmod(void) { return _pmod_chunk; }
	QByteArray pgen(void) { return _pgen_chunk; }
	QByteArray inst(void) { return _inst_chunk; }
	QByteArray ibag(void) { return _ibag_chunk; }
	QByteArray imod(void) { return _imod_chunk; }
	QByteArray igen(void) { return _igen_chunk; }
	QByteArray shdr(void) { return _shdr_chunk; }
	SflibError error(void) { return _error; }
private:
	SflibError _error;
	QByteArray _getChunk(QByteArray &ba);
	QString _getTag(QByteArray &ba);
	QByteArray _phdr_chunk;
	QByteArray _pbag_chunk;
	QByteArray _pmod_chunk;
	QByteArray _pgen_chunk;
	QByteArray _inst_chunk;
	QByteArray _ibag_chunk;
	QByteArray _imod_chunk;
	QByteArray _igen_chunk;
	QByteArray _shdr_chunk;
};

#endif // PDTACHUNK_H
