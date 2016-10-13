#include "camera.h"

Camera::Camera(const glm::vec3 & pos, float fov, float aspect, float zNear, float zFar)
{
	this->perspective = buildPerspectiveMatrix(fov, aspect, zNear, zFar);
	this->position = pos;
	this->forward = glm::vec3(0, 0, 1);
	this->up = glm::vec3(0, 1, 0);
}

glm::mat4 Camera::GetView() const
{
#ifndef USE_CUSTOM_CAMERA_MATRICES 
	return glm::lookAt(position, position + forward, up);
#else
	glm::vec3 eye = position;
	glm::vec3 center = position + forward;
	// up is up. No need to redefine;

	glm::vec3  lookAt = glm::normalize(center - eye);
	glm::vec3  lookUp = glm::normalize(up);
	glm::vec3  lookRight = glm::normalize(glm::cross(lookAt, lookUp));
	lookUp = cross(lookRight, lookAt);

	glm::mat4 result(1.0f);
	result[0][0] = lookRight.x;
	result[1][0] = lookRight.y;
	result[2][0] = lookRight.z;
	result[0][1] = lookUp.x;
	result[1][1] = lookUp.y;
	result[2][1] = lookUp.z;
	result[0][2] = -lookAt.x;
	result[1][2] = -lookAt.y;
	result[2][2] = -lookAt.z;
	result[3][0] = -glm::dot(lookRight, position);
	result[3][1] = -glm::dot(lookUp, position);
	result[3][2] = glm::dot(lookAt, position);
	return result;
#endif // USE_CUSTOM_CAMERA_MATRICES
}

void Camera::moveCamera(float x, float z)
{
	position += forward * z;
	position += glm::cross(up, forward) * x;
#ifdef LOCKED_Y_MOVEMENT
	position.y = CAMERA_HEIGHT;
#endif // !LOCKED_Y_MOVEMENT
}

void Camera::pitch(float angle)
{
	glm::vec3 right = glm::normalize(glm::cross(up, forward));
#ifndef USE_CUSTOM_CAMERA_MATRICES
	glm::mat4 rotation = glm::rotate(angle, right);
#else
	//Rodrigues Rotation about an arbitrary vector
	//I + w * sin(t) + w^2 * (1-cos(t))
	//I
	glm::mat4 identity = glm::mat4(1.0f);
	//w
	glm::mat4 assymetricMatrix = glm::mat4();
	assymetricMatrix[0][1] = right.z;
	assymetricMatrix[0][2] = -right.y;
	assymetricMatrix[1][0] = -right.z;
	assymetricMatrix[1][2] = right.x;
	assymetricMatrix[2][0] = right.y;
	assymetricMatrix[2][1] = -right.x;
	//I + w * sin(t) + w^2 * (1-cos(t))
	glm::mat4 rodriguesRotation = identity + assymetricMatrix * sin(angle) + (assymetricMatrix * assymetricMatrix) * (1 - cos(angle));
	glm::mat4 rotation = rodriguesRotation;
#endif //USE_CUSTOM_CAMERA_MATRICES
	forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0f)));
	up = glm::normalize(glm::cross(forward, right));
#ifdef LOCKED_Y_MOVEMENT
	position.y = CAMERA_HEIGHT;
#endif // !LOCKED_Y_MOVEMENT
}

 void Camera::yaw(float angle)
{
#ifndef USE_CUSTOM_CAMERA_MATRICES
	static const glm::vec3 UP(0.0f, 1.0f, 0.0f);
	glm::mat4 rotation = glm::rotate(angle, UP);
#else
	glm::mat4 rotation = glm::mat4(1.0f);
	rotation[0][0] = cos(angle);
	rotation[0][2] = -sin(angle);
	rotation[2][0] = sin(angle);
	rotation[2][2] = cos(angle);
#endif // !USE_CUSTOM_MATRICES
	forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0f)));
	up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0f)));
#ifdef LOCKED_Y_MOVEMENT
	position.y = CAMERA_HEIGHT;
#endif // !LOCKED_Y_MOVEMENT
}

glm::mat4 Camera::buildPerspectiveMatrix(float fov, float aspect, float zNear, float zFar) const
{
#ifndef USE_CUSTOM_CAMERA_MATRICES
	return glm::perspective(fov, aspect, zNear, zFar);
#else
	//return glm::perspective(fov, aspect, zNear, zFar);
	float f = 1 / tan(fov / 2);
	glm::mat4 perspectiveProjection = glm::mat4();
	perspectiveProjection[0][0] = f / aspect;
	perspectiveProjection[1][1] = f;
	perspectiveProjection[2][2] = (zFar + zNear) / (zNear - zFar);
	perspectiveProjection[2][3] = -1;
	perspectiveProjection[3][2] = (2 * zNear * zFar) / (zNear - zFar);
	return perspectiveProjection;
#endif // !USE_CUSTOM_CAMERA_MATRICES
}
