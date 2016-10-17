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
#define LOAD_LARGE

class Scene
{
public:
	Scene() : shader("./res/basicShader"),
		camera(glm::vec3(0, 0.5f, -3.0f), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 500.0f),
#ifdef LOAD_LARGE
		parkingLotMesh("./res/ParkingLot.obj"),
		parkingLotTexture("./res/ParkingLot.bmp"),
		humanoidMesh("./res/monster.obj"),
		brickTexture("./res/bricks.jpg"),
#endif // LOAD_LARGE
		xMovement(0),
		zMovement(0),
		xRotation(0),
		yRotation(0)
	{ }
	virtual ~Scene()
	{ }

	void Render();

	enum TirePosition
	{
		FRONT_RIGHT,
		FRONT_LEFT,
		BACK_RIGHT,
		BACK_LEFT
	};
	
	inline void setXMovement(float movement)
	{
		xMovement = movement;
	}

	inline float getXMovement() const
	{
		return xMovement;
	}

	inline void setZMovement(float movement)
	{
		zMovement = movement;
	}

	inline float getZMovement() const
	{
		return zMovement;
	}

	inline void setXRotation(float rotation)
	{
		xRotation = rotation;
	}

	inline float getXRotation() const
	{
		return xRotation;
	}

	inline void setYRotation(float rotation)
	{
		yRotation = rotation;
	}

	inline float getYRotation() const
	{
		return yRotation;
	}

	inline void setTireOrientation(float orientation)
	{
		car.setTireOrientation(orientation);
	}

	inline float getTireOrientation() const
	{
		return car.getTireOrientation();
	}
private:
	Shader shader;

	Camera camera;
	float xMovement;
	float zMovement;
	float xRotation;
	float yRotation;

	Car car;

	Mesh parkingLotMesh;
	Mesh humanoidMesh;

	Texture parkingLotTexture;
	Texture brickTexture;

	Transform getParkingLotTransform() const;
	const glm::vec3 PARKING_LOT_POSITION = glm::vec3(4.2f, 0, -4.8f);
	const glm::vec3 PARKING_LOT_ROTATION = glm::vec3(0, (2 * M_PI)/ 3, 0);
	const glm::vec3 PARKING_LOT_SCALE = glm::vec3(0.8f);

	Transform getHumanoidTransform() const;
	const glm::vec3 HUMANOID_POSITION = glm::vec3(0, 0.67f, 0.05f);
	const glm::vec3 HUMANOID_ROTATION = glm::vec3(0, M_PI, 0);
	const glm::vec3 HUMANOID_SCALE = glm::vec3(0.05f);
};

