#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Camera.h"
#include "Texture.h"
#include "Model.h"


void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseCallback(GLFWwindow* window, double xPos, double yPos);

double lastX, lastY;
bool firstMouse = true;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f));

int main()
{
	if (!glfwInit())
	{
		std::cerr << "init failure";
		return EXIT_FAILURE;
	}
	GLFWwindow* window;
	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MAJOR, 5);

	window = glfwCreateWindow(1280,720, "OpenGL Tutorial", NULL, NULL);
	if (!window)
	{
		std::cerr << "window failure";
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();

	// Vertex Array Object
	// VBO
	std::vector<Vertex> vertices = {
		// positions							// normals						// texture coords
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3( 0.5f, -0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3( 0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3( 0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(0.0f, 0.0f)),

		Vertex(glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f,  0.0f, 1.0f),   glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3( 0.5f, -0.5f,  0.5f),  glm::vec3(0.0f,  0.0f, 1.0f),   glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3( 0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  0.0f, 1.0f),   glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3( 0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  0.0f, 1.0f),   glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  0.0f, 1.0f),   glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f,  0.0f, 1.0f),   glm::vec2(0.0f, 0.0f)),
																									 
		Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 0.0f)),
																									 
		 Vertex(glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 0.0f)),
		 Vertex(glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 1.0f)),
		 Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 1.0f)),
		 Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 1.0f)),
		 Vertex(glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 0.0f)),
		 Vertex(glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 0.0f)),
																									 
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3( 0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3( 0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3( 0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(0.0f, 1.0f)),
																									 
		Vertex(glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3( 0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3( 0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3( 0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(0.0f, 1.0f))
	};
	
	std::vector<unsigned int> indices = {};
	for (int i = 0; i < 36; i++)
		indices.push_back(i);


	
	// Load Texture //////////////////////////////////////////////////////////////
	std::vector<Texture> textures;
	Texture diffuseTexture("res/container.png");
	diffuseTexture.SetType("texture_diffuse");
	textures.push_back(diffuseTexture);

	// Create Mesh
	Mesh* cube = new Mesh(vertices, indices, textures);
	Model model("res/model/backpack.obj");

	// Shader ////////////////////////////////////////////////////////////////////

	Shader shader("res/shaders/cube-mesh");
	glm::vec3 lightPos = glm::vec3(3.0, 3.0, -3.0);
	
	glm::mat4 projection = glm::perspective(glm::radians(50.0f), (float)1280 / 720, 0.1f, 100.0f);
	glm::mat4 transform = glm::mat4(1);
	//transform = glm::scale(transform, glm::vec3(0.3));
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetWindowSizeCallback(window, framebufferSizeCallback);
	glEnable(GL_DEPTH_TEST);
	lastX = 1280 / 2;
	lastY = 720 / 2;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	while (!glfwWindowShouldClose(window))
	{
		float time = (float)glfwGetTime();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Bind();
		auto view = camera.GetLookAtMatrix();
		shader.SetMat4("projection", projection);
		shader.SetMat4("model", transform);
		shader.SetMat4("view", view);
		shader.SetVec3("viewPos", camera.GetCameraPos().x, camera.GetCameraPos().y, camera.GetCameraPos().z);
		diffuseTexture.Bind();
		//shader.SetInt("texture_diffuse1", 0);
		//cube->Draw(shader);
		model.Draw(shader);
		shader.Unbind();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::cerr << "Key pressed" << std::endl;
	const float cameraSpeed = 0.25f;
	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera.MoveForward(cameraSpeed);
	if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera.MoveForward(-cameraSpeed);
	if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera.MoveRight(-cameraSpeed);
	if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera.MoveRight(cameraSpeed);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}
