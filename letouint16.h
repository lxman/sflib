#ifndef LETOUINT16_H
#define LETOUINT16_H

#include <QByteArray>

class LEtoUINT16 {
public:
	LEtoUINT16(QByteArray ba);
	u_int16_t uint16(void) { return _val; }
private:
	u_int16_t _val;
};

#endif // LETOUINT16_H
