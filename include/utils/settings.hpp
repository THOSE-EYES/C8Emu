/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

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