
#include "musicPlayer.h"
#include "utils.h"
#include <cstdio>

MusicPlayer::MusicPlayer()
    : head(nullptr), current(nullptr), tail(nullptr), isPlayed(false) {}

MusicPlayer::~MusicPlayer() {
    if (isPlayed) {
        ma_device_uninit(&pDevice);
        ma_decoder_uninit(&pDecoder);
    }

    audio_song* temp = head;
    while (temp->next != nullptr) {
        printf("Duty of handling memory Leaks\n");
        audio_song* nextSong = temp->next;
        delete temp;
        temp = nextSong;
    }
    printf("the Playlist and Audio memory are cleaned");
}

void MusicPlayer::addSong(std::string songTitle, std::string filepath) {
    audio_song* new_songs = new audio_song(songTitle, filepath);

    if (head == nullptr || current == nullptr || tail == nullptr) {
        head = new_songs;
        tail = new_songs;
        current = new_songs;
        return;
    } else {
        tail->next = new_songs;
        new_songs->prev = tail;
        tail = new_songs;
    }
    printf("push the filepath: %s song title: %s\n", songTitle.c_str(),
           filepath.c_str());
}

void MusicPlayer::data_callback(ma_device* pDevice, void* pOutput,
                                const void* pInput, ma_uint32 frameCount) {
    MusicPlayer* player = (MusicPlayer*)pDevice->pUserData;

    if (player == nullptr || !player->isPlayed) {
        return;
    }

    ma_decoder_read_pcm_frames(&player->pDecoder, pOutput, frameCount, NULL);
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
    printf("Playing the song: %s", current->songTitle.c_str());
    getchar();
}

void MusicPlayer::nextPlay() {
    if (current == nullptr && current->next == nullptr) {
        printf("\n tidak ada playlist di next");
        return;
    }
    current = current->next;
    currentPlay();
}

void MusicPlayer::prevPlay() {
    if (current == nullptr && current->prev == nullptr) {
        printf("\n tidak ada playlist di prev");
        return;
    }
    current = current->prev;
    currentPlay();
}
