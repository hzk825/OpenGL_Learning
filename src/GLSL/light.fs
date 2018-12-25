#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 fragPos;
uniform vec3 viewPos;
struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Material material;
uniform Light light;


void main(){
	vec3 ambient = material.ambient * light.ambient;

	vec3 normalDir = normalize(Normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normalDir, lightDir), 0.0f);
	vec3 diffuse = (diff * material.diffuse) * light.diffuse;

	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normalDir);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = (spec * material.specular) * light.specular;

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0f);
}