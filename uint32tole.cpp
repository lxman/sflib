#include "uint32tole.h"

UINT32toLE::UINT32toLE(u_int32_t val) {
	_val.append((val & 0xFF));
	_val.append((val & 0xFF00) / 0x100);
	_val.append((val & 0xFF0000) / 0x10000);
	_val.append((val & 0xFF000000) / 0x1000000);
}

