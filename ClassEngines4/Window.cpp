#include "Window.h"
#include "Debug.h"
Window::Window() : window(nullptr), context(nullptr)
{

}

Window::~Window()
{
	OnDestroy();
}

bool Window::OnCreate(std::string name_, int width_, int height_)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		Debug::FatalError("Failed to initialize Window", "Window.cpp", __LINE__);
		return false;
	}
	height = height_;
	width = width_;

	SetPreAttributes();

	window = SDL_CreateWindow(name_.c_str(),

		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,

		width,
		height,

		SDL_WINDOW_OPENGL);

	if (!window) {
		Debug::FatalError("Failed to create window", "Window.cpp", __LINE__);
		return false;
	}
	context = SDL_GL_CreateContext(window);
	SetPostAttributes();

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		Debug::FatalError("Failed to create GLEW", "Window.cpp", __LINE__);
		return false;
	}

	Debug::FatalError("open GL version " + std::string((char*)glGetString(GL_VERSION)), "Window.cpp", __LINE__);

	glViewport(0, 0, width, height);

	return true;
}

void Window::OnDestroy()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}
	
int Window::GetWidth() const
{
	return width;
}

int Window::GetHeight() const
{
	return height;
}

SDL_Window* Window::GetWindow() const
{
	return window;
}

void Window::SetPreAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	glewExperimental = GL_TRUE;
}

void Window::SetPostAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
}
