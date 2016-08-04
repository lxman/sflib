#ifndef GENLIST_H
#define GENLIST_H

#include <QVariant>
#include <QString>
#include "genlisttranslator.h"
#include "sflib_global.h"

class GenItem {
public:
	GenItem();
	void setGenerator(SFGenerator gen) { _sfGenOper = gen; }
	void setGenAmount(genAmountType amt) { _genAmount = amt; }
	SFGenerator sfGenOper(void) { return _sfGenOper; }
	genAmountType genAmount(void) { return _genAmount; }
	sfGenItem *generator(void);
private:
	SFGenerator _sfGenOper;
	genAmountType _genAmount;
	sfGenItem *_generator = new sfGenItem();
};

#endif // GENLIST_H
