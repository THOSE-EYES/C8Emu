#pragma once

#include "exceptions.h"

#include <AL/al.h>
#include <AL/alc.h>

#include <thread>

#define FILE "music/track.wav"
#define OAL 0	//OpenAL

class AbstractPlayer {
public:
	static AbstractPlayer* createInstance(unsigned char);

	virtual void playBuzzer() = 0;
	virtual void stop() = 0;
};

//Only *.waw files. Use Vorbis to decode *.mp3
class OpenAL final: public AbstractPlayer {
private:
	friend class AbstractPlayer;

	ALCdevice* device = nullptr;
	ALCcontext* context = nullptr;
	ALuint source;

	std::thread thread;

	OpenAL();

public:
	~OpenAL();

	void playBuzzer() override;
	void stop() override;
};