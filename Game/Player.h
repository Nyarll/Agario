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

	int scroll;
}PlayerObject;

typedef enum
{
	PACKET_GAME_START,
	PACKET_OK
}PacketType;

typedef struct
{
	PlayerObject player1;
	PlayerObject player2;
	PacketType type;
}PacketObject;

void InitPlayer1(void);
void InitPlayer2(void);
void UpdatePlayer1(void);
void UpdatePlayer2(void);

void DrawPlayer1offline(void);
void DrawPlayer1(void);
void DrawPlayer2(void);


extern PlayerObject player1;
extern PlayerObject player2;

extern PacketObject object_packet;

//extern int scroll;
extern Mouse mouse;