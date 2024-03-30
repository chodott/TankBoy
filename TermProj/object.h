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
#include <algorithm>
using namespace std;

#define PI 3.141592/180
#define PLATE_SIZE 25.0f

class Object
{
public:

	float x = 0;
	float y = 0;
	float z = 0;

	float width_volume = 0.f;
	float height_volume = 0.f;

	virtual void draw(unsigned int modelLocation, unsigned int objColorLocation);

	void move();

	virtual void update();

	virtual void setBoundary(float width, float height);

	virtual void block();

	virtual bool returnCollide(Object* obj);
};


class Plate : public Object
{
public:
	static GLuint VAO[2];
	static GLuint VBO[2];
	static float plate[48];
	static float cube[216];
	void draw(unsigned int modelLocation, unsigned int objColorLocation);
};

class HpBar : public Plate
{
public:
	float maxHp;
	float size;
	bool bEnemy = true;

	inline void setType(bool b) { bEnemy = b; }
	void draw(unsigned int modelLocation, unsigned int objColorLocation);
	void update(float x, float y, float z,  float curHp);
};