#include "genitem.h"
#include "pgenselector.h"

GenItem::GenItem() {}

sfGenItem *GenItem::generator(void) {
	_generator->sfGenOper = _sfGenOper;
	_generator->genAmount.wAmount = _genAmount.wAmount;
	return _generator;
}
