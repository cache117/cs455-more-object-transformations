#include "car.h"

void Car::Render(Shader & shader, Camera & camera)
{
	incrementFrontTireRotation(getTireRotationSpeed());
	move();

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
	if (carForwardSpeed != 0)
		carRotation += glm::vec3(0, -amount, 0);
	else
		carRotation += glm::vec3(0, -amount / 2.0f, 0);
}

Transform Car::getChasisTransform() const
{
	return Transform(position, carRotation);
}

Transform Car::getTireTransform(const TirePosition & tirePosition) const
{
	Transform tireTransform;
	switch (tirePosition)
	{
	case Car::FRONT_RIGHT:
		tireTransform = Transform(glm::vec3(TIRE_X, TIRE_Y, FRONT_TIRE_Z), getTireRotation(Car::FRONT_RIGHT), TIRE_SCALE);
		break;
	case Car::FRONT_LEFT:
		tireTransform = Transform(glm::vec3(-TIRE_X, TIRE_Y, FRONT_TIRE_Z), getTireRotation(Car::FRONT_LEFT), TIRE_SCALE);
		break;
	case Car::BACK_RIGHT:
		tireTransform = Transform(glm::vec3(TIRE_X, TIRE_Y, BACK_TIRE_Z), getTireRotation(Car::BACK_RIGHT), TIRE_SCALE);
		break;
	case Car::BACK_LEFT:
		tireTransform = Transform(glm::vec3(-TIRE_X, TIRE_Y, BACK_TIRE_Z), getTireRotation(Car::BACK_LEFT), TIRE_SCALE);
		break;
	default:
		tireTransform = Transform();
		break;
	}
	return Transform::computeMatrixMultiplication(getChasisTransform(), tireTransform);
	//return tireTransform;
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

void Car::move()
{
	forward = glm::vec3(glm::rotate(-tireRotation, glm::vec3(0, 1.0f, 0)) * glm::vec4(forward, 1.0f));
	position += forward * carForwardSpeed;
}
