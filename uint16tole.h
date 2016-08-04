#ifndef UINT16TOLE_H
#define UINT16TOLE_H

#include <QByteArray>

class UINT16toLE {
public:
	UINT16toLE(u_int16_t val);
	QByteArray parsed(void) { return _val; }
private:
	QByteArray _val;
};

#endif // UINT16TOLE_H
