#ifndef GAME1_H
#define GAME1_H

#include "CoreEngine.h"
#include "StartScene.h"
#include "GameScene.h"
class Game1 : public GameInterface
{
public:
	Game1();
	virtual ~Game1();

	bool OnCreate()override;
	void Update(const float deltaTime_)override;
	void Render() override;
private:
	int currentSceneNum;
	Scene* currentScene;
	void BuildScene();

};

#endif