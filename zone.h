#ifndef ZONE_H
#define ZONE_H

#include <QList>
#include "genitem.h"
#include "moditem.h"
#include "sample.h"
#include "sflib_global.h"

class Zone {
public:
	Zone() {}
	void addGenItem(GenItem *g) { _gens.append(g); }
	void addModItem(ModItem *m) { _mods.append(m); }
	void setInstIndex(int index) { _inst_index = index; }
	void setSample(sfSample *s) { _sample = s; }
	void setIndex(int index) { _index = index; }
	void setExcisedSample(Sample *s) { _excisedSample = s; }
	void removeLastGen(void) { _gens.removeLast(); }
	int genCount(void) { return _gens.count(); }
	int modCount(void) { return _mods.count(); }
	QList<GenItem *> genList(void) { return _gens; }
	QList<ModItem *> modList(void) { return _mods; }
	GenItem *genItem(int index) { return _gens.at(index); }
	ModItem *modItem(int index) { return _mods.at(index); }
	int instrumentIndex(void) { return _inst_index; }
	sfSample *sample(void) { return _sample; }
	Sample *excisedSample(void) { return _excisedSample; }
	int index(void) { return _index; }
private:
	QList<GenItem *> _gens;
	QList<ModItem *> _mods;
	int _inst_index = -1;
	int _index;
	sfSample *_sample = NULL;
	Sample *_excisedSample;
};

#endif // ZONE_H
