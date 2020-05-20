#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
	Camera(const glm::vec3& cameraPos, const glm::vec3& cameraTarget, const glm::vec3& up);
	const glm::vec3 GetCameraPos() { return m_cameraPos; };
	void SetCameraTarget(const glm::vec3& cameraTarget);
	void SetCameraPos(const glm::vec3& cameraPos);
	void MoveForward(float cameraSpeed);
	void MoveRight(float cameraSpeed);
	void ProcessMouseMovement(double xpos, double ypos);
	glm::mat4 GetLookAtMatrix();
private:

	void SetCameraDirection();
	void SetCameraRight();
	void SetCameraUp();
	void Update();

	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraTarget;
	glm::vec3 m_up;
	glm::vec3 m_cameraDirection;
	glm::vec3 m_cameraRight;
	glm::vec3 m_cameraUp;

	float yaw = -90.0f;
	float pitch = 0.0f;

	float mouseSensi = 0.05f;
};
