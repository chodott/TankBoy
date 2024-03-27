#include "Obstacle.h"

void Obstacle::draw(unsigned int modelLocation, unsigned int objColorLocation)
{
	if (type == 3) block_y = -90.0f;
	glm::mat4 BLOCK = glm::mat4(1.0f);
	BLOCK = glm::translate(BLOCK, glm::vec3(this->x, this->y, this->z));
	BLOCK = glm::rotate(BLOCK, (GLfloat)glm::radians(block_y), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(BLOCK));
	glUniform3f(objColorLocation, 0.7, 0.7, 0.7);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, block_texture);
	if (type == 1) {
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, block_obj[0]);
	}
	else {
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, block_obj[1]);
	}
}

GLuint Obstacle::VAO[2];
GLuint Obstacle::VBO[2][3];
unsigned int Obstacle::block_texture; //��ֹ� �ؽ�ó�� �� ���Ϸ� ó������
int Obstacle::block_obj[2];