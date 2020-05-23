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
	/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);*/

	lastX = 1280 / 2;
	lastY = 720 / 2;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	// Load Texture //////////////////////////////////////////////////////////////

	Texture diffuseTexture("res/container.png",0);
	Texture specularTexture("res/specular.png",1);

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


	VertexArray lightVAO;
	lightVAO.Bind();
	lightVAO.AddBuffer(vb);
	Shader lightShader(vertexSrcLamp, fragSrcLamp);
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