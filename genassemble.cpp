#include "genassemble.h"

GenAssemble::GenAssemble(GenItem *gen) {
	_assembled.append(UINT16toLE(gen->sfGenOper()).parsed());
	_assembled.append(UINT16toLE(gen->genAmount().wAmount).parsed());
}

