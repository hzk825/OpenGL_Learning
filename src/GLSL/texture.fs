#version 330 core
in vec3 ourColor;
in vec2 ourTexCrood;
out vec4 FragColor;

uniform sampler2D ourTexture0;
uniform sampler2D ourTexture1;
uniform float visibility;
void main(){
	FragColor = mix(texture(ourTexture0, ourTexCrood),
					texture(ourTexture1, vec2(1.0 - ourTexCrood.x, ourTexCrood.y)),
					visibility);
}