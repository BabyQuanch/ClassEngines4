#include "GameScene.h"
#include "GameObject.h"
GameScene::GameScene() : shape(nullptr)
{
}

GameScene::~GameScene()
{
	model = nullptr;
	delete shape;
	shape = nullptr;
}

bool GameScene::OnCreate()
{
	Debug::Info("Game Scene was loaded", "GameScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));
	
	//TextureHandler::GetInstance()->CreateTexture("CheckerboardTexture", "CheckerboardTexture.png");


	model = new Model("Models/Dice.obj", "Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	//SubMesh subMesh;
	//subMesh.vertexList = vertexList;
	//subMesh.textureID = TextureHandler::GetInstance()->GetTexture("CheckerboardTexture");
	//model->AddMesh(new Mesh(subMesh, ShaderHandler::GetInstance()->GetShader("basicShader")));
	////model->SetScale(glm::vec3(0.5f));
	
	shape = new GameObject(model);
	shape->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	return true;
}

void GameScene::Update(const float deltaTime_)
{
	shape->Update(deltaTime_);
}

void GameScene::Render()
{
	shape->Render(CoreEngine::GetInstance()->GetCamera());
}
