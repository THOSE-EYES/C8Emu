#pragma once

// Include C/C++ STL headers
#include <fstream>

// Include Boost headers
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

// Include project headers
#include "constants.hpp"

struct Settings final {
public:
	//Window section
	unsigned short windowHeight;
	unsigned short windowWidth;
	
	bool fullscreen;

	//Emulator section

	//Game section
};

namespace boost {
	namespace serialization {
		template <class Archive>
		void serialize(Archive& ar, Settings& instance, const unsigned int version) {
			//Serializing some variables using "&" on the Boost archive
			ar & instance.fullscreen;
		}
	}
}

void save(Settings*);	//Serialize

Settings* load();	//Deserialize