#ifndef FINALPRESET_H
#define FINALPRESET_H

#include <QList>
#include <QString>
#include "sflib_global.h"
#include "zone.h"

class Preset {
public:
	Preset();
	void setAchPresetName(QString name);
	void setwPreset(u_int16_t preset);
	void setwBank(u_int16_t bank);
	void setdwLibrary(u_int32_t library);
	void setdwGenre(u_int32_t genre);
	void setdwMorphology(u_int32_t morphology);
	void addZone(Zone *z) { _zones.append(z); }
	Zone *zone(int index) { return _zones.at(index); }
	QList<Zone *> zones(void) { return _zones; }
	QByteArray achPresetName(void) { return _achPresetName; }
	u_int16_t wBank(void) { return _wBank; }
	u_int16_t wPreset(void) { return _wPreset; }
	u_int32_t dwGenre(void) { return _dwGenre; }
	u_int32_t dwLibrary(void) { return _dwLibrary; }
	u_int32_t dwMorphology(void) { return _dwMorphology; }
	sfPresetHeaderItem *sfPHeaderItem(void) { return _hi; }
private:
	sfPresetHeaderItem *_hi = new sfPresetHeaderItem();
	QByteArray _achPresetName;
	u_int16_t _wPreset;
	u_int16_t _wBank;
	u_int32_t _dwLibrary;
	u_int32_t _dwGenre;
	u_int32_t _dwMorphology;
	QList<Zone *> _zones;
};

#endif // FINALPRESET_H
