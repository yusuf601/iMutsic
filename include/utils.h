#ifndef UTILS_H
#define UTILS_H
#include "miniaudio.h"
#include <string>

struct audio_song {
    struct audio_song* next;
    struct audio_song* prev;

    int idList;
    std::string songTitle;
    std::string filepath;

    audio_song(int idList, std::string s, std::string f)
        : idList(idList), songTitle(s), filepath(f) {
        prev = nullptr;
        next = nullptr;
    }
};

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput,
                   ma_uint32 frameCount);

#endif  // !UTILS_H
