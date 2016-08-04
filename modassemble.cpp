#include "modassemble.h"

ModAssemble::ModAssemble(sfModItem *m) {
	_assembled.append(UINT16toLE(m->sfModSrcOper).parsed());
	_assembled.append(UINT16toLE(m->sfModDestOper).parsed());
	_assembled.append(UINT16toLE(m->modAmount).parsed());
	_assembled.append(UINT16toLE(m->sfModAmtSrcOper).parsed());
	_assembled.append(UINT16toLE(m->sfModTransOper).parsed());
}

