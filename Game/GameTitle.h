#pragma once

void InitTitle(void);

void RenderMyIPaddress(void);

void RenderTitle(void);

GameScene UpdateMenu(void);
GameScene UpdateSelectOnlineMode(void);

void RenderMenu(void);

BOOL InputIPAddress(IPDATA *IP);
//void RenderInputIP(void);

struct MenuObject
{
	int x, y;	// ç¿ïW
	ColorCode color;
};