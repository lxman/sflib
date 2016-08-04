#ifndef SLTRANSLATOR_H
#define SLTRANSLATOR_H

#include <QMap>

class SLTranslator {
public:
	SLTranslator();
	QString translated(int ID) { return _samplelink.value(ID); }
private:
	QMap<int, QString> _samplelink;
};

#endif // SLTRANSLATOR_H
