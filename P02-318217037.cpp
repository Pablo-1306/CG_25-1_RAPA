//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá
static const char* vShaderAzul = "shaders/shader_azul.vert";
static const char* vShaderRojo = "shaders/shader_rojo.vert";
static const char* vShaderVerde = "shaders/shader_verde.vert";
static const char* vShaderVerdeO = "shaders/shader_verdeO.vert";
static const char* vShaderCafe = "shaders/shader_cafe.vert";


float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	//GLfloat vertices_letras[] = {
	//	//X			Y			Z			R		G		B
	//	-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
	//	1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
	//	1.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
	//	/*1.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
	//	-1.0f,  1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
	//	-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,*/

	//};
	//MeshColor* letras = new MeshColor();
	//letras->CreateMeshColor(vertices_letras, 18);
	//meshColorList.push_back(letras);

	//GLfloat vertices_triangulorojo[] = {
	//	//X			Y			Z			R		G		B
	//	-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
	//	1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
	//	1.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,

	//};

	//MeshColor* triangulorojo = new MeshColor();
	//triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	//meshColorList.push_back(triangulorojo);

	//GLfloat vertices_cuadradoverde[] = {
	//	//X			Y			Z			R		G		B
	//	-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
	//	0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
	//	0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
	//	-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
	//	0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
	//	-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	//};

	//MeshColor* cuadradoverde = new MeshColor();
	//cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	//meshColorList.push_back(cuadradoverde);

	////triangulo azul
	//GLfloat vertices_trianguloazul[] = {
	//	//X			Y			Z			R		G		B
	//	-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
	//	1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
	//	0.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,

	//};

	//MeshColor* trianguloazul = new MeshColor();
	//trianguloazul->CreateMeshColor(vertices_trianguloazul, 18);
	//meshColorList.push_back(trianguloazul);

	////triangulo verde
	//GLfloat vertices_trianguloverde[] = {
	//	//X			Y			Z			R		G		B
	//	-1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
	//	1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
	//	0.0f,	1.0f,		0.5f,			0.0f,	0.5f,	0.0f,

	//};

	//MeshColor* trianguloverde = new MeshColor();
	//trianguloverde->CreateMeshColor(vertices_trianguloverde, 18);
	//meshColorList.push_back(trianguloverde);

	//GLfloat vertices_cuadradorojo[] = {
	//	//X			Y			Z			R		G		B
	//	-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
	//	0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
	//	0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
	//	-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
	//	0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
	//	-0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,

	//};

	//MeshColor* cuadradorojo = new MeshColor();
	//cuadradorojo->CreateMeshColor(vertices_cuadradorojo, 36);
	//meshColorList.push_back(cuadradorojo);

	//GLfloat vertices_cuadradocafe[] = {
	//	//X			Y			Z			R		G		B
	//	-0.5f,	-0.5f,		0.5f,			0.478, 0.255, 0.067,
	//	0.5f,	-0.5f,		0.5f,			0.478, 0.255, 0.067,
	//	0.5f,	0.5f,		0.5f,			0.478, 0.255, 0.067,
	//	-0.5f,	-0.5f,		0.5f,			0.478, 0.255, 0.067,
	//	0.5f,	0.5f,		0.5f,			0.478, 0.255, 0.067,
	//	-0.5f,	0.5f,		0.5f,			0.478, 0.255, 0.067,

	//};

	//MeshColor* cuadradocafe = new MeshColor();
	//cuadradocafe->CreateMeshColor(vertices_cuadradocafe, 36);
	//meshColorList.push_back(cuadradocafe);

	////P
	//GLfloat vertices_letrap[] = {
	//	-0.80f, -0.4f, 0.0f,	0.0, 0.0, 0.5,
	//	-0.80f, 0.4f,  0.0f,	0.0, 0.0, 0.5,
	//	-0.67f, -0.4f, 0.0f,	0.0, 0.0, 0.5,
	//	-0.80f, 0.4f,  0.0f, 	0.0, 0.0, 0.5,
	//	-0.67f, -0.4f, 0.0f,	0.0, 0.0, 0.5,
	//	-0.67f, 0.4f,  0.0f, 	0.0, 0.0, 0.5,
	//	-0.67f, 0.4f,  0.0f, 	0.0, 0.0, 0.5,
	//	-0.40f, 0.4f,  0.0f,	0.0, 0.0, 0.5,
	//	-0.40f, 0.26f, 0.0f, 	0.0, 0.0, 0.5,
	//	-0.67f, 0.4f,  0.0f, 	0.0, 0.0, 0.5,
	//	-0.40f, 0.26f, 0.0f, 	0.0, 0.0, 0.5,
	//	-0.67f, 0.26f, 0.0f,	0.0, 0.0, 0.5,
	//	-0.54f, 0.26f, 0.0f, 	0.0, 0.0, 0.5,
	//	-0.40f, 0.13f, 0.0f,  	0.0, 0.0, 0.5,
	//	-0.40f, 0.26f, 0.0f, 	0.0, 0.0, 0.5,
	//	-0.54f, 0.26f, 0.0f, 	0.0, 0.0, 0.5,
	//	-0.40f, 0.13f, 0.0f, 	0.0, 0.0, 0.5,
	//	-0.54f, 0.13f, 0.0f,	0.0, 0.0, 0.5,
	//	-0.67f, 0.13f, 0.0f, 	0.0, 0.0, 0.5,
	//	-0.40f, 0.13f, 0.0f, 	0.0, 0.0, 0.5,
	//	-0.40f, 0.00f, 0.0f, 	0.0, 0.0, 0.5,
	//	-0.67f, 0.13f, 0.0f, 	0.0, 0.0, 0.5,
	//	-0.40f, 0.00f, 0.0f, 	0.0, 0.0, 0.5,
	//	-0.67f, 0.00f, 0.0f,	0.0, 0.0, 0.5,
	//};

	//MeshColor* letra_p = new MeshColor();
	//letra_p->CreateMeshColor(vertices_letrap, 144);
	//meshColorList.push_back(letra_p);

	//	//A
	//GLfloat vertices_letraa[] = {
	//	-0.20f, 0.4f,  0.0f,	0.12, 0.7, 0.47, 
	//	-0.20f, -0.4f, 0.0f,	0.12, 0.7, 0.47,
	//	-0.07f, -0.4f, 0.0f,	0.12, 0.7, 0.47,
	//	-0.20f, 0.4f,  0.0f, 	0.12, 0.7, 0.47,
	//	-0.07f, -0.4f, 0.0f,	0.12, 0.7, 0.47,
	//	-0.07f, 0.4f,  0.0f, 	0.12, 0.7, 0.47,
	//	-0.07f, 0.4f,  0.0f, 	0.12, 0.7, 0.47,
	//	0.07f, 0.4f,   0.0f, 	0.12, 0.7, 0.47,
	//	0.07f, 0.26f,  0.0f, 	0.12, 0.7, 0.47,
	//	-0.07f, 0.4f,  0.0f, 	0.12, 0.7, 0.47,
	//	0.07f, 0.26f,  0.0f, 	0.12, 0.7, 0.47,
	//	-0.07f, 0.26f, 0.0f,	0.12, 0.7, 0.47,
	//	0.07f, 0.4f,   0.0f, 	0.12, 0.7, 0.47,
	//	0.20f, 0.4f,   0.0f,	0.12, 0.7, 0.47,
	//	0.20f, -0.4f,  0.0f,	0.12, 0.7, 0.47,
	//	0.20f, -0.4f,  0.0f,	0.12, 0.7, 0.47,
	//	0.07f, 0.4f,   0.0f, 	0.12, 0.7, 0.47,
	//	0.07f, -0.4f,  0.0f,	0.12, 0.7, 0.47,
	//	-0.07f, 0.13f, 0.0f,	0.12, 0.7, 0.47,
	//	0.07f, 0.13f,  0.0f,	0.12, 0.7, 0.47,
	//	0.07f, 0.0f,   0.0f,	0.12, 0.7, 0.47,
	//	-0.07f, 0.13f, 0.0f,	0.12, 0.7, 0.47,
	//	0.07f, 0.0f,   0.0f,	0.12, 0.7, 0.47,
	//	-0.07f, 0.0f,  0.0f,	0.12, 0.7, 0.47,
	//};

	//MeshColor* letra_a = new MeshColor();
	//letra_a->CreateMeshColor(vertices_letraa, 144);
	//meshColorList.push_back(letra_a);

	//	////R
	//GLfloat vertices_letrar[] = {
	//	0.4f, -0.4f,  0.0f,		0.62, 1.0, 0.0,
	//	0.4f, 0.4f,   0.0f,		0.62, 1.0, 0.0,
	//	0.53f, -0.4f, 0.0f,		0.62, 1.0, 0.0,
	//	0.4f, 0.4f,   0.0f,		0.62, 1.0, 0.0,
	//	0.53f, -0.4f, 0.0f,		0.62, 1.0, 0.0,
	//	0.53f, 0.4f,  0.0f,		0.62, 1.0, 0.0,
	//	0.53f, 0.4f,  0.0f,		0.62, 1.0, 0.0,
	//	0.80f, 0.4f,  0.0f,		0.62, 1.0, 0.0,
	//	0.80f, 0.26f, 0.0f,		0.62, 1.0, 0.0,
	//	0.80f, 0.26f, 0.0f,		0.62, 1.0, 0.0,
	//	0.53f, 0.4f,  0.0f,		0.62, 1.0, 0.0,
	//	0.53f, 0.26f, 0.0f,		0.62, 1.0, 0.0,
	//	0.67f, 0.26f, 0.0f,		0.62, 1.0, 0.0,
	//	0.80f, 0.26f, 0.0f,		0.62, 1.0, 0.0,
	//	0.80f, 0.13f, 0.0f,		0.62, 1.0, 0.0,
	//	0.67f, 0.26f, 0.0f,		0.62, 1.0, 0.0,
	//	0.80f, 0.13f, 0.0f,		0.62, 1.0, 0.0,
	//	0.67f, 0.13f, 0.0f,		0.62, 1.0, 0.0,
	//	0.53f, 0.13f, 0.0f,		0.62, 1.0, 0.0,
	//	0.80f, 0.13f, 0.0f,		0.62, 1.0, 0.0,
	//	0.80f, 0.0f,  0.0f,		0.62, 1.0, 0.0,
	//	0.80f, 0.0f,  0.0f,		0.62, 1.0, 0.0,
	//	0.53f, 0.0f,  0.0f,		0.62, 1.0, 0.0,
	//	0.53f, 0.13f, 0.0f,		0.62, 1.0, 0.0,
	//	0.4f, 0.26f,  0.0f,		0.62, 1.0, 0.0,
	//	0.70f, -0.4f, 0.0f,		0.62, 1.0, 0.0,
	//	0.80f, -0.3f, 0.0f,		0.62, 1.0, 0.0,
	//};

	//MeshColor* letra_r = new MeshColor();
	//letra_r->CreateMeshColor(vertices_letrar, 162);
	//meshColorList.push_back(letra_r);

}


void CreateShaders()
{

	//Shader* shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	//shader1->CreateFromFiles(vShader, fShader);
	//shaderList.push_back(*shader1);

	Shader* shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide color azul
	shader1->CreateFromFiles(vShaderAzul, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide color rojo
	shader2->CreateFromFiles(vShaderRojo, fShader);
	shaderList.push_back(*shader2);

	Shader* shader3 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide color cafe
	shader3->CreateFromFiles(vShaderCafe, fShader);
	shaderList.push_back(*shader3);

	Shader* shader4 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide color verde
	shader4->CreateFromFiles(vShaderVerde, fShader);
	shaderList.push_back(*shader4);

	Shader* shader5 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide color rojo
	shader5->CreateFromFiles(vShaderVerdeO, fShader);
	shaderList.push_back(*shader5);

	//Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	//shader2->CreateFromFiles(vShaderColor, fShaderColor);
	//shaderList.push_back(*shader2);
}


int main()
{
	mainWindow = Window(800, 800);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	//CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad


		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();

		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		////triangulo azul (techo)
		//model = glm::mat4(1.0);
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//model = glm::rotate(model, 135 * toRadians, glm::vec3(.0f, .0f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[0]->RenderMeshColor();

		////cuadrado rojo	(fachada)
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, -0.5f, -4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[5]->RenderMeshColor();

		////cuadrado verde	(ventanas y puerta)
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-0.25f, -0.3f, -3.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[2]->RenderMeshColor();

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.25f, -0.3f, -3.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[2]->RenderMeshColor();

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, -0.8f, -3.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[2]->RenderMeshColor();

		////troncos
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-0.8f, -.9f, -3.0f));
		//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[6]->RenderMeshColor();

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.8f, -.9f, -3.0f));
		//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[6]->RenderMeshColor();

		////complemento arbol
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.8f, -.6f, -3.0f));
		//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[4]->RenderMeshColor();

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-0.8f, -.6f, -3.0f));
		//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[4]->RenderMeshColor();

		////letra p
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-.1f, -0.0f, -4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[0]->RenderMeshColor();

		////letra a
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, -0.0f, -4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[1]->RenderMeshColor();

		////letra r
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.1f, -0.0f, -4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[2]->RenderMeshColor();


		//Para el cubo y la pirámide se usa el primer set de shaders con índice 0 en ShaderList

		//creación fachada con shader color rojo
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//creación techo con shader color azul
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.3f, -3.0f));
		model = glm::scale(model, glm::vec3(1.5f, .6f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//creación ventanas con shader color verde
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.25f, -.27f, -2.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.25f, -0.27f, -2.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//creación puerta con shader color verde
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, -2.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//creación troncos con shader color cafe
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-.8f, -0.9f, -2.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(.8f, -0.9f, -2.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//creación complementos de arbo con shader color verde oscuro
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-.8f, -0.5f, -2.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.6f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(.8f, -0.5f, -2.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.6f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();


		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/