#pragma once

#include "exceptions.h"

class Window {
protected :
	//Some stuff to inherit 
	
public :
	//Some stuff to inherit 
};

class MainWindow final : public Window {
private:
	MainWindow();

public:
	~MainWindow();

	static MainWindow* window;	//Check if it's possible to leave this variable in the Window class
};