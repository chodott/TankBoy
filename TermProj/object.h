#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;

#define PI 3.141592/180
#define PLATE_SIZE 25.0f

class Object
{
public:

	float x, y, z;

	virtual void draw(unsigned int modelLocation, unsigned int objColorLocation);

	void move();

	virtual void update();
};


class Plate : public Object
{
public:
	static GLuint VAO;
	static GLuint VBO;
	static float plate[48];
	void draw(unsigned int modelLocation, unsigned int objColorLocation);
};

class HpBar : public Plate
{
public:
	void draw(unsigned int modelLocation, unsigned int objColorLocation);
	void update(float x, float y, float z);
};

class Pawn : public Object
{
public:

	HpBar* hpbar = nullptr;
	int maxHp;
	int hp;

	Pawn() { hpbar = new HpBar(); };
	void setPos(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void draw(unsigned int modelLocation, unsigned int objColorLocation);
	void update();
};