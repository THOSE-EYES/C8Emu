#include "settings.h"

void save(Settings* instance) {
	std::fstream file;
	file.open(SETTINGS_FILE, std::fstream::trunc | std::fstream::out);

	if(file.is_open()) {
		boost::archive::text_oarchive archive(file);
		archive << *instance;

		file.close();
	}
	else {
		//Throw an exception
	}
}

Settings* load() {
	std::fstream file;
	file.open(SETTINGS_FILE, std::fstream::trunc | std::fstream::out);

	if(file.is_open()) {
		Settings* instance = new Settings();

		boost::archive::text_oarchive archive(file);
		archive << *instance;

		file.close();

		return instance;
	}
	else {
		//Throw an exception
	}
}