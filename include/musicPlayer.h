#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "utils.h"
#include "playlist_manager.hpp"
class MusicPlayer {
   public:
   Playlist_Manager manager;
   public:
    void currentPlay();
    void nextPlay();
    void prevPlay();
    void addSong(int idlist, std::string songTitle, std::string filepath);
    void playList();
    void loopingPlayback();
    static void data_callback(ma_device* pDevice, void* pOutput,
                              const void* pInput, ma_uint32 frameCount);
  };

#endif  // !MUSIC_PLAYER_H
