//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  �Q�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   ���t
//!
//! @author ����Җ�
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma warning (disable:4244)

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"

#include "GameTitle.h"

#include "Player.h"
#include "Item.h"



// �萔�̒�` ==============================================================

//#define DEBUG



// �\���̂̒�` ============================================================




// �O���[�o���ϐ��̒�` ====================================================
GameScene scene;
HNET handle;
HNET new_nethandle;

IPDATA Ip;
static IPDATA ip;

BOOL host = FALSE;


// �v���g�^�C�v�錾 ========================================================

void InitializeGame(void);  // �Q�[���̏���������
void UpdateGame(void);      // �Q�[���̍X�V����
void RenderGame(void);      // �Q�[���̕`�揈��
void FinalizeGame(void);    // �Q�[���̏I������




// �֐��̒�` ==============================================================

// �Q�[���̏���������
void InitializeGame(void)
{
	scene = TITLE;

	handle = -1;
	new_nethandle = -1;

	SetWindowSizeExtendRate(1.0);
	SetWindowSizeChangeEnableFlag(TRUE);

	InitTitle();
	InitPlayer1();
	InitPlayer2();
	InitItem();
}

// �Q�[���̍X�V����
void UpdateGame(void)
{
	static BOOL IP_flag = FALSE;
	static int cnt = 2;

	switch (scene)
	{
	case TITLE:
		scene = UpdateMenu();
		break;

	case SELECT_ONLINE_MODE:
		scene = UpdateSelectOnlineMode();
		break;

	case USER_INPUT:
		if (!IP_flag)
		{
			IP_flag = InputIPAddress(&ip);
			host = TRUE;
		}
		else
		{
			SetFontSize(25);
			//DrawFormatString((SCREEN_RIGHT - 8 * 25), (SCREEN_BOTTOM - 25), COLOR_WHITE, "Now Loading....");
			//ScreenFlip();
		}

		if (IP_flag)
		{
			handle = ConnectNetWork(ip, 9850);
			if (handle != -1)
			{
				DrawFormatString((SCREEN_RIGHT - 8 * 25), (SCREEN_BOTTOM - 25), COLOR_WHITE, "O K !");
				scene = ONLINE_PLAY;
			}
			else
			{
				DrawFormatString((SCREEN_RIGHT - 8 * 25), (SCREEN_BOTTOM - 25), COLOR_WHITE, "Not Found !");
			}
		}
		break;

	case USER_WAIT:
		// �ڑ��҂�
		RenderMyIPaddress();

		if (handle != -1)
		{
			DrawFormatString((SCREEN_RIGHT - 8 * 25), (SCREEN_BOTTOM - 50), COLOR_WHITE, "O K !");
			GetNetWorkIP(handle, &Ip);
			scene = ONLINE_PLAY;
		}
		else
		{
			handle = GetNewAcceptNetWork();
			PreparationListenNetWork(9850);
		}
		break;

	case ONLINE_PLAY:
#ifdef DEBUG
		SetFontSize(25);
		DrawFormatString((SCREEN_RIGHT - 8 * 25), (SCREEN_BOTTOM - 50), COLOR_WHITE, "ONLINE !");
#endif 
		if (host)
		{
			UpdatePlayer1();
		}
		else
		{
			UpdatePlayer2();
		}

		UpdateItem();

		if (cnt == 0)
		{
			cnt = 2;
			SendData();
		}
		RecvData();

		PlayerCollision();

		cnt--;
		break;

	case OFFLINE_PLAY:
		UpdatePlayer1();
		UpdateItem();
		break;
	}
}

// �Q�[���̕`�揈��
void RenderGame(void)
{
	switch (scene)
	{
	case TITLE:
		RenderTitle();
		RenderMyIPaddress();
		RenderMenu();
		break;

	case ONLINE_PLAY:
		DrawPlayer1();
		DrawPlayer2();
		DrawItem();

	case OFFLINE_PLAY:
		DrawPlayer1offline();
		DrawItem();
		break;
	}
}

// �Q�[���̏I������
void FinalizeGame(void)
{
	CloseNetWork(handle);
	StopListenNetWork();
}


// �ȉ��I���W�i���֐� --------------------------------------------------

void SendData(void)
{
	PacketObject* packet_buf = &object_packet;
	NetWorkSend(handle, packet_buf, sizeof(object_packet));
}
void RecvData(void)
{
	PacketObject packet_buf;
	int temp = GetNetWorkDataLength(handle);

	if (temp != 0)
	{
		NetWorkRecv(handle, &packet_buf, sizeof(packet_buf));

		if (host)
		{
			player2 = packet_buf.player2;
		}
		else
		{
			player1 = packet_buf.player1;
		}
	}
}

void PlayerCollision(void)
{
	if (CircleCollision(player1.circle.r, player2.circle.r,
		player1.obj.pos.x, player2.obj.pos.x, player1.obj.pos.y, player2.obj.pos.y))
	{
		if ((player1.circle.r * 4) > ((player2.circle.r * 4) + (player2.circle.r * 2)))
		{
			player1.circle.r += player2.circle.r / 4;
			InitPlayer2();
		}
		if ((player2.circle.r * 4) > ((player1.circle.r * 4) + (player1.circle.r * 2)))
		{
			player2.circle.r += player1.circle.r / 4;
			InitPlayer1();
		}
	}
}