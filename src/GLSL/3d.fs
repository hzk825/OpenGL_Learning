#version 330 core
in vec2 crood;
out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main(){
	FragColor = mix(texture(texture0, crood),
					texture(texture1, vec2(crood.x, crood.y)),
					0.2f);
}