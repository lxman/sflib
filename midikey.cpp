#include "midikey.h"

MidiKey::MidiKey(u_int8_t i) {
	int octave;
	u_int8_t key;
	_root_keys.insert(60, "C");
	_root_keys.insert(61, "C#");
	_root_keys.insert(62, "D");
	_root_keys.insert(63, "D#");
	_root_keys.insert(64, "E");
	_root_keys.insert(65, "F");
	_root_keys.insert(66, "F#");
	_root_keys.insert(67, "G");
	_root_keys.insert(68, "G#");
	_root_keys.insert(69, "A");
	_root_keys.insert(70, "A#");
	_root_keys.insert(71, "B");
	if(i > 127) i = 60;
	key = (i % 12) + 60;
	octave = (i / 12) - 2;
	_translated = _root_keys.value(key) + " " + QString::number(octave);
}

