#include "pgenselector.h"

PGENSelector::PGENSelector(SFGenerator gen) {
	switch(gen) {
		case startAddrsOffset:
		case startAddrsCoarseOffset:
		case initialFilterFc:
		case initialFilterQ:
		case chorusEffectsSend:
		case reverbEffectsSend:
		case sustainModEnv:
		case sustainVolEnv:
		case velocity:
		case initialAttenuation:
		case sampleModes:
		case scaleTuning:
		case exclusiveClass:
		case instrument:
		case sampleID:
			_word = true;
			break;
		case endAddrsOffset:
		case startloopAddrsOffset:
		case endloopAddrsOffset:
		case modLfoToPitch:
		case vibLfoToPitch:
		case modEnvToPitch:
		case modLfoToFilterFc:
		case modEnvToFilterFc:
		case endAddrsCoarseOffset:
		case modLfoToVolume:
		case pan:
		case delayModLFO:
		case freqModLFO:
		case delayVibLFO:
		case freqVibLFO:
		case delayModEnv:
		case attackModEnv:
		case holdModEnv :
		case decayModEnv:
		case releaseModEnv:
		case keynumToModEnvHold:
		case keynumToModEnvDecay:
		case delayVolEnv:
		case attackVolEnv:
		case holdVolEnv:
		case decayVolEnv:
		case releaseVolEnv:
		case keynumToVolEnvHold:
		case keynumToVolEnvDecay:
		case startloopAddrsCoarseOffset:
		case endloopAddrsCoarseOffset:
		case coarseTune:
		case fineTune:
			_short = true;
			break;
		case keyRange:
		case velRange:
		case keynum:
		case overridingRootKey:
			_ranges = true;
			break;
		default:
			break;
	}
}

