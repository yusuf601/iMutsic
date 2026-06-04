
#include "../include/musicPlayer.h"
#include "../include/playlist_manager.hpp"
#include "utils.h"
#include <cstdio>
#include <cstdlib>
void MusicPlayer::addSong(int idlist, std::string songTitle,
                          std::string filepath) {
    audio_song* new_songs = new audio_song(idlist, songTitle, filepath);

    if (manager.head == nullptr) {
        printf("initialize newsong to all nodes\n");
        manager.head = new_songs;
        manager.tail = new_songs;
        manager.current = new_songs;
        return;
    } else {
        manager.tail->next = new_songs;
        new_songs->prev = manager.tail;
        manager.tail = new_songs;
    }
    printf("push the filepath: %s song title: %s\n", manager.tail->songTitle.c_str(),
           manager.tail->filepath.c_str());
}

void MusicPlayer::data_callback(ma_device* pDevice, void* pOutput,
                                const void* pInput, ma_uint32 frameCount) {
    MusicPlayer* player = (MusicPlayer*)pDevice->pUserData;

    if (player == nullptr || !player->manager.isPlayed) {
        return;
    }

    ma_uint64 framesRead = 0;
    if (ma_decoder_read_pcm_frames(&player->manager.pDecoder, pOutput, frameCount,
                                   &framesRead) &&
        framesRead == MA_SUCCESS) {
        ma_decoder_seek_to_pcm_frame(&player->manager.pDecoder, framesRead);
        player->manager.endOfsong = true;
    }
    (void)pInput;
}

void MusicPlayer::currentPlay() {
    if (manager.current == nullptr) {
        return;
    }
    if (manager.isPlayed) {
        ma_device_uninit(&manager.pDevice);
        ma_decoder_uninit(&manager.pDecoder);
    }

    if (ma_decoder_init_file(manager.current->filepath.c_str(), NULL, &manager.pDecoder) !=
        MA_SUCCESS) {
        printf("\nERROR init filepath: %s", manager.current->filepath.c_str());
        return;
    }

    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format = manager.pDecoder.outputFormat;
    config.playback.channels = manager.pDecoder.outputChannels;
    config.sampleRate = manager.pDecoder.outputSampleRate;

    config.dataCallback = data_callback;
    config.pUserData = this;

    if (ma_device_init(NULL, &config, &manager.pDevice) != MA_SUCCESS) {
        printf("ERROR init device\n");
        return;
    }

    ma_device_start(&manager.pDevice);
    manager.isPlayed = true;
    printf("Playing the song: %s\n", manager.current->songTitle.c_str());
}

void MusicPlayer::nextPlay() {
    // checking manager.current->next if playlist has one song
    if (manager.current->next == nullptr) {
        manager.current->next = manager.head;
        return;
    }

    // Traverse circularly the next node to complete the audio playlist
    manager.current = manager.current->next;
    currentPlay();
    manager.tail->next = manager.head;
}

void MusicPlayer::prevPlay() {
    if (manager.current == nullptr && manager.current->prev == nullptr) {
        printf("\n tidak ada playlist di prev");
        return;
    }

    while (manager.current->prev != nullptr) {
        manager.current = manager.current->prev;
        currentPlay();
        manager.tail->prev = manager.head->next;
    }
}

void MusicPlayer::playList() {
    if (manager.current == nullptr) {
        return;
    }
    printf("======Playlist=====\n");
    while (manager.head != nullptr) {
        printf("%d", manager.head->idList);
        if (manager.head->next != nullptr) {
            printf("->");
        }
        manager.head = manager.head->next;
    }
}

void MusicPlayer::loopingPlayback() {
    if (manager.endOfsong == true) {
        printf("\nlagu selesai mainkan playlist selanjutnya\n");
        nextPlay();
        manager.endOfsong = false;
    }
}
