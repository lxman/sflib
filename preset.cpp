#include "preset.h"

Preset::Preset() {}

void Preset::setAchPresetName(QString name) {
	_achPresetName.append(name);
	for(int x = 0; x < name.length(); x++) _hi->achPresetName[x] = name.at(x).toLatin1();
	_hi->achPresetName[name.length()] = '\0';
}

void Preset::setwPreset(u_int16_t preset) {
	_wPreset = preset;
	_hi->wPreset = preset;
}

void Preset::setwBank(u_int16_t bank) {
	_wBank = bank;
	_hi->wBank = bank;
}

void Preset::setdwLibrary(u_int32_t library) {
	_dwLibrary = library;
	_hi->dwLibrary = library;
}

void Preset::setdwGenre(u_int32_t genre) {
	_dwGenre = genre;
	_hi->dwGenre = genre;
}

void Preset::setdwMorphology(u_int32_t morphology) {
	_dwMorphology = morphology;
	_hi->dwMorphology = morphology;
}
