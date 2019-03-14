#ifndef PLAYER_H_
#define PLAYER_H_

#include "exceptions.h"
#include "queue.h"
#include "gerdabPlayer.hpp"


class Player
{
public:
	Player();
	void set_queue(Queue* _queue);
	void next_music();
	void previous_music();
	void pause();
	void play();
	void repeat_one();
	void repeat();
private:
	GerdabPlayer gerdab_player;
};






#endif