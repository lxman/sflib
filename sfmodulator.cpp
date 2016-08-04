#include "sfmodulator.h"

SfModulator::SfModulator(sfModItem *m) {
	_sfModSrc = new sfModStruct;
	_sfModAmtSrc = new sfModStruct;
	_sfModSrc->modController.midiPalette = (m->sfModSrcOper & 0x0E);
	_sfModSrc->cc = (sfModSrcCC)((m->sfModSrcOper & 0x80) >> 7);
	_sfModSrc->direction = (sfModSrcDirection)((m->sfModSrcOper & 0x100) >> 8);
	_sfModSrc->polarity = (sfModSrcPolarity)((m->sfModSrcOper & 0x200) >> 9);
	_sfModSrc->srcType = (sfModSrcType)((m->sfModSrcOper & 0xFC00) >> 10);
	_sfModAmtSrc->modController.midiPalette = (m->sfModAmtSrcOper & 0x0E);
	_sfModAmtSrc->cc = (sfModSrcCC)((m->sfModAmtSrcOper & 0x80) >> 7);
	_sfModAmtSrc->direction = (sfModSrcDirection)((m->sfModAmtSrcOper & 0x100) >> 8);
	_sfModAmtSrc->polarity = (sfModSrcPolarity)((m->sfModAmtSrcOper & 0x200) >> 9);
	_sfModAmtSrc->srcType = (sfModSrcType)((m->sfModAmtSrcOper & 0xFC00) >> 10);
	_txfm = (sfModSrcTransform)(m->sfModTransOper);
	_modDestOper = m->sfModDestOper;
	_modAmount = m->modAmount;
	_ctlMapper.insert(0, "none");
	_ctlMapper.insert(2, "Note-On Velocity");
	_ctlMapper.insert(3, "Note-On Key Number");
	_ctlMapper.insert(10, "Poly Pressure");
	_ctlMapper.insert(13, "Channel Pressure");
	_ctlMapper.insert(14, "Pitch Wheel");
	_ctlMapper.insert(16, "Pitch Wheel Sensitivity");
	_ctlMapper.insert(127, "Link");
}

sfModController SfModulator::palette(sfModSrcFrom src) {
	switch(src) {
		case modSource:
			return _sfModSrc->modController;
			break;
		case modAmtSource:
			return _sfModAmtSrc->modController;
			break;
		default:
			break;
	}
	return _sfModSrc->modController;
}

sfModSrcCC SfModulator::ccVal(sfModSrcFrom src) {
	switch(src) {
		case modSource:
			return _sfModSrc->cc;
			break;
		case modAmtSource:
			return _sfModAmtSrc->cc;
			break;
		default:
			break;
	}
	return _sfModSrc->cc;
}

sfModSrcDirection SfModulator::direction(sfModSrcFrom src) {
	switch(src) {
		case modSource:
			return _sfModSrc->direction;
			break;
		case modAmtSource:
			return _sfModAmtSrc->direction;
			break;
		default:
			break;
	}
	return _sfModSrc->direction;
}

sfModSrcPolarity SfModulator::polarity(sfModSrcFrom src) {
	switch(src) {
		case modSource:
			return _sfModSrc->polarity;
			break;
		case modAmtSource:
			return _sfModAmtSrc->polarity;
			break;
		default:
			break;
	}
	return _sfModSrc->polarity;
}

sfModSrcType SfModulator::srcType(sfModSrcFrom src) {
	switch(src) {
		case modSource:
			return _sfModSrc->srcType;
			break;
		case modAmtSource:
			return _sfModAmtSrc->srcType;
			break;
		default:
			break;
	}
	return _sfModSrc->srcType;
}

sfModSrcTransform SfModulator::transform() { return _txfm; }

QString SfModulator::strCCVal(sfModSrcFrom src) {
	switch(src) {
		case modSource:
			switch(_sfModSrc->cc) {
				case general:
					return "general";
					break;
				case midi:
					return "midi";
					break;
			}
			break;
		case modAmtSource:
			switch(_sfModAmtSrc->cc) {
				case general:
					return "general";
					break;
				case midi:
					return "midi";
					break;
			}
			break;
		default:
			break;
	}
	return "unknown";
}

QString SfModulator::strDirection(sfModSrcFrom src) {
	switch(src) {
		case modSource:
			switch(_sfModSrc->direction) {
				case dirFwd:
					return "forward";
					break;
				case dirRev:
					return "reverse";
					break;
			}
			break;
		case modAmtSource:
			switch(_sfModAmtSrc->direction) {
				case dirFwd:
					return "forward";
					break;
				case dirRev:
					return "reverse";
					break;
			}
			break;
		default:
			break;
	}
	return "unknown";
}

QString SfModulator::strModAmount(void) { return QString::number(_modAmount); }

QString SfModulator::strModDestOper(void) { return GenListTranslator().translated(_modDestOper); }

QString SfModulator::strPalette(sfModSrcFrom src) {
	switch(src) {
		case modSource:
			if(_sfModSrc->cc == general) {
				return _ctlMapper.value(_sfModSrc->modController.midiPalette);
			}
			if(_sfModSrc->cc == midi) {
				return "Midi controller " + QString::number(_sfModSrc->modController.midiPalette);
			}
			break;
		case modAmtSource:
			if(_sfModSrc->cc == general) {
				return _ctlMapper.value(_sfModAmtSrc->modController.midiPalette);
			}
			if(_sfModSrc->cc == midi) {
				return "Midi controller " + QString::number(_sfModAmtSrc->modController.midiPalette);
			}
			break;
		default:
			break;
	}
	return "unknown";
}

QString SfModulator::strPolarity(sfModSrcFrom src) {
	switch(src) {
		case modSource:
			switch(_sfModSrc->polarity) {
				case unipolar:
					return "unipolar";
					break;
				case bipolar:
					return "bipolar";
					break;
			}
			break;
		case modAmtSource:
			switch(_sfModAmtSrc->polarity) {
				case unipolar:
					return "unipolar";
					break;
				case bipolar:
					return "bipolar";
					break;
			}
			break;
		default:
			break;
	}
	return "unknown";
}

QString SfModulator::strSrcType(sfModSrcFrom src) {
	switch(src) {
		case modSource:
			switch(_sfModSrc->srcType) {
				case srcLinear:
					return "Linear";
					break;
				case srcConcave:
					return "Concave";
					break;
				case srcConvex:
					return "Convex";
					break;
				case srcSwitch:
					return "Switch";
					break;
			}
			break;
		case modAmtSource:
			switch(_sfModAmtSrc->srcType) {
				case srcLinear:
					return "Linear";
					break;
				case srcConcave:
					return "Concave";
					break;
				case srcConvex:
					return "Convex";
					break;
				case srcSwitch:
					return "Switch";
					break;
			}
			break;
		default:
			break;
	}
	return "unknown";
}

QString SfModulator::strTransform(void) {
	switch(_txfm) {
		case 0:
			return "Linear";
			break;
		case 2:
			return "Absolute Value";
			break;
		default:
			break;
	}
	return "unknown";
}
