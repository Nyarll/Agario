// ============================================================
// 作成日 : 2018 / 06 / 07
// 用途   : 構造体の定義
// 備考   : 授業用でもたぶん使える
// ============================================================

#pragma once

// 構造体の定義 ===============================================

// x,y 成分 / double型, double型
struct Vector2D
{
	double x, y;
};
typedef struct Vector2D Vector2D;

// 二次元の四角用 / int型, int型, int型, int型
struct Box
{
	int x1, y1;
	int x2, y2;
};
typedef struct Box Box;

// 二次元の四角形 / Vector2D型, int型, int型, Box型
// 中心座標, 辺の長さ, 左上と右下の座標
struct Square
{
	Vector2D pos;
	int side_x,side_y;
	Box box;

};
typedef struct Square Square;

// 二次元の円 / Vector2D型, int型
struct Circle
{
	Vector2D pos;
	int r;
};
typedef struct Circle Circle;

// 描画用 / int x,y , int width,height
struct Sprite
{
	int texture;
	int x, y;
	int width, height;
};
typedef struct Sprite Sprite;

// デグリーとラジアン
struct DegRad
{
	double deg, rad;
};
typedef struct DegRad DegRad;

// 例
struct GameObject
{
	Vector2D pos;
	Vector2D vel;
	Vector2D speed;
	Sprite sprite;
};
typedef struct GameObject GameObject;

