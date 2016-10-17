#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <cmath>

#define LOCKED_Y_MOVEMENT
#define USE_CUSTOM_CAMERA_MATRICES

class Camera
{
public:
	Camera() : xMovementSpeed(0),
		zMovementSpeed(0),
		xRotationSpeed(0),
		yRotationSpeed(0)
	{ }
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);
	virtual ~Camera()
	{ }

	inline void setXMovementSpeed(float movement)
	{
		xMovementSpeed = movement;
	}

	inline float getXMovementSpeed() const
	{
		return xMovementSpeed;
	}

	inline void setZMovementSpeed(float movement)
	{
		zMovementSpeed = movement;
	}

	inline float getZMovementSpeed() const
	{
		return zMovementSpeed;
	}

	inline void setXRotationSpeed(float rotation)
	{
		xRotationSpeed = rotation;
	}

	inline float getXRotationSpeed() const
	{
		return xRotationSpeed;
	}

	inline void setYRotationSpeed(float rotation)
	{
		yRotationSpeed = rotation;
	}

	inline float getYRotationSpeed() const
	{
		return yRotationSpeed;
	}

	glm::mat4 GetView() const;
	inline glm::mat4 GetViewProjection() const
	{
		return perspective * GetView();
	}
	void moveCamera(float x, float z);
	void pitch(float angle);
	void yaw(float angle);
	void applyMovements();
private:
	glm::mat4 perspective;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;
	const float CAMERA_HEIGHT = 0.6f;

	glm::mat4 buildPerspectiveMatrix(float fov, float aspect, float zNear, float zFar) const;

	float xMovementSpeed;
	float zMovementSpeed;
	float xRotationSpeed;
	float yRotationSpeed;
};

