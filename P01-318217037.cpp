#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <glew.h>
#include <glfw3.h>
#include <time.h>
//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;
GLuint VAO, VBO, shader;

//Vertex Shader
//recibir color, salida Vcolor
static const char* vShader = "						\n\
#version 330										\n\
layout (location =0) in vec3 pos;					\n\
void main()											\n\
{													\n\
gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); 			\n\
}";
//recibir Vcolor y dar de salida color
static const char* fShader = "						\n\
#version 330										\n\
out vec4 color;										\n\
void main()											\n\
{													\n\
	color = vec4(1.0f,1.0f,1.0f,1.0f);	 			\n\
}";



void CrearTriangulo()
{
	GLfloat vertices[] = {
		//P
		-0.80f, -0.4f,  0.0f,
		-0.80f,  0.4f,  0.0f,
		-0.67f, -0.4f,  0.0f,
		-0.80f,  0.4f,  0.0f, //b
		-0.67f, -0.4f,  0.0f, //c
		-0.67f,  0.4f,  0.0f, //d
		-0.67f,  0.4f,  0.0f, //d
		-0.40f,  0.4f,  0.0f,
		-0.40f,  0.26f, 0.0f, //o
		-0.67f,  0.4f,  0.0f, //d
		-0.40f,  0.26f, 0.0f, //o
		-0.67f,  0.26f, 0.0f,
		-0.54f,  0.26f, 0.0f, //l
		-0.40f,  0.13f, 0.0f, //n 
		-0.40f,  0.26f, 0.0f, //o
		-0.54f,  0.26f, 0.0f, //l
		-0.40f,  0.13f, 0.0f, //n
		-0.54f,  0.13f, 0.0f,
		-0.67f,  0.13f, 0.0f, //j
		-0.40f,  0.13f, 0.0f, //n
		-0.40f,  0.00f, 0.0f, //f
		-0.67f,  0.13f, 0.0f, //j
		-0.40f,  0.00f, 0.0f, //f
		-0.67f,  0.00f, 0.0f,

		//A
		-0.20f,  0.4f,  0.0f, //i
		-0.20f, -0.4f,  0.0f,
		-0.07f, -0.4f,  0.0f, //u
		-0.20f,  0.4f,  0.0f, //i
		-0.07f, -0.4f,  0.0f, //u
		-0.07f,  0.4f,  0.0f, //b1
		-0.07f,  0.4f,  0.0f, //b1
		 0.07f,  0.4f,  0.0f, //c1
		 0.07f,  0.26f, 0.0f, //s
		-0.07f,  0.4f,  0.0f, //b1
		 0.07f,  0.26f, 0.0f, //s
		-0.07f,  0.26f, 0.0f, 
		0.07f,   0.4f,  0.0f, //c1
		0.20f,   0.4f,  0.0f,
		0.20f,  -0.4f,  0.0f,
		0.20f,  -0.4f,  0.0f,
		0.07f,   0.4f,  0.0f, //c1
		0.07f,  -0.4f,  0.0f,
		-0.07f,  0.13f, 0.0f, 
		 0.07f,  0.13f, 0.0f, 
		 0.07f,  0.0f,  0.0f, 
		-0.07f,  0.13f, 0.0f, 
		0.07f,   0.0f,   0.0f, 
		-0.07f,  0.0f,  0.0f, 
		
		//R
		0.4f,  -0.4f, 0.0f,
		0.4f,   0.4f, 0.0f,
		0.53f, -0.4f, 0.0f,
		0.4f,   0.4f, 0.0f,
		0.53f, -0.4f, 0.0f,
		0.53f,  0.4f, 0.0f,
		0.53f,  0.4f, 0.0f,
		0.80f,  0.4f, 0.0f,
		0.80f,  0.26f, 0.0f,
		0.80f,  0.26f, 0.0f,
		0.53f,  0.4f, 0.0f,
		0.53f, 0.26f, 0.0f,
		0.67f, 0.26f, 0.0f,
		0.80f,  0.26f, 0.0f,
		0.80f,  0.13f, 0.0f,
		0.67f, 0.26f, 0.0f,
		0.80f,  0.13f, 0.0f,
		0.67f, 0.13f, 0.0f,
		0.53f, 0.13f, 0.0f,
		0.80f, 0.13f, 0.0f,
		0.80f, 0.0f, 0.0f,
		0.80f, 0.0f, 0.0f,
		0.53f, 0.0f, 0.0f,
		0.53f, 0.13f, 0.0f,
		0.4f, 0.26f, 0.0f,
		0.70f, -0.4f, 0.0f,
		0.80f, -0.3f, 0.0f,

	};
	glGenVertexArrays(1, &VAO); //generar 1 VAO
	glBindVertexArray(VAO);//asignar VAO

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, los datos y en este caso es estático pues no se modificarán los valores

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
		glEnableVertexAttribArray(0);
		//agregar valores a vèrtices y luego declarar un nuevo vertexAttribPointer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

}
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) //Función para agregar los shaders a la tarjeta gráfica
//the Program recibe los datos de theShader


{
	GLuint theShader = glCreateShader(shaderType);//theShader es un shader que se crea de acuerdo al tipo de shader: vertex o fragment
	const GLchar* theCode[1];
	theCode[0] = shaderCode;//shaderCode es el texto que se le pasa a theCode
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);//longitud del texto
	glShaderSource(theShader,1, theCode, codeLength);//Se le asigna al shader el código
	glCompileShader(theShader);//Se comila el shader
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	//verificaciones y prevención de errores
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al compilar el shader %d es: %s \n",shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);//Si no hubo problemas se asigna el shader a theProgram el cual asigna el código a la tarjeta gráfica
}

void CompileShaders() {
	shader= glCreateProgram(); //se crea un programa
	if (!shader)
	{
		printf("Error creando el shader");
		return;
	}
	AddShader(shader, vShader, GL_VERTEX_SHADER);//Agregar vertex shader
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);//Agregar fragment shader
	//Para terminar de linkear el programa y ver que no tengamos errores
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shader);//se linkean los shaders a la tarjeta gráfica
	 //verificaciones y prevención de errores
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al linkear es: %s \n", eLog);
		return;
	}
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al validar es: %s \n", eLog);
		return;
	}



}
int main()
{
	srand((unsigned)time(NULL));
	float red_color = (rand() % 10) / 10.0, green_color = (rand() % 10) / 10.0, blue_color = (rand() % 10) / 10.0, counter = 0.0f;
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Ejercicio Practica 1", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);

 //Crear tríangulo
	CrearTriangulo();
	CompileShaders();


	//Loop mientras no se cierra la ventana
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Recibir eventos del usuario
		glfwPollEvents();

		counter += 0.0005;

		if (counter > 4.0) {
			red_color = (rand() % 10) / 10.0;
			green_color = (rand() % 10) / 10.0;
			blue_color = (rand() % 10) / 10.0;
			counter = 0.0;
		}


		//Limpiar la ventana
		glClearColor(red_color, green_color, blue_color, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,75);
		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);

	}


	return 0;
}