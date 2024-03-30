#include "object.h"


GLuint Title::VAO[3];
GLuint Title::VBO[3][3];
 int Title::title_obj[3];
 unsigned int Title::title_texture;

GLuint Plate::VAO[2];
GLuint Plate::VBO[2];

float Plate::plate[] = {
	-PLATE_SIZE, 0.0f, -PLATE_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, -PLATE_SIZE, 0.0f, PLATE_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, PLATE_SIZE, 0.0f, PLATE_SIZE, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-PLATE_SIZE, 0.0f, -PLATE_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, PLATE_SIZE, 0.0f, PLATE_SIZE, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, PLATE_SIZE, 0.0f, -PLATE_SIZE, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
};

float Plate::cube[] = {
-1.0, -1.0, -1.0, 0.0f, 0.0f, -1.0f, 1.0, -1.0, -1.0, 0.0f, 0.0f, -1.0f, 1.0, 1.0, -1.0, 0.0f, 0.0f, -1.0f,
1.0, 1.0, -1.0, 0.0f, 0.0f, -1.0f, -1.0, 1.0, -1.0, 0.0f, 0.0f, -1.0f, -1.0, -1.0, -1.0, 0.0f, 0.0f, -1.0f,
-1.0, -1.0, 1.0, 0.0f, 0.0f, 1.0f, 1.0, -1.0, 1.0, 0.0f, 0.0f, 1.0f, 1.0, 1.0, 1.0, 0.0f, 0.0f, 1.0f,
1.0, 1.0, 1.0, 0.0f, 0.0f, 1.0f, -1.0, 1.0, 1.0, 0.0f, 0.0f, 1.0f, -1.0, -1.0, 1.0, 0.0f, 0.0f, 1.0f,
-1.0, 1.0, 1.0, -1.0f, 0.0f, 0.0f, -1.0, 1.0, -1.0, -1.0f, 0.0f, 0.0f, -1.0, -1.0, -1.0, -1.0f, 0.0f, 0.0f,
-1.0, -1.0, -1.0, -1.0f, 0.0f, 0.0f, -1.0, -1.0, 1.0, -1.0f, 0.0f, 0.0f, -1.0, 1.0, 1.0, -1.0f, 0.0f, 0.0f,
1.0, 1.0, 1.0, 1.0f, 0.0f, 0.0f, 1.0, 1.0, -1.0, 1.0f, 0.0f, 0.0f, 1.0, -1.0, -1.0, 1.0f, 0.0f, 0.0f,
1.0, -1.0, -1.0, 1.0f, 0.0f, 0.0f, 1.0, -1.0, 1.0, 1.0f, 0.0f, 0.0f, 1.0, 1.0, 1.0, 1.0f, 0.0f, 0.0f,
-1.0, -1.0, -1.0, 0.0f, -1.0f, 0.0f, 1.0, -1.0, -1.0, 0.0f, -1.0f, 0.0f, 1.0, -1.0, 1.0, 0.0f, -1.0f, 0.0f,
1.0, -1.0, 1.0, 0.0f, -1.0f, 0.0f, -1.0, -1.0, 1.0, 0.0f, -1.0f, 0.0f, -1.0, -1.0, -1.0, 0.0f, -1.0f, 0.0f,
-1.0, 1.0, -1.0, 0.0f, 1.0f, 0.0f, 1.0, 1.0, -1.0, 0.0f, 1.0f, 0.0f, 1.0, 1.0, 1.0, 0.0f, 1.0f, 0.0f,
1.0, 1.0, 1.0, 0.0f, 1.0f, 0.0f, -1.0, 1.0, 1.0, 0.0f, 1.0f, 0.0f, -1.0, 1.0, -1.0, 0.0f, 1.0f, 0.0f
};

void Object::draw(unsigned int modelLocation, unsigned int objColorLocation)
{
}

void Object::move()
{
}

void Object::update()
{
}

void Object::setBoundary(float width, float height)
{
	width_volume = width;
	height_volume = height;
}

void Object::block()
{
}

bool Object::returnCollide(Object* obj)
{
 	if (x + width_volume / 2 < obj->x - obj->width_volume/2 ||
		x - width_volume / 2 > obj->x + obj->width_volume/2) return false;

	if (z + height_volume / 2 < obj->z - obj->height_volume/2 ||
		z - height_volume / 2 > obj->z + obj->height_volume/2) return false;

	return true;
}

void Plate::draw(unsigned int modelLocation, unsigned int objColorLocation)
{
}

void HpBar::draw(unsigned int modelLocation, unsigned int objColorLocation)
{
	glm::mat4 HP = glm::mat4(1.0f);
	HP = glm::translate(HP, glm::vec3(x, y, z));
	HP = glm::rotate(HP, glm::radians(45.0f), glm::vec3(0, 1, 0));
	if(bEnemy) HP = glm::scale(HP, glm::vec3(size, 0.01f, 0.02f));
	else HP = glm::scale(HP, glm::vec3(size, 0.01f, 0.1f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(HP));
	glUniform3f(objColorLocation, 1.0, 0, 0);
	glBindVertexArray(VAO[1]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void HpBar::update(float x, float y, float z, float curHp)
{
	this->x = x + (bEnemy == true ? 0.f : 2.f);
	this->y = y + (bEnemy == true ? 1.0f : 3.0f);
	this->z = z +( bEnemy == true? 0.f : 2.f);
	size = 0.5f * curHp / maxHp;
}