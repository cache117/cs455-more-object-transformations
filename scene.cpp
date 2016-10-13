#include "scene.h"

void Scene::Render()
{
	camera.moveCamera(xMovement, zMovement);
	camera.pitch(xRotation);
	camera.yaw(yRotation);
	shader.Bind();

	carTexture.Bind(0);
	shader.Update(getCarTransform(), camera);
	carMesh.Draw();

	tireTexture.Bind(0);
	shader.Update(getTireTransform(Scene::FRONT_RIGHT), camera);
	tireMesh.Draw();

	tireTexture.Bind(0);
	shader.Update(getTireTransform(Scene::FRONT_LEFT), camera);
	tireMesh.Draw();

	tireTexture.Bind(0);
	shader.Update(getTireTransform(Scene::BACK_RIGHT), camera);
	tireMesh.Draw();

	tireTexture.Bind(0);
	shader.Update(getTireTransform(Scene::BACK_LEFT), camera);
	tireMesh.Draw();
#ifdef LOAD_LARGE 
	parkingLotTexture.Bind(0);
	shader.Update(getParkingLotTransform(), camera);
	parkingLotMesh.Draw();

	brickTexture.Bind(0);
	shader.Update(getHumanoidTransform(), camera);
	humanoidMesh.Draw();
#endif // LOAD_LARGE
}

Transform Scene::getCarTransform() const
{
	return Transform();
}

Transform Scene::getParkingLotTransform() const
{
	return Transform(PARKING_LOT_POSITION, PARKING_LOT_ROTATION, PARKING_LOT_SCALE);
}

Transform Scene::getTireTransform(const TirePosition& tirePosition) const
{
	switch (tirePosition)
	{
	case Scene::FRONT_RIGHT:
		return Transform(glm::vec3(TIRE_X, TIRE_Y, FRONT_TIRE_Z), getTireRotation(Scene::FRONT_RIGHT), TIRE_SCALE);
		break;
	case Scene::FRONT_LEFT:
		return Transform(glm::vec3(-TIRE_X, TIRE_Y, FRONT_TIRE_Z), getTireRotation(Scene::FRONT_LEFT), TIRE_SCALE);
		break;
	case Scene::BACK_RIGHT:
		return Transform(glm::vec3(TIRE_X, TIRE_Y, BACK_TIRE_Z), getTireRotation(Scene::BACK_RIGHT), TIRE_SCALE);
		break;
	case Scene::BACK_LEFT:
		return Transform(glm::vec3(-TIRE_X, TIRE_Y, BACK_TIRE_Z), getTireRotation(Scene::BACK_LEFT), TIRE_SCALE);
		break;
	default:
		return Transform();
		break;
	}
}

Transform Scene::getHumanoidTransform() const
{
	return Transform(HUMANOID_POSITION, HUMANOID_ROTATION, HUMANOID_SCALE);
}

glm::vec3 Scene::getTireRotation(const TirePosition& tirePosition) const
{
	switch (tirePosition)
	{
	case Scene::FRONT_RIGHT:
		switch (tireOrientation)
		{
		case Scene::TURNED_RIGHT:
			return RIGHT_TIRE_ROTATION - FRONT_TIRE_TURNED;
			break;
		case Scene::TURNED_LEFT:
			return RIGHT_TIRE_ROTATION + FRONT_TIRE_TURNED;
			break;
		default:
			return RIGHT_TIRE_ROTATION;
			break;
		}
		break;
	case Scene::FRONT_LEFT:
		switch (tireOrientation)
		{
		case Scene::TURNED_RIGHT:
			return LEFT_TIRE_ROTATION - FRONT_TIRE_TURNED;
			break;
		case Scene::TURNED_LEFT:
			return LEFT_TIRE_ROTATION + FRONT_TIRE_TURNED;
			break;
		default:
			return LEFT_TIRE_ROTATION;
			break;
		}
		break;
	case Scene::BACK_LEFT:
		return LEFT_TIRE_ROTATION;
		break;
	default:
		return RIGHT_TIRE_ROTATION;
		break;
	}
}


