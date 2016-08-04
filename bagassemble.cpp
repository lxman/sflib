#include "bagassemble.h"

BagAssemble::BagAssemble(sfBag *b) {
	_assembled.append(UINT16toLE(b->wGenNdx).parsed());
	_assembled.append(UINT16toLE(b->wModNdx).parsed());
}

