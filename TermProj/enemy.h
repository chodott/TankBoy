#pragma once
#include <Windows.h>
#include "object.h"
#include "Bullet.h"

class Enemy : public Object
{
public:
	time_t attacked_time = 0;
	Object* target = nullptr;
	vector<ABullet*> bullet_vec;
	float speed = 0.01;
	float rotate = 0;
	float range = 4.0f;
	float size = 1.0f;
	float hpSize = 0.2f;
	float reloadLength = 1.f;
	float hp;
	int power = 0;
	int condition = 0;
	bool active = false;

	Enemy(float x, float z, Object* obj) :  power(power), target(obj)
	{
		this->x = x;
		y = 0.f;
		this->z = z;
		this->hp = hp;
	}
	void update();
	void attack();
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
		hp = level * 5.f;
		power = level;
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
		hp = level * 7.f;
		power = level * 2.f;
	};


	void draw(unsigned int modelLocation, unsigned int objColorLocation);

};

