#include "gerdabPlayer.hpp"
#include <iostream>

using namespace std;

GerdabPlayer::GerdabPlayer(){
  Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
  index = 0;
  repeat = 0;
}

Mix_Music* GerdabPlayer::music;
bool GerdabPlayer::repeat;
int GerdabPlayer::index;
std::vector<std::string> GerdabPlayer::queue;
std::string GerdabPlayer::nextMusic;

void GerdabPlayer::resume()
{
    Mix_ResumeMusic();
}

void GerdabPlayer::goToNext(){
  GerdabPlayer::stop();
  index++;
  if(index >= queue.size()){
    if(repeat){
      index = 0;
    }else{
      queue.clear();
      return;
    }
  }
  GerdabPlayer::setMusic(queue[index]);
  GerdabPlayer::play();
}

void musicFinishCallback(){
  GerdabPlayer::goToNext();
}

void GerdabPlayer::play()
{
    if(queue.size() != 0){
      music = Mix_LoadMUS(queue[index].c_str());
      Mix_PlayMusic(music, 1);
      Mix_HookMusicFinished(musicFinishCallback);
    }
}

void GerdabPlayer::setMusic(std::string path)
{
  Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
  music = Mix_LoadMUS(path.c_str());
}
void GerdabPlayer::pause()
{
  Mix_PauseMusic();
}

void GerdabPlayer::stop()
{
  Mix_HaltMusic();
}

void GerdabPlayer::setRepeat(bool _repeat)
{
  repeat = _repeat;
}

void GerdabPlayer::setQueue(std::vector<std::string> _queue)
{
  queue = _queue;
}

void GerdabPlayer::next()
{
  if(index < queue.size())
    index++;
  if(index >= queue.size()){
    if(repeat){
      index = 0;
    }else{
      queue.clear();
      return;
    }
  }
  GerdabPlayer::setMusic(queue[index]);
  GerdabPlayer::play();
}

void GerdabPlayer::previous()
{
  if(index >= 0)
    index--;
  if(index == -1){
    if(repeat){
      index = queue.size()-1;
    }else{
      return;
    }
  }
  GerdabPlayer::setMusic(queue[index]);
  GerdabPlayer::play();
}
