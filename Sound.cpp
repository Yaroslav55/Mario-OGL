#include "stdafx.h"
#include "Sound.h"

int Sound::init() {

	if (HIWORD(BASS_GetVersion()) != BASSVERSION) {
		MessageBox(NULL, "Bass version error.", NULL, 0);
		return -1;
	}
	if (!BASS_Init(-1, 22050, BASS_DEVICE_3D, 0, NULL)) {
		MessageBox(NULL, "BASS.. Error", NULL, 0);
		printf("BASS.. Error\n");
		return -1;
	}
	return 0;
}

int Sound::play(char *soundName) {
	if (!(m_stream = BASS_StreamCreateFile(FALSE, soundName, 0, 0, 0))) {
		printf("Stream error file: %s .. Error", soundName);
		return -1;
	}
	BASS_ChannelSetAttribute(m_stream, BASS_ATTRIB_VOL, m_volume);
	BASS_ChannelPlay(m_stream, m_playSound);
	return 0;
}

int Sound::clean() {
	if ((m_stream) && (!BASS_ChannelIsActive(m_stream)))
	{
		BASS_StreamFree(m_stream);
	}
	return 0;
}

int Sound::setVolume(float volume) {
	m_volume = volume;
	return 0;
}