#ifndef INSTMAPPER_H
#define INSTMAPPER_H

#include <QList>
#include <QMap>
#include "genitem.h"
#include "moditem.h"
#include "sflib_global.h"

class InstMapper {
public:
	InstMapper();
	void setSource(sfInst *source) { _source = source; }
	void addGenerator(int zone, GenItem *gen) {
		QList<GenItem *> tmp;
		while(_generators.count() <= zone) _generators.append(tmp);
		_generators[zone].append(gen);
	}
	void addModulator(int zone, ModItem *mod) {
		QList<ModItem *> tmp;
		while(_modulators.count() <= zone) _modulators.append(tmp);
		_modulators[zone].append(mod);
	}
	void setSample(int zone, sfSample *sample) {
		sfSample *tmp = new sfSample();
		while(_shdr.count() < zone) _shdr.append(tmp);
		_shdr.append(sample); }
	QList<ModItem *> modulators(int zone) {
		QList<ModItem *> tmp;
		while(_modulators.count() <= zone) _modulators.append(tmp);
		return _modulators.at(zone); }
	QList<GenItem *> generators(int zone) { return _generators.at(zone); }
	sfInst *source(void) { return _source; }
	sfSample *sample(int zone) { return _shdr.at(zone); }
	int zoneCount(void) { return _generators.count(); }
	QList<sfSample *> samples(void) { return _shdr; }
private:
	sfInst *_source;
	QList<QList<ModItem *> > _modulators;
	QList<QList<GenItem *> > _generators;
	QList<sfSample *> _shdr;
};

#endif // INSTMAPPER_H
