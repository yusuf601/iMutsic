
#include "../include/musicPlayer.h"
#include "utils.h"
#include <cstdio>
#include <cstdlib>
MusicPlayer::MusicPlayer()
    : head(nullptr), current(nullptr), tail(nullptr), isPlayed(false),
      endOfsong(false) {}

MusicPlayer::~MusicPlayer() {
    if (isPlayed) {
        ma_device_uninit(&pDevice);
        ma_decoder_uninit(&pDecoder);
    }

    audio_song* temp = head;
    while (temp != nullptr) {
        audio_song* nextSong = temp->next;
        printf("Duty of handling memory Leaks\n");
        delete temp;
        temp = nextSong;
    }
    head = nullptr;
    current = nullptr;
    tail = nullptr;
    printf("\nthe Playlist and Audio memory are cleaned");
}

void MusicPlayer::addSong(int idlist, std::string songTitle,
                          std::string filepath) {
    audio_song* new_songs = new audio_song(idlist, songTitle, filepath);

    if (head == nullptr) {
        printf("initialize newsong to all nodes\n");
        head = new_songs;
        tail = new_songs;
        current = new_songs;
        return;
    } else {
        tail->next = new_songs;
        new_songs->prev = tail;
        tail = new_songs;
    }
    printf("push the filepath: %s song title: %s\n", tail->songTitle.c_str(),
           tail->filepath.c_str());
}

void MusicPlayer::data_callback(ma_device* pDevice, void* pOutput,
                                const void* pInput, ma_uint32 frameCount) {
    MusicPlayer* player = (MusicPlayer*)pDevice->pUserData;

    if (player == nullptr || !player->isPlayed) {
        return;
    }

    ma_uint64 framesRead = 0;
    if (ma_decoder_read_pcm_frames(&player->pDecoder, pOutput, frameCount,
                                   &framesRead) &&
        framesRead == MA_SUCCESS) {
        ma_decoder_seek_to_pcm_frame(&player->pDecoder, framesRead);
        player->endOfsong = true;
    }
    (void)pInput;
}

void MusicPlayer::currentPlay() {
    if (current == nullptr) {
        return;
    }
    if (isPlayed) {
        ma_device_uninit(&pDevice);
        ma_decoder_uninit(&pDecoder);
    }

    if (ma_decoder_init_file(current->filepath.c_str(), NULL, &pDecoder) !=
        MA_SUCCESS) {
        printf("\nERROR init filepath: %s", current->filepath.c_str());
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
    printf("Playing the song: %s\n", current->songTitle.c_str());
}

void MusicPlayer::nextPlay() {
    // checking current->next if playlist has one song
    if (current->next == nullptr) {
        current->next = head;
        return;
    }

    // Traverse circularly the next node to complete the audio playlist
    current = current->next;
    currentPlay();
    tail->next = head;
}

void MusicPlayer::prevPlay() {
    if (current == nullptr && current->prev == nullptr) {
        printf("\n tidak ada playlist di prev");
        return;
    }

    while (current->prev != nullptr) {
        current = current->prev;
        currentPlay();
        tail->prev = head->next;
    }
}

void MusicPlayer::playList() {
    if (current == nullptr) {
        return;
    }
    printf("======Playlist=====\n");
    while (head != nullptr) {
        printf("%d", head->idList);
        if (head->next != nullptr) {
            printf("->");
        }
        head = head->next;
    }
}

void MusicPlayer::loopingPlayback() {
    if (endOfsong == true) {
        printf("\nlagu selesai mainkan playlist selanjutnya\n");
        nextPlay();
        endOfsong = false;
    }
}
