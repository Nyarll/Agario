//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  ゲーム関連のソースファイル
//!
//! @date   日付
//!
//! @author 制作者名
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma warning (disable:4244)

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"

#include "GameTitle.h"

#include "Player.h"
#include "Item.h"



// 定数の定義 ==============================================================
#define DEBUG



// 構造体の定義 ============================================================




// グローバル変数の定義 ====================================================
GameScene scene;
HNET handle;
HNET new_nethandle;

IPDATA Ip;
static IPDATA ip;


// プロトタイプ宣言 ========================================================

void InitializeGame(void);  // ゲームの初期化処理
void UpdateGame(void);      // ゲームの更新処理
void RenderGame(void);      // ゲームの描画処理
void FinalizeGame(void);    // ゲームの終了処理




// 関数の定義 ==============================================================

// ゲームの初期化処理
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

// ゲームの更新処理
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
		// 接続待ち
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

// ゲームの描画処理
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

// ゲームの終了処理
void FinalizeGame(void)
{
	CloseNetWork(handle);
	StopListenNetWork();
}


// 以下オリジナル関数 --------------------------------------------------
