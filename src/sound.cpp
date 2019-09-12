#include "sound.h"

AbstractPlayer* AbstractPlayer::createInstance(unsigned char api) {
	//Declaring or assigning a value to variables
	AbstractPlayer* player = nullptr;

	//Check the choice
	switch(api) {
		//OpenAL
		case OAL :
			player = new OpenAL();

			break;

		default :
			//Throw an exception
			throw Exception(SLIBCHERR);
	}

	return player;
}

OpenAL::OpenAL() {
	//Open the default device
	device = alcOpenDevice(NULL);
	
	//Check if the device is opened
	if (!device) {
        //Handle errors

	}

	//Reset the error stack
	alGetError();

	//Create the context
	context = alcCreateContext(device, NULL);
	
	if (!alcMakeContextCurrent(context)) {
        //alGetError() to check errors

	}
}

OpenAL::~OpenAL() {
	
}

void OpenAL::playBuzzer() {
	//Connect a source and a device using std::thread
	/*
	thread = std::thread([] {
		while (true) {
			alSourcePlay(source);
		}
	});
	*/
}

void OpenAL::stop() {
	//Detach the thread to stop playing a soundtrack
	thread.detach();
}