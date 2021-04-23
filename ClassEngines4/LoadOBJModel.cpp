#include "LoadOBJModel.h"


LoadOBJModel::LoadOBJModel() : vertices(std::vector<glm::vec3>()), normals(std::vector<glm::vec3>()),
textureCoords(std::vector<glm::vec2>()), indices(std::vector<unsigned int>()), 
normalIndices(std::vector<unsigned int>()), textureIndices(std::vector<unsigned int>()),
meshVertices(std::vector<Vertex>()), subMesh(std::vector<SubMesh>()), currentMaterial(Material())
{
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMesh.reserve(10);
	
}
LoadOBJModel::~LoadOBJModel()
{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMesh.clear();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_)
{
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes()
{
	return subMesh;
}

BoundingBox LoadOBJModel::GetBoundingBox() const
{
	return boundingBox;
}

void LoadOBJModel::PostProcessing()
{
	for (unsigned int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.position = vertices[indices[i] - 1];
		vert.normal = normals[normalIndices[i] - 1];
		vert.textureCoordinates = textureCoords[textureIndices[i] -1];
		meshVertices.push_back(vert);
	}
		SubMesh mesh;
		mesh.vertexList = meshVertices;
		mesh.meshIndices = indices;
		mesh.material = currentMaterial;

		subMesh.push_back(mesh);

		indices.clear();
		normalIndices.clear();
		textureIndices.clear();
		meshVertices.clear();

		currentMaterial = Material();
	
}

void LoadOBJModel::LoadModel(const std::string& filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot Open OBJ file " + filePath_, "LoadOBJModel.cpp", __LINE__);
		return;
	}
	std::string line;

	while (std::getline(in, line)) {
		if (line.substr(0, 2) == "v " ){
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));

			if (boundingBox.maxVert.x < x) boundingBox.maxVert.x = x;
			if (boundingBox.maxVert.y < y) boundingBox.maxVert.y = y;
			if (boundingBox.maxVert.z < z) boundingBox.maxVert.z = z;

			if (boundingBox.minVert.x > x) boundingBox.minVert.x = x;
			if (boundingBox.minVert.y > y) boundingBox.minVert.y = y;
			if (boundingBox.minVert.z > z) boundingBox.minVert.z = z;
		}
		if (line.substr(0, 3) == "vn ") {
			std::stringstream v(line.substr(3));
			float x, y, z;
			v >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}
		if (line.substr(0, 3) == "vt ") {
			std::stringstream v(line.substr(3));
			float x, y;
			v >> x >> y;
			textureCoords.push_back(glm::vec2(x, y));
		}
	
		else if (line.substr(0, 2) == "f ") { //face data
			std::stringstream f(line.substr(2));
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			
			char slash;

			f >> vertexIndex[0] >> slash >> uvIndex[0] >> slash >> normalIndex[0] >>
			vertexIndex[1] >> slash >> uvIndex[1] >> slash >> normalIndex[1] >>
			vertexIndex[2] >> slash >> uvIndex[2] >> slash >> normalIndex[2];
			
			indices.push_back(vertexIndex[0]);
			indices.push_back(vertexIndex[1]);
			indices.push_back(vertexIndex[2]);
			textureIndices.push_back(uvIndex[0]);
			textureIndices.push_back(uvIndex[1]);
			textureIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else if (line.substr(0, 7) == "usemtl ") {

			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	PostProcessing();
	in.close();
}

void LoadOBJModel::LoadMaterial(const std::string& matName_)
{
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_)
{
	MaterialLoader::LoadMaterial(matFilePath_);
}
