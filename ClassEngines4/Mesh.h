#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "MaterialHandler.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
	
};
struct SubMesh {
	std::vector<Vertex> vertexList;
	std::vector<unsigned int> meshIndices;
	Material material;
};
class Mesh
{
public:
	Mesh(SubMesh& subMesh_, GLuint shaderProgram_);
	~Mesh();

	void Render(std::vector<glm::mat4>& instances_, Camera* camera_);

private:
	void GenerateBuffers();

	GLuint VAO, VBO;
	SubMesh subMesh;
	GLuint shaderProgram;
	GLuint modelLoc, viewLoc, projectionLoc, textureLoc;
	GLuint viewPos, lightPos, ambientValue, diffuseValue, specularValue, lightColour;
};


#endif