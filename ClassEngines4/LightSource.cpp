#include "LightSource.h"


LightSource::LightSource(glm::vec3 position_, float ambientValue_, float diffuseValue_, float specularValue_, glm::vec3 lightColour_) : 
	position(glm::vec3(0.0f,0.0f,0.0f)), ambientValue(0), diffuseValue(0), specularValue(0), lightColour(glm::vec3(0.0f, 0.0f, 0.0f))
{
	position = position_;
	ambientValue = ambientValue_;
	diffuseValue = diffuseValue_;
	specularValue = specularValue_;
	lightColour = lightColour_;
}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::GetPosition() const
{
	return glm::vec3(position);
}

float LightSource::GetAmbient() const
{
	return ambientValue;
	
}

float LightSource::GetDiffuse() const
{
	return diffuseValue;
}

float LightSource::GetSpecular() const
{
	return specularValue;
}

glm::vec3 LightSource::GetLightColour() const
{
	return glm::vec3(lightColour);
}

void LightSource::SetAmbient(float ambientValue_)
{
	ambientValue = ambientValue_;
}

void LightSource::SetDiffuse(float diffuseValue_)
{
	diffuseValue = diffuseValue_;
}

void LightSource::SetSpecular(float specularValue_)
{
	specularValue = specularValue_;
}

void LightSource::SetPosition(glm::vec3 position_)
{
	position = position_;
}

void LightSource::SetLightColour(glm::vec3 lightColour_)
{
	lightColour = lightColour_;
}
