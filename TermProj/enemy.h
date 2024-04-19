#pragma once
#include <Windows.h>
#include "Pawn.h"

#define ENEMY_SIZE 1.0f
#define RIFLE_RANGE 4.f;
#define RIFLE_RELOAD 2.f;
#define BAZOOKA_RANGE 7.f
#define BAZOOKA_RELOAD 3.f

class Enemy : public Pawn
{
public:
	Object* target = nullptr;
	float speed = 0.01;
	float range = 4.0f;
	

	Enemy(float x, float z, Object* obj) : target(obj)
	{
		this->x = x;
		y = 0.f;
		this->z = z;
		setBoundary(ENEMY_SIZE, ENEMY_SIZE);
	}

	void draw(unsigned int modelLocation, unsigned int objColorLocation);
	void update();
};

class ARifleMan : public Enemy
{
public:
	static GLuint VAO;
	static GLuint VBO[3];
	static time_t spawnTime;
	static time_t spawnLength;
	static int rifle_obj;
	static unsigned int rifle_texture;

	ARifleMan(float x, float z, int level, Object* obj) : Enemy(x, z, obj) 
	{
		setMaxHp(level * 5.f);
		power = level;
		range = RIFLE_RANGE;
		reloadLength = RIFLE_RELOAD;
	};

	void draw(unsigned int modelLocation, unsigned int objColorLocation);
};


class ABazookaMan : public Enemy
{

public:

	static GLuint VAO;
	static GLuint VBO[3];
	static time_t spawnTime;
	static time_t spawnLength;
	static unsigned bazooka_texture;
	static int bazooka_obj;

	ABazookaMan(float x, float z, int level, Object* obj) : Enemy(x, z, obj) 
	{
		setMaxHp(level * 7.f);
		power = level * 2.f;
		range = BAZOOKA_RANGE;
		reloadLength = BAZOOKA_RELOAD;
	};

	void draw(unsigned int modelLocation, unsigned int objColorLocation);
};

