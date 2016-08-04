#ifndef MODLIST_H
#define MODLIST_H

#include <QList>
#include "sfmodulator.h"
#include "sflib_global.h"

class ModItem {
public:
	ModItem() {}
	void addModulator(sfModItem *ml) {
		_modulator = ml;
		_mod_translated = new SfModulator(ml);
	}
	sfModItem *modulator(void) { return _modulator; }
	SfModulator *modTranslated(void) { return _mod_translated; }
private:
	sfModItem *_modulator;
	SfModulator *_mod_translated;
};

#endif // MODLIST_H
