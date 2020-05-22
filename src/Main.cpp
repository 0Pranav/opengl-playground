#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Shader.h"
#include "Camera.h"
#include "VertexBuffer.h"


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
	
	VertexBuffer vb(vertices, sizeof(vertices));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);

	lastX = 1280 / 2;
	lastY = 720 / 2;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	// Load Texture //////////////////////////////////////////////////////////////
	int texWidth, texHeight, nrChannels = 0;
	auto data = stbi_load("res/container.png",&texWidth, &texHeight, &nrChannels, NULL);
	uint32_t diffuseTexture;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &diffuseTexture);
	glBindTexture(GL_TEXTURE_2D, diffuseTexture);
	GLenum format;
	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3)
		format = GL_RGB;
	else if (nrChannels == 4)
		format = GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, format, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	auto specularData = stbi_load("res/specular.png", &texWidth, &texHeight, &nrChannels, NULL);
	uint32_t specularTexture;
	glActiveTexture(GL_TEXTURE1);
	glGenTextures(1, &specularTexture);
	glBindTexture(GL_TEXTURE_2D, specularTexture);
	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3)
		format = GL_RGB;
	else if (nrChannels == 4)
		format = GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, format, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, specularData); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(specularData);

	glm::mat4 transform = glm::mat4(1);
	// Shader ////////////////////////////////////////////////////////////////////
	std::string vertexSrc = R"(
		
	#version 450 core
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec3 aNormal;
	layout (location = 2) in vec2 aTexCoords;

	uniform mat4 transform;
	uniform mat4 view;
	uniform mat4 projection;

	out vec3 Normal;
	out vec3 FragPos;
	out vec2 TexCoords;

	void main()
	{
		gl_Position =  projection * view * transform * vec4(aPos, 1.0);
		FragPos = vec3(transform * vec4(aPos, 1.0));
		Normal = mat3(transpose(inverse(transform))) * aNormal;  
		TexCoords = aTexCoords;
	}       
	)";
	std::string fragSrc = R"(
	#version 450 core
		
	struct Material {
		sampler2D diffuse;
		sampler2D specular;
		float shininess;
	}; 
  
	struct Light {
		vec3 position;
  
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
	};

	in vec3 Normal;
	in vec3 FragPos;
	in vec2 TexCoords;
  
	uniform Light light;  
	uniform Material material;
	uniform vec3 viewPos;

	out vec4 FragColor;

	void main()
	{
		vec3 ambient = texture2D(material.diffuse, TexCoords).rgb * light.ambient;

		// Diffuse
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(light.position - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = (diff * texture2D(material.diffuse, TexCoords).rgb) * light.diffuse ;

		// Specular
		float specularStrength = 0.5;
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = (texture2D(material.specular, TexCoords).rgb * spec) * light.specular;  

		vec3 result = (ambient + diffuse + specular);
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
	vb.Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	Shader lightShader(vertexSrcLamp, fragSrcLamp);
	glm::vec3 lightPos = glm::vec3(3.0, 3.0, -3.0);
	
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetWindowSizeCallback(window, framebufferSizeCallback);
	glm::mat4 projection = glm::perspective(glm::radians(50.0f), (float)1280 / 720, 0.1f, 100.0f);
	shader.Bind();
	shader.SetVec3("material.specular", 0.5f, 0.5f, 0.5f);
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
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices));
		glBindVertexArray(0);
		shader.Unbind();

		lightShader.Bind();
		lightShader.SetMat4("projection", projection);
		auto lightTransform = glm::translate(glm::mat4(1), lightPos);
		lightTransform = glm::scale(lightTransform, glm::vec3(0.1));
		lightShader.SetMat4("transform", lightTransform);
		lightShader.SetMat4("view", view);
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices));
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