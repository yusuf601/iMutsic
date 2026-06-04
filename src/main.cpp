
#include "../include/musicPlayer.h"
#include "../include/playlist_manager.hpp"
int main(int argc, const char* argv[]) {
    MusicPlayer musicPlayer;
    Playlist_Manager manager;

    musicPlayer.addSong(0, "meme vine-boom", "audio_files/vine-boom.wav");
    musicPlayer.addSong(1, "meme fahh", "audio_files/fahhh.mp3");
    musicPlayer.addSong(2, "meme heehee", "audio_files/heehee.mp3");

    musicPlayer.currentPlay();
    for(auto it = manager.begin();it != manager.end();++it){
        musicPlayer.loopingPlayback();
    }
    return 0;
}
