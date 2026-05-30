
#include "musicPlayer.h"
#include <cstdio>

int main(int argc, const char* argv[]) {
    MusicPlayer musicPlayer;
    bool isRunning = true;

    musicPlayer.addSong(0, "meme vine-boom", "audio_files/vine-boom.wav");
    musicPlayer.addSong(1, "meme fahh", "audio_files/fahhh.mp3");
    musicPlayer.addSong(2, "meme heehee", "audio_files/heehee.mp3");

    musicPlayer.currentPlay();
    while (isRunning) {
        musicPlayer.loopingPlayback();
    }

    return 0;
}
