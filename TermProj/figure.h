#include "manage.h"

void setBlock();

#define PLATE_SIZE 25.0f
#define PI 3.141592/180
#define BLOCK_AMOUNT 50
#define RIFLE_AMOUNT 30
#define ITEM_AMOUNT 10

//평면
unsigned int ground_texture, wall_texture;
float plate[] = {
	-PLATE_SIZE, 0.0f, -PLATE_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, -PLATE_SIZE, 0.0f, PLATE_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, PLATE_SIZE, 0.0f, PLATE_SIZE, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-PLATE_SIZE, 0.0f, -PLATE_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, PLATE_SIZE, 0.0f, PLATE_SIZE, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, PLATE_SIZE, 0.0f, -PLATE_SIZE, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
};

//정육면체
float vertices[] = { 
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

//포물선 점
float track[] = {
	0,0,0,0,0,0
};

class Point {
public:
	float x, y, z;
};

GLuint bullet_enemy_VAO; //적 탄환
GLuint bullet_enemy_VBO[3];
int bullet_enemy_obj;
GLuint bullet_ally_VAO; //내 탄환
GLuint bullet_ally_VBO[3];
int bullet_ally_obj;
unsigned int rifle_texture; //소총병의 텍스처를 탄환도 공유해서 여기다적었엉

//총알
class Bullet {
public:
	Point point[100] = {};
	float size = 0.1f;
	float x, y, z;
	float r = 0;
	float speed = 0.2f;
	int tic = 0;
	bool active = 0;
	Bullet() : x{ 0 }, y{ 0 }, z{ 0 } {}

	void move() {
		if (this->active) {
			this->x = this->point[tic].x;
			this->y = this->point[tic].y;
			this->z = this->point[tic].z;
			this->tic += 3;
		if (this->tic == 100)  this->active = 0;
		else if (this->point[tic].y <= 0) this->active = 0;
		}
	}

	void enemy_move() { //총알이 같은 클래스라 적 총알 매커니즘 따로 구현했슴다!
		if (this->active) {
			this->x += cos(this->r) * this->speed;
			this->z += sin(this->r) * this->speed;
		}
	}

	void draw(GLuint VAO, int triangles, unsigned int texture, unsigned int modelLocation, unsigned int objColorLocation) {
		if (this->active) {
			glm::mat4 TANKBULLET = glm::mat4(1.0f);
			TANKBULLET = glm::translate(TANKBULLET, glm::vec3(this->x, this->y, this->z));
			TANKBULLET = glm::rotate(TANKBULLET, glm::radians(this->r), glm::vec3(0, 1, 0));
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TANKBULLET));
			glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, triangles);
		}
		else return;
	}

	bool block_collide(float extraX, float extraY, float extraZ, int shape) {
		// 장애물 사이즈 1:1x1 2:2x1 3:1x2
		float left, right, top, bottom;
		float extra_left = 0, extra_right = 0, extra_top = 0, extra_bottom = 0;
		left = this->x - this->size / 2;
		right = this->x + this->size / 2;
		top = this->z + this->size / 2;
		bottom = this->z - this->size / 2;
		switch (shape) {

		case 1:
			extra_left = extraX - 0.5f;
			extra_right = extraX + 0.5f;
			extra_top = extraZ + 0.5f;
			extra_bottom = extraZ - 0.5f;
			break;

		case 2:
			extra_left = extraX - 0.5f;
			extra_right = extraX + 1.5f;
			extra_top = extraZ + 0.5f;
			extra_bottom = extraZ - 0.5f;
			break;

		case 3:
			extra_left = extraX - 0.5f;
			extra_right = extraX + 0.5f;
			extra_top = extraZ + 1.5f;
			extra_bottom = extraZ - 0.5f;
			break;
		}
		if (left <= extra_right && left >= extra_left && top <= extra_top && top >= extra_bottom) return true;
		if (right <= extra_right && right >= extra_left && top <= extra_top && top >= extra_bottom) return true;
		if (left <= extra_right && left >= extra_left && bottom <= extra_top && bottom >= extra_bottom) return true;
		if (right <= extra_right && right >= extra_left && bottom <= extra_top && bottom >= extra_bottom) return true;
		return false;
	}
};

//탱크
class Tank {
public:
	GLuint VAO[4]; //[0]:탱크 몸통 [1]:포물선 [2]:탱크 머리 [3]:탱크 포신
	GLuint VBO_pos[4], VBO_nor[4], VBO_tex[4];
	Bullet *bullet[10];
	Point point[100] = {};
	float tankSpeed = 0.0f;
	float maxSpeed = 0.12f;
	float tankR = 0; //몸체 각도
	float headR = 0; //머리 각도
	float heady = 0.0f; //머리 애니메이션에 사용
	float maxRange = 10.0f;
	float minRange = 2.0f;
	float range = 4.3f;
	float size = 1.0f;
	float bulletSize = 0.1f;
	float x, y, z;
	unsigned int body_texture, head_texture, cannon_texture;
	int hp = 5;
	int bulletCnt = 0;
	int obj_body = 0, obj_head = 0, obj_cannon = 0;
	int head_frame = 0; //머리 흔들리는 애니메이션에 사용
	bool death = 0;
	bool moving = 0;
	bool push = 0;
	bool supermode = 1;
	
	Tank() : x{ 0 }, y{ 0 }, z{ 0 } { //탱크 생성자
		for (int i = 0; i < 10; i++) {
			this->bullet[i] = new Bullet();
		}
	}

	void draw(unsigned int modelLocation, unsigned int objColorLocation) {
		if(!this->death){
		//탱크 출력
		glm::mat4 TANK = glm::mat4(1.0f);
		TANK = glm::translate(TANK, glm::vec3(this->x, 0.0f, this->z));
		TANK = glm::rotate(TANK, glm::radians(this->tankR + 90.0f), glm::vec3(0, 1, 0));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TANK));
		glUniform3f(objColorLocation, 0.7, 0.7, 0.7);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->body_texture);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, this->obj_body);
		
		//머리 출력
		glm::mat4 HEAD = glm::mat4(1.0f);
		if (this->head_frame >= 3) {
			this->head_frame = 0;
			if (this->heady > 0.0f) this->heady = 0.0f;
			else this->heady = 0.03f;
		}
		this->head_frame++;
		HEAD = glm::translate(HEAD, glm::vec3(this->x, this->heady, this->z));
		HEAD = glm::rotate(HEAD, glm::radians(this->headR + this->tankR + 90.0f), glm::vec3(0, 1, 0));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(HEAD));
		glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->head_texture);
		glBindVertexArray(VAO[2]);
		glDrawArrays(GL_TRIANGLES, 0, this->obj_head);

		//발사구 출력
		glm::mat4 CANNON = glm::mat4(1.0f);
		CANNON = HEAD;
		CANNON = glm::translate(CANNON, glm::vec3(0.0f, 0.7f, 0));
		//포신 각도 변환 들어가야함
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(CANNON));
		glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, this->cannon_texture);
		glBindVertexArray(VAO[3]);
		glDrawArrays(GL_TRIANGLES, 0, this->obj_cannon);

		//총알 출력
		for (int i = 0; i < 10; i++) this->bullet[i]->draw(bullet_ally_VAO, bullet_ally_obj, rifle_texture, modelLocation, objColorLocation);

		//포물선 출력
		for (int i = 0; i < 100; i += 9) {
			glm::mat4 POINT = glm::mat4(1.0f);
			POINT = glm::translate(POINT, glm::vec3(this->point[i].x, this->point[i].y, this->point[i].z));
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(POINT));
			glUniform3f(objColorLocation, 0.0, 0.0, 0.0);
			glPointSize(5);
			glBindVertexArray(VAO[1]);
			glDrawArrays(GL_POINTS, 0, 1);
		}
		}
	}

	void move(int straight){ //이동 함수
		if (straight > 0) {
			if (moving == 1 && this->tankSpeed <= this->maxSpeed) this->tankSpeed += 0.004f;
			else if (keyStates[5] && moving == 0) {
				this->tankSpeed -= 0.006f;
				if (this->tankSpeed <= 0.0f) { this->tankSpeed = 0.0f; keyStates[5] = false;}
			}
		}
		else if(straight < 0) {
			if (moving == 1 && this->tankSpeed >= (-1.0f * this->maxSpeed)) this->tankSpeed -= 0.004f;
			else if (keyStates[7] && moving == 0) {
				this->tankSpeed += 0.006f;
				if ( this->tankSpeed >= 0.0f) { this->tankSpeed = 0.0f; keyStates[7] = false; }
			}
		}
		float nextx = this->x + cos(-this->tankR * PI) * (3 * this->tankSpeed);
		float nextz = this->z + sin(-this->tankR * PI) * (3 * this->tankSpeed);
		if (nextx >= 24.6f || nextx <= -24.6f) this->x = this->x;
		else this->x = this->x + cos(-this->tankR * PI) * this->tankSpeed;
		if (nextz >= 24.6f || nextz <= -24.6f) this->z = this->z;
		else this->z = this->z + sin(-this->tankR * PI) * this->tankSpeed;
	}

	void update() {
		for (int i = 0; i < 10; i++) this->bullet[i]->move();

		//포물선 업데이트
		float gap = this->range / 100.0f;
		float gravity = 0.02f / 100.0f;
		float height_accel = 2.0f / 100.0f;
		for (int i = 0; i < 100; i++) {
			this->point[i].x = this->x + cos(-(this->tankR + this->headR) * PI) * (float)(gap * i);
			this->point[i].z = this->z + sin(-(this->tankR + this->headR) * PI)* (float)(gap * i);
			this->point[i].y = 0.1f + height_accel * i;
			height_accel -= gravity;
		}
	}

	void attack() { //공격 함수
		this->bullet[this->bulletCnt]->active = 1;
		this->bullet[this->bulletCnt]->tic = 0; 
		for (int i = 0; i < 100; i++) this->bullet[bulletCnt]->point[i] = this->point[i];
		this->bullet[this->bulletCnt]->r = this->headR + this->tankR;
		this->bulletCnt = (this->bulletCnt + 1) % 9;

		if (this->supermode) {
			float gap = this->range / 100.0f;
			this->bullet[this->bulletCnt]->active = 1;
			this->bullet[this->bulletCnt]->tic = 0;
			this->bullet[this->bulletCnt + 1]->active = 1;
			this->bullet[this->bulletCnt + 1]->tic = 0;
			for (int i = 0; i < 100; i++) {
				this->bullet[bulletCnt]->point[i].x = this->x + cos(-(this->tankR + this->headR - 15) * PI) * (float)(gap * i);
				this->bullet[bulletCnt]->point[i].y = this->point[i].y;
				this->bullet[bulletCnt]->point[i].z = this->z + sin(-(this->tankR + this->headR - 15) * PI) * (float)(gap * i);
				this->bullet[this->bulletCnt]->r = this->headR + this->tankR;
				this->bullet[this->bulletCnt]->size = this->bulletSize;
				this->bullet[bulletCnt + 1]->point[i].x = this->x + cos(-(this->tankR + this->headR + 15) * PI) * (float)(gap * i);
				this->bullet[bulletCnt + 1]->point[i].y = this->point[i].y;
				this->bullet[bulletCnt + 1]->point[i].z = this->z + sin(-(this->tankR + this->headR + 15) * PI) * (float)(gap * i);
				this->bullet[this->bulletCnt + 1]->r = this->headR + this->tankR;
				this->bullet[this->bulletCnt + 1]->size = this->bulletSize;
			}
		}
	}

	void hit() {
		this->hp -= 1;
		if (this->hp <= 0) this->death = 1;
	}

	void upgrade(int skill) {
		switch (skill) {
		case 0: this->bulletSize += 0.1f; break;
		case 1: this->size += 0.1f; break;
		case 2: this->maxRange + 0.1f; break;
		case 3: this->hp += 5; break;
		case 4: break;
		}
	}

	bool collide(float extraX, float extraY, float extraZ, float extraSize) {
		float distance = sqrt((this->x - extraX) * (this->x - extraX) + (this->y - extraY) * (this->y - extraY) + (this->z - extraZ) * (this->z - extraZ));
		if (extraSize * sqrt(2) + this->size * sqrt(2) >= distance) return true;
		return false;
	}
	
	bool block_collide(float extraX, float extraY, float extraZ, int shape) {
		// 장애물 사이즈 1:1x1 2:2x1 3:1x2
		float left, right, top, bottom;
		float extra_left = 0, extra_right =0, extra_top = 0, extra_bottom = 0;
		left = this->x - this->size / 2; 
		right = this->x + this->size / 2; 
		top = this->z + this->size / 2; 
		bottom = this->z - this->size / 2;
		switch (shape) {

		case 1:
			extra_left = extraX - 0.5f; 
			extra_right = extraX + 0.5f; 
			extra_top = extraZ + 0.5f; 
			extra_bottom = extraZ - 0.5f;
			break;

		case 2:
			extra_left = extraX - 0.5f;
			extra_right = extraX + 1.5f;
			extra_top = extraZ + 0.5f;
			extra_bottom = extraZ - 0.5f;
			break;

		case 3:
			extra_left = extraX - 0.5f;
			extra_right = extraX + 0.5f;
			extra_top = extraZ + 1.5f;
			extra_bottom = extraZ - 0.5f;
			break;
		}
		if (left <= extra_right && left >= extra_left && top <= extra_top && top >= extra_bottom) return true;
		if (right <= extra_right && right >= extra_left && top <= extra_top && top >= extra_bottom) return true;
		if (left <= extra_right && left >= extra_left && bottom <= extra_top && bottom >= extra_bottom) return true;
		if (right <= extra_right && right >= extra_left && bottom <= extra_top && bottom >= extra_bottom) return true;
		return false;
	}
};

//병사
GLuint rifle_VAO;
GLuint rifle_VBO[3];
int rifle_obj;
class RifleMan {
public:
	time_t attack_timer = 0;
	Bullet bullet[3];
	float speed = 0.01;
	float x, y, z;
	float rotate = 0;
	float range = 2.0f;
	float size = 1.0f;
	int reload = 1;
	int hp = 1;
	int power = 0;
	int condition = 0;
	bool active = 0;

	void spawn(int level) { //소환
		this->active = 1;
		while (-1) {
			int x = rand() % 50;
			int z = rand() % 50;
			if (map[z][x] == 0) {
				this->x = (x - 25) + 0.5f;
				this->y = 0.1f;
				this->z = (z - 25) + 0.5f;
				break;
			}
		}
		this->power = level;
	}

	void draw(unsigned int modelLocation, unsigned int objColorLocation) {
		if (this->active) {
			glm::mat4 RIFLE = glm::mat4(1.0f);
			RIFLE = glm::translate(RIFLE, glm::vec3(this->x, this->y, this->z));
			RIFLE = glm::rotate(RIFLE, -this->rotate + 90.0f, glm::vec3(0,1,0));
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(RIFLE));
			glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, rifle_texture);
			glBindVertexArray(rifle_VAO);
			glDrawArrays(GL_TRIANGLES, 0, rifle_obj);
		}
		this->bullet[0].draw(bullet_enemy_VAO, bullet_enemy_obj, rifle_texture, modelLocation, objColorLocation);
	}

	void move(float tankX, float tankZ) {
		float distance = sqrt((tankZ - this->z) * (tankZ - this->z) + (tankX - this->x) * (tankX - this->x)); //간격
		this->rotate = atan2((tankZ - this->z), (tankX - this->x));
		if (distance > this->range && this->condition == 0) { //사정거리 보다 멀면 이동
			this->x += cos(this->rotate) * this->speed;
			this->z += sin(this->rotate) * this->speed;
		}
		else this->attack();

		//총알 이동
		this->bullet[0].enemy_move();
	}

	void update(float tankX, float tankZ) {
		if (this->active) {
			this->move(tankX, tankZ);
		}
	}

	void hit() {
		if (this->active) {
			this->hp -= 1;
			if (this->hp <= 0) { 
				this->active = 0; 
				playingKill();
			}
		}
	}

	void attack() {
		if (time(NULL) - this->attack_timer > this->reload) {
			PlaySound(TEXT("explosion.wav"), NULL, SND_ASYNC | SND_NOSTOP);
			this->attack_timer = time(NULL);
			this->bullet[0].active = 1;
			this->bullet[0].x = this->x;
			this->bullet[0].y = 0.01f;
			this->bullet[0].z = this->z;
			this->bullet[0].r = this->rotate;
		}
	}

	bool collide(float extraX, float extraY, float extraZ,  float extraSize) {
		float distance = sqrt((this->x - extraX) * (this->x - extraX) + (this->y - extraY)* (this->y-extraY) +(this->z - extraZ) * (this->z - extraZ));
		if (extraSize * sqrt(2) + this->size * sqrt(2) >= distance) return true;
		return false;
	}
};

GLuint block_VAO[2];
GLuint block_VBO[2][3];
unsigned int block_texture; //장애물 텍스처는 한 파일로 처리했음
int block_obj[2];
class Block {
public:
	float x, y, z;
	float blocky = 0.0f;
	int shape = 0; // 장애물 사이즈 1:1x1 2:2x1 3:1x2

	void getPos(float x, float y, float z) {
		this->x = x; this->y = y; this->z = z;
	}

	void draw(unsigned int modelLocation, unsigned int objColorLocation) {
		if (this->shape == 3)
			blocky = -90.0f;
		glm::mat4 BLOCK = glm::mat4(1.0f);
		BLOCK = glm::translate(BLOCK, glm::vec3(this->x, this->y, this->z));
		BLOCK = glm::rotate(BLOCK, (GLfloat)glm::radians(blocky), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(BLOCK));
		glUniform3f(objColorLocation, 0.7, 0.7, 0.7);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, block_texture);
		if (this->shape == 1) {
			glBindVertexArray(block_VAO[0]);
			glDrawArrays(GL_TRIANGLES, 0, block_obj[0]);
		}
		else {
			glBindVertexArray(block_VAO[1]);
			glDrawArrays(GL_TRIANGLES, 0, block_obj[1]);
		}
	}
};

class Item {
public:
	float x, y, z;
	float size = 0.1;
	float speed = 0.005;
	int skill = 0;
	bool active = 0;
	bool onfoot = 0;

	void draw(unsigned int modelLocation, unsigned int objColorLocation) {
		if (this->active) {
			glm::mat4 ITEM = glm::mat4(1.0f);
			ITEM = glm::translate(ITEM, glm::vec3(this->x, this->y, this->z));
			ITEM = glm::scale(ITEM, glm::vec3(this->size, this->size, this->size));
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(ITEM));
			glUniform3f(objColorLocation, 0.0, 0.0, 0.7);
			glBindVertexArray(VAO[1]);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	void spawn() {
		this->onfoot = 0;
		this->active = 1;
		while (-1) {
			int x = rand() % 50;
			int z = rand() % 50;
			if (map[z][x] == 0) {
				this->x = (x - 25) + 0.5f;
				this->y = 5.10f;
				this->z = (z - 25) + 0.5f;
				this->skill = rand() % 3;
				break;
			}
		}
	}

	void update() {
		if (this->active) {
			this->move();
		}
	}

	void move() {
		if (!this->onfoot) {
			if (this->y <= this->size / 2) { this->y = this->size / 2; this->onfoot = 1; }
			else this->y -= this->speed;
		}
	}
};


Tank tank;

Block block[BLOCK_AMOUNT];

RifleMan rifle[RIFLE_AMOUNT];

Item item[ITEM_AMOUNT];

void setBlock() {
	map[24][24] = true;
	map[24][25] = true;
	map[25][24] = true;
	map[25][25] = true;

	for (int i = 0; i < BLOCK_AMOUNT; i++) {
		while (1) {
			block[i].shape = (rand() % 3) + 1;
			if (block[i].shape == 1) {
				int x = rand() % 50;
				int z = rand() % 50;
				if (!map[z][x]) {
					block[i].x = (x - 25) + 0.5f;
					block[i].y = 0.0f;
					block[i].z = (z - 25) + 0.5f;
					map[z][x] = true;
					break;
				}
			}
			else if (block[i].shape == 2 || block[i].shape == 3) {
				int x = rand() % 49;
				int z = rand() % 49;
				if (!map[z][x]) {
					block[i].x = (x - 25) + 0.5f;
					block[i].y = 0.0f;
					block[i].z = (z - 25) + 0.5f;

					map[z][x] = true;
					if (block[i].shape == 2)
						map[z][x + 1] = true;
					else if (block[i].shape == 3)
						map[z + 1][x] = true;
					break;
				}
			}
		}
	}
}