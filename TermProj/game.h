#pragma once
#include "figure.h"
void draw(unsigned int modelLocation, unsigned int objColorLocation, GLuint* VAO) {
	tank.draw(modelLocation, objColorLocation);
	for (int i = 0; i < BLOCK_AMOUNT; i++) {
		block[i].draw(modelLocation, objColorLocation, VAO[1]);
	}
}

void update() {
	tank.update();

}