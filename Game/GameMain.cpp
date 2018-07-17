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
#define DEBUG



// �\���̂̒�` ============================================================




// �O���[�o���ϐ��̒�` ====================================================
GameScene scene;
HNET handle;
HNET new_nethandle;

IPDATA Ip;
static IPDATA ip;


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
	InitPlayer();
	InitItem();
}

// �Q�[���̍X�V����
void UpdateGame(void)
{
	static BOOL IP_flag = FALSE;

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
		DrawFormatString((SCREEN_RIGHT - 8 * 25), (SCREEN_BOTTOM - 50), COLOR_WHITE, "ONLINE !");
#endif 

		break;

	case OFFLINE_PLAY:
		UpdatePlayer();
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

	case OFFLINE_PLAY:
		DrawPlayer();
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
