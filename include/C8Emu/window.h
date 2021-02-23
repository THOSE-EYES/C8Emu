#include <array>
#include <string>
#include <stdexcept>
#include <cstdint>

#include "global.hpp"

/**
 * Superclass for windows classes
 */
class Window {
protected:
	std::string title_;
	std::array<uint16_t, 2> size_;

public:
	/**
	 * Constructor
	 * @param title new title of the window
	 * @param size new size of the window
	 */
	Window(std::string title, std::array<uint16_t, 2> size);

	/**
	 * Constructor
	 * @param title new title of the window
	 */
	Window(std::string title);

	/**
	 * Virtual function for drawing a window
	 */
	virtual void create() = 0;

	/**
	 * Setter fo the title
	 * @param title new title of the window
	 */
	void setTitle(std::string title);

	/**
	 * Getter fo the title
	 * @return the title of the window
	 */
	std::string getTitle(void) const noexcept;

	/**
	 * Setter for the size of the window
	 * @param size new size of the window
	 */
	void setSize(std::array<uint16_t, 2> size);

	/**
	 * Getter for the size of the window
	 * @return size of the window
	 */
	std::array<uint16_t, 2> getSize(void) const noexcept;
};