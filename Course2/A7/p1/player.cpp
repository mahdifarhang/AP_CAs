#include "player.h"

using namespace std;

Player::Player() {}

void Player::set_queue(Queue* _queue)
{
	gerdab_player.setQueue(_queue->get_musics_addresses());
}

void Player::play()
{
	gerdab_player.play();
}

void Player::pause()
{
	gerdab_player.pause();
}

void Player::next_music()
{
	gerdab_player.next();
}

void Player::previous_music()
{
	gerdab_player.previous();
}

void Player::repeat_one()
{
	
}

void Player::repeat()
{
	gerdab_player.setRepeat(!gerdab_player.get_repeat());
}