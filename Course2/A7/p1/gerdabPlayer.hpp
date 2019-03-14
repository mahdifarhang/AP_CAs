#include "sdlHeaders.hpp"
#include "exceptions.h"
#include <iostream>
#include <string>
#include <vector>

void Delay(int milis);
class GerdabPlayer
{
public:
    GerdabPlayer();
    static void play();
    static void setMusic(std::string path);
    static void pause();
    static void resume();
    static void next();
    static void previous();
    static void stop();
    bool get_repeat() { return repeat; }
    static void setRepeat(bool repeat);
    static void setQueue(std::vector<std::string> queue);
    friend void musicFinishCallback();
    static std::string nextMusic;
    std::vector<std::string> getter() {return queue;}

 private:
    static Mix_Music *music;
    static std::vector<std::string> queue;
    static bool repeat;
    static int index;
    static void goToNext();
};


