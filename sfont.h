#ifndef DACCESS_H
#define DACCESS_H

#include <QSharedDataPointer>
#include "sflib_global.h"
#include "sfliberror.h"

class SFontData;

class SFont : public QSharedData {
public:
	SFont();
	SFont(const SFont &);
	SFont &operator=(const SFont &);
	~SFont();
	bool isValid(void) { return _valid; }
	SflibError errors(void) { return _error; }
	void loadFont(QString fileName);
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
	QByteArray deliver(void) {
		return _package;
		_package.clear();
	}
	QList<int> bankList(void);
	QList<presetItem *> bankPresets(int bank);
	int presetZoneCount(u_int16_t wBank, u_int16_t wPreset);
private:
	QByteArray _package;
	bool _valid = false;
	SflibError _error;
	QSharedDataPointer<SFontData> _d;
};

#endif // DACCESS_H
