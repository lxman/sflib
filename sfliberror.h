#ifndef SFLIBERROR_H
#define SFLIBERROR_H

#include <QList>
#include "sflib_global.h"

class SflibError {
public:
	SflibError();
	void addError(violations v) { _errors.append(v); }
	void addError(SflibError e) { _errors.append(e.errors()); }
	void clearErrors(void) { _errors.clear(); }
	QList<violations> errors(void) { return _errors; }
private:
	QList<violations> _errors;
};

#endif // SFLIBERROR_H
