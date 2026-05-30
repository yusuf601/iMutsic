# iMutsic audio player using miniaudio library implemented using linkedlist c++ 

-----

## main Feature currently
* **Dinamically playlist management:** using doubly linkedlist data structure that would probably be added the songs unlimited allocation static array.
* **Asynchronous:** support functional current playlist audio background.
* **auto-next / auto-looping:** audio player is automatically detecting an end of PCM file and switch over to the *next node* in linkedlist sequences.
## Technical Architecture

This project is developed the performance and secure low level API memory is under focus:

1. **audio engine (miniaudio):** * using a separated function between `ma_decoder` (file Reader) and `ma_device` (*speaker handling* or PCM Requests)
* autonomously synchronous between *sample_rate* format audio file input with hardware *output*.
2. **memory management:** *heap allocation* (`new`/`delete`) is strictly managed every node of song trantition.
3. **next features:** shuffle random playing audio, thread safety enhanced is to secure usage architecture  
-----
