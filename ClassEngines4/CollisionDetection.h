#ifndef COLLISSIONDETECTION_H
#define COLLISSIONDETECTION_H

#include "Camera.h"
struct Ray;
struct BoundingBox;


class CollisionDetection
{
public:
	CollisionDetection(const CollisionDetection&) = delete;
	CollisionDetection(CollisionDetection&&) = delete;
	CollisionDetection& operator=(const CollisionDetection&) = delete;
	CollisionDetection& operator=(CollisionDetection&&) = delete;

	CollisionDetection() = delete;
	~CollisionDetection();
	static Ray MousePosWorldRay(glm::vec2 mouseCoords_, float screenWidth_, float screenHeight_, Camera* camera_);
	static bool RayObbIntersection(Ray* ray_, BoundingBox* boundingBox_);
};

#endif // !COLLISSIONDETECTION_H 