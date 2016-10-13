#include "display.h"

Display::Display(int width, int height, const std::string& title)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "Couldn't initialize SDL:" << SDL_GetError() << std::endl;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);

	GLenum status = glewInit();
	
	if (status != GLEW_OK)
	{
		std::cerr << "Glew failed to initialize!" << std::endl;
	}

	m_isClosed = false;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}


Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Display::manageKeyPress(Scene& scene, const SDL_Keycode& key)
{
	switch (key)
	{
	case SDLK_w:
		scene.setZMovement(MOVEMENT_AMOUNT);
		break;
	case SDLK_s:
		scene.setZMovement(-MOVEMENT_AMOUNT);
		break;
	case SDLK_d:
		scene.setXMovement(-MOVEMENT_AMOUNT);
		break;
	case SDLK_a:
		scene.setXMovement(MOVEMENT_AMOUNT);
		break;
	case SDLK_i:
		scene.setXRotation(ROTATION_AMOUNT);
		break;
	case SDLK_k:
		scene.setXRotation(-ROTATION_AMOUNT);
		break;
	case SDLK_l:
		scene.setYRotation(-ROTATION_AMOUNT);
		break;
	case SDLK_j:
		scene.setYRotation(ROTATION_AMOUNT);
		break;
	case SDLK_q:
		scene.setTireOrientation(Scene::TURNED_LEFT);
		break;
	case SDLK_e:
		scene.setTireOrientation(Scene::TURNED_RIGHT);
	}
}

void Display::manageKeyRelease(Scene& scene, const SDL_Keycode& key)
{
	switch (key)
	{
	case SDLK_w:
		if (scene.getZMovement() == MOVEMENT_AMOUNT)
			scene.setZMovement(0);
		break;
	case SDLK_s:
		if (scene.getZMovement() == -MOVEMENT_AMOUNT)
			scene.setZMovement(0);
		break;
	case SDLK_d:
		if (scene.getXMovement() == -MOVEMENT_AMOUNT)
			scene.setXMovement(0);
	case SDLK_a:
		if (scene.getXMovement() == MOVEMENT_AMOUNT)
			scene.setXMovement(0);
		break;
	case SDLK_i:
		if (scene.getXRotation() == ROTATION_AMOUNT)
			scene.setXRotation(0);
		break;
	case SDLK_k:
		if (scene.getXRotation() == -ROTATION_AMOUNT)
			scene.setXRotation(0);
		break;
	case SDLK_l:
		if (scene.getYRotation() == -ROTATION_AMOUNT)
			scene.setYRotation(0);
		break;
	case SDLK_j:
		if (scene.getYRotation() == ROTATION_AMOUNT)
			scene.setYRotation(0);
		break;
	case SDLK_q:
		if (scene.getTireOrientation() == Scene::TURNED_LEFT)
			scene.setTireOrientation(Scene::FORWARD);
		break;
	case SDLK_e:
		if (scene.getTireOrientation() == Scene::TURNED_RIGHT)
			scene.setTireOrientation(Scene::FORWARD);
	}
}

void Display::Update(Scene& scene)
{
	SDL_GL_SwapWindow(m_window);

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_isClosed = true;
			break;
		case SDL_KEYDOWN:
			manageKeyPress(scene, event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			manageKeyRelease(scene, event.key.keysym.sym);
			break;
		}
	}
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
