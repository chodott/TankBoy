#include "callback.h"

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
	//PlaySound(TEXT("background.wav"), NULL, SND_ASYNC | SND_LOOP|SND_NOSTOP);
	//playingBgm();
	for (int i = 0; i < 256; i++) keyStates[i] = false; //키 값 초기화
	start = time(NULL); //시작 시간 설정
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	//create shader program
	GLuint vShader;
	GLuint fShader;

	vShader = MakeVertexShader("vertex.glsl", 0);
	fShader = MakeFragmentShader("fragment.glsl", 0);
	//shader program
	s_program[0] = glCreateProgram();
	glAttachShader(s_program[0], vShader);
	glAttachShader(s_program[0], fShader);
	glLinkProgram(s_program[0]);
	checkCompileErrors(s_program[0], "PROGRAM");

	setBlock();
	glEnable(GL_DEPTH_TEST);
	InitBuffer();
	InitTexture();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(UpKeyboard);
	glutSpecialFunc(Special);
	glutSpecialUpFunc(UpSpecial);
	glutTimerFunc(100, Timer, 1);
	glutMainLoop();
}
