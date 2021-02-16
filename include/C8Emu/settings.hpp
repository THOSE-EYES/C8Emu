#pragma once

#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "exceptions.hpp"

#define SETTINGS_FILE "settings.dat"

struct Settings final{
	//Window section
	unsigned short windowHeight;
	unsigned short windowWidth;
	
	bool isFullScreen;

	//Emulator section

	//Game section
};

namespace boost {
	namespace serialization {
		template <class Archive>
		void serialize(Archive& ar, Settings& instance, const unsigned int version) {
			//Serializing some variables using "&" on the Boost archive
			ar & instance.isFullScreen;
		}
	}
}

void save(Settings*);	//Serialize

Settings* load();	//Deserialize