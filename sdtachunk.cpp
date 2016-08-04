#include "sdtachunk.h"
#include "letouint32.h"
#include <qstring.h>
#include <stdlib.h>
#include <QDebug>

SdtaChunk::SdtaChunk(QByteArray ba) {
	u_int64_t array_size_16, array_size_24 = 0;
	_tag = ba.left(4);
	if(_tag == "sdta") {
		ba.remove(0, 4);
		int index = ba.indexOf("sm24");
		if(index != -1) {
			_data24.reserve(ba.length() - index);
			_data24 = ba.right(ba.length() - index);
			ba.chop(index - 1);
			_tag = _data24.left(4);
			if(_tag == "sm24") {
				_data24.remove(0, 4);
				array_size_24 = LEtoUINT32(ba.left(4)).uint32();
				_data24.remove(0, 4);
			}
		}
		_tag = ba.left(4);
		if(_tag == "smpl") {
			ba.remove(0, 4);
			array_size_16 = LEtoUINT32(ba.left(4)).uint32();
			ba.remove(0, 4);
			_data16.reserve(array_size_16);
			_data16 = ba;
		}
		if((u_int64_t)((_data16.length() + 1) / 2) != array_size_24) _data24.clear();
	}
}

QList<int32_t> SdtaChunk::subSample(int start, int end) {
	if(_samples.contains(start)) return _samples.value(start);
	int len = (end - start);
	_retvalue.clear();
	QByteArray tmp;
	tmp.reserve((len * 2));
	tmp = _data16.mid((start * 2), (len * 2));
	shWord word;
	word.bytes.high = 0;
	word.bytes.top = 0;
	QByteArray::const_iterator it = tmp.constBegin();
	if(_data24.length() == 0) {
		while(it < tmp.constEnd()) {
			word.bytes.low = *it++;
			word.bytes.mid = *it++;
			_retvalue.append(word.word16);
		}
	} else {
		QByteArray tmp2;
		tmp2.reserve(len);
		tmp2 = _data24.mid(start, len);
		QByteArray::const_iterator it2 = tmp2.constBegin();
		while(it < tmp.constEnd()) {
			word.bytes.low = *it2++;
			word.bytes.mid = *it++;
			word.bytes.high = *it++;
			_retvalue.append(word.word32);
		}
	}
	if(!_samples.keys().contains(start)) _samples.insert(start, _retvalue);
	return _retvalue;
}

QByteArray SdtaChunk::sample(int start, int end) {
	return _data16.mid((start * 2), ((end * 2) - (start * 2)));
}
