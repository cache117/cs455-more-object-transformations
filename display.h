#pragma once

#include <string>
#include <iostream>
#include <SDL2\SDL.h>
#include <GL\glew.h>
#include "scene.h"

class Display
{
public:
	Display(int width, int height, const std::string& title);
	virtual ~Display();

	void Clear(float r, float g, float b, float a);
	void Update(Scene& scene);

	inline bool isClosed() const
	{
		return m_isClosed;
	}
private:
	void manageKeyPress(Scene& scene, const SDL_Keycode& key);
	void manageKeyRelease(Scene& scene, const SDL_Keycode& key);

	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;
	const float MOVEMENT_AMOUNT = 0.007f;
	const float ROTATION_AMOUNT = 0.002f;
};

