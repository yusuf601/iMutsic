#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "utils.h"

class MusicPlayer {
   public:
    MusicPlayer();
    ~MusicPlayer();
    void currentPlay();
    void nextPlay();
    void prevPlay();
    void addSong(std::string songTitle, std::string filepath);
    void playList();
    static void data_callback(ma_device* pDevice, void* pOutput,
                              const void* pInput, ma_uint32 frameCount);

   private:
    audio_song* head;
    audio_song* current;
    audio_song* tail;
    ma_decoder pDecoder;
    ma_device pDevice;
    bool isPlayed;
};

#endif  // !MUSIC_PLAYER_H
