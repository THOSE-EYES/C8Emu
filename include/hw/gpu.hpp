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
#include <array>
#include <cstdint>

namespace application {
	namespace hw {
		/**
		 * 
		 */
		class GPU {
		public:
			using Point = std::array<uint16_t, 2>;
		public:
			/**
			 * Constructor
			 */
			GPU();

		public:
			/**
			 * Set the point in the buffer
			 * @param point the point to set
			 * @param value the value of the point to set
			 */
			void set(const Point& point, const bool& value);

			/**
			 * Get the point from the buffer
			 * @param point the point to get
			 * @return value of the point in the buffer
			 */
			bool get(const Point& point) const;
		};
	} // namespace hw
} // namespace application