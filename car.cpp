#include "car.h"

void Car::Render(Shader & shader, Camera & camera)
{
	incrementFrontTireRotation(getTireRotationSpeed());

	chasisTexture.Bind(0);
	shader.Update(getChasisTransform(), camera);
	chasisMesh.Draw();

	tireTexture.Bind(0);
	shader.Update(getTireTransform(Car::FRONT_RIGHT), camera);
	tireMesh.Draw();

	tireTexture.Bind(0);
	shader.Update(getTireTransform(Car::FRONT_LEFT), camera);
	tireMesh.Draw();

	tireTexture.Bind(0);
	shader.Update(getTireTransform(Car::BACK_RIGHT), camera);
	tireMesh.Draw();

	tireTexture.Bind(0);
	shader.Update(getTireTransform(Car::BACK_LEFT), camera);
	tireMesh.Draw();
}

void Car::incrementFrontTireRotation(float amount)
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

Transform Car::getChasisTransform() const
{
	return Transform();
}

Transform Car::getTireTransform(const TirePosition & tirePosition) const
{
	switch (tirePosition)
	{
	case Car::FRONT_RIGHT:
		return Transform(glm::vec3(TIRE_X, TIRE_Y, FRONT_TIRE_Z), getTireRotation(Car::FRONT_RIGHT), TIRE_SCALE);
		break;
	case Car::FRONT_LEFT:
		return Transform(glm::vec3(-TIRE_X, TIRE_Y, FRONT_TIRE_Z), getTireRotation(Car::FRONT_LEFT), TIRE_SCALE);
		break;
	case Car::BACK_RIGHT:
		return Transform(glm::vec3(TIRE_X, TIRE_Y, BACK_TIRE_Z), getTireRotation(Car::BACK_RIGHT), TIRE_SCALE);
		break;
	case Car::BACK_LEFT:
		return Transform(glm::vec3(-TIRE_X, TIRE_Y, BACK_TIRE_Z), getTireRotation(Car::BACK_LEFT), TIRE_SCALE);
		break;
	default:
		return Transform();
		break;
	}
}

inline glm::vec3 Car::getTireRotation(const TirePosition & tirePosition) const
{
	switch (tirePosition)
	{
	case Car::FRONT_RIGHT:
		return RIGHT_TIRE_ROTATION - frontTireRotation;
		break;
	case Car::FRONT_LEFT:
		return LEFT_TIRE_ROTATION - frontTireRotation;
		break;
	case Car::BACK_LEFT:
		return LEFT_TIRE_ROTATION;
		break;
	case Car::BACK_RIGHT:
		return RIGHT_TIRE_ROTATION;
		break;
	default:
		return glm::vec3();
		break;
	}
}
