#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Shader.h"
#include "Camera.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"


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
	VertexArray vao;
	vao.Bind();
	// VBO
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};
	
	std::shared_ptr<VertexBuffer> vb;
	vb.reset(new VertexBuffer(vertices, sizeof(vertices)));
	BufferLayout layout = {
		 BufferElement("position",3),
		 BufferElement("normal",3),
		 BufferElement("TexCoords",2)
	};
	vb->SetLayout(layout);
	vao.AddBuffer(vb);

	lastX = 1280 / 2;
	lastY = 720 / 2;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	// Load Texture //////////////////////////////////////////////////////////////

	Texture diffuseTexture("res/container.png",0);
	Texture specularTexture("res/specular.png",1);

	glm::mat4 transform = glm::mat4(1);
	// Shader ////////////////////////////////////////////////////////////////////

	Shader shader("res/shaders/cube");

	VertexArray lightVAO;
	lightVAO.Bind();
	lightVAO.AddBuffer(vb);
	Shader lightShader("res/shaders/lamp");
	glm::vec3 lightPos = glm::vec3(3.0, 3.0, -3.0);
	
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetWindowSizeCallback(window, framebufferSizeCallback);
	glm::mat4 projection = glm::perspective(glm::radians(50.0f), (float)1280 / 720, 0.1f, 100.0f);
	shader.Bind();
	shader.SetFloat("material.shininess", 256.0f);

	shader.SetVec3("light.ambient", 0.1f, 0.1f, 0.1f);
	shader.SetVec3("light.diffuse", 1.0f, 0.5f, 0.31f);
	shader.SetVec3("light.specular", 0.5f, 0.5f, 0.5f);

	shader.SetInt("material.diffuse", 0);
	shader.SetInt("material.specular", 1);

	shader.Unbind();
	glEnable(GL_DEPTH_TEST);


	while (!glfwWindowShouldClose(window))
	{
		float time = (float)glfwGetTime();
		lightPos = glm::vec3(cos(time), sin(time), sin(time));
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Bind();
		shader.SetMat4("projection", projection);
		auto view = camera.GetLookAtMatrix();
		shader.SetMat4("transform", transform);
		shader.SetMat4("view", view);
		shader.SetVec3("light.position", lightPos.x, lightPos.y, lightPos.z);
		const glm::vec3 cameraPos = camera.GetCameraPos();
		shader.SetVec3("viewPos", cameraPos.x, cameraPos.y, cameraPos.z);
		vao.DrawArray();
		shader.Unbind();

		lightShader.Bind();
		auto lightTransform = glm::translate(glm::mat4(1), lightPos);
		lightTransform = glm::scale(lightTransform, glm::vec3(0.1));
		lightShader.SetMat4("transform", lightTransform);
		lightShader.SetMat4("projection", projection);
		lightShader.SetMat4("view", view);
		lightVAO.DrawArray();
		lightShader.Unbind();

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