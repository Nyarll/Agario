#pragma once

typedef struct
{
	GameObject obj;
	Circle circle;
	double angle;

	Mouse terget;
	GameScene *scene;

	BOOL net_server_flag;
	HNET net_handle;

	BOOL conect;
}PlayerObject;

typedef struct
{
	PlayerObject player;
	PlayerObject enemy;
}MoveObject;

void InitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

extern PlayerObject player;
extern PlayerObject enemy;

extern MoveObject set_game_object;

extern int scroll;
extern Mouse mouse;