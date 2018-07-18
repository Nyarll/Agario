#include <math.h>
#include "Player.h"

#define PLAYER_SPEED 2

PacketObject object_packet;

PlayerObject player1;
PlayerObject player2;

static char keys[256];

static Mouse mouse;

char key[256];
char key_old[256];

static 	double rad;

void InitPlayer(void)
{
	player1.obj.pos.x = SCREEN_CENTER_X / 2;
	player1.obj.pos.y = SCREEN_CENTER_Y;
	player1.obj.speed.x = PLAYER_SPEED;
	player1.obj.speed.y = PLAYER_SPEED;
	player1.obj.vel.x = 1;
	player1.obj.vel.y = 1;

	player1.circle.r = 20;

	player1.angle = 0;

	player2.obj.pos.x = (SCREEN_CENTER_X / 2) * 3;
	player2.obj.pos.y = SCREEN_CENTER_Y;
	player2.obj.speed.x = PLAYER_SPEED;
	player2.obj.speed.y = PLAYER_SPEED;
	player2.obj.vel.x = 1;
	player2.obj.vel.y = 1;

	player2.circle.r = 20;

	player2.angle = 0;

	rad = 0;

	SetMouseDispFlag(TRUE);

	player1.scroll = 1;
	player2.scroll = 1;
}
void UpdatePlayer1(void)
{
	GetMousePoint(&mouse.x, &mouse.y);
	GetHitKeyStateAll(key);

	player1.scroll += GetMouseWheelRotVol();

	if ((key[KEY_INPUT_UP] == 1) && (key_old[KEY_INPUT_UP] == 0))
	{
		player1.scroll -= 1;
	}
	if ((key[KEY_INPUT_DOWN] == 1) && (key_old[KEY_INPUT_DOWN] == 0))
	{
		player1.scroll += 1;
	}

	rad = atan2(player1.obj.pos.y - mouse.y, player1.obj.pos.x - mouse.x);

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

	player1.obj.vel.x = cos(rad);
	player1.obj.vel.y = sin(rad);

	player1.obj.pos.x -= player1.obj.vel.x * player1.obj.speed.x;
	player1.obj.pos.y -= player1.obj.vel.y * player1.obj.speed.y;

	if (player1.obj.pos.x < SCREEN_LEFT)
	{
		player1.obj.pos.x = SCREEN_LEFT;
	}
	if (player1.obj.pos.x > SCREEN_RIGHT)
	{
		player1.obj.pos.x = SCREEN_RIGHT;
	}
	if (player1.obj.pos.y < SCREEN_TOP)
	{
		player1.obj.pos.y = SCREEN_TOP;
	}
	if (player1.obj.pos.y > SCREEN_BOTTOM)
	{
		player1.obj.pos.y = SCREEN_BOTTOM;
	}

	object_packet.player1 = player1;

	GetHitKeyStateAll(key_old);
}
void UpdatePlayer2(void)
{
	GetMousePoint(&mouse.x, &mouse.y);
	GetHitKeyStateAll(key);

	player2.scroll += GetMouseWheelRotVol();

	if ((key[KEY_INPUT_UP] == 1) && (key_old[KEY_INPUT_UP] == 0))
	{
		player2.scroll -= 1;
	}
	if ((key[KEY_INPUT_DOWN] == 1) && (key_old[KEY_INPUT_DOWN] == 0))
	{
		player2.scroll += 1;
	}

	rad = atan2(player2.obj.pos.y - mouse.y, player2.obj.pos.x - mouse.x);

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

	player2.obj.vel.x = cos(rad);
	player2.obj.vel.y = sin(rad);

	player2.obj.pos.x -= player2.obj.vel.x * player2.obj.speed.x;
	player2.obj.pos.y -= player2.obj.vel.y * player2.obj.speed.y;

	if (player2.obj.pos.x < SCREEN_LEFT)
	{
		player2.obj.pos.x = SCREEN_LEFT;
	}
	if (player2.obj.pos.x > SCREEN_RIGHT)
	{
		player2.obj.pos.x = SCREEN_RIGHT;
	}
	if (player2.obj.pos.y < SCREEN_TOP)
	{
		player2.obj.pos.y = SCREEN_TOP;
	}
	if (player2.obj.pos.y > SCREEN_BOTTOM)
	{
		player2.obj.pos.y = SCREEN_BOTTOM;
	}

	object_packet.player2 = player2;

	GetHitKeyStateAll(key_old);
}


void DrawPlayer1offline(void)
{
	DrawCircle(player1.obj.pos.x, player1.obj.pos.y, player1.circle.r / player1.scroll, COLOR_RED, TRUE);
	DrawCircle(mouse.x, mouse.y, 2, COLOR_WHITE, TRUE);

	DrawLine(player1.obj.pos.x, player1.obj.pos.y, mouse.x, mouse.y, COLOR_WHITE);

	DrawFormatString((int)(player1.obj.pos.x - ((player1.circle.r / player1.scroll) / 4)), (int)(player1.obj.pos.y - (player1.circle.r / player1.scroll) / 4), COLOR_BLUE, "%d", player1.circle.r * 4);
}
void DrawPlayer1(void)
{
	DrawCircle(player1.obj.pos.x, player1.obj.pos.y, player1.circle.r / player1.scroll, COLOR_RED, TRUE);
	//DrawCircle(mouse.x, mouse.y, 2, COLOR_WHITE, TRUE);

	//DrawLine(player1.obj.pos.x, player1.obj.pos.y, mouse.x, mouse.y, COLOR_WHITE);

	DrawFormatString((int)(player1.obj.pos.x - ((player1.circle.r / player1.scroll) / 4)), (int)(player1.obj.pos.y - (player1.circle.r / player1.scroll) / 4), COLOR_BLUE, "%d", player1.circle.r * 4);
}
void DrawPlayer2(void)
{
	DrawCircle(player2.obj.pos.x, player2.obj.pos.y, player2.circle.r / player2.scroll, COLOR_WHITE, TRUE);
	//DrawCircle(mouse.x, mouse.y, 2, COLOR_WHITE, TRUE);

	//DrawLine(player1.obj.pos.x, player1.obj.pos.y, mouse.x, mouse.y, COLOR_WHITE);

	DrawFormatString((int)(player2.obj.pos.x - ((player2.circle.r / player2.scroll) / 4)), (int)(player2.obj.pos.y - (player2.circle.r / player2.scroll) / 4), COLOR_BLUE, "%d", player2.circle.r * 4);
}