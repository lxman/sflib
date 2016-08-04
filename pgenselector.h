#ifndef PGENSELECTOR_H
#define PGENSELECTOR_H

#include "sflib_global.h"

class PGENSelector {
public:
	PGENSelector(SFGenerator gen);
	bool isRanges(void) { return _ranges; }
	bool isShort(void) { return _short; }
	bool isWord(void) { return _word; }
private:
	bool _ranges = false, _short = false, _word = false;
};

#endif // PGENSELECTOR_H
