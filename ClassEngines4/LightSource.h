#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "Debug.h"
#include <glm/gtc/matrix_transform.hpp>

class LightSource
{
public:

	LightSource(glm::vec3 position_, float ambientValue_,float diffuseValue_,float specularValue_, glm::vec3 lightColour_);
	~LightSource();

	glm::vec3 GetPosition() const;
	float GetAmbient()const;
	float GetDiffuse()const;
	float GetSpecular()const;
	glm::vec3 GetLightColour() const;



	void SetAmbient(float ambientValue_);
	void SetDiffuse(float diffuseValue_);
	void SetSpecular(float specularValue_);
	void SetPosition(glm::vec3 position_);
	void SetLightColour(glm::vec3 lightColour_);

private:


	glm::vec3 position;
	float ambientValue = 0.0f;
	float diffuseValue = 0.0f;
	float specularValue = 0.0f;
	glm::vec3 lightColour;

};

#endif // !LIGHTSOURCE_H