#include "../include/playlist_manager.hpp"
Playlist_Manager::Playlist_Manager()
    : head(nullptr), current(nullptr), tail(nullptr){}

Playlist_Manager::~Playlist_Manager() {
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
bool Playlist_Manager::is_end(){
    if(!head->next)return true;
    return false;
}
void Playlist_Manager::push_back(audio_song* song){
    if(!head){
        head = tail = current = song;
        return;
    }
    tail->next = song;
    song->prev = tail; 
    tail = song;
}
void Playlist_Manager::info_playlist(){
    if (get_current() == nullptr) {
        return;
    }
    printf("======Playlist=====\n");
    while (get_head() != nullptr) {
        printf("%d", head->idList);
        if (head->next != nullptr) {
            printf("->");
        }
        next();
    }
}
void Playlist_Manager::next(){
    if(!current)return;
    if(!current->next){
        current->next = head;
        current = current->next;
        //endOfsong = true;
        return;
    }
    current = current->next;
}

void Playlist_Manager::prev(){
    if(!current){
        printf("\nPlaylist kosong");
        return;
    }
    if(!current && !current->prev){
        printf("\ntidak ada playlist di prev");
    }
    current = current->prev;
}
void Playlist_Manager::get_playlist(){
    
}
audio_song* Playlist_Manager::get_head()const{
    return head;
}
audio_song* Playlist_Manager::get_tail()const{
    return tail;
}
audio_song* Playlist_Manager::get_current()const{
    return current;
}
