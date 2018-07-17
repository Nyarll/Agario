#pragma once

//���b�Z�[�W�{�b�N�X
#define MSG(m)	{	MessageBox(NULL,m,"Message Info",MB_OK);}
#define EXIT	{	MSG("�Q�[�����I�����܂�") PostQuitMessage(0);}
#define EXIT_GAME	{PostQuitMessage(0);}

#define PI (3.141592653589793238)
#define DEG_TO_RAD(DEG)	((DEG) * (PI / 180.0))
#define RAD_TO_DEG(RAD)	((RAD) * (180.0 / PI))

#define SCREEN_WIDTH    (1024)                  // ��ʂ̕�[pixel]
#define SCREEN_HEIGHT   (768)                  // ��ʂ̍���[pixel]

#define SCREEN_TOP      (0)                    // ��ʂ̏�[
#define SCREEN_BOTTOM   (SCREEN_HEIGHT)        // ��ʂ̉��[
#define SCREEN_LEFT     (0)                    // ��ʂ̍��[
#define SCREEN_RIGHT    (SCREEN_WIDTH)         // ��ʂ̉E�[

#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)    // ��ʂ̒���(X���W)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)    // ��ʂ̒���(Y���W)

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