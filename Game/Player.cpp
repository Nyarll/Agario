#include <math.h>
#include "Player.h"

#define PLAYER_SPEED 2

MoveObject set_game_object;

PlayerObject player;
PlayerObject enemy;

static char keys[256];

static Mouse mouse;

int scroll;
char key[256];
char key_old[256];

static 	double rad;

void InitPlayer(void)
{
	player.obj.pos.x = SCREEN_CENTER_X;
	player.obj.pos.y = SCREEN_CENTER_Y;
	player.obj.speed.x = PLAYER_SPEED;
	player.obj.speed.y = PLAYER_SPEED;
	player.obj.vel.x = 1;
	player.obj.vel.y = 1;

	player.circle.r = 20;

	player.angle = 0;

	set_game_object.enemy = player;
	enemy = set_game_object.player;

	rad = 0;

	SetMouseDispFlag(TRUE);

	scroll = 1;
}
void UpdatePlayer(void)
{
	GetMousePoint(&mouse.x, &mouse.y);
	GetHitKeyStateAll(key);

	scroll += GetMouseWheelRotVol();

	if ((key[KEY_INPUT_UP] == 1) && (key_old[KEY_INPUT_UP] == 0))
	{
		scroll -= 1;
	}
	if ((key[KEY_INPUT_DOWN] == 1) && (key_old[KEY_INPUT_DOWN] == 0))
	{
		scroll += 1;
	}

	rad = atan2(player.obj.pos.y - mouse.y, player.obj.pos.x - mouse.x);

	/*if (mouse.x > player.obj.pos.x)
	{
		player.obj.pos.x += player.obj.vel.x * player.obj.speed.x;
	}
	if (mouse.x < player.obj.pos.x)
	{
		player.obj.pos.x -= player.obj.vel.x * player.obj.speed.x;
	}
	if (mouse.y > player.obj.pos.y)
	{
		player.obj.pos.y += player.obj.vel.y * player.obj.speed.y;
	}
	if (mouse.y < player.obj.pos.y)
	{
		player.obj.pos.y -= player.obj.vel.y * player.obj.speed.y;
	}*/

	player.obj.vel.x = cos(rad);
	player.obj.vel.y = sin(rad);

	player.obj.pos.x -= player.obj.vel.x * player.obj.speed.x;
	player.obj.pos.y -= player.obj.vel.y * player.obj.speed.y;

	if (player.obj.pos.x < SCREEN_LEFT)
	{
		player.obj.pos.x = SCREEN_LEFT;
	}
	if (player.obj.pos.x > SCREEN_RIGHT)
	{
		player.obj.pos.x = SCREEN_RIGHT;
	}
	if (player.obj.pos.y < SCREEN_TOP)
	{
		player.obj.pos.y = SCREEN_TOP;
	}
	if (player.obj.pos.y > SCREEN_BOTTOM)
	{
		player.obj.pos.y = SCREEN_BOTTOM;
	}

	set_game_object.enemy = player;
	enemy = set_game_object.player;

	GetHitKeyStateAll(key_old);
}
void DrawPlayer(void)
{
	DrawCircle(player.obj.pos.x, player.obj.pos.y, player.circle.r / scroll, COLOR_RED, TRUE);
	DrawCircle(mouse.x, mouse.y, 2, COLOR_WHITE, TRUE);

	DrawLine(player.obj.pos.x, player.obj.pos.y, mouse.x, mouse.y, COLOR_WHITE);

	DrawFormatString((int)(player.obj.pos.x - ((player.circle.r / scroll) / 4)), (int)(player.obj.pos.y - (player.circle.r / scroll) / 4), COLOR_BLUE, "%d", player.circle.r * 4);
}
