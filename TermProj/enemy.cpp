#include "enemy.h"

void ARifleMan::draw(unsigned int texture, unsigned int modelLocation, unsigned int objColorLocation)
{
	if (!active) return;

	//라이플맨
	glm::mat4 RIFLE = glm::mat4(1.0f);
	RIFLE = glm::translate(RIFLE, glm::vec3(this->x, this->y, this->z));
	RIFLE = glm::rotate(RIFLE, -this->rotate + 90.0f, glm::vec3(0, 1, 0));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(RIFLE));
	glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, rifle_texture);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, rifle_obj);
}

void ARifleMan::move()
{
}

void ARifleMan::update()
{
}


void ABazookaMan::draw(unsigned int texture, unsigned int modelLocation, unsigned int objColorLocation)
{


}

void ABazookaMan::move()
{
}

void ABazookaMan::update()
{
}

GLuint ARifleMan::VAO;
GLuint ARifleMan::VBO[3];
int ARifleMan::rifle_obj;
unsigned int ARifleMan::rifle_texture;

GLuint ABazookaMan::VAO;
GLuint ABazookaMan::VBO[3];
unsigned ABazookaMan::bazooka_texture;
int ABazookaMan::bazooka_obj;