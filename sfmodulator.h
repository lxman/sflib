#ifndef SFMODULATOR_H
#define SFMODULATOR_H

#include <QMap>
#include <QString>
#include "genlisttranslator.h"
#include "sflib_global.h"

class SfModulator {
public:
	SfModulator(sfModItem *m);
	sfModController palette(sfModSrcFrom src);
	sfModSrcCC ccVal(sfModSrcFrom src);
	sfModSrcDirection direction(sfModSrcFrom src);
	sfModSrcPolarity polarity(sfModSrcFrom src);
	sfModSrcType srcType(sfModSrcFrom src);
	sfModSrcTransform transform(void);
	int16_t modAmount(void) { return _modAmount; }
	SFGenerator modDestOper(void) { return _modDestOper; }
	QString strPalette(sfModSrcFrom src);
	QString strCCVal(sfModSrcFrom src);
	QString strDirection(sfModSrcFrom src);
	QString strPolarity(sfModSrcFrom src);
	QString strSrcType(sfModSrcFrom src);
	QString strTransform(void);
	QString strModAmount(void);
	QString strModDestOper(void);
private:
	sfModStruct *_sfModSrc, *_sfModAmtSrc;
	sfModSrcTransform _txfm;
	SFGenerator _modDestOper;
	int16_t _modAmount;
	QMap<int, QString> _ctlMapper;
};

#endif // SFMODULATOR_H
