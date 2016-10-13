#pragma once

#include <GL\glew.h>
#include <SDL2\SDL.h>
#include <cmath>
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

#define WIDTH 800
#define HEIGHT 600
#define LOAD_LARGE

class Scene
{
public:
	Scene() : shader("./res/basicShader"),
		camera(glm::vec3(0, 0.5f, -3.0f), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 500.0f),
		carMesh("./res/car.obj"),
		carTexture("./res/car.bmp"),
		tireTexture("./res/tire.bmp"),
		tireMesh("./res/tire.obj"),
#ifdef LOAD_LARGE
		parkingLotMesh("./res/ParkingLot.obj"),
		parkingLotTexture("./res/ParkingLot.bmp"),
		humanoidMesh("./res/monster.obj"),
		brickTexture("./res/bricks.jpg"),
#endif // LOAD_LARGE
		xMovement(0),
		zMovement(0),
		xRotation(0),
		yRotation(0),
		tireOrientation(FORWARD)
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

	enum TireOrientation
	{
		TURNED_RIGHT,
		TURNED_LEFT,
		FORWARD
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

	inline void setTireOrientation(const TireOrientation& orientation)
	{
		tireOrientation = orientation;
	}

	inline TireOrientation getTireOrientation() const
	{
		return tireOrientation;
	}
private:
	Shader shader;

	Camera camera;
	float xMovement;
	float zMovement;
	float xRotation;
	float yRotation;

	Mesh tireMesh;
	Mesh parkingLotMesh;
	Mesh carMesh;
	Mesh humanoidMesh;

	Texture tireTexture;
	Texture parkingLotTexture;
	Texture carTexture;
	Texture brickTexture;

	Transform getCarTransform() const;

	Transform getParkingLotTransform() const;
	const glm::vec3 PARKING_LOT_POSITION = glm::vec3(4.2f, 0, -4.8f);
	const glm::vec3 PARKING_LOT_ROTATION = glm::vec3(0, (2 * M_PI)/ 3, 0);
	const glm::vec3 PARKING_LOT_SCALE = glm::vec3(0.8f);

	Transform getTireTransform(const TirePosition& tirePosition) const;
	inline glm::vec3 getTireRotation(const TirePosition& tirePosition) const;
	const glm::vec3 TIRE_SCALE = glm::vec3(0.25f);
	const glm::vec3 LEFT_TIRE_ROTATION = glm::vec3(0, (float)M_PI, 0);
	const glm::vec3 RIGHT_TIRE_ROTATION = glm::vec3(0.0f);
	const float FRONT_TIRE_Z = -0.53f;
	const float BACK_TIRE_Z = 0.47f;
	const float TIRE_X = 0.35f;
	const float TIRE_Y = 0.15f;
	TireOrientation tireOrientation;
	const glm::vec3 FRONT_TIRE_TURNED = glm::vec3(0, 0.75f, 0);

	Transform getHumanoidTransform() const;
	const glm::vec3 HUMANOID_POSITION = glm::vec3(0, 0.67f, 0.05f);
	const glm::vec3 HUMANOID_ROTATION = glm::vec3(0, M_PI, 0);
	const glm::vec3 HUMANOID_SCALE = glm::vec3(0.05f);
};

