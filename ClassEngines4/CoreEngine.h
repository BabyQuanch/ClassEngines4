#ifndef COREENGINE_H
#define COREENGINE_H

#include <memory>
#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "Scene.h"
#include "Camera.h"
#include "EventListener.h"
#include "GameObject.h"
#include "SceneGraph.h"
#include "ShaderHandler.h"
#include "TextureHandler.h"
#include "MaterialHandler.h"


class CoreEngine
{
public:

	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;

	static CoreEngine* GetInstance();

	bool OnCreate(std::string name_, int width, int height);
	void run();
	void Exit();

	bool GetIsRunning()const;
	int GetCurrentScene()const;
	float GetScreenHeight() const;
	float GetScreenWidth() const;
	Camera* GetCamera() const;

	void SetGameInterface(GameInterface* gameInterface_);
	void SetCurrentScene(int sceneNum_);
	void SetCamera(Camera* camera_);

	void NotifyOfMousePressed(glm::ivec2 mouse_, int buttonType_);
	void NotifyOfMouseReleased(glm::ivec2 mouse_, int buttonType_);
	void NotifyOfMouseMoved(glm::ivec2 mouse_);
	void NotifyOfMouseScrolled(int y_);
private:

	CoreEngine();
	~CoreEngine();

	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();
	

	static std::unique_ptr<CoreEngine> engineInstance;
	friend std::default_delete<CoreEngine>;

	Timer timer;
	Window* window;
	bool isRunning;
	unsigned int fps;
	GameInterface* gameInterface;
	int currentSceneNum;
	Camera* camera;
};

#endif // !COREENGINE_H