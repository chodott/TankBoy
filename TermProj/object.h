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

class Object
{
public:

	float x, y, z;

	virtual void draw(unsigned int modelLocation, unsigned int objColorLocation);

	void move();

	virtual void update();
};

