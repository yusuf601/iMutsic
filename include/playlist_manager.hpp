#ifndef __PLAYLIST_MANAGER
#define __PLAYLIST_MANAGER
#include "utils.h"
#include "iterator_pattern/iterator.hpp"
#include "../include/mode.hpp"
#include "miniaudio.h"
#include <atomic>
class Playlist_Manager{
    public:
        Playlist_Manager();
        ~Playlist_Manager();
    public:
         void addSong(int idlist, std::string songTitle, std::string filepath);
    private:
        audio_song* head;
        audio_song* current;
        audio_song* tail;
    public:
        void next();
        void prev();
        void info_playlist();
        bool is_end();
        audio_song* get_head()const;
        audio_song* get_tail()const;
        audio_song* get_current()const;
        void push_back(audio_song* song);
        void choose_mode(order* modes);
        void get_playlist();
    public:
        Iterator begin(){
            return Iterator(head);
        }
        Iterator end(){
            return Iterator(nullptr);
        }
};

#endif // !__PLAYLIST_MANAGER
