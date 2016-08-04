#include "mainchunk.h"
#include "letouint32.h"
#include <QDebug>

MainChunk::MainChunk(QByteArray ba) {
	_ID = ba.left(4);
	if(_ID == "RIFF") {
		ba.remove(0, 4);
		u_int32_t size = LEtoUINT32(ba.left(4)).uint32();
		ba.remove(0, 4);
		if(size > (uint)ba.length()) _error = riffChunkTooLarge;
		if(size < (uint)ba.length()) _error = riffChunkTooSmall;
		if(_error == riffChunkTooSmall) return;
		_main = ba.left(size);
		ba.remove(0, size);
		if(ba.length() > 0) _leftover = ba;
		ba.clear();
		_tag = _main.left(4);
		if(_tag == "sfbk") {
			_main.remove(0, 4);
			_tag.clear();
			_tag = _main.left(4);
			if(_tag == "LIST") {
				_main.remove(0, 4);
				size = LEtoUINT32(_main.left(4)).uint32();
				_main.remove(0, 4);
				if((uint)_main.length() < size) {
					_error = fileBroken;
					return;
				}
				_list1.append(_main.data(), size);
				_main.remove(0, size);
				_tag.clear();
				_tag = _main.left(4);
				if(_tag == "LIST") {
					_main.remove(0, 4);
					size = LEtoUINT32(_main.left(4)).uint32();
					_main.remove(0, 4);
					if((uint)_main.length() < size) {
						_error = fileBroken;
						return;
					}
					_list2.reserve(size);
					_list2.append(_main.data(), size);
					_main.remove(0, size);
					_tag.clear();
					_tag = _main.left(4);
					if(_tag == "LIST") {
						_main.remove(0, 4);
						size = LEtoUINT32(_main.left(4)).uint32();
						_main.remove(0, 4);
						if((uint)_main.length() < size) {
							_error = fileBroken;
							return;
						}
						_list3.append(_main.data(), size);
						_main.remove(0, size);
					} else _error = fileBroken;
				} else _error = fileBroken;
			} else _error = fileBroken;
		} else _error = fileBroken;
	} else _error = fileBroken;
}

void MainChunk::clear(void) {
	_leftover.clear();
	_main.clear();
	_list1.clear();
	_list2.clear();
	_list3.clear();
}
