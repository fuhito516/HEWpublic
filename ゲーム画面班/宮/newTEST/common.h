#pragma once

#define SCREEN_WIDTH  (1024)
#define SCREEN_HEIGHT (576)

#define FRAME_PER_SECOND (60)

#define GRAVITY (9.8f / 3)

// �ՓˑΏ�
enum eDirection
{
	DIRECTION_NONE,
	DIRECTION_UP,
	DIRECTION_UPRIGHT,
	DIRECTION_RIGHT,
	DIRECTION_DOWNRIGHT,
	DIRECTION_DOWN,
	DIRECTION_DOWNLEFT,
	DIRECTION_LEFT,
	DIRECTION_UPLEFT
};
// �ՓˑΏ�
enum eCollision
{
	COLLISION_NONE,
	COLLISION_GROUND,
	COLLISION_WALL,
	COLLISION_CEILING,
	COLLISION_PLAYER,
	COLLISION_SEIKA,
	COLLISION_BRIDGE
};