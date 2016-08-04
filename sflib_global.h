#ifndef SFLIB_GLOBAL_H
#define SFLIB_GLOBAL_H

#include <QString>
#include <QtCore/qglobal.h>
#include <QMetaType>

#if defined(SFLIB_LIBRARY)
#  define SFLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SFLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

typedef u_int16_t SFModulator;
typedef u_int16_t SFTransform;

typedef enum { startAddrsOffset = 0, endAddrsOffset, startloopAddrsOffset, endloopAddrsOffset,
			   startAddrsCoarseOffset, modLfoToPitch, vibLfoToPitch, modEnvToPitch, initialFilterFc,
			   initialFilterQ, modLfoToFilterFc, modEnvToFilterFc, endAddrsCoarseOffset, modLfoToVolume,
			   chorusEffectsSend = 15, reverbEffectsSend, pan, delayModLFO = 21, freqModLFO, delayVibLFO, freqVibLFO,
			   delayModEnv, attackModEnv, holdModEnv , decayModEnv, sustainModEnv, releaseModEnv,
			   keynumToModEnvHold, keynumToModEnvDecay, delayVolEnv, attackVolEnv, holdVolEnv, decayVolEnv,
			   sustainVolEnv, releaseVolEnv, keynumToVolEnvHold, keynumToVolEnvDecay, instrument, keyRange = 43, velRange,
			   startloopAddrsCoarseOffset, keynum, velocity, initialAttenuation, endloopAddrsCoarseOffset = 50,
			   coarseTune, fineTune, sampleID, sampleModes, scaleTuning = 56, exclusiveClass, overridingRootKey, endOper = 60 } SFGenerator;
typedef enum { noController, noteOnVelocity = 2, noteOnKeyNum, polyPressure = 10, channelPressure = 13, pitchWheel,
			   pitchWheelSensitivity = 16, link = 127 } sfModSource;
typedef enum { monoSample = 1, rightSample = 2, leftSample = 4, linkedSample = 8, romMonoSample = 32769, romRightSample = 32770,
			   romLeftSample = 32772, romLinkedSample = 32776 } SFSampleLink;
typedef union { u_int8_t midiPalette; sfModSource generalPalette; } sfModController;
typedef enum { srcLinear, srcConcave, srcConvex, srcSwitch } sfModSrcType;
typedef enum { dirFwd, dirRev } sfModSrcDirection;
typedef enum { general, midi } sfModSrcCC;
typedef enum { tfmLinear, tfmAbs = 2 } sfModSrcTransform;
typedef enum { unipolar, bipolar } sfModSrcPolarity;
typedef enum { modSource, modAmtSource } sfModSrcFrom;
typedef struct { sfModController modController; sfModSrcDirection direction; sfModSrcPolarity polarity; sfModSrcType srcType;
			   sfModSrcCC cc; } sfModStruct;
typedef struct { char achPresetName[20]; u_int16_t wPreset; u_int16_t wBank; u_int16_t wPresetBagNdx; u_int32_t dwLibrary; u_int32_t dwGenre;
				 u_int32_t dwMorphology; } sfPresetHeader;
typedef struct { char achPresetName[20]; u_int16_t wPreset; u_int16_t wBank; u_int32_t dwLibrary; u_int32_t dwGenre; u_int32_t dwMorphology;
			   } sfPresetHeaderItem;
typedef struct { u_int16_t wGenNdx; u_int16_t wModNdx; } sfBag;
typedef struct { SFModulator sfModSrcOper; SFGenerator sfModDestOper; int16_t modAmount; SFModulator sfModAmtSrcOper;
				 SFTransform sfModTransOper; } sfModItem;
typedef struct { u_int8_t byLo; u_int8_t byHi; } rangesType;
Q_DECLARE_METATYPE(rangesType)
typedef union { rangesType ranges; int16_t shAmount; u_int16_t wAmount; } genAmountType;
typedef struct { SFGenerator sfGenOper; genAmountType genAmount; } sfGenItem;
typedef struct { QString achInstName; u_int16_t wInstBagNdx; } sfInst;
typedef struct { QByteArray achSampleName; u_int32_t dwStart; u_int32_t dwEnd; u_int32_t dwStartLoop; u_int32_t dwEndLoop;
				 u_int32_t dwEndSamp; u_int32_t dwSampleRate; u_int8_t byOriginalPitch; int8_t chPitchCorrection;
				 u_int16_t wSampleLink; u_int32_t index; u_int16_t origIndex; SFSampleLink sfSampleType; } sfSample;
typedef struct { char *achSampleName; u_int32_t dwStart; u_int32_t dwEnd; u_int32_t dwStartLoop; u_int32_t dwEndLoop; u_int32_t dwSampleRate;
				 u_int8_t byOriginalPitch; int8_t chPitchCorrection; u_int16_t wSampleLink; SFSampleLink sfSampleType; } sfSampleItem;
typedef struct { u_int16_t wMajor; u_int16_t wMinor; } sfVersionTag;
typedef struct { u_int16_t low; u_int16_t high; } Range;
typedef struct { u_int8_t low; u_int8_t mid; u_int8_t high; u_int8_t top; } Bytes;
typedef union { Bytes bytes; int16_t word16; int32_t word32; } shWord;
typedef enum { success, pNdxNonMonotic, pbagCountBad, pbagGenNdxNonMonotic, pbagModNdxNonMonotonic, pbagGenCountBad, pbagModCountBad,
			   iNdxNonMonotonic, ibagCountBad, ibagGenNdxNonMonotonic, ibagModNdxNonMonotonic, ibagGenCountBad, ibagModCountBad, badFileName,
			   riffChunkTooLarge, riffChunkTooSmall, ifilMissing, isngMissing, INAMMissing, ifilBadLength, phdrChunkBad, pbagChunkBad,
			   pmodChunkBad, pgenChunkBad, instChunkBad, ibagChunkBad, imodChunkBad, igenChunkBad, shdrChunkBad, fileBroken
			 } violations;
typedef struct { u_int8_t preset; QString *name; } presetItem;

#endif // SFLIB_GLOBAL_H
