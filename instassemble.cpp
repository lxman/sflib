#include "instassemble.h"

InstAssemble::InstAssemble(sfInst *i) {
	_assembled.append(i->achInstName);
	while(_assembled.length() < 20) _assembled.append('\0');
	if(_assembled.length() > 20) _assembled.truncate(20);
	_assembled.append(UINT16toLE(i->wInstBagNdx).parsed());
}

