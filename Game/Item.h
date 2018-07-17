#pragma once

#define ITEM_NUM 64

typedef struct Items
{
	Circle circle;
	int score;
	int color;
	BOOL flag;	// ���ꂽ���ǂ���
}Items;

void InitItem(void);
void UpdateItem(void);
void DrawItem(void);

void ItemPlayerCollision(void);