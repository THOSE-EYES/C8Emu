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