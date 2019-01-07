#include "Player.h"

Player::Player()
{
	type = cross;
	health = 5;
	//collides = 0;
}
Player::Player(size_t x, size_t y, Sublevel * sub) : Player()
{
	this->x = x;
	this->y = y;
	vectorXPos = x;
	vectorYPos = y;
	current_sublevel = sub;
}
void Player::shoot()
{
	
}
void Player::movement()
{

	if(GetAsyncKeyState(VK_UP))
	{
		move(0, -1);
		dirX = 0;
		dirY = -1;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		move(0, 1);
		dirX = 0;
		dirY = 1;
		Sleep(50); //�������
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		move(1, 0);
		dirX = 1;
		dirY = 0;
		Sleep(50); //�������
		//move(right_);
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		move(-1, 0);
		dirX = -1;
		dirY = 0;
		//move(left_);
	}
	if(GetAsyncKeyState(VK_SPACE))
	{
		shoot();
	}
}
void Player::update()
{
	movement();
	draw();
}
Player::~Player()
{
}
