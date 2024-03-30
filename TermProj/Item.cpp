#include "Item.h"

GLuint Item::VAO;
GLuint Item::VBO[3];
unsigned int Item::item_texture;
int Item::item_obj;
time_t Item::spawnTime = 0.f;
time_t Item::spawnLength = 7.f;
float Item::size = 1.f;

void Item::draw(unsigned int modelLocation, unsigned int objColorLocation)
{
	glm::mat4 ITEM = glm::mat4(1.0f);
	ITEM = glm::translate(ITEM, glm::vec3(this->x, this->y, this->z));
	ITEM = glm::rotate(ITEM, glm::radians(rot), glm::vec3(0, 1, 0));
	ITEM = glm::scale(ITEM, glm::vec3(size, size, size));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(ITEM));
	glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, item_texture);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, item_obj);
}

void Item::update()
{
	if (!onfoot) 
	{
		if (y <= size / 2) { y = size / 2; onfoot = 1; }
		else y -= speed;
	}
	if (rot <= 360.0f) rot += 1.0f;
	else rot = 0;
}
