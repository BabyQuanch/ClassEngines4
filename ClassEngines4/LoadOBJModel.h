#ifndef LOADOBJMODEL_H
#define LOADOBJMODEL_H

#include <sstream>
#include "Mesh.h"
#include "TextureHandler.h"

class LoadOBJModel{
public:
	LoadOBJModel();
	~LoadOBJModel();

	void LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_);
	std::vector <SubMesh> GetSubMeshes();

private:
	void PostProcessing();
	void LoadModel(const std::string& filePath_);
	void LoadMaterial(const std::string& matPath_);
	void LoadMaterialLibrary(const std::string& matFilePath_);

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureCoords;
	std::vector<unsigned int> indices, normalIndices, textureIndices;
	std::vector<Vertex> meshVertices;
	std::vector<SubMesh> subMesh;
	GLuint currentTexture;
};

#endif // !LOADOBJMODEL_H