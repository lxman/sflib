#include "shdrassemble.h"

SHDRAssemble::SHDRAssemble(sfSample *s) {
	_assembled.append(s->achSampleName);
	while(_assembled.length() < 20) _assembled.append('\0');
	if(_assembled.length() > 20) _assembled.truncate(20);
	_assembled.append(UINT32toLE(s->dwStart).parsed());
	_assembled.append(UINT32toLE(s->dwEnd).parsed());
	_assembled.append(UINT32toLE(s->dwStartLoop).parsed());
	_assembled.append(UINT32toLE(s->dwEndLoop).parsed());
	_assembled.append(UINT32toLE(s->dwSampleRate).parsed());
	_assembled.append(s->byOriginalPitch);
	_assembled.append(s->chPitchCorrection);
	_assembled.append(UINT16toLE(s->wSampleLink).parsed());
	_assembled.append(UINT16toLE(s->sfSampleType).parsed());
}

