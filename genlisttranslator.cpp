#include "genlisttranslator.h"

GenListTranslator::GenListTranslator() {
	_gen_list.insert(0, "startAddrsOffset");
	_gen_list.insert(1, "endAddrsOffset");
	_gen_list.insert(2, "startloopAddrsOffset");
	_gen_list.insert(3, "endloopAddrsOffset");
	_gen_list.insert(4, "startAddrsCoarseOffset");
	_gen_list.insert(5, "modLfoToPitch");
	_gen_list.insert(6, "vibLfoToPitch");
	_gen_list.insert(7, "modEnvToPitch");
	_gen_list.insert(8, "initialFilterFc");
	_gen_list.insert(9, "initialFilterQ");
	_gen_list.insert(10, "modLfoToFilterFc");
	_gen_list.insert(11, "modEnvToFilterFc");
	_gen_list.insert(12, "endAddrsCoarseOffset");
	_gen_list.insert(13, "modLfoToVolume");
	_gen_list.insert(15, "chorusEffectsSend");
	_gen_list.insert(16, "reverbEffectsSend");
	_gen_list.insert(17, "pan");
	_gen_list.insert(20, "delayModLFO");
	_gen_list.insert(21, "freqModLFO");
	_gen_list.insert(22, "delayVibLFO");
	_gen_list.insert(23, "freqVibLFO");
	_gen_list.insert(24, "delayModEnv");
	_gen_list.insert(25, "attackModEnv");
	_gen_list.insert(26, "holdModEnv ");
	_gen_list.insert(27, "decayModEnv");
	_gen_list.insert(28, "sustainModEnv");
	_gen_list.insert(29, "releaseModEnv");
	_gen_list.insert(30, "keynumToModEnvHold");
	_gen_list.insert(31, "keynumToModEnvDecay");
	_gen_list.insert(32, "delayVolEnv");
	_gen_list.insert(33, "attackVolEnv");
	_gen_list.insert(34, "holdVolEnv");
	_gen_list.insert(35, "decayVolEnv");
	_gen_list.insert(36, "sustainVolEnv");
	_gen_list.insert(37, "releaseVolEnv");
	_gen_list.insert(38, "keynumToVolEnvHold");
	_gen_list.insert(39, "keynumToVolEnvDecay");
	_gen_list.insert(41, "instrument");
	_gen_list.insert(43, "keyRange");
	_gen_list.insert(44, "velRange");
	_gen_list.insert(45, "startloopAddrsCoarseOffset");
	_gen_list.insert(46, "keynum");
	_gen_list.insert(47, "velocity");
	_gen_list.insert(48, "initialAttenuation");
	_gen_list.insert(50, "endloopAddrsCoarseOffset");
	_gen_list.insert(51, "coarseTune");
	_gen_list.insert(52, "fineTune");
	_gen_list.insert(53, "sampleID");
	_gen_list.insert(54, "sampleModes");
	_gen_list.insert(56, "scaleTuning");
	_gen_list.insert(57, "exclusiveClass");
	_gen_list.insert(58, "overridingRootKey");
}

QString GenListTranslator::translated(int ID) {
	return _gen_list.value(ID);
}
