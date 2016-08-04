#ifndef GENLISTTRANSLATOR_H
#define GENLISTTRANSLATOR_H

#include <QMap>

class GenListTranslator {
public:
	GenListTranslator();
	QString translated(int ID);
private:
	QMap<int, QString> _gen_list;
};

#endif // GENLISTTRANSLATOR_H
