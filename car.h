#pragma once

#include <cmath>
#include "mesh.h"
#include "camera.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"

#ifndef M_PI
#define M_PI 3.14159
#endif

class Car
{
public:
	Car() : chasisMesh("./res/car.obj"),
		chasisTexture("./res/car.bmp"),
		tireTexture("./res/tire.bmp"),
		tireMesh("./res/tire.obj"),
		tireRotation(0)
	{ }
	virtual ~Car()
	{ }
	void Render(Shader & shader, Camera & camera);

	inline void setTireOrientation(float orientation)
	{
		tireRotation = orientation;
	}

	inline float getTireOrientation() const
	{
		return tireRotation;
	}

	inline void incrementFrontTireRotation(float amount)
	{
		if (amount > 0)
		{
			if (frontTireRotation.y + amount <= MAX_FRONT_TIRE_TURNED)
				frontTireRotation.y += amount;
			else
				frontTireRotation.y = MAX_FRONT_TIRE_TURNED;
		}
		else if (amount < 0)
		{
			if (frontTireRotation.y + amount >= -MAX_FRONT_TIRE_TURNED)
				frontTireRotation.y += amount;
			else
				frontTireRotation.y = -MAX_FRONT_TIRE_TURNED;
		}
		else if (frontTireRotation.y + amount == 0)
		{
			frontTireRotation.y = 0;
		}
	}

	enum TirePosition
	{
		FRONT_RIGHT,
		FRONT_LEFT,
		BACK_RIGHT,
		BACK_LEFT
	};

	Mesh chasisMesh;
	Texture chasisTexture;
	Transform getChasisTransform() const;

	Mesh tireMesh;
	Texture tireTexture;

	Transform getTireTransform(const TirePosition& tirePosition) const;
	inline glm::vec3 getTireRotation(const TirePosition& tirePosition) const;
	const glm::vec3 TIRE_SCALE = glm::vec3(0.25f);
	const glm::vec3 LEFT_TIRE_ROTATION = glm::vec3(0, (float)M_PI, 0);
	const glm::vec3 RIGHT_TIRE_ROTATION = glm::vec3(0.0f);
	const float FRONT_TIRE_Z = -0.53f;
	const float BACK_TIRE_Z = 0.47f;
	const float TIRE_X = 0.35f;
	const float TIRE_Y = 0.15f;
	glm::vec3 frontTireRotation;
	float tireRotation;
	const float MAX_FRONT_TIRE_TURNED = (11.0f / 60.0f) * (float)M_PI;
	const glm::vec3 FRONT_TIRE_TURNED = glm::vec3(0, MAX_FRONT_TIRE_TURNED, 0);
};

