
#include "musicPlayer.h"
#include <cstdio>

int main(int argc, const char* argv[]) {
    MusicPlayer musicPlayer;

    musicPlayer.addSong("meme vine-boom", "audio_files/vine-boom.wav");
    musicPlayer.addSong("onesevenbeatxs", "audio_files/onesevenbeatxs.mp3");
    musicPlayer.currentPlay();
    musicPlayer.nextPlay();
    musicPlayer.prevPlay();

    return 0;
}
