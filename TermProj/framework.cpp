#include "framework.h"
#include "stb_image.h"
#include "Bullet.h"

#define BLOCK_AMOUNT 50

int Framework::loadObj(const char* filename)
{
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	FILE* objFile;

	fopen_s(&objFile, filename, "rb");

	if (objFile == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}
	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(objFile, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(objFile, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

			if (vertex.x < minX) minX = vertex.x;
			if (vertex.y < minY) minY = vertex.y;
			if (vertex.z < minZ) minZ = vertex.z;
			if (vertex.x > maxX) maxX = vertex.x;
			if (vertex.y > maxY) maxY = vertex.y;
			if (vertex.z > maxZ) maxZ = vertex.z;
			sumX += vertex.x;
			sumY += vertex.y;
			sumZ += vertex.z;

			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(objFile, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(objFile, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(objFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	std::cout << "minX: " << minX << " minY: " << minY << " minZ: " << minZ << std::endl;
	std::cout << "maxX: " << maxX << " maxY: " << maxY << " maxZ: " << maxZ << std::endl;

	aveX = sumX / vertexIndices.size();
	aveY = sumY / vertexIndices.size();
	aveZ = sumZ / vertexIndices.size();
	scaleX = (1.0 - maxX) * 10 + 1;
	scaleY = (1.0 - maxY) * 10 + 1;
	scaleZ = (1.0 - maxZ) * 10 + 1;

	if (scaleX > scaleY) {
		if (scaleY > scaleZ)
			scaleAll = scaleZ;
		else
			scaleAll = scaleY;
	}
	else if (scaleX < scaleY) {
		if (scaleX < scaleZ)
			scaleAll = scaleX;
		else
			scaleAll = scaleZ;
	}
	std::cout << "aveX: " << aveX << " aveY: " << aveY << " aveZ: " << aveZ << std::endl;

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		outvertex.push_back(vertex);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 vertex = temp_uvs[uvIndex - 1];
		outuv.push_back(vertex);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 vertex = temp_normals[normalIndex - 1];
		outnormal.push_back(vertex);
	}

	return outvertex.size();
}


int Framework::loadObj_normalize_center(const char* filename)
{
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	FILE* objFile;

	fopen_s(&objFile, filename, "rb");

	if (objFile == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}
	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(objFile, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(objFile, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

			if (vertex.x < minX) minX = vertex.x;
			if (vertex.y < minY) minY = vertex.y;
			if (vertex.z < minZ) minZ = vertex.z;
			if (vertex.x > maxX) maxX = vertex.x;
			if (vertex.y > maxY) maxY = vertex.y;
			if (vertex.z > maxZ) maxZ = vertex.z;
			sumX += vertex.x;
			sumY += vertex.y;
			sumZ += vertex.z;

			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(objFile, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(objFile, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(objFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	std::cout << "minX: " << minX << " minY: " << minY << " minZ: " << minZ << std::endl;
	std::cout << "maxX: " << maxX << " maxY: " << maxY << " maxZ: " << maxZ << std::endl;

	aveX = sumX / vertexIndices.size();
	aveY = sumY / vertexIndices.size();
	aveZ = sumZ / vertexIndices.size();
	scaleX = maxX - minX;
	scaleY = maxY - minY;
	scaleZ = maxZ - minZ;

	glm::vec3 temp;

	std::cout << "aveX: " << aveX << " aveY: " << aveY << " aveZ: " << aveZ << std::endl;

	std::cout << "scaleX: " << scaleX << " scaleY: " << scaleY << " scaleZ: " << scaleZ << std::endl;

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		temp = temp_vertices[vertexIndex - 1];
		temp.x = temp.x - minX;
		temp.y = temp.y - minY;
		temp.z = temp.z - minZ;

		temp.x = ((temp.x * 2.0f) / scaleX) - 1.0f;
		temp.y = ((temp.y * 2.0f) / scaleY) - 1.0f;
		temp.z = ((temp.z * 2.0f) / scaleZ) - 1.0f;

		outvertex.push_back(temp);
		//glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		//outvertex.push_back(vertex);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 vertex = temp_uvs[uvIndex - 1];
		outuv.push_back(vertex);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 vertex = temp_normals[normalIndex - 1];
		outnormal.push_back(vertex);
	}

	return outvertex.size();
}

void Framework::InitBuffer()
{
	//벽
	glGenVertexArrays(3, Plate::VAO);
	glGenBuffers(3, Plate::VBO);
	glBindVertexArray(Plate::VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, Plate::VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Plate::plate), Plate::plate, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//큐브
	glBindVertexArray(Plate::VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, Plate::VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Plate::cube), Plate::cube, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//탱크(임의)
	ATank::obj_body = loadObj("tank_body.obj");
	cout << "탱크 삼각형 수" << ATank::obj_body << endl;

	glGenBuffers(4, ATank::VBO_pos);
	glGenBuffers(4, ATank::VBO_nor);
	glGenBuffers(4, ATank::VBO_tex);

	glGenVertexArrays(4, ATank::VAO);
	glBindVertexArray(ATank::VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, ATank::VBO_pos[0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	outvertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, ATank::VBO_nor[0]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	outnormal.clear();

	glBindBuffer(GL_ARRAY_BUFFER, ATank::VBO_tex[0]);
	glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	outuv.clear();

	//탱크 머리
	ATank::obj_head = loadObj("tank_head.obj");

	glBindVertexArray(ATank::VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, ATank::VBO_pos[2]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	outvertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, ATank::VBO_nor[2]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	outnormal.clear();

	glBindBuffer(GL_ARRAY_BUFFER, ATank::VBO_tex[2]);
	glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	outuv.clear();

	//탱크 포신
	ATank::obj_cannon = loadObj("tank_cannon.obj");

	glBindVertexArray(ATank::VAO[3]);
	glBindBuffer(GL_ARRAY_BUFFER, ATank::VBO_pos[3]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	outvertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, ATank::VBO_nor[3]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	outnormal.clear();

	glBindBuffer(GL_ARRAY_BUFFER, ATank::VBO_tex[3]);
	glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	outuv.clear();

	Obstacle::block_obj[0] = loadObj("obsta1x1.obj");

	glGenVertexArrays(2, Obstacle::VAO);

	glGenBuffers(3, Obstacle::VBO[0]); //1x1사이즈 장애물
	glBindVertexArray(Obstacle::VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, Obstacle::VBO[0][0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	outvertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, Obstacle::VBO[0][1]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	outnormal.clear();

	glBindBuffer(GL_ARRAY_BUFFER, Obstacle::VBO[0][2]);
	glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	outuv.clear();

	Obstacle::block_obj[1] = loadObj("obsta2x1.obj");

	glGenBuffers(3, Obstacle::VBO[1]); //2x1사이즈 장애물
	glBindVertexArray(Obstacle::VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, Obstacle::VBO[1][0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	outvertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, Obstacle::VBO[1][1]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	outnormal.clear();

	glBindBuffer(GL_ARRAY_BUFFER, Obstacle::VBO[1][2]);
	glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	outuv.clear();

	//라이플맨
	ARifleMan::rifle_obj = loadObj("rifle.obj");
	cout << "라이플맨 삼각형 수" << ARifleMan::rifle_obj << endl;

	glGenBuffers(3, ARifleMan::VBO);

	glGenVertexArrays(1, &ARifleMan::VAO);
	glBindVertexArray(ARifleMan::VAO);

	glBindBuffer(GL_ARRAY_BUFFER, ARifleMan::VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	outvertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, ARifleMan::VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	outnormal.clear();

	glBindBuffer(GL_ARRAY_BUFFER, ARifleMan::VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	outuv.clear();

	//바주카맨
	ABazookaMan::bazooka_obj = loadObj("bazooka.obj");
	cout << "바주카맨 삼각형 수" << ABazookaMan::bazooka_obj << endl;

	glGenBuffers(3, ABazookaMan::VBO);

	glGenVertexArrays(1, &ABazookaMan::VAO);
	glBindVertexArray(ABazookaMan::VAO);

	glBindBuffer(GL_ARRAY_BUFFER, ABazookaMan::VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	outvertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, ABazookaMan::VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	outnormal.clear();

	glBindBuffer(GL_ARRAY_BUFFER, ABazookaMan::VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	outuv.clear();

	//Bullet
	ABullet::bullet_obj = loadObj("bullet_ally.obj");

	glGenBuffers(3, ABullet::bullet_VBO);

	glGenVertexArrays(1, &ABullet::bullet_VAO);
	glBindVertexArray(ABullet::bullet_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, ABullet::bullet_VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	outvertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, ABullet::bullet_VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	outnormal.clear();

	glBindBuffer(GL_ARRAY_BUFFER, ABullet::bullet_VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	outuv.clear();

	//아이템
	Item::item_obj = loadObj("item.obj");

	glGenBuffers(3, Item::VBO);

	glGenVertexArrays(1, &Item::VAO);
	glBindVertexArray(Item::VAO);

	glBindBuffer(GL_ARRAY_BUFFER, Item::VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	outvertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, Item::VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	outnormal.clear();

	glBindBuffer(GL_ARRAY_BUFFER, Item::VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	outuv.clear();

	//UI


	Title::title_obj[0] = loadObj("title_logo.obj");
	Title::title_obj[1] = loadObj("title_start.obj");
	Title::title_obj[2] = loadObj("title_quit.obj");

	for (int i = 0; i < 3; ++i)
	{
		switch (i)
		{
		case 0: Title::title_obj[i] = loadObj("title_logo.obj"); break;
		case 1:Title::title_obj[i] = loadObj("title_start.obj"); break;
		case 2:Title::title_obj[i] = loadObj("title_quit.obj"); break;
		}
		glGenVertexArrays(1, &Title::VAO[i]);

		glGenBuffers(3, Title::VBO[i]);
		glBindVertexArray(Title::VAO[i]);
		glBindBuffer(GL_ARRAY_BUFFER, Title::VBO[i][0]);
		glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		outvertex.clear();

		glBindBuffer(GL_ARRAY_BUFFER, Title::VBO[i][1]);
		glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
		outnormal.clear();

		glBindBuffer(GL_ARRAY_BUFFER, Title::VBO[i][2]);
		glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		glEnableVertexAttribArray(2);
		outuv.clear();
	}
	makeMap();
}

void Framework::InitTexture()
{
	int widthImage, heightImage, numberOfChannel;
	stbi_set_flip_vertically_on_load(true);

	widthImage = 512;
	heightImage = 512;
	numberOfChannel = 0;

	glGenTextures(1, &Wall::ground_texture);

	glBindTexture(GL_TEXTURE_2D, Wall::ground_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data0 = stbi_load("room_ground.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data0);

	glGenTextures(1, &Wall::wall_texture); //벽

	glBindTexture(GL_TEXTURE_2D, Wall::wall_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data5 = stbi_load("room_wall.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data5);

	glGenTextures(1, &ATank::body_texture);

	glBindTexture(GL_TEXTURE_2D, ATank::body_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data1 = stbi_load("tank_body_diffuse.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);

	glGenTextures(1, &ATank::head_texture);

	glBindTexture(GL_TEXTURE_2D, ATank::head_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data2 = stbi_load("tank_head_diffuse.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);

	glGenTextures(1, &ATank::cannon_texture);

	glBindTexture(GL_TEXTURE_2D, ATank::cannon_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data3 = stbi_load("tank_cannon_diffuse.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data3);

	glGenTextures(1, &Obstacle::block_texture);

	glBindTexture(GL_TEXTURE_2D, Obstacle::block_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data4 = stbi_load("obsta_diffuse.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data4);

	glGenTextures(1, &ARifleMan::rifle_texture); //소총병, 탄환 색

	glBindTexture(GL_TEXTURE_2D, ARifleMan::rifle_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data6 = stbi_load("rifle.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data6);

	glGenTextures(1, &ABazookaMan::bazooka_texture); //소총병, 탄환 색

	glBindTexture(GL_TEXTURE_2D, ABazookaMan::bazooka_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data7 = stbi_load("bazooka.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data7);

	glGenTextures(1, &Item::item_texture); //소총병, 탄환 색

	glBindTexture(GL_TEXTURE_2D, Item::item_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data8 = stbi_load("item.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data8);

	glGenTextures(1, &Title::title_texture);

	glBindTexture(GL_TEXTURE_2D, Title::title_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data9 = stbi_load("title_diffuse.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data9);


	stbi_image_free(data0);
	stbi_image_free(data1);
	stbi_image_free(data2);
	stbi_image_free(data3);
	stbi_image_free(data4);
	stbi_image_free(data5);
	stbi_image_free(data6);
	stbi_image_free(data7);
	stbi_image_free(data8);
	stbi_image_free(data9);
}

void Framework::keyInput(unsigned char key, bool bPush)
{
	if (bStarted == false && key == ' ')
	{
		if (onStartButton) bStarted = true;
		else exit(1);
	}
	controller->keyInput(key, bPush);
}

void Framework::keyInput(int key, bool bPush)
{
	if (bStarted == false && bPush)
	{
		switch (key)
		{
		case GLUT_KEY_UP:
		case GLUT_KEY_DOWN:
			onStartButton = onStartButton ? false : true;
			break;
		}
		return;
	}
	controller->keyInput(key, bPush);
}

void Framework::makeMap()
{
	map[24][24] = true;
	map[24][25] = true;
	map[25][24] = true;
	map[25][25] = true;

	for (int i = 0; i < BLOCK_AMOUNT; i++) {
		Obstacle* block = new Obstacle();
		object_vec[2].emplace_back(block);
		int shape = 0;
		while (1) {
			shape = (rand() % 3) + 1;
			if (shape == 1) {
				int x = rand() % 50;
				int z = rand() % 50;
				if (!map[z][x]) {
					x = (x - 25) + 0.5f;
					z = (z - 25) + 0.5f;
					block->setPos(x, z, shape);
					map[z][x] = true;
					break;
				}
			}
			else if (shape == 2 || shape == 3) {
				int x = rand() % 49;
				int z = rand() % 49;
				if (!map[z][x]) {
					x = (x - 25) + 0.5f;
					z = (z - 25) + 0.5f;
					block->setPos(x, z, shape);
					map[z][x] = true;
					if (shape == 2)
						map[z][x + 1] = true;
					else if (shape == 3)
						map[z + 1][x] = true;
					break;
				}
			}
		}
	}
}

void Framework::spawn(int level)
{
	if (bStarted == false) return;

	time_t now = time(NULL) - start_time;

	int x = rand() % 50;
	int z = rand() % 50;
	if (map[25][25] == 0) 
	{
		x = (x - 25) + 0.5f;
		z = (z - 25) + 0.5f;
	}

	if (now - ARifleMan::spawnTime > ARifleMan::spawnLength)
	{
		ARifleMan* rifleman = new ARifleMan(x, z, level, controller->getPlayer());
		ARifleMan::spawnTime = now;
		object_vec[ENEMY].emplace_back(rifleman);
	}

	if (now - ABazookaMan::spawnTime > ABazookaMan::spawnLength)
	{
		ABazookaMan* bazookaman = new ABazookaMan(x, z, level, controller->getPlayer());
		ABazookaMan::spawnTime = now;
		object_vec[ENEMY].emplace_back(bazookaman);
	}

	if (now - Item::spawnTime > Item::spawnLength)
	{
		Item* item = new Item(x, z);
		Item::spawnTime = now;
		object_vec[ITEM].emplace_back(item);
	}
}

void Framework::draw(GLuint s_program)
{
	unsigned int modelLocation = glGetUniformLocation(s_program, "modelTransform");
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform");
	unsigned int	projLoc = glGetUniformLocation(s_program, "projection");
	unsigned int viewPos = glGetUniformLocation(s_program, "viewPos");
	unsigned int objColorLocation = glGetUniformLocation(s_program, "objectColor");

	glm::vec3 playerPos = controller->getPlayerPos();
	//뷰 변환
	glm::vec3 cameraPos = glm::vec3(playerPos.x + 5.0f, 10.0f, playerPos.z + 5.0f); //--- 카메라 위치
	glm::vec3 cameraTarget = glm::vec3(playerPos.x, 0.5f, playerPos.z);
	glm::vec3 cameraDirection = glm::normalize(-cameraPos + cameraTarget); //--- 카메라 바라보는 방향
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향
	glm::vec3 cameraRight = glm::cross(Up, cameraDirection);
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraTarget, cameraUp);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
	glUniform3fv(viewPos, 1, glm::value_ptr(cameraPos));

	//투영 변환
	glm::mat4 proj = glm::mat4(1.0f);
	proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 50.0f);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0][0]);

	//조명
	unsigned int lightPosLocation = glGetUniformLocation(s_program, "lightPos");
	unsigned int lightColorLocation = glGetUniformLocation(s_program, "lightColor");
	glUniform3f(lightPosLocation, 0, 5.0f, 0);
	glUniform3f(lightColorLocation, 1.0f, 1.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, Title::title_texture);
	glm::mat4 GAME_TITLE = glm::mat4(1.0f);
	GAME_TITLE = glm::translate(GAME_TITLE, glm::vec3(0.0, 3.0, 0.0));
	GAME_TITLE = glm::rotate(GAME_TITLE, glm::radians(45.0f), glm::vec3(0, 1, 0));
	GAME_TITLE = glm::rotate(GAME_TITLE, glm::radians(-45.0f), glm::vec3(1, 0, 0));
	GAME_TITLE = glm::scale(GAME_TITLE, glm::vec3(5, 5, 5));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(GAME_TITLE));
	glUniform3f(objColorLocation, 0.6, 0.6, 0.6);
	glBindVertexArray(Title::VAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, Title::title_obj[0]);

	glm::mat4 GAME_START = glm::mat4(1.0f);
	GAME_START = glm::translate(GAME_START, glm::vec3(3.0, 5.0, 3.0));
	GAME_START = glm::rotate(GAME_START, glm::radians(45.0f), glm::vec3(0, 1, 0));
	GAME_START = glm::rotate(GAME_START, glm::radians(-45.0f), glm::vec3(1, 0, 0));
	GAME_START = glm::scale(GAME_START, glm::vec3(5, 5, 5));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(GAME_START));
	if (onStartButton) glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
	else glUniform3f(objColorLocation, 0.6, 0.6, 0.6);
	glBindVertexArray(Title::VAO[1]);
	glDrawArrays(GL_TRIANGLES, 0, Title::title_obj[1]);

	glm::mat4 GAME_END = glm::mat4(1.0f);
	GAME_END = glm::translate(GAME_END, glm::vec3(3.4, 4.5, 3.4));
	GAME_END = glm::rotate(GAME_END, glm::radians(45.0f), glm::vec3(0, 1, 0));
	GAME_END = glm::rotate(GAME_END, glm::radians(-45.0f), glm::vec3(1, 0, 0));
	GAME_END = glm::scale(GAME_END, glm::vec3(5, 5, 5));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(GAME_END));
	if (!onStartButton) glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
	else glUniform3f(objColorLocation, 0.6, 0.6, 0.6);
	glBindVertexArray(Title::VAO[2]);
	glDrawArrays(GL_TRIANGLES, 0, Title::title_obj[2]);

	for (auto& objects : object_vec)
	{
		for (auto& object : objects)
		{
			object->draw(modelLocation, objColorLocation);
		}
	}
}

void Framework::update()
{
	spawn(1);
	for (auto& objects : object_vec)
	{
		for (auto& object : objects)
		{
			object->update();
		}
	}
	checkCollide();
	deleteTrash();
	update_level();
}

void Framework::checkCollide()
{
	for (int i = 0; i <= ITEM; ++i)
	{
		for (int j = 0; j <=ITEM; ++j)
		{
			if (i == j) continue;
			for (auto& obj_a : object_vec[i])
			{
				for (auto& obj_b : object_vec[j])
				{
					bool bCrashed = obj_a->returnCollide(obj_b);
					if (bCrashed == false) continue;
					obj_a->block();
					obj_b->block();
				}
			}
		}
	}
}

void Framework::deleteTrash()
{
	for (int type = ENEMY; type <= ITEM; ++type)
	{	//제거해야할 오브젝트 추출
		vector<Object*>& objects = object_vec[type];
		for (int index=0; index < objects.size(); ++index)
		{
			if (objects[index]->active == true) continue;
			delete_pq.push(make_pair(EObjectType(type), index));
		}
	}

	while (!delete_pq.empty())
	{	//오브젝트 벡터에서 제거
		auto& info = delete_pq.top();
		delete_pq.pop();
		int type = info.first;
		int index = info.second;
		vector<Object*>& objects = object_vec[type];
		delete(objects[index]);
		objects.erase(objects.begin() + index);
	}
}

void Framework::update_level()
{
	time_t startToNow = time(NULL) - start_time;
	if (startToNow >= 80 && GAME_LEVEL != 5) GAME_LEVEL = 5;
	else 	if (startToNow >= 60 && GAME_LEVEL != 4) GAME_LEVEL = 4;
	else 	if (startToNow >= 40 && GAME_LEVEL != 3) GAME_LEVEL = 3;
	else 	if (startToNow >= 20 && GAME_LEVEL != 2) GAME_LEVEL = 2;
}
