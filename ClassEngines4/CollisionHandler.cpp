#include "CollisionHandler.h"

std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector<GameObject*>();
OctSpatialPartition* CollisionHandler::scenePartition = nullptr;
CollisionHandler::CollisionHandler()
{
    
    prevCollisions.reserve(10);
}

CollisionHandler::~CollisionHandler()
{
    OnDestroy();
}

CollisionHandler* CollisionHandler::GetInstance()
{
    if (collisionInstance.get() == nullptr) {
        collisionInstance.reset(new CollisionHandler);
    }
    return collisionInstance.get();
}

void CollisionHandler::OnCreate(float worldSize_)
{
   scenePartition = new OctSpatialPartition(worldSize_);
   prevCollisions.clear();
}

void CollisionHandler::AddGameObject(GameObject* gameObject_)
{
    scenePartition->AddGameObject(gameObject_);

}

void CollisionHandler::MouseUpdate(glm::vec2 mousePosition_, int buttonType_)
{
    Ray mouseRay = CollisionDetection::MousePosWorldRay(mousePosition_, 
                                                        CoreEngine::GetInstance()->GetScreenWidth(),
                                                        CoreEngine::GetInstance()->GetScreenHeight(),
                                                        CoreEngine::GetInstance()->GetCamera());
    if (scenePartition != nullptr) {
        GameObject* hitResult = scenePartition->GetCollision(mouseRay);

        if (hitResult) {
            hitResult->SetHit(true, buttonType_);
        }



        for (auto c : prevCollisions) {
            if (hitResult != c && c != nullptr) {
                c->SetHit(false, buttonType_);
            }
            c = nullptr;
        }
        prevCollisions.clear();
        if (hitResult) {
            prevCollisions.push_back(hitResult);
        }
    }
}

void CollisionHandler::OnDestroy()
{
    delete scenePartition;
    scenePartition = nullptr;

    for (auto entry : prevCollisions) {
        entry = nullptr;
    }
    prevCollisions.clear();
}

