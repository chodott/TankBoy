#include "Bullet.h"

void ABullet::draw(unsigned int modelLocation, unsigned int objColorLocation)
{
	glm::mat4 TANKBULLET = glm::mat4(1.0f);
	TANKBULLET = glm::translate(TANKBULLET, glm::vec3(x, y, z));
	TANKBULLET = glm::rotate(TANKBULLET, glm::radians(rotate), glm::vec3(0, 1, 0));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TANKBULLET));
	glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(bullet_VAO);
	glDrawArrays(GL_TRIANGLES, 0, bullet_obj);
}

void ABullet::update()
{
	x += cos(rotate * PI) * speed;
	z += sin(rotate * PI) * speed;
}

unsigned int ABullet::texture;
GLuint ABullet::bullet_enemy_VAO; //Àû ÅºÈ¯
GLuint ABullet::bullet_enemy_VBO[3];
int ABullet::bullet_enemy_obj;
GLuint ABullet::bullet_VAO; //³» ÅºÈ¯
GLuint ABullet::bullet_VBO[3];
int ABullet::bullet_obj;