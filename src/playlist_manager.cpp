#include "../include/playlist_manager.hpp"

Playlist_Manager::Playlist_Manager()
    : head(nullptr), current(nullptr), tail(nullptr), isPlayed(false),
      endOfsong(false) {}

Playlist_Manager::~Playlist_Manager() {
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

void Playlist_Manager::next(){
    if(!current)return;
    current = current->next;
}

void Playlist_Manager::prev(){
    if(!current)return;
    current = current->prev;
}
