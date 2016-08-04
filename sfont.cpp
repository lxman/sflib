#include "sfont.h"
#include <QList>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include "infolist.h"
#include "preset.h"
#include "instrument.h"
#include "bagzone.h"
#include "mainchunk.h"
#include "phdrparse.h"
#include "phdrassemble.h"
#include "bagparse.h"
#include "bagassemble.h"
#include "modparse.h"
#include "modassemble.h"
#include "genparse.h"
#include "genassemble.h"
#include "instparse.h"
#include "instassemble.h"
#include "shdrparse.h"
#include "shdrassemble.h"
#include "infoassemble.h"
#include "sdtachunk.h"
#include "pdtachunk.h"
#include "uint16tole.h"
#include "uint32tole.h"
#include "letouint16.h"
#include "letouint32.h"
#include "letoint16.h"
#include "sample.h"
#include <QDebug>

class SFontData : public QSharedData {
public:
	void _dumpInfo(void) {
		foreach(Preset *p, _presets) {
			foreach(Zone *z, p->zones()) {
				foreach(GenItem *g, z->genList()) delete g;
				foreach(ModItem *m, z->modList()) delete m;
				delete z;
			}
			delete p->sfPHeaderItem();
			delete p;
		}
		_presets.clear();
		foreach(Instrument *i, _instruments) {
			foreach(Zone *z, i->zones()) {
				foreach(GenItem *g, z->genList()) delete g;
				foreach(ModItem *m, z->modList()) delete m;
				delete z;
			}
			delete i;
		}
		_instruments.clear();
	}
	QByteArray _package_chunk(QByteArray &ba, QString header) {
		QByteArray tmp;
		tmp.append(header);
		ba.prepend(UINT32toLE(ba.length()).parsed());
		return ba.prepend(tmp);
	}
	QList<Preset *> _presets;
	QList<Instrument *> _instruments;
	SdtaChunk *_sc;
	InfoList *_il;
};

SFont::SFont() : _d(new SFontData()) {}

//SFont::SFont(const SFont &rhs) : _d(new SFontData()) {}

SFont &SFont::operator=(const SFont &rhs) {
	if (this != &rhs)
		_d.operator=(rhs._d);
	return *this;
}

SFont::~SFont() {
	_d.data()->_dumpInfo();
}

void SFont::loadFont(QString fileName) {
	if(fileName == "") {
		_error.addError(badFileName);
		return;
	}
	QFile f(fileName);
	if(!f.exists()) {
		_error.addError(badFileName);
		return;
	}
	if(f.open(QFile::ReadOnly)) {
		PdtaChunk *_pc = NULL;
		QList<BagZone *> _PHDR_ZONE;
		QList<BagZone *> _INST_ZONE;
		PHDRParse *PHDR = NULL;
		BagParse *PBAG = NULL;
		ModParse *PMOD = NULL;
		GenParse *PGEN = NULL;
		INSTParse *INST = NULL;
		BagParse *IBAG = NULL;
		ModParse *IMOD = NULL;
		GenParse *IGEN = NULL;
		SHDRParse *SHDR = NULL;
		_d.data()->_dumpInfo();
		u_int32_t size = f.size();
		char *_ID = new char[size];
		f.read(_ID, size);
		f.close();
		QByteArray _main_chunk;
		_main_chunk.reserve(size);
		_main_chunk.append(_ID, size);
		delete _ID;
		MainChunk mc = MainChunk(_main_chunk);
		if(mc.error() == riffChunkTooSmall) _error.addError(riffChunkTooSmall);
		_main_chunk.clear();
		_d.data()->_il = new InfoList(mc.info());
		if(_d.data()->_il->error() == ifilMissing) {
			delete _d.data()->_il;
			_error.addError(ifilMissing);
			return;
		}
		_pc = new PdtaChunk(mc.pdta());
		if(_pc->error().errors().last() != success) {
			_error.addError(_pc->error());
			delete _d.data()->_il;
			delete _pc;
			return;
		}
		_d.data()->_sc = new SdtaChunk(mc.sdta());
		mc.clear();
		PHDR = new PHDRParse(_pc->phdr());
		PBAG = new BagParse(_pc->pbag());
		PMOD = new ModParse(_pc->pmod());
		PGEN = new GenParse(_pc->pgen());
		INST = new INSTParse(_pc->inst());
		IBAG = new BagParse(_pc->ibag());
		IMOD = new ModParse(_pc->imod());
		IGEN = new GenParse(_pc->igen());
		SHDR = new SHDRParse(_pc->shdr());
		delete _pc;
		_pc = NULL;
		for(int x = 0; x < (PHDR->count() - 1); x++)
			if(PHDR->phdr(x)->wPresetBagNdx >= PHDR->phdr(x + 1)->wPresetBagNdx) {
				delete _d.data()->_il;
				_error.addError(pNdxNonMonotic);
				return;
			}
		if(PBAG->count() < PHDR->phdr(PHDR->count() - 1)->wPresetBagNdx) {
			delete _d.data()->_il;
			_error.addError(pbagCountBad);
			return;
		}
		for(int x = 0; x < (PBAG->count() - 1); x++) {
			if(PBAG->bag(x)->wGenNdx > PBAG->bag(x + 1)->wGenNdx) {
				delete _d.data()->_il;
				_error.addError(pbagGenNdxNonMonotic);
				return;
			}
			if(PBAG->bag(x)->wModNdx > PBAG->bag(x + 1)->wModNdx) {
				delete _d.data()->_il;
				_error.addError(pbagModNdxNonMonotonic);
				return;
			}
		}
		if(PGEN->count() < PBAG->bag(PBAG->count() - 1)->wGenNdx) {
			delete _d.data()->_il;
			_error.addError(pbagGenCountBad);
			return;
		}
		if(PMOD->count() < PBAG->bag(PBAG->count() - 1)->wModNdx) {
			delete _d.data()->_il;
			_error.addError(pbagModCountBad);
			return;
		}
		for(int x = 0; x < (INST->count() - 1); x++)
			if(INST->inst(x)->wInstBagNdx >= INST->inst(x + 1)->wInstBagNdx) {
				delete _d.data()->_il;
				_error.addError(iNdxNonMonotonic);
				return;
			}
		if(IBAG->count() < INST->inst(INST->count() - 1)->wInstBagNdx) {
			delete _d.data()->_il;
			_error.addError(ibagCountBad);
			return;
		}
		for(int x = 0; x < (IBAG->count() - 1); x++) {
			if(IBAG->bag(x)->wGenNdx > IBAG->bag(x + 1)->wGenNdx) {
				delete _d.data()->_il;
				_error.addError(ibagGenNdxNonMonotonic);
				return;
			}
			if(IBAG->bag(x)->wModNdx > IBAG->bag(x + 1)->wModNdx) {
				delete _d.data()->_il;
				_error.addError(ibagModNdxNonMonotonic);
				return;
			}
		}
		if(IGEN->count() < IBAG->bag(IBAG->count() - 1)->wGenNdx) {
			delete _d.data()->_il;
			_error.addError(ibagGenCountBad);
			return;
		}
		if(IMOD->count() < IBAG->bag(IBAG->count() - 1)->wModNdx) {
			delete _d.data()->_il;
			_error.addError(ibagModCountBad);
			return;
		}
		for(int x = 0; x < (PHDR->count() - 1); x++) {
			_d.data()->_presets.append(new Preset());
			sfPresetHeader *p = PHDR->phdr(x);
			_d.data()->_presets.last()->setAchPresetName(p->achPresetName);
			_d.data()->_presets.last()->setdwGenre(p->dwGenre);
			_d.data()->_presets.last()->setdwLibrary(p->dwLibrary);
			_d.data()->_presets.last()->setdwMorphology(p->dwMorphology);
			_d.data()->_presets.last()->setwBank(p->wBank);
			_d.data()->_presets.last()->setwPreset(p->wPreset);
		}
		int x, y, z;
		for(x = 0; x < (PHDR->count() - 1); x++) {
			y = PHDR->phdr(x)->wPresetBagNdx;
			BagZone *tmp = new BagZone();
			while(y < PHDR->phdr(x + 1)->wPresetBagNdx) tmp->addBag(PBAG->bag(y++));
			tmp->addBag(PBAG->bag(y));
			_PHDR_ZONE.append(tmp);
		}
		for(x = 0; x < _PHDR_ZONE.count(); x++) {
			BagZone *bz = _PHDR_ZONE.at(x);
			for(y = 0; y < (bz->bags().count() - 1); y++) {
				Zone *zone = new Zone();
				zone->setIndex(y);
				for(z = bz->bags().at(y)->wGenNdx; z < bz->bags().at(y + 1)->wGenNdx; z++) zone->addGenItem(PGEN->gen(z));
				for(z = bz->bags().at(y)->wModNdx; z < bz->bags().at(y + 1)->wModNdx; z++) zone->addModItem(PMOD->pmod(z));
				_d.data()->_presets.at(x)->addZone(zone);
			}
		}
		for(x = 0; x < INST->count(); x++) {
			_d.data()->_instruments.append(new Instrument());
			_d.data()->_instruments.last()->setName(INST->inst(x)->achInstName.toLocal8Bit());
			_d.data()->_instruments.last()->setIndex(x);
		}
		for(x = 0; x < (INST->count() - 1); x++) {
			y = INST->inst(x)->wInstBagNdx;
			BagZone *tmp = new BagZone();
			while(y < INST->inst(x + 1)->wInstBagNdx) tmp->addBag(IBAG->bag(y++));
			tmp->addBag(IBAG->bag(y));
			_INST_ZONE.append(tmp);
		}
		for(x = 0; x < _INST_ZONE.count(); x++) {
			BagZone *bz = _INST_ZONE.at(x);
			for(y = 0; y < (bz->bags().count() - 1); y++) {
				Zone *zone = new Zone();
				zone->setIndex(y);
				for(z = bz->bags().at(y)->wGenNdx; z < bz->bags().at(y + 1)->wGenNdx; z++) zone->addGenItem(IGEN->gen(z));
				for(z = bz->bags().at(y)->wModNdx; z < bz->bags().at(y + 1)->wModNdx; z++) zone->addModItem(IMOD->imod(z));
				_d.data()->_instruments.at(x)->addZone(zone);
			}
		}
		foreach(Instrument *i, _d.data()->_instruments) {
			foreach(Zone *z, i->zones()) {
				if(z->genCount() > 0) {
					if(z->genList().last()->sfGenOper() == sampleID) {
						z->setSample(SHDR->shdr(z->genList().last()->genAmount().wAmount));
						z->sample()->origIndex = z->genList().last()->genAmount().wAmount;
						z->removeLastGen();
					}
				}
			}
		}
		foreach(Preset *p, _d.data()->_presets) {
			foreach(Zone *z, p->zones()) {
				if(z->genCount() > 0) {
					if(z->genList().last()->sfGenOper() == instrument) {
						z->setInstIndex(z->genList().last()->genAmount().wAmount);
						z->removeLastGen();
					}
				}
			}
		}
		for(x = 0; x < SHDR->count(); x++) {
			QString tmp = QString(SHDR->shdr(x)->achSampleName);
			if(tmp == "EOS") SHDR->removeOne(SHDR->shdr(x));
		}
		QList<sfSample *> samp_zones;
		for(x = 0; x < SHDR->count(); x++) samp_zones.append(SHDR->shdr(x));
		bool swapped = true;
		while(swapped) {
			swapped = false;
			for(x = 0; x < (samp_zones.count() - 1); x++) {
				for(y = x + 1; y < samp_zones.count(); y++) {
					if(samp_zones.at(x)->dwStart > samp_zones.at(y)->dwStart) {
						samp_zones.swap(x, y);
						swapped = true;
					}
				}
			}
		}
		for(x = 0; (x < samp_zones.count() - 1); x++) samp_zones.at(x)->dwEndSamp = samp_zones.at(x + 1)->dwStart;
		samp_zones.at(samp_zones.count() - 1)->dwEndSamp = _d.data()->_sc->count() + 1;
		_PHDR_ZONE.clear();
		_INST_ZONE.clear();
		delete PHDR;
		delete PBAG;
		delete PMOD;
		delete PGEN;
		delete INST;
		delete IBAG;
		delete IMOD;
		delete IGEN;
		delete SHDR;
		foreach(Preset *p, _d.data()->_presets) if(p->achPresetName() == "EOP") _d.data()->_presets.removeOne(p);
		foreach(Instrument *i, _d.data()->_instruments) if(i->name() == "EOI") _d.data()->_instruments.removeOne(i);
	}
	_valid = true;
	_error.addError(success);
	return;
}

QList<sfPresetHeaderItem *> SFont::presets(void) {
	QList<sfPresetHeaderItem *> items;
	foreach(Preset *p, _d.data()->_presets) items.append(p->sfPHeaderItem());
	return items;
}

QMap<int, QList<sfGenItem *> > SFont::presetGenerators(u_int16_t wBank, u_int16_t wPreset) {
	QMap<int, QList<sfGenItem *> > zone_list;
	QList<sfGenItem *> gens;
	foreach(Preset *p, _d.data()->_presets) {
		if((p->sfPHeaderItem()->wBank == wBank) && (p->sfPHeaderItem()->wPreset == wPreset)) {
			foreach(Zone *z, p->zones()) {
				foreach(GenItem *g, z->genList()) gens.append(g->generator());
				zone_list.insert(z->index(), gens);
				gens.clear();
			}
		}
	}
	return zone_list;
}

QMap<int, QList<sfModItem *> > SFont::presetModulators(u_int16_t wBank, u_int16_t wPreset) {
	QMap<int, QList<sfModItem *> > zone_list;
	QList<sfModItem *> mods;
	foreach(Preset *p, _d.data()->_presets) {
		if((p->sfPHeaderItem()->wBank == wBank) && (p->sfPHeaderItem()->wPreset == wPreset)) {
			foreach(Zone *z, p->zones()) {
				foreach(ModItem *m, z->modList()) mods.append(m->modulator());
				zone_list.insert(z->index(), mods);
				mods.clear();
			}
		}
	}
	return zone_list;
}

bool SFont::hasInstrument(u_int16_t wBank, u_int16_t wPreset, u_int16_t pzone) {
	bool hasInst = false;
	foreach(Preset *p, _d.data()->_presets) {
		if((p->sfPHeaderItem()->wBank == wBank) && (p->sfPHeaderItem()->wPreset == wPreset)) {
			if(pzone < p->zones().count()) hasInst = (p->zone(pzone)->instrumentIndex() > -1);
		}
	}
	return hasInst;
}

QStringList SFont::instruments(void) {
	QStringList retvalue;
	foreach(Instrument *i, _d.data()->_instruments) retvalue.append(QString(i->name()));
	return retvalue;
}

QString SFont::zoneInstrument(u_int16_t wBank, u_int16_t wPreset, u_int16_t pzone) {
	QString retvalue;
	foreach(Preset *p, _d.data()->_presets) {
		if((p->sfPHeaderItem()->wBank == wBank) && (p->sfPHeaderItem()->wPreset == wPreset)) {
			if(pzone < p->zones().count()) {
				if(p->zone(pzone)->instrumentIndex() > -1) {
					retvalue = QString(_d.data()->_instruments.at(p->zone(pzone)->instrumentIndex())->name());
				}
			}
		}
	}
	return retvalue;
}

QMap<int, QList<sfGenItem *> > SFont::instrumentGenerators(u_int16_t wBank, u_int16_t wPreset, u_int16_t pzone) {
	QMap<int, QList<sfGenItem *> > zone_list;
	QList<sfGenItem *> gens;
	foreach(Preset *p, _d.data()->_presets) {
		if((p->sfPHeaderItem()->wBank == wBank) && (p->sfPHeaderItem()->wPreset == wPreset)) {
			if(pzone < p->zones().count()) {
				if(p->zone(pzone)->instrumentIndex() > -1) {
					Instrument *i = _d.data()->_instruments.at(p->zone(pzone)->instrumentIndex());
					foreach (Zone *z, i->zones()) {
						foreach(GenItem *g, z->genList()) gens.append(g->generator());
						zone_list.insert(z->index(), gens);
						gens.clear();
					}
				}
			}
		}
	}
	return zone_list;
}

QMap<int, QList<sfModItem *> > SFont::instrumentModulators(u_int16_t wBank, u_int16_t wPreset, u_int16_t pzone) {
	QMap<int, QList<sfModItem *> > zone_list;
	QList<sfModItem *> mods;
	foreach(Preset *p, _d.data()->_presets) {
		if((p->sfPHeaderItem()->wBank == wBank) && (p->sfPHeaderItem()->wPreset == wPreset)) {
			if(pzone < p->zones().count()) {
				if(p->zone(pzone)->instrumentIndex() > -1) {
					Instrument *i = _d.data()->_instruments.at(p->zone(pzone)->instrumentIndex());
					foreach (Zone *z, i->zones()) {
						foreach(ModItem *m, z->modList()) mods.append(m->modulator());
						zone_list.insert(z->index(), mods);
						mods.clear();
					}
				}
			}
		}
	}
	return zone_list;
}

bool SFont::hasSample(u_int16_t wBank, u_int16_t wPreset, u_int16_t pzone, u_int16_t izone) {
	bool answer = false;
	foreach(Preset *p, _d.data()->_presets) {
		if((p->sfPHeaderItem()->wBank == wBank) && (p->sfPHeaderItem()->wPreset == wPreset)) {
			if(pzone < p->zones().count()) {
				if(p->zone(pzone)->instrumentIndex() > -1) {
					Instrument *i = _d.data()->_instruments.at(p->zone(pzone)->instrumentIndex());
					if(izone < i->zones().count()) {
						Zone *z = i->zones().at(izone);
						if(z->sample()) answer = true;
					}
				}
			}
		}
	}
	return answer;
}

sfSampleItem SFont::sampleHeader(u_int16_t wBank, u_int16_t wPreset, u_int16_t pzone, u_int16_t izone) {
	sfSampleItem sample;
	foreach(Preset *p, _d.data()->_presets) {
		if((p->sfPHeaderItem()->wBank == wBank) && (p->sfPHeaderItem()->wPreset == wPreset)) {
			if(pzone < p->zones().count()) {
				if(p->zone(pzone)->instrumentIndex() > -1) {
					Instrument *i = _d.data()->_instruments.at(p->zone(pzone)->instrumentIndex());
					if(izone < i->zones().count()) {
						Zone *z = i->zones().at(izone);
						if(z->sample()) {
							int begin = z->sample()->dwStart;
							sample.dwStart = z->sample()->dwStart - begin;
							sample.dwEnd = z->sample()->dwEnd - begin;
							sample.dwStartLoop = z->sample()->dwStartLoop - begin;
							sample.dwEndLoop = z->sample()->dwEndLoop - begin;
							sample.achSampleName = z->sample()->achSampleName.data();
							sample.byOriginalPitch = z->sample()->byOriginalPitch;
							sample.chPitchCorrection = z->sample()->chPitchCorrection;
							sample.dwSampleRate = z->sample()->dwSampleRate;
							sample.sfSampleType = z->sample()->sfSampleType;
							sample.wSampleLink = z->sample()->wSampleLink;
						}
					}
				}
			}
		}
	}
	return sample;
}

QList<int32_t> SFont::sample(u_int16_t wBank, u_int16_t wPreset, u_int16_t pzone, u_int16_t izone) {
	QList<int32_t> sample;
	foreach(Preset *p, _d.data()->_presets) {
		if((p->sfPHeaderItem()->wBank == wBank) && (p->sfPHeaderItem()->wPreset == wPreset)) {
			if(pzone < p->zones().count()) {
				if(p->zone(pzone)->instrumentIndex() > -1) {
					Instrument *i = _d.data()->_instruments.at(p->zone(pzone)->instrumentIndex());
					if(izone < i->zones().count()) {
						Zone *z = i->zones().at(izone);
						if(z->sample()) sample = _d.data()->_sc->subSample(z->sample()->dwStart, z->sample()->dwEnd);
					}
				}
			}
		}
	}
	return sample;
}

int SFont::extract(u_int16_t wBank, u_int16_t wPreset) {
	if(_package.size() > 0) _package.clear();
	QList<int> inst_refs;
	INFOAssemble info;
	QByteArray smpl_chunk, shdr_chunk, igen_chunk, imod_chunk, ibag_chunk, inst_chunk, pgen_chunk, pmod_chunk, pbag_chunk, phdr_chunk,
			info_chunk, sdta_chunk, pdta_chunk, silly_header1, silly_header2, silly_header3, silly_header4, sample_buffer;
	silly_header1.append("sfbk");
	silly_header2.append("pdta");
	silly_header3.append("sdta");
	silly_header4.append("INFO");
	for(int x = 0; x < 92; x++) sample_buffer.append('\0');
	info.setICMT(_d.data()->_il->ICMT());
	info.setICOP(_d.data()->_il->ICOP());
	info.setICRD(_d.data()->_il->ICRD());
	info.setIENG(_d.data()->_il->IENG());
	info.setIfil(_d.data()->_il->ifil());
	info.setIPRD(_d.data()->_il->IPRD());
	info.setIrom(_d.data()->_il->irom());
	info.setISFT(_d.data()->_il->ISFT());
	info.setIsng(_d.data()->_il->isng());
	info.setIver(_d.data()->_il->iver());
	foreach(Preset *p, _d.data()->_presets) {
		if((p->wBank() == wBank) && (p->wPreset() == wPreset)) {
			sfPresetHeader *curr_preset = new sfPresetHeader();
			for(int x = 0; x < p->achPresetName().length(); x++)
				curr_preset->achPresetName[x] = p->achPresetName().at(x);
			curr_preset->achPresetName[p->achPresetName().length()] = '\0';
			curr_preset->dwGenre = p->dwGenre();
			curr_preset->dwLibrary = p->dwLibrary();
			curr_preset->dwMorphology = p->dwMorphology();
			curr_preset->wBank = p->wBank();
			curr_preset->wPreset = p->wPreset();
			curr_preset->wPresetBagNdx = 0;
			foreach(Zone *z, p->zones()) if(z->instrumentIndex() > -1) inst_refs.append(z->instrumentIndex());
			foreach(Instrument *i, _d.data()->_instruments) {
				if(inst_refs.contains(i->index())) {
					sfInst *inst = new sfInst();
					inst->achInstName = i->name();
					inst->wInstBagNdx = ibag_chunk.length() / 4;
					QList<Sample *> samples_reffed;
					foreach(Zone *z, i->zones()) if(z->sample()) {
							sfSample *new_header = new sfSample();
							new_header->dwStart = 0;
							new_header->dwEnd = z->sample()->dwEnd - z->sample()->dwStart;
							new_header->dwStartLoop = z->sample()->dwStartLoop - z->sample()->dwStart;
							new_header->dwEndLoop = new_header->dwEnd + z->sample()->dwEndLoop - z->sample()->dwEnd;
							new_header->dwSampleRate = z->sample()->dwSampleRate;
							new_header->achSampleName = z->sample()->achSampleName;
							new_header->byOriginalPitch = z->sample()->byOriginalPitch;
							new_header->chPitchCorrection = z->sample()->chPitchCorrection;
							new_header->sfSampleType = z->sample()->sfSampleType;
							new_header->wSampleLink = z->sample()->wSampleLink;
							new_header->origIndex = z->sample()->origIndex;
							bool sample_done = false;
							foreach(Sample *s, samples_reffed) {
								if((new_header->dwStart == s->header()->dwStart) &&
										(new_header->dwEnd == s->header()->dwEnd) &&
										(new_header->dwStartLoop == s->header()->dwStartLoop) &&
										(new_header->dwEndLoop == s->header()->dwEndLoop) &&
										(new_header->dwSampleRate == s->header()->dwSampleRate) &&
										(new_header->achSampleName == s->header()->achSampleName) &&
										(new_header->byOriginalPitch == s->header()->byOriginalPitch) &&
										(new_header->chPitchCorrection == s->header()->chPitchCorrection) &&
										(new_header->sfSampleType == s->header()->sfSampleType) &&
										(new_header->wSampleLink == s->header()->wSampleLink) &&
										(new_header->origIndex == s->header()->origIndex)) {
									z->setExcisedSample(s);
									sample_done = true;
								}
							}
							if(!sample_done) {
								Sample *s = new Sample();
								s->setSample(_d.data()->_sc->sample(z->sample()->dwStart, z->sample()->dwEnd));
								int zero_count = 0;
								int index = s->sample().length() - 1;
								if(s->sample().length() > 0) {
									while((s->sample().at(index--) == 0) && (index > -1)) zero_count++;
									while(zero_count < 93) {
										s->sample().append('\0');
										zero_count++;
									}
								} else return 0;
								s->setHeader(new_header);
								if((s->header()->dwEnd - s->header()->dwStart) < 48) return 0;
								if((s->header()->dwEnd - s->header()->dwEndLoop) < 8) s->header()->dwEndLoop = s->header()->dwEnd - 8;
								if((s->header()->dwStartLoop - s->header()->dwStart) < 8) s->header()->dwStartLoop = s->header()->dwStart + 8;
								if((s->header()->dwEndLoop - s->header()->dwStartLoop) < 32) return 0;
								z->setExcisedSample(s);
								samples_reffed.append(s);
							}
						}
					foreach(Sample *s, samples_reffed) {
						u_int32_t offset = (smpl_chunk.length() / 2);
						smpl_chunk.append(s->sample());
						s->header()->dwStart += offset;
						s->header()->dwEnd += offset;
						s->header()->dwStartLoop += offset;
						s->header()->dwEndLoop += offset;
						if((s->header()->sfSampleType == rightSample) ||
								(s->header()->sfSampleType == leftSample) ||
								(s->header()->sfSampleType == romRightSample) ||
								(s->header()->sfSampleType == romLeftSample)) {
							u_int16_t original_link = s->header()->wSampleLink;
							bool found_link = false;
							foreach(Sample *s, samples_reffed) {
								if(original_link == s->header()->origIndex) {
									s->header()->wSampleLink = shdr_chunk.length() / 46;
									found_link = true;
								}
								if(!found_link) switch(s->header()->sfSampleType) {
									case rightSample:
									case leftSample:
										s->header()->sfSampleType = monoSample;
										s->header()->wSampleLink = 0;
										break;
									case romRightSample:
									case romLeftSample:
										s->header()->sfSampleType = romMonoSample;
										s->header()->wSampleLink = 0;
										break;
									default:
										break;
								}
							}
						}
						s->header()->index = shdr_chunk.length() / 46;
						shdr_chunk.append(SHDRAssemble(s->header()).assembled());
					}
					foreach(Zone *z, i->zones()) {
						sfBag *b = new sfBag();
						b->wGenNdx = igen_chunk.length() / 4;
						b->wModNdx = imod_chunk.length() / 10;
						if(z->sample()) {
							GenItem *gi = new GenItem();
							genAmountType amt;
							amt.wAmount = z->excisedSample()->header()->index;
							gi->setGenerator(sampleID);
							gi->setGenAmount(amt);
							z->addGenItem(gi);
						}
						int index = 0;
						while((index < z->genCount()) || (index < z->modCount())) {
							if(index < z->genCount()) igen_chunk.append(GenAssemble(z->genItem(index)).assembled());
							if(index < z->modCount()) imod_chunk.append(ModAssemble(z->modItem(index)->modulator()).assembled());
							index++;
						}
						ibag_chunk.append(BagAssemble(b).assembled());
						delete b;
					}
					foreach(Zone *z, p->zones()) if(z->instrumentIndex() == i->index()) z->setInstIndex(inst_chunk.length() / 22);
					inst_chunk.append(InstAssemble(inst).assembled());
					delete inst;
				}
			}
			foreach(Zone *z, p->zones()) {
				if(z->instrumentIndex() > -1) {
					GenItem *gi = new GenItem();
					gi->setGenerator(instrument);
					genAmountType amt;
					amt.wAmount = z->instrumentIndex();
					gi->setGenAmount(amt);
					z->addGenItem(gi);
				}
			}
			foreach(Zone *z, p->zones()) {
				sfBag *b = new sfBag();
				b->wGenNdx = pgen_chunk.length() / 4;
				b->wModNdx = pmod_chunk.length() / 10;
				int index = 0;
				while((index < z->genCount()) || (index < z->modCount())) {
					if(index < z->genCount()) pgen_chunk.append(GenAssemble(z->genItem(index)).assembled());
					if(index < z->modCount()) pmod_chunk.append(ModAssemble(z->modItem(index)->modulator()).assembled());
					index++;
				}
				pbag_chunk.append(BagAssemble(b).assembled());
				delete b;
			}
			phdr_chunk.append(PHDRAssemble(curr_preset).assembled());
			sfPresetHeader *ph = new sfPresetHeader();
			ph->achPresetName[0] = 'E';
			ph->achPresetName[1] = 'O';
			ph->achPresetName[2] = 'P';
			ph->achPresetName[3] = 0;
			ph->wPresetBagNdx = pbag_chunk.length() / 4;
			phdr_chunk.append(PHDRAssemble(ph).assembled());
			delete ph;
			sfBag *bag = new sfBag();
			bag->wGenNdx = pgen_chunk.length() / 4;
			bag->wModNdx = pmod_chunk.length() / 10;
			pbag_chunk.append(BagAssemble(bag).assembled());
			delete bag;
			GenItem *gi = new GenItem();
			genAmountType t;
			t.wAmount = 0;
			gi->setGenAmount(t);
			gi->setGenerator(startAddrsOffset);
			pgen_chunk.append(GenAssemble(gi).assembled());
			sfModItem *mi = new sfModItem();
			mi->modAmount = 0;
			mi->sfModSrcOper = 0;
			mi->sfModDestOper = startAddrsOffset;
			mi->sfModAmtSrcOper = 0;
			mi->sfModTransOper = 0;
			pmod_chunk.append(ModAssemble(mi).assembled());
			sfInst *i = new sfInst();
			i->achInstName = "EOI";
			i->wInstBagNdx = ibag_chunk.length() / 4;
			inst_chunk.append(InstAssemble(i).assembled());
			delete i;
			bag = new sfBag();
			bag->wGenNdx = igen_chunk.length() / 4;
			bag->wModNdx = imod_chunk.length() / 10;
			ibag_chunk.append(BagAssemble(bag).assembled());
			delete bag;
			igen_chunk.append(GenAssemble(gi).assembled());
			delete gi;
			imod_chunk.append(ModAssemble(mi).assembled());
			delete mi;
			sfSample *sample = new sfSample();
			sample->achSampleName = "EOS";
			sample->dwStart = smpl_chunk.length() / 2;
			sample->dwEnd = sample->dwStart;
			sample->dwStartLoop = sample->dwStart;
			sample->dwEndLoop = sample->dwStart;
			shdr_chunk.append(SHDRAssemble(sample).assembled());
			delete sample;
			if((smpl_chunk.length() % 2) != 0) smpl_chunk.append('\0');
			sdta_chunk.reserve(smpl_chunk.length() + 16);
			if(smpl_chunk.length() > 0) {
				sdta_chunk = _d.data()->_package_chunk(smpl_chunk, "smpl");
				smpl_chunk.clear();
				if((sdta_chunk.length() % 2) != 0) sdta_chunk.append('\0');
				sdta_chunk.prepend(silly_header3);
				sdta_chunk = _d.data()->_package_chunk(sdta_chunk, "LIST");
				if((shdr_chunk.length() % 2) != 0) shdr_chunk.append('\0');
				if((igen_chunk.length() % 2) != 0) igen_chunk.append('\0');
				if((imod_chunk.length() % 2) != 0) imod_chunk.append('\0');
				if((ibag_chunk.length() % 2) != 0) ibag_chunk.append('\0');
				if((inst_chunk.length() % 2) != 0) inst_chunk.append('\0');
				if((pgen_chunk.length() % 2) != 0) pgen_chunk.append('\0');
				if((pmod_chunk.length() % 2) != 0) pmod_chunk.append('\0');
				if((pbag_chunk.length() % 2) != 0) pbag_chunk.append('\0');
				if((phdr_chunk.length() % 2) != 0) phdr_chunk.append('\0');
				pdta_chunk.reserve(shdr_chunk.length() + igen_chunk.length() + imod_chunk.length() + ibag_chunk.length() + inst_chunk.length() +
								   pgen_chunk.length() + pmod_chunk.length() + pbag_chunk.length() + phdr_chunk.length() + 44);
				pdta_chunk = _d.data()->_package_chunk(phdr_chunk, "phdr");
				phdr_chunk.clear();
				pdta_chunk += _d.data()->_package_chunk(pbag_chunk, "pbag");
				pbag_chunk.clear();
				pdta_chunk += _d.data()->_package_chunk(pmod_chunk, "pmod");
				pmod_chunk.clear();
				pdta_chunk += _d.data()->_package_chunk(pgen_chunk, "pgen");
				pgen_chunk.clear();
				pdta_chunk += _d.data()->_package_chunk(inst_chunk, "inst");
				inst_chunk.clear();
				pdta_chunk += _d.data()->_package_chunk(ibag_chunk, "ibag");
				ibag_chunk.clear();
				pdta_chunk += _d.data()->_package_chunk(imod_chunk, "imod");
				imod_chunk.clear();
				pdta_chunk += _d.data()->_package_chunk(igen_chunk, "igen");
				igen_chunk.clear();
				pdta_chunk += _d.data()->_package_chunk(shdr_chunk, "shdr");
				shdr_chunk.clear();
				pdta_chunk.prepend(silly_header2);
				pdta_chunk = _d.data()->_package_chunk(pdta_chunk, "LIST");
				info.setINAM(curr_preset->achPresetName);
				info_chunk.append(info.assembled());
				if((info_chunk.length() % 2) != 0) info_chunk.append('\0');
				info_chunk.prepend(silly_header4);
				info_chunk = _d.data()->_package_chunk(info_chunk, "LIST");
				_package.clear();
				_package.reserve(info_chunk.length() + sdta_chunk.length() + pdta_chunk.length() + 20);
				_package.append(info_chunk);
				info_chunk.clear();
				_package.append(sdta_chunk);
				sdta_chunk.clear();
				_package.append(pdta_chunk);
				pdta_chunk.clear();
				_package.prepend(silly_header1);
				_package = _d.data()->_package_chunk(_package, "RIFF");
				inst_refs.clear();
			} else {
				phdr_chunk.clear();
				pbag_chunk.clear();
				pmod_chunk.clear();
				pgen_chunk.clear();
				inst_chunk.clear();
				ibag_chunk.clear();
				imod_chunk.clear();
				igen_chunk.clear();
				shdr_chunk.clear();
				inst_refs.clear();
			}
		}
	}
	return _package.size();
}

QList<int> SFont::bankList(void) {
	QList<int> banks;
	foreach(Preset *p, _d.data()->_presets) if(!banks.contains(p->wBank())) banks.append(p->wBank());
	bool swapped = true;
	while(swapped) {
		swapped = false;
		for(int x = 0; x < (banks.count() - 1); x++) {
			for(int y = x + 1; y < banks.count(); y++) {
				if(banks.at(x) > banks.at(y)) {
					banks.swap(x, y);
					swapped = true;
				}
			}
		}
	}
	return banks;
}

QList<presetItem *> SFont::bankPresets(int bank) {
	QList<presetItem *> presets;
	foreach(Preset *p, _d.data()->_presets) if(p->wBank() == bank) {
		presetItem *pi = new presetItem();
		pi->preset = p->wPreset();
		QString *s = new QString();
		s->append(p->achPresetName().data());
		pi->name = s;
		presets.append(pi);
	}
	bool swapped = true;
	while(swapped) {
		swapped = false;
		for(int x = 0; x < (presets.count() - 1); x++) {
			for(int y = x + 1; y < presets.count(); y++) {
				if(presets.at(x)->preset > presets.at(y)->preset) {
					presets.swap(x, y);
					swapped = true;
				}
			}
		}
	}
	return presets;
}

int SFont::presetZoneCount(u_int16_t wBank, u_int16_t wPreset) {
	foreach(Preset *p, _d.data()->_presets) if((p->wBank() == wBank) && (p->wPreset() == wPreset)) return p->zones().count();
	return 0;
}
