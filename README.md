# sflib
A library based on Qt that handles sf2 (soundfont) libraries.

The soundfont 2.0 specification is a freely available specification which can be downloaded here: http://freepats.zenvoid.org/sf2/sfspec24.pdf <http://freepats.zenvoid.org/sf2/sfspec24.pdf>

sf2 files are files which contain sound samples, most usually in wav format. They may contain anywhere from 1 to 100’s of different samples for 1 to 100’s of different kinds of instruments. A large variety of sf2 files are available for free on the Internet, and can be downloaded and played with free software (e.g. linuxsamplesr, synthfont, fluidsynth). This library will allow you to access the individual samples within an sf2 library containing multiple samples and repackage them to your liking. It uses Qt containers (QByteArray, QString, QMap, etc.) for information exchange between the host application and the sf2 package. This makes querying and unpacking/repacking a very trivial experience for anyone familiar with Qt.
