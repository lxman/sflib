#ifndef LETOINT16_H
#define LETOINT16_H

#include <QByteArray>

class LEtoINT16 {
public:
	LEtoINT16(QByteArray ba);
	int16_t int16(void) { return _val; }
private:
	int16_t _val;
};

#endif // LETOINT16_H
