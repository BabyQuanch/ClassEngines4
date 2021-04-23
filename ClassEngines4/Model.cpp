#include "Model.h"

Model::Model(const std::string& objPath_, const std::string& matPath_, GLuint shaderProgram_) : meshes(std::vector<Mesh*>()), shaderProgram(0),
modelInstances(std::vector<glm::mat4>())
{
	meshes.reserve(10);
	modelInstances.reserve(5);
	shaderProgram = shaderProgram_;
	obj = new LoadOBJModel();
	obj->LoadModel(objPath_, matPath_);
	LoadModel();
}

Model::~Model()
{
	if (meshes.size() > 0) {
		for (auto m : meshes) {

			delete m;
			m = nullptr;

		}
		meshes.clear();
	}
	if (modelInstances.size() > 0) {
		modelInstances.clear();
	}
}

void Model::Render(Camera* camera_)
{
	glUseProgram(shaderProgram);
	for (auto m : meshes) {
		m->Render(modelInstances, camera_);
	}
}

void Model::AddMesh(Mesh* mesh_)
{
	meshes.push_back(mesh_);
}

unsigned int Model::CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modelInstances.push_back(CreateTransform(position_, angle_, rotation_, scale_));

	return modelInstances.size() - 1;
}

void Model::UpdateInstance(unsigned int index, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modelInstances[index]= CreateTransform(position_, angle_, rotation_, scale_);
}


glm::mat4 Model::GetTransform(unsigned int index_) const
{

	return modelInstances[index_];
}

GLuint Model::GetShaderProgram() const
{
	return shaderProgram;
}

BoundingBox Model::GetBoundingBox() const
{
	return boundingBox;
}

glm::mat4 Model::CreateTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const
{
	glm:: mat4 model;
	model = glm::translate(model, position_);
	model = glm::rotate(model, angle_, rotation_);
	model = glm::scale(model, scale_);

	return model;
}

void Model::LoadModel()
{
	for (int i = 0; i < obj->GetSubMeshes().size(); i++) {
		meshes.push_back(new Mesh(obj->GetSubMeshes()[i], shaderProgram));
	}

	boundingBox = obj->GetBoundingBox();

	delete obj;
	obj = nullptr;

}
