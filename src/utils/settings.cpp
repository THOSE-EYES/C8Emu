#include "utils/settings.hpp"

void save(Settings* instance) {
	//Open a file
	std::fstream file;
	file.open(constants::utils::settings_file, std::fstream::trunc | std::fstream::out);

	//Check if the fie is opened
	if(file.is_open()) {
		//Serialize
		boost::archive::text_oarchive archive(file);
		archive << *instance;

		//Close the file
		file.close();
	}
	else {
		//Throw an exception
		throw new std::runtime_error("Could not open file");
	}
}

Settings* load() {
	//Open a file
	std::fstream file;
	file.open(constants::utils::settings_file, std::fstream::trunc | std::fstream::out);

	//Check if the fie is opened
	if(file.is_open()) {
		//Deseerialize
		Settings* instance = new Settings();

		boost::archive::text_oarchive archive(file);	//Close the filehive archive(file);
		archive << *instance;

		//Close the file
		file.close();

		return instance;
	}
	else {
		//Throw an exception
		throw new std::runtime_error("Could not open file");
	}
}