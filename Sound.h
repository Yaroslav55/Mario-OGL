#pragma once

#include <bass.h>

class Sound
{
public:

	int init();
	int play(char *soundName);
	int clean();
	int setVolume(float volume);
private:
	HSTREAM m_stream;
	boolean m_playSound = true;
	float m_volume = 0.3;
};