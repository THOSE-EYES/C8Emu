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