#include "window.h"

Window::Window(std::string title, std::array<unsigned short, 2> size) {
	setTitle(title);
	setSize(size);
}

Window::Window(std::string title) {
	size_[0] = constants::window::MIN_WINDOW_WIDTH;
	size_[1] = constants::window::MIN_WINDOW_HEIGHT;

	setTitle(title);
}

void Window::setTitle(std::string title) {
	if (
		title.size() == 0 || 
		title.size() >= constants::window::MAX_TITLE_SIZE
		)
		throw new std::invalid_argument("Title is not correct. Decrease the size to" + 
										std::to_string(constants::window::MAX_TITLE_SIZE));

	title_ = title;
}

std::string Window::getTitle(void) const noexcept {
	return title_;
}

void Window::setSize(std::array<uint16_t, 2> size) {
	size_ = size;
}

std::array<uint16_t, 2> Window::getSize(void) const noexcept {
	return size_;
}