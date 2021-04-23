#include "MouseEventListener.h"
#include "CoreEngine.h"

CoreEngine* MouseEventListener::engineInstance = nullptr;
glm::ivec2 MouseEventListener::mouse = glm::ivec2();
glm::ivec2 MouseEventListener::prevMouse = glm::ivec2();
bool MouseEventListener::firstUpdate = true;

MouseEventListener::~MouseEventListener()
{
	engineInstance = nullptr;
}

void MouseEventListener::RegisterEngineObject(CoreEngine* engine_)
{
	engineInstance = engine_;
}

void MouseEventListener::Update(SDL_Event e_)
{
	if (e_.type == SDL_MOUSEBUTTONDOWN) {
		UpdateMousePosition();
		NotifyOfMousePressed(e_.button.button);
	}
	else if (e_.type == SDL_MOUSEBUTTONUP) {
		UpdateMousePosition();
		NotifyOfMouseReleased(e_.button.button);
	}
	else if (e_.type == SDL_MOUSEMOTION) {
		UpdateMousePosition();
		NotifyOfMouseMoved();
		
	}
	else if (e_.type == SDL_MOUSEWHEEL) {
		UpdateMousePosition();
		NotifyOfMouseScrolled(e_.wheel.y);
	}
}

void MouseEventListener::NotifyOfMousePressed(int buttonType_)
{
	if (engineInstance) {
		engineInstance->NotifyOfMousePressed(mouse, buttonType_);
	}
}

void MouseEventListener::NotifyOfMouseReleased(int buttonType_)
{
	if (engineInstance) {
		engineInstance->NotifyOfMouseReleased(mouse, buttonType_);
	}
}

void MouseEventListener::NotifyOfMouseMoved()
{
	if (engineInstance) {
		engineInstance->NotifyOfMouseMoved(mouse);
	}
}

void MouseEventListener::NotifyOfMouseScrolled(int y_)
{
	if (engineInstance) {
		engineInstance->NotifyOfMouseScrolled(y_);
	}
}

glm::vec2 MouseEventListener::GetPreviousMousePosition()
{
	return prevMouse;
}

glm::vec2 MouseEventListener::GetMousePosition()
{
	return mouse;
}

glm::vec2 MouseEventListener::GetMouseOffset()
{
	return glm::vec2(mouse.x - prevMouse.x, prevMouse.y - mouse.y);
}

void MouseEventListener::UpdateMousePosition()
{
	int tempX, tempY;
	SDL_GetMouseState(&tempX, &tempY);
	tempY = static_cast<int>(engineInstance->GetScreenHeight()) - tempY;
	if (firstUpdate) {
		prevMouse.x = mouse.x = tempX;
		prevMouse.y = mouse.y = tempY;
		firstUpdate = false;
	}
	else {
		prevMouse.x = mouse.x;
		prevMouse.y = mouse.y;
		mouse.x = tempX;
		mouse.y = tempY;
	}
}
