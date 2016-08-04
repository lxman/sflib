#include "sflib.h"
#include <QFile>
#include "uint16tole.h"
#include "uint32tole.h"

SFont *_sfont = new SFont();

Sflib::Sflib(QString filename) { _sfont->loadFont(filename); }

bool Sflib::isValid(void) {
	return _sfont->isValid();
}

SflibError Sflib::errors(void) {
	return _sfont->errors();
}

QList<sfPresetHeaderItem *> Sflib::presets(void) {
	return _sfont->presets();
}

QMap<int, QList<sfGenItem *> > Sflib::presetGenerators(u_int16_t wBank, u_int16_t wPreset) {
	return _sfont->presetGenerators(wBank, wPreset);
}

QMap<int, QList<sfModItem *> > Sflib::presetModulators(u_int16_t wBank, u_int16_t wPreset) {
	return _sfont->presetModulators(wBank, wPreset);
}

bool Sflib::hasInstrument(u_int16_t wBank, u_int16_t wPreset, u_int16_t pzone) {
	return _sfont->hasInstrument(wBank, wPreset, pzone);
}

QStringList Sflib::instruments(void) { return _sfont->instruments(); }

QString Sflib::zoneInstrument(u_int16_t wBank, u_int16_t wPreset, u_int16_t pzone) {
	return _sfont->zoneInstrument(wBank, wPreset, pzone);
}

QMap<int, QList<sfGenItem *> > Sflib::instrumentGenerators(u_int16_t wBank, u_int16_t wPreset, u_int16_t pzone) {
	return _sfont->instrumentGenerators(wBank, wPreset, pzone);
}

QMap<int, QList<sfModItem *> > Sflib::instrumentModulators(u_int16_t wBank, u_int16_t wPreset, u_int16_t pzone) {
	return _sfont->instrumentModulators(wBank, wPreset, pzone);
}

bool Sflib::hasSample(u_int16_t wBank, u_int16_t wPreset, u_int16_t pzone, u_int16_t izone) {
	return _sfont->hasSample(wBank, wPreset, pzone, izone);
}

sfSampleItem Sflib::sampleHeader(u_int16_t wBank, u_int16_t wPreset, u_int16_t pzone, u_int16_t izone) {
	return _sfont->sampleHeader(wBank, wPreset, pzone, izone);
}

QList<int32_t> Sflib::sample(u_int16_t wBank, u_int16_t wPreset, u_int16_t pzone, u_int16_t izone) {
	return _sfont->sample(wBank, wPreset, pzone, izone);
}

int Sflib::extract(u_int16_t wBank, u_int16_t wPreset) {
	return _sfont->extract(wBank, wPreset);
}

QByteArray Sflib::deliver(void) {
	return _sfont->deliver();
}

QList<int> Sflib::bankList(void) {
	return _sfont->bankList();
}

QList<presetItem *> Sflib::bankPresets(int bank) {
	return _sfont->bankPresets(bank);
}

int Sflib::presetZoneCount(u_int16_t wBank, u_int16_t wPreset) {
	return _sfont->presetZoneCount(wBank, wPreset);
}
