#ifndef __ITERATOR_PATTERN
#define __ITERATOR_PATTERN

#include "../utils.h"

class Iterator{
    private:
        audio_song* current;
    public:
        Iterator() = default;
        explicit Iterator(audio_song* current): current(current){}
        Iterator& operator++(){ //post increment
            current = current->next;
            return *this; //kembalikan object saat ini
        }
        Iterator operator++(int){
            Iterator temp = *this;
            current = current->next;
            return temp;
        }
        Iterator& operator--(){
            current = current->prev;
            return *this;
        }
        Iterator operator--(int){
            Iterator temp = *this;
            current = current->prev;
            return temp;
        }
        bool operator!=(const Iterator& comp){
            return current != comp.current;
        }
};
#endif // __ITERATOR_PATTERN

