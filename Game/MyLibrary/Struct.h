// ============================================================
// ì¬“ú : 2018 / 06 / 07
// —p“r   : \‘¢‘Ì‚Ì’è‹`
// ”õl   : ö‹Æ—p‚Å‚à‚½‚Ô‚ñg‚¦‚é
// ============================================================

#pragma once

// \‘¢‘Ì‚Ì’è‹` ===============================================

// x,y ¬•ª / doubleŒ^, doubleŒ^
struct Vector2D
{
	double x, y;
};
typedef struct Vector2D Vector2D;

// “ñŸŒ³‚ÌlŠp—p / intŒ^, intŒ^, intŒ^, intŒ^
struct Box
{
	int x1, y1;
	int x2, y2;
};
typedef struct Box Box;

// “ñŸŒ³‚ÌlŠpŒ` / Vector2DŒ^, intŒ^, intŒ^, BoxŒ^
// ’†SÀ•W, •Ó‚Ì’·‚³, ¶ã‚Æ‰E‰º‚ÌÀ•W
struct Square
{
	Vector2D pos;
	int side_x,side_y;
	Box box;

};
typedef struct Square Square;

// “ñŸŒ³‚Ì‰~ / Vector2DŒ^, intŒ^
struct Circle
{
	Vector2D pos;
	int r;
};
typedef struct Circle Circle;

// •`‰æ—p / int x,y , int width,height
struct Sprite
{
	int texture;
	int x, y;
	int width, height;
};
typedef struct Sprite Sprite;

// ƒfƒOƒŠ[‚Æƒ‰ƒWƒAƒ“
struct DegRad
{
	double deg, rad;
};
typedef struct DegRad DegRad;

// —á
struct GameObject
{
	Vector2D pos;
	Vector2D vel;
	Vector2D speed;
	Sprite sprite;
};
typedef struct GameObject GameObject;

