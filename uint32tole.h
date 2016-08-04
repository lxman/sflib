#ifndef UINTTOLE_H
#define UINTTOLE_H

#include <QByteArray>

class UINT32toLE {
public:
	UINT32toLE(u_int32_t val);
	QByteArray parsed(void) { return _val; }
private:
	QByteArray _val;
};

#endif // UINTTOLE_H
