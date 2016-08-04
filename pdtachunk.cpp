#include "pdtachunk.h"
#include "letouint32.h"
#include <QDebug>

PdtaChunk::PdtaChunk(QByteArray ba) {
	QString tag = ba.left(4);
	if(tag == "pdta") {
		ba.remove(0, 4);
		tag = _getTag(ba);
		if(tag == "phdr") {
			_phdr_chunk = _getChunk(ba);
			if((_phdr_chunk.length() < 76) ||
					((_phdr_chunk.length() % 38) != 0)) _error.addError(phdrChunkBad);
			tag = _getTag(ba);
			if(tag == "pbag") {
				_pbag_chunk = _getChunk(ba);
				if((_pbag_chunk.length() < 8) ||
						((_pbag_chunk.length() % 4) != 0)) _error.addError(pbagChunkBad);
				tag = _getTag(ba);
				if(tag == "pmod") {
					_pmod_chunk = _getChunk(ba);
					if((_pmod_chunk.length() < 10) ||
							((_pmod_chunk.length() % 10) != 0)) _error.addError(pmodChunkBad);
					tag = _getTag(ba);
					if(tag == "pgen") {
						_pgen_chunk = _getChunk(ba);
						if((_pgen_chunk.length() < 4) ||
								((_pgen_chunk.length() % 4) != 0)) _error.addError(pgenChunkBad);
						tag = _getTag(ba);
						if(tag == "inst") {
							_inst_chunk = _getChunk(ba);
							if((_inst_chunk.length() < 44) ||
									((_inst_chunk.length() % 22) != 0)) _error.addError(instChunkBad);
							tag = _getTag(ba);
							if(tag == "ibag") {
								_ibag_chunk = _getChunk(ba);
								if((_ibag_chunk.length() < 8) ||
										((_ibag_chunk.length() % 4) != 0)) _error.addError(ibagChunkBad);
								tag = _getTag(ba);
								if(tag == "imod") {
									_imod_chunk = _getChunk(ba);
									if((_imod_chunk.length() < 10) ||
											((_imod_chunk.length() % 10) != 0)) _error.addError(imodChunkBad);
									tag = _getTag(ba);
									if(tag == "igen") {
										_igen_chunk = _getChunk(ba);
										if((_igen_chunk.length() < 4) ||
												((_igen_chunk.length() % 4) != 0)) _error.addError(igenChunkBad);
										tag = _getTag(ba);
										if(tag == "shdr") {
											_shdr_chunk = _getChunk(ba);
											if((_shdr_chunk.length() < 92) ||
													((_shdr_chunk.length() % 46) != 0)) _error.addError(shdrChunkBad);
											else _error.addError(success);
										} else _error.addError(fileBroken);
									} else _error.addError(fileBroken);
								} else _error.addError(fileBroken);
							} else _error.addError(fileBroken);
						} else _error.addError(fileBroken);
					} else _error.addError(fileBroken);
				} else _error.addError(fileBroken);
			} else _error.addError(fileBroken);
		} else _error.addError(fileBroken);
	} else _error.addError(fileBroken);
}

QByteArray PdtaChunk::_getChunk(QByteArray &ba) {
	u_int32_t size = LEtoUINT32(ba.left(4)).uint32();
	ba.remove(0, 4);
	QByteArray chunk = ba.left(size);
	ba.remove(0, size);
	return chunk;
}

QString PdtaChunk::_getTag(QByteArray &ba) {
	QString tag = ba.left(4);
	ba.remove(0, 4);
	return tag;
}
