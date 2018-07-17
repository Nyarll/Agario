#pragma once

//メッセージボックス
#define MSG(m)	{	MessageBox(NULL,m,"Message Info",MB_OK);}
#define EXIT	{	MSG("ゲームを終了します") PostQuitMessage(0);}
#define EXIT_GAME	{PostQuitMessage(0);}

#define PI (3.141592653589793238)
#define DEG_TO_RAD(DEG)	((DEG) * (PI / 180.0))
#define RAD_TO_DEG(RAD)	((RAD) * (180.0 / PI))

#define SCREEN_WIDTH    (1024)                  // 画面の幅[pixel]
#define SCREEN_HEIGHT   (768)                  // 画面の高さ[pixel]

#define SCREEN_TOP      (0)                    // 画面の上端
#define SCREEN_BOTTOM   (SCREEN_HEIGHT)        // 画面の下端
#define SCREEN_LEFT     (0)                    // 画面の左端
#define SCREEN_RIGHT    (SCREEN_WIDTH)         // 画面の右端

#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)    // 画面の中央(X座標)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)    // 画面の中央(Y座標)

typedef struct
{
	int x, y;
}Mouse;


enum GameScene
{
	TITLE,
	SELECT_ONLINE_MODE,
	USER_INPUT,
	USER_WAIT,
	ONLINE_PLAY,
	OFFLINE_PLAY,
	RESULT
};