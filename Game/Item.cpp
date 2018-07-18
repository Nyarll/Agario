#include <stdlib.h>
#include <time.h>
#include "Item.h"
#include "Player.h"

static Items item[ITEM_NUM];

void InitItem(void)
{
	int i;

	srand((unsigned int)time(NULL));

	for (i = 0; i < ITEM_NUM; i++)
	{
		item[i].score = 10;
		item[i].circle.r = item[i].score;
		item[i].circle.pos.x = rand() % (SCREEN_RIGHT - 5) + 5;
		item[i].circle.pos.y = rand() % (SCREEN_BOTTOM - 5) + 5;
		item[i].color = COLOR_BLUE;

		item[i].flag = FALSE;
	}
}
void UpdateItem(void)
{
	int i;

	ItemPlayerCollision();

	for (i = 0; i < ITEM_NUM; i++)
	{
		if (item[i].flag)
		{
			item[i].score = 10;
			item[i].circle.r = item[i].score;
			item[i].circle.pos.x = rand() % (SCREEN_RIGHT - 5) + 5;
			item[i].circle.pos.y = rand() % (SCREEN_BOTTOM - 5) + 5;
			item[i].color = COLOR_BLUE;

			item[i].flag = FALSE;
		}
	}
}
void DrawItem(void)
{
	int i;

	for (i = 0; i < ITEM_NUM; i++)
	{
		DrawCircle(item[i].circle.pos.x, item[i].circle.pos.y, (item[i].circle.r / 2), item[i].color, TRUE);
	}
}

void ItemPlayerCollision(void)
{
	int i;

	for (i = 0; i < ITEM_NUM; i++)
	{
		if (CircleCollision(player1.circle.r / player1.scroll, item[i].circle.r, player1.obj.pos.x, item[i].circle.pos.x, player1.obj.pos.y, item[i].circle.pos.y))
		{
			item[i].flag = TRUE;
			player1.circle.r += item[i].score / 4;
		}

		if (CircleCollision(player2.circle.r / player2.scroll, item[i].circle.r, player2.obj.pos.x, item[i].circle.pos.x, player2.obj.pos.y, item[i].circle.pos.y))
		{
			item[i].flag = TRUE;
			player2.circle.r += item[i].score / 4;
		}
	}

}