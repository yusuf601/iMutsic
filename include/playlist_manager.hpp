#ifndef __PLAYLIST_MANAGER
#define __PLAYLIST_MANAGER
#include "utils.h"
#include "iterator_pattern/iterator.hpp"
#include "miniaudio.h"
#include <atomic>
class Playlist_Manager{
    public:
        Playlist_Manager();
        ~Playlist_Manager();
    public:
        audio_song* head;
        audio_song* current;
        audio_song* tail;
        ma_decoder pDecoder;
        std::atomic<bool> endOfsong;
        ma_device pDevice;
        bool isPlayed;
    public:
        void next();
        void prev();
    public:
        Iterator begin(){
            return Iterator(head);
        }
        Iterator end(){
            return Iterator(nullptr);
        }
};

#endif // !__PLAYLIST_MANAGER
