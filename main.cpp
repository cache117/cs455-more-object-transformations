#include "display.h"
#include "scene.h"

int main(int argc, char** argv)
{
	Display display(WIDTH, HEIGHT, "Object Transformations");
	Scene scene;

	while (!display.isClosed())
	{		
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
		scene.Render();
		display.Update(scene);
	}
	return 0;
}