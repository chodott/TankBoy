#include "figure.h"
#include "shader.h"
#include "callback.h"
#include "objRead.cpp"

GLchar* vertexSource;
GLchar* fragmentSource;

void main(int argc, char** argv)
{
	//윈도우 생성
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example1");
	srand(time(NULL));
	//GLEW 초기화하기
	for (int i = 0; i < 256; i++) keyStates[i] = false; //키 값 초기화

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	//create shader program
	GLuint vShader[4];
	GLuint fShader[4];

	vShader[0] = MakeVertexShader("vertex.glsl", 0);			// Sun
	fShader[0] = MakeFragmentShader("fragment.glsl", 0);
	//shader program
	s_program[0] = glCreateProgram();
	glAttachShader(s_program[0], vShader[0]);
	glAttachShader(s_program[0], fShader[0]);
	glLinkProgram(s_program[0]);
	checkCompileErrors(s_program[0], "PROGRAM");


	glEnable(GL_DEPTH_TEST);
	InitBuffer();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(UpKeyboard);
	glutSpecialFunc(Special);
	glutSpecialUpFunc(UpSpecial);
	glutTimerFunc(100, Timer, 1);
	glutMainLoop();
}
