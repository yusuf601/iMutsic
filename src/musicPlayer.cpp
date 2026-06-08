#include "../include/musicPlayer.h"
#include "../include/playlist_manager.hpp"
#include "utils.h"
#include <cstdio>
#include <cstdlib>
MusicPlayer::MusicPlayer(): isPlayed(false){}

MusicPlayer::~MusicPlayer(){
    if (isPlayed) {
        ma_device_uninit(&pDevice);
        ma_decoder_uninit(&pDecoder);
    }
}

void MusicPlayer::addSong(int idlist, std::string songTitle,std::string filepath) {
    printf("initialize newsong to all nodes\n");
    audio_song* song = new audio_song(idlist,songTitle,filepath);
    manager.push_back(song);
    
    printf("push the filepath: %s song title: %s\n", songTitle.c_str(),filepath.c_str());
}

void MusicPlayer::data_callback(ma_device* pDevice, void* pOutput,const void* pInput, ma_uint32 frameCount) {
    MusicPlayer* player = (MusicPlayer*)pDevice->pUserData;

    if (player == nullptr || !player->isPlayed) {
        return;
    }

    ma_uint64 framesRead = 0;
    if (ma_decoder_read_pcm_frames(&player->pDecoder, pOutput, frameCount,&framesRead) && framesRead == frameCount) {
        ma_decoder_seek_to_pcm_frame(&player->pDecoder, framesRead);
        player->endOfsong = true;
    }
    (void)pInput;
}

void MusicPlayer::currentPlay() {
    if (manager.get_current() == nullptr) {
        return;
    }
    if (isPlayed) {
        ma_device_uninit(&pDevice);
        ma_decoder_uninit(&pDecoder);
    }

    if (ma_decoder_init_file(manager.get_current()->filepath.c_str(), NULL, &pDecoder) !=
        MA_SUCCESS) {
        printf("\nERROR init filepath: %s", manager.get_current()->filepath.c_str());
        return;
    }

    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format = pDecoder.outputFormat;
    config.playback.channels = pDecoder.outputChannels;
    config.sampleRate = pDecoder.outputSampleRate;

    config.dataCallback = data_callback;
    config.pUserData = this;

    if (ma_device_init(NULL, &config, &pDevice) != MA_SUCCESS) {
        printf("ERROR init device\n");
        return;
    }

    ma_device_start(&pDevice);
    isPlayed = true;
    printf("Playing the song: %s\n", manager.get_current()->songTitle.c_str());
}

void MusicPlayer::nextPlay() {
    if(manager.is_end())endOfsong = true;
    manager.next();
    currentPlay();
}

void MusicPlayer::prevPlay() {
    if (manager.get_current() == nullptr && manager.get_current()->prev == nullptr) {
        printf("\n tidak ada playlist di prev");
        return;
    }
    manager.prev();
}

void MusicPlayer::playList() {
    manager.info_playlist();
}

void MusicPlayer::loopingPlayback() {
    if (endOfsong == true) {
        printf("\nlagu selesai mainkan playlist selanjutnya\n");
        nextPlay();
        endOfsong = false;
    }
}
