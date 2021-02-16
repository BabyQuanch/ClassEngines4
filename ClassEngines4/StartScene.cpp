#include "StartScene.h"

bool StartScene::OnCreate()
{
    Debug::Info("start scene", "StartScene.cpp", __LINE__);
    CoreEngine::GetInstance()->SetCurrentScene(1);
    return true;
}

void StartScene::Update(const float deltaTime_)
{
}

void StartScene::Render()
{
}
