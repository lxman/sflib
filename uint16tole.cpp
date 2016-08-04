#include "uint16tole.h"

UINT16toLE::UINT16toLE(u_int16_t val) {
	_val.append((val & 0xFF));
	_val.append((val & 0xFF00) / 0x100);
}

