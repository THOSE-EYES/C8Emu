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

#include "ui/window.hpp"

using application::exceptions::ui::InvalidTitleException;

namespace application {
	namespace ui {
		Window::Window(const std::string& title, const Size& size) {
			set_title(title);
			set_size(size);
		}

		void Window::set_title(const std::string& value) {
			if (value.empty() or 
				value.size() >= constants::window::max_title_size)
				throw InvalidTitleException(value);

			title_ = value;
		}

		std::string Window::get_title(void) const noexcept {
			return title_;
		}

		void Window::set_size(const Size& value) {
			size_ = value;
		}

		Window::Size Window::get_size(void) const noexcept {
			return size_;
		}
	} // namespace ui
} // namespace application