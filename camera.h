#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <cmath>

#define LOCKED_Y_MOVEMENT
#define USE_CUSTOM_CAMERA_MATRICES

class Camera
{
public:
	Camera()
	{ }
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);
	virtual ~Camera()
	{ }

	glm::mat4 GetView() const;
	inline glm::mat4 GetViewProjection() const
	{
		return perspective * GetView();
	}
	void moveCamera(float x, float z);
	void pitch(float angle);
	void yaw(float angle);
private:
	glm::mat4 perspective;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;
	const float CAMERA_HEIGHT = 0.6f;

	glm::mat4 buildPerspectiveMatrix(float fov, float aspect, float zNear, float zFar) const;
};

