#pragma once
#include "object.h"
#define ITEM_SPAWN_Y 5.f

class Item : public Plate
{
public:
	static GLuint VAO;
	static GLuint VBO[3];
	static int item_obj;
	static unsigned int item_texture;

	static time_t spawnTime;
	static time_t spawnLength;
	static float size;
	float speed = 0.005;
	bool onfoot = false;

	Item() {
		setBoundary(size, size);
		y = ITEM_SPAWN_Y;
	};
	Item(float x, float z) : Plate(x, z) {Item();}

	void draw(unsigned int modelLocation, unsigned int objColorLocation);
	void update();
};

