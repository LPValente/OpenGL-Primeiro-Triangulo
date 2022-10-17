#include <iostream>
#include <cassert>
#include <array>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>


const int Width = 800;

const int Height = 600;

int main() {
	

	// Inicializar a biblioteca GLFW
	assert(glfwInit() == GLFW_TRUE);

	// Criar uma janela
	GLFWwindow* Window = glfwCreateWindow(Width, Height, "Blue Marble", nullptr, nullptr);
	assert(Window);

	// Ativa o contexto criado na janela Window
	glfwMakeContextCurrent(Window);

	// Inicializar a biblioteca glew

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	// Verificar a versão do OpenGL que estamos usando
	GLint GLMajorVersion = 0;
	GLint GLMinorVersion = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &GLMajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &GLMinorVersion);
	std::cout << "OpenGL Version: " << GLMajorVersion << "." << GLMinorVersion << std::endl;
	
	// Usar o glGetString() para obter infromações do driver que estamos usando
	std::cout << "OpenGL Vendor		: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL Renderer	: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version	: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version		: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	// Definir um triangulo em coordenadas normalizadas
	std::array<glm::vec3, 3> Triangle = {
		glm::vec3{-1.0f,-1.0f, 0.0f},
		glm::vec3{1.0f,-1.0f, 0.0f},
		glm::vec3{0.0f,1.0f, 0.0f}
	};

	// Agora, vamos copiar os vértices do triangulo para a memoria da GPU
	GLuint VertexBuffer;

	// Pedir para o OpenGL gerar o identificador do VertexBuffer
	glGenBuffers(1, &VertexBuffer);

	// Ativar o VertexBuffer como sendo o vbuffer para onde vamos copiar os dados do triangulo
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

	// Copiar os dados para a memoria de video
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle.data(), GL_STATIC_DRAW);
	
	// Definir a cor de fundo
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

	// Entrar no loop de eventos da aplicação

	while (!glfwWindowShouldClose(Window)) {

		// glClear vai limpar o framebuffer. GL_BUFFER_BIT diz para limpar o buffer de cor
		// Depois de limpar, ele vai preencher com a cor que foi configurada no glClearColor
		// Quando formos desenhar geometrias 3D, vamos voltar ao glClear pois teremos que limpar o buffer de profundidade (depth buffer). 
		glClear(GL_COLOR_BUFFER_BIT);

		glEnableVertexAttribArray(0);

		// Diz para o OpenGL que o VertexBuffer vai ser o buffer ativo no momento
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

		// Informa ao OpenGl onde, dentro do VertexBuffer, onde os vertices estão
		// No caso o array Trianglçes é contiguo em memoria, logo basta dizer quantos vertices vamos usar para desenhar o triangulo
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		// Finalmmente, diz para o OpenGl desenhar o triangulo com os dados que estão armazenados no VertexBuffer
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Processa todos os eventos da fila de eventos do GLFW
		// Eventos podem ser eventos do teclado, mouse, gamepad
		glfwPollEvents();

		// Envia o conteudo do framebuffer da janela para ser desenhado na tela
		glfwSwapBuffers(Window);
	}

	// Encerra a biblioteca GLFW
	glfwTerminate();

	return 0;
}