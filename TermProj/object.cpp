#include "object.h"

void Object::draw(unsigned int modelLocation, unsigned int objColorLocation)
{
}

void Object::move()
{
}

void Object::update()
{
}

GLuint Plate::VAO;
GLuint Plate::VBO;

float Plate::plate[] = {
	-PLATE_SIZE, 0.0f, -PLATE_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, -PLATE_SIZE, 0.0f, PLATE_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, PLATE_SIZE, 0.0f, PLATE_SIZE, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-PLATE_SIZE, 0.0f, -PLATE_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, PLATE_SIZE, 0.0f, PLATE_SIZE, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, PLATE_SIZE, 0.0f, -PLATE_SIZE, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
};

void Plate::draw(unsigned int modelLocation, unsigned int objColorLocation)
{
}

void HpBar::draw(unsigned int modelLocation, unsigned int objColorLocation)
{
	glm::mat4 HP = glm::mat4(1.0f);
	HP = glm::translate(HP, glm::vec3(x, y, z));
	HP = glm::rotate(HP, glm::radians(45.0f), glm::vec3(0, 1, 0));
	HP = glm::scale(HP, glm::vec3(0.2f, 0.01f, 0.1f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(HP));
	glUniform3f(objColorLocation, 1.0, 0, 0);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void HpBar::update(float x, float y, float z)
{
	this->x = x; 
	this->y = y;
	this->z = z;
}


void Pawn::draw(unsigned int modelLocation, unsigned int objColorLocation)
{
	hpbar->draw(modelLocation, objColorLocation);
}

void Pawn::update()
{
	hpbar->update(x, y, z);
}
