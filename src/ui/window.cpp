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