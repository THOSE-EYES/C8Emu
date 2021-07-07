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

// Include C++/C STL headers
#include <array>
#include <string>
#include <stdexcept>
#include <cstdint>

// Include project headers
#include "exceptions.hpp"
#include "constants.hpp"

namespace application {
	namespace ui {
		/**
		 * Superclass for windows classes
		 */
		class Window {
		public:
			using Size = std::array<uint16_t, 2>;

		public:
			/**
			 * Constructor
			 * @param title new title of the window
			 * @param size new size of the window
			 */
			Window(const std::string& title, 
				const Size& size = {constants::window::min_width, 
									constants::window::min_height});

		public:
			/**
			 * Virtual function for drawing a window
			 */
			virtual void create() = 0;

			/**
			 * Setter fo the title
			 * @param value new title of the window
			 */
			void set_title(const std::string& value);

			/**
			 * Getter fo the title
			 * @return the title of the window
			 */
			std::string get_title() const noexcept;

			/**
			 * Setter for the size of the window
			 * @param value new size of the window
			 */
			void set_size(const Size& value);

			/**
			 * Getter for the size of the window
			 * @return size of the window
			 */
			Size get_size() const noexcept;

		private:
			std::string	title_;
			Size 		size_;
		};
	} // namespace ui
} // namespace application