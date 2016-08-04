#ifndef LETOUINT_H
#define LETOUINT_H

#include <QByteArray>

class LEtoUINT32 {
public:
	LEtoUINT32(QByteArray ba);
	u_int32_t uint32(void) { return _val; }
private:
	u_int32_t _val;
};

#endif // LETOUINT_H
