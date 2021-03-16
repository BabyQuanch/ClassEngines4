#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;

struct Light {
	vec3 position;
	float ambientValue = 0.0f;
	float diffuseValue = 0.0f;
	float specularValue = 0.0f;
	vec3 lightColour;
};

uniform Light light;
uniform sampler2D inputTexture;
uniform vec3 cameraPosition;

out vec4 fColour;

void main(){




fColour = texture(inputTexture, TexCoords);
}
