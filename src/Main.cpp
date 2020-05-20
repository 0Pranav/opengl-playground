#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include "Shader.h"
#include "Camera.h"


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
	uint32_t VAO;
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	uint32_t VBO;
	float vertex[] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f

	};
	glCreateBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	lastX = 1280 / 2;
	lastY = 720 / 2;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Index Buffer

	glm::mat4 transform = glm::mat4(1);
	// Shader
	std::string vertexSrc = R"(
		#version 450 core
		layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
		layout (location = 1) in vec3 aNormal;

		uniform mat4 transform;
		uniform mat4 view;
		uniform mat4 projection;
	
		uniform vec3 objectColor;
		uniform vec3 lightColor;
		uniform vec3 lightPos;
		uniform vec3 viewPos;

		out vec3 Normal;
		out vec3 FragPos;
		out vec3 result;

		void main()
		{

			// ambient 
			float ambientStrength = 0.25;
			vec3 ambient = ambientStrength * lightColor;

			// Diffuse
			vec3 normal = normalize(aNormal);
			vec3 lightDir = normalize(lightPos - aPos);
			float diff = max(dot(normal, lightDir), 0.0);
			vec3 diffuse = diff * lightColor;
		
			// Specular
			float specularStrength = 0.5;
			float shininess = 32;
			vec3 reflectDir = reflect(-lightDir, normal);
			vec3 viewDir = normalize(viewPos - aPos);
			float spec = pow(max(dot(reflectDir, viewDir),0.0), shininess);
			vec3 specular = specularStrength * spec * lightColor;
		
			result = (ambient + diffuse + specular) * objectColor;

			gl_Position =  projection * view * transform * vec4(aPos, 1.0);
		}       
	)";
	std::string fragSrc = R"(
		#version 450 core
	
		in vec3 result;

		out vec4 FragColor;

		void main()
		{
			FragColor = vec4(result, 1.0);
		}
	)";

	std::string fragSrcLamp = R"(
		#version 450 core
		out vec4 FragColor;


		void main()
		{
			FragColor = vec4(1.0);
		}
	)";
	std::string vertexSrcLamp = R"(
		
		#version 450 core
		layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
	
		uniform mat4 transform;
		uniform mat4 view;
		uniform mat4 projection;

		void main()
		{
			gl_Position =  projection * view * transform * vec4(aPos, 1.0);
		}       
	)";

	Shader shader(vertexSrc, fragSrc);


	uint32_t lightVAO;
	glCreateVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	Shader lightShader(vertexSrcLamp, fragSrcLamp);
	glm::vec3 lightPos = glm::vec3(3.0, 3.0, -3.0);
	
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetWindowSizeCallback(window, framebufferSizeCallback);
	glm::mat4 projection = glm::perspective(glm::radians(50.0f), (float)1280 / 720, 0.1f, 100.0f);
	shader.Bind();
	shader.SetVec3("objectColor", 1.0f, 0.5f, 0.31f);
	shader.SetVec3("lightColor", 1.0f, 1.0f, 1.0f);
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
		shader.SetVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);
		const glm::vec3 cameraPos = camera.GetCameraPos();
		shader.SetVec3("viewPos", cameraPos.x, cameraPos.y, cameraPos.z);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertex));
		glBindVertexArray(0);
		shader.Unbind();

		lightShader.Bind();
		lightShader.SetMat4("projection", projection);
		auto lightTransform = glm::translate(glm::mat4(1), lightPos);
		lightTransform = glm::scale(lightTransform, glm::vec3(0.1));
		lightShader.SetMat4("transform", lightTransform);
		lightShader.SetMat4("view", view);
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertex));
		glBindVertexArray(0);
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