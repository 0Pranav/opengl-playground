#include "Camera.h"

Camera::Camera(const glm::vec3& cameraPos, const glm::vec3& cameraTarget, const glm::vec3& up)
{
	this->m_cameraPos = cameraPos;
	this->m_cameraTarget = cameraTarget;
	this->m_up = up;
	Update();
}

void Camera::Update()
{
	SetCameraDirection();
	SetCameraRight();
	SetCameraUp();
}

void Camera::SetCameraDirection()
{
	m_cameraDirection = glm::normalize(m_cameraPos - m_cameraTarget);
}

void Camera::SetCameraRight()
{
	m_cameraRight = glm::normalize(glm::cross(m_up, m_cameraDirection));
}

void Camera::SetCameraUp()
{
	m_cameraUp = glm::normalize(glm::cross(m_cameraDirection, m_cameraRight));
}

void Camera::SetCameraPos(const glm::vec3& cameraPos)
{
	this->m_cameraPos = cameraPos;
	Update();
}

void Camera::SetCameraTarget(const glm::vec3& cameraTarget)
{
	this->m_cameraTarget = cameraTarget;
	Update();
}

glm::mat4 Camera::GetLookAtMatrix()
{
	return glm::lookAt(m_cameraPos, m_cameraPos + m_cameraTarget, m_cameraUp);
}

void Camera::MoveForward(float cameraSpeed)
{
	SetCameraPos(m_cameraPos + cameraSpeed * glm::vec3(m_cameraTarget.x, m_cameraTarget.y, m_cameraTarget.z));
}

void Camera::MoveRight(float cameraSpeed)
{
	SetCameraPos(m_cameraPos + (glm::normalize(glm::cross(m_cameraTarget, m_cameraUp))) * cameraSpeed);
}

void Camera::ProcessMouseMovement(double xOffset, double yOffset)
{
	xOffset *= mouseSensi;
	yOffset *= mouseSensi;

	this->yaw += xOffset;
	this->pitch += yOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	SetCameraTarget(glm::normalize(front));

}

