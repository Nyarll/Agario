#include "GameTitle.h"

MenuObject menu_object;
ColorCode netgame, offlinegame, end;

Mouse mouse;

int left_old;

void InitTitle(void)
{
	netgame = COLOR_YELLOW;
	offlinegame = COLOR_WHITE;
	end = COLOR_WHITE;
}

void RenderMyIPaddress(void)
{
	IPDATA ip;	// IPアドレス保存用の構造体
	GetMyIPAddress(&ip);	// 自分のマシンのIPアドレスを取得
	// IPアドレスの表示
	SetFontSize(25);
	DrawFormatString((SCREEN_RIGHT - 18 * 25), (SCREEN_BOTTOM - 25), COLOR_WHITE, "Your IP Address : %d.%d.%d.%d", ip.d1, ip.d2, ip.d3, ip.d4);
}

void RenderTitle(void)
{
	static int red = 255, green = 0, blue = 255;
	static BOOL red_flag = TRUE, green_flag = FALSE, blue_flag = FALSE;

	if (red_flag)
	{
		green++;
		blue--;
		if (green > 255)
		{
			green = 255;
			blue = 0;
			red_flag = FALSE;
			green_flag = TRUE;
		}
	}
	if (green_flag)
	{
		blue++;
		red--;
		if (blue > 255)
		{
			blue = 255;
			red = 0;
			green_flag = FALSE;
			blue_flag = TRUE;
		}
	}
	if (blue_flag)
	{
		red++;
		green--;
		if (red > 255)
		{
			red = 255;
			green = 0;
			blue_flag = FALSE;
			red_flag = TRUE;
		}
	}
	SetFontSize(60);
	DrawFormatString(SCREEN_CENTER_X - 2 * 60, SCREEN_CENTER_Y / 2 - 60, GetColor(red, green, blue), "Agar.io");
}

GameScene UpdateMenu(void)
{
	GetMousePoint(&mouse.x, &mouse.y);

	netgame = COLOR_WHITE;
	offlinegame = COLOR_WHITE;
	end = COLOR_WHITE;
	if (BoxCollision(mouse.x, mouse.y, 2, 2,
		SCREEN_CENTER_X - 10, (SCREEN_CENTER_Y / 4) * 3 + 16,
		4 * 30, 18))
	{
		netgame = COLOR_YELLOW;
		if (((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) && (left_old == 0))
		{
			return SELECT_ONLINE_MODE;
		}
	}

	if (BoxCollision(mouse.x, mouse.y, 2, 2,
		SCREEN_CENTER_X - 10, (SCREEN_CENTER_Y / 4) * 4 + 16,
		4 * 30, 18))
	{
		offlinegame = COLOR_YELLOW;
		if (((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) && (left_old == 0))
		{
			return OFFLINE_PLAY;
		}
	}
	
	if (BoxCollision(mouse.x, mouse.y, 2, 2,
		SCREEN_CENTER_X - 10, (SCREEN_CENTER_Y / 4) * 5 + 16,
		4 * 30, 18))
	{
		end = COLOR_YELLOW;
		if (((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) && (left_old == 0))
		{
			EXIT_GAME;
		}
	}

	left_old = (GetMouseInput() & MOUSE_INPUT_LEFT);
}

GameScene UpdateSelectOnlineMode(void)
{
	static ColorCode host = COLOR_WHITE, wait = COLOR_WHITE;
	host = COLOR_WHITE, wait = COLOR_WHITE;

	GetMousePoint(&mouse.x, &mouse.y);

	if (BoxCollision(mouse.x, mouse.y, 2, 2,
		SCREEN_CENTER_X - 10, (SCREEN_BOTTOM / 5) * 2 + 16,
		4 * 30, 18))
	{
		host = COLOR_YELLOW;
		if (((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) && (left_old == 0))
		{
			return USER_INPUT;
		}
	}

	if (BoxCollision(mouse.x, mouse.y, 2, 2,
		SCREEN_CENTER_X - 10, (SCREEN_BOTTOM / 5) * 3 + 16,
		4 * 30, 18))
	{
		wait = COLOR_YELLOW;
		if (((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) && (left_old == 0))
		{
			return USER_WAIT;
		}
	}

	left_old = (GetMouseInput() & MOUSE_INPUT_LEFT);

	// Render
	SetFontSize(30);
	DrawFormatString(SCREEN_CENTER_X - 4 * 30, (SCREEN_BOTTOM / 5) * 2, host, "Waiting Connect");
	DrawFormatString(SCREEN_CENTER_X - 4 * 30, (SCREEN_BOTTOM / 5) * 3, wait, "Connect");
	return SELECT_ONLINE_MODE;
}

void RenderMenu(void)
{
	SetFontSize(30);
	DrawFormatString(SCREEN_CENTER_X - 4 * 30, (SCREEN_CENTER_Y / 4) * 3, netgame, "Network Game !");
	DrawFormatString(SCREEN_CENTER_X - 4 * 30, (SCREEN_CENTER_Y / 4) * 4, offlinegame, "OffLine Game !");
	DrawFormatString(SCREEN_CENTER_X - 4 * 30, (SCREEN_CENTER_Y / 4) * 5, end, "Quit !");
}

BOOL InputIPAddress(IPDATA *IP)
{
	// IPアドレス
	IPDATA ip;
	// 有効なIPアドレス
	BOOL ip_valid = FALSE;

	char StrBuf[81];

	// IPの入力する
	SetKeyInputStringColor2(DX_KEYINPSTRCOLOR_NORMAL_STR, COLOR_BLACK);
	SetKeyInputStringColor2(DX_KEYINPSTRCOLOR_NORMAL_CURSOR, COLOR_BLACK);
	SetKeyInputStringColor2(DX_KEYINPSTRCOLOR_SELECT_STR, COLOR_BLACK);

	SetFontSize(40);
	DrawFormatString(SCREEN_CENTER_X / 2, SCREEN_CENTER_Y / 2, COLOR_WHITE, "Please enter IP address !");
	SetFontSize(20);
	DrawFormatString(SCREEN_CENTER_X / 2, SCREEN_CENTER_Y / 2 + 40, COLOR_WHITE, "* ピリオドも入力してください ＊");
	DrawFormatString(SCREEN_CENTER_X / 2, SCREEN_CENTER_Y / 2 + 60, COLOR_WHITE, "* 例 : 172.255.255.255 ＊");

	DrawBox(SCREEN_CENTER_X / 2, SCREEN_CENTER_Y - 10, (SCREEN_CENTER_X / 2) * 3, SCREEN_CENTER_Y + 40, COLOR_WHITE, TRUE);

	SetFontSize(40);
	if (KeyInputSingleCharString(SCREEN_CENTER_X / 2, SCREEN_CENTER_Y, 30, StrBuf, TRUE) != 1)
		return FALSE;
	{
		char StrBuf2[81];
		int i, j, k;
		// ピリオドが３つあるか調べる
		j = 0;
		for (i = 0; i < 80; i++)
		{
			if (StrBuf[i] == '.') j++;
		}

		// もし３つピリオドがあった場合
		if (j == 3)
		{
			// 文字列からＩＰを抜き出す
			j = 0;
			k = 0;
			i = 0;
			while (!ProcessMessage())
			{
				if (StrBuf[i] == '.' || StrBuf[i] == '\0')
				{
					StrBuf2[j] = '\0';
					switch (k)
					{
					case 0:IP->d1 = atoi(StrBuf2); break;
					case 1:IP->d2 = atoi(StrBuf2); break;
					case 2:IP->d3 = atoi(StrBuf2); break;
					case 3:IP->d4 = atoi(StrBuf2); break;
					}
					k++;
					if (k == 4) break;

					j = 0;
				}
				else
				{
					StrBuf2[j] = StrBuf[i];
					j++;
				}
				i++;
			}
			return TRUE;
		}
	}

	return FALSE;
}
void RenderInputWarningIP(void)
{
	
}