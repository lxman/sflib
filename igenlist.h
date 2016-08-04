#ifndef IGENLIST_H
#define IGENLIST_H

#include <QList>
#include <QModelIndex>
#include "sdtachunk.h"
#include "genitem.h"
#include "moditem.h"
#include "sflib_global.h"

class IGENList {
public:
	IGENList();
	void setSource(sfInst *i) { _source = i; }
	void addIGen(GenItem *p) { _igens.append(p); }
	void setSHDR(sfSample *samples) {
		_shdrValid = true;
		_shdr = samples; }
	QList<GenItem *> IGENs(void) { return _igens; }
	bool shdrValid(void) { return _shdrValid; }
	sfSample *SHDR(void) { return _shdr; }
	QList<int32_t> sample(SdtaChunk *sc) { return sc->subSample(SHDR()->dwStart, SHDR()->dwEnd); }
	sfInst *source(void) { return _source; }
private:
	QList<GenItem *> _igens;
	sfSample *_shdr;
	bool _shdrValid = false;
	sfInst *_source = NULL;
};

#endif // IGENLIST_H
