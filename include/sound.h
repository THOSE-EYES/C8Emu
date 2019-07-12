#pragma once

class SoundPlayer {
private:
	SoundPlayer();
	~SoundPlayer();
public:
	static SoundPlayer* createInstance(char api);

	virtual void playBuzzer() = 0;
	virtual void stop() = 0;
};

class OpenAL : public SoundPlayer {
private:


public:
	OpenAL();
	~OpenAL();

	void playBuzzer();
	void stop();
}