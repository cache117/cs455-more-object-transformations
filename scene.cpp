#include "scene.h"

void Scene::Render()
{
	camera.applyMovements();

	shader.Bind();
	car.Render(shader, camera);
#ifdef LOAD_LARGE 
	parkingLotTexture.Bind(0);
	shader.Update(getParkingLotTransform(), camera);
	parkingLotMesh.Draw();

	brickTexture.Bind(0);
	shader.Update(getHumanoidTransform(), camera);
	humanoidMesh.Draw();
#endif // LOAD_LARGE
}

Transform Scene::getParkingLotTransform() const
{
	return Transform(PARKING_LOT_POSITION, PARKING_LOT_ROTATION, PARKING_LOT_SCALE);
}

Transform Scene::getHumanoidTransform() const
{
	return Transform(HUMANOID_POSITION, HUMANOID_ROTATION, HUMANOID_SCALE);
}


