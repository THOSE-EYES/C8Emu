#pragma once

//C or C++ Library
#include <fstream>

//Boost Library
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#define SETTINGS_FILE "settings.dat"

struct Settings {
	//Window section
	bool isFullScreen;

	//Emulator section

	//
};

namespace boost {
	namespace serialization {
		template <class Archive>
		void serialize(Archive& ar, Settings& instance, const unsigned int version) {
			//Serializing some variables using "&" on the Boost archive
			ar & instance.isFullscreen;
		}

	}
}

void save(Settings* instance);	//

Settings* load();