#include "phdrassemble.h"

PHDRAssemble::PHDRAssemble(sfPresetHeader *p) {
	_assembled.append(p->achPresetName);
	while(_assembled.length() < 20) _assembled.append('\0');
	if(_assembled.length() > 20) _assembled.truncate(20);
	_assembled.append(UINT16toLE(p->wPreset).parsed());
	_assembled.append(UINT16toLE(p->wBank).parsed());
	_assembled.append(UINT16toLE(p->wPresetBagNdx).parsed());
	_assembled.append(UINT32toLE(p->dwLibrary).parsed());
	_assembled.append(UINT32toLE(p->dwGenre).parsed());
	_assembled.append(UINT32toLE(p->dwMorphology).parsed());
}

