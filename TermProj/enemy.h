#pragma once
#include <Windows.h>
#include "object.h"
class ARifleMan : public Object
{
public:
	static GLuint VAO;
	static GLuint VBO[3];
	static int rifle_obj;
	static unsigned int rifle_texture;

	time_t attack_timer = 0;
	float speed = 0.01;
	float rotate = 0;
	float range = 4.0f;
	float size = 1.0f;
	float hpSize = 0.2f;
	int reload = 1;
	int maxHp = 0;
	int hp = 0;
	int power = 0;
	int condition = 0;
	bool active = false;

	void draw(unsigned int texture, unsigned int modelLocation, unsigned int objColorLocation);

	void move();

	void update();
};




class ABazookaMan : public Object
{

public:

	static GLuint VAO;
	static GLuint VBO[3];
	static unsigned bazooka_texture;
	static int bazooka_obj;

	void draw(unsigned int texture, unsigned int modelLocation, unsigned int objColorLocation);

	void move();

	void update();
};

