#pragma once

#include <GL\glew.h>
#include <SDL2\SDL.h>
#include <cmath>
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
#include "car.h"

#define WIDTH 800
#define HEIGHT 600
//#define LOAD_LARGE

class Scene
{
public:
	Scene() : shader("./res/basicShader"),
		camera(glm::vec3(0, 0.5f, -3.0f), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 500.0f)
#ifdef LOAD_LARGE
		,
		parkingLotMesh("./res/ParkingLot.obj"),
		parkingLotTexture("./res/ParkingLot.bmp"),
		humanoidMesh("./res/monster.obj"),
		brickTexture("./res/bricks.jpg")
#endif // LOAD_LARGE
	{ }
	virtual ~Scene()
	{ }

	void Render();
	
	inline void setXMovementSpeed(float movement)
	{
		camera.setXMovementSpeed(movement);
	}

	inline float getXMovementSpeed() const
	{
		return camera.getXMovementSpeed();
	}

	inline void setZMovementSpeed(float movement)
	{
		camera.setZMovementSpeed(movement);
	}

	inline float getZMovementSpeed() const
	{
		return camera.getZMovementSpeed();
	}

	inline void setXRotationSpeed(float rotation)
	{
		camera.setXRotationSpeed(rotation);
	}

	inline float getXRotationSpeed() const
	{
		return camera.getXRotationSpeed();
	}

	inline void setYRotationSpeed(float rotation)
	{
		camera.setYRotationSpeed(rotation);
	}

	inline float getYRotationSpeed() const
	{
		return camera.getYRotationSpeed();
	}

	inline void setTireRotationSpeed(float orientation)
	{
		car.setTireRotationSpeed(orientation);
	}

	inline float getTireRotationSpeed() const
	{
		return car.getTireRotationSpeed();
	}

	inline void setCarForwardSpeed(float speed)
	{
		car.setCarForwardSpeed(speed);
	}

	inline float getCarForwardSpeed()
	{
		return car.getCarForwardSpeed();
	}
private:
	Shader shader;
	Camera camera;

	Car car;

	Mesh parkingLotMesh;
	Texture parkingLotTexture;
	Transform getParkingLotTransform() const;
	const glm::vec3 PARKING_LOT_POSITION = glm::vec3(4.2f, 0, -4.8f);
	const glm::vec3 PARKING_LOT_ROTATION = glm::vec3(0, (2 * M_PI) / 3, 0);
	const glm::vec3 PARKING_LOT_SCALE = glm::vec3(0.8f);

	Texture brickTexture;
	Mesh humanoidMesh;
	Transform getHumanoidTransform() const;
	const glm::vec3 HUMANOID_POSITION = glm::vec3(0, 0.67f, 0.05f);
	const glm::vec3 HUMANOID_ROTATION = glm::vec3(0, M_PI, 0);
	const glm::vec3 HUMANOID_SCALE = glm::vec3(0.05f);
};

