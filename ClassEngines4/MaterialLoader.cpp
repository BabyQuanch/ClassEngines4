#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader()
{
}

void MaterialLoader::LoadMaterial(std::string filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in); 
	if (!in) {
		Debug::Error("Cannot open MTL file" + filePath_, "MaterialLoader.cpp", __LINE__);
		return;
	}
	Material m = Material();
	std::string matName = "";
	std::string line;
	while (std::getline(in,line)) {
		if (line.substr(0,7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
			m.name = matName;
		}
		//shininess
		else if(line.substr(0, 4) == "\tNs "){
			std::stringstream ns(line.substr(4));
			float shine;
			ns >> shine;
			m.shininess = shine;
		}
		//transparency
		else if (line.substr(0, 3) == "\td ") {
			std::stringstream d(line.substr(3));
			float trans;
			d >> trans;
			m.transparency = trans;
		}
		//ambient
		else if (line.substr(0, 4) == "\tKa ") {
			std::stringstream ka(line.substr(4));
			float x, y, z;
			ka >> x >> y >> z;
			m.ambient = glm::vec3(x, y, z);
		}
		//diffuse
		else if (line.substr(0, 4) == "\tKd ") {
			std::stringstream kd(line.substr(4));
			float x, y, z;
			kd >> x >> y >> z;
			m.diffuse = glm::vec3(x, y, z);
		}
		//specular
		else if (line.substr(0, 4) == "\tKs ") {
			std::stringstream ks(line.substr(4));
			float x, y, z;
			ks >> x >> y >> z;
			m.specular = glm::vec3(x, y, z);
		}
	}
	if (m.diffuseMap != 0) {
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();
	
}

GLuint MaterialLoader::LoadTexture(std::string fileName_)
{
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);

	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(fileName_, "Textures/" + fileName_ + ".png");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}
