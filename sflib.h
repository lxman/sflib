#ifndef SFLIB_H
#define SFLIB_H

#include <QString>
#include <QMap>
#include "sflib_global.h"
#include "sfliberror.h"
#include "sfont.h"

class SFLIBSHARED_EXPORT Sflib {
public:
	Sflib(QString filename);
	bool isValid(void);
	SflibError errors(void);
	QList<sfPresetHeaderItem *> presets(void);
	QMap<int, QList<sfGenItem *> > presetGenerators(u_int16_t wBank, u_int16_t wPreset);
	QMap<int, QList<sfModItem *> > presetModulators(u_int16_t wBank, u_int16_t wPreset);
	bool hasInstrument(u_int16_t wBank, u_int16_t wPreset, u_int16_t pzone);
	QStringList instruments(void);
	QString zoneInstrument(u_int16_t wBank, u_int16_t wPreset, u_int16_t pzone);
	QMap<int, QList<sfGenItem *> > instrumentGenerators(u_int16_t wBank, u_int16_t wPreset, u_int16_t pzone);
	QMap<int, QList<sfModItem *> > instrumentModulators(u_int16_t wBank, u_int16_t wPreset, u_int16_t pzone);
	bool hasSample(u_int16_t wBank, u_int16_t wPreset, u_int16_t pzone, u_int16_t izone);
	sfSampleItem sampleHeader(u_int16_t wBank, u_int16_t wPreset, u_int16_t pzone, u_int16_t izone);
	QList<int32_t> sample(u_int16_t wBank, u_int16_t wPreset, u_int16_t pzone, u_int16_t izone);
	int extract(u_int16_t wBank, u_int16_t wPreset);
	QByteArray deliver(void);
	QList<int> bankList(void);
	QList<presetItem *> bankPresets(int bank);
	int presetZoneCount(u_int16_t wBank, u_int16_t wPreset);
private:
};

#endif // SFLIB_H
