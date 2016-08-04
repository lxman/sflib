#include "sltranslator.h"

SLTranslator::SLTranslator() {
	_samplelink.insert(1, "mono");
	_samplelink.insert(2, "rightSample");
	_samplelink.insert(4, "leftSample");
	_samplelink.insert(8, "linkedSample");
	_samplelink.insert(0x8001, "RomMonoSample");
	_samplelink.insert(0x8002, "RomRightSample");
	_samplelink.insert(0x8004, "RomLeftSample");
	_samplelink.insert(0x8008, "RomLinkedSample");
}

