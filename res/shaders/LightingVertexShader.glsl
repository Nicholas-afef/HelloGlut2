#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNorms;
layout(location = 2) in vec2 texCoord;

uniform mat4 lightModelView;
uniform mat4 lightPerspective;

void main(){
	gl_Position = lightPerspective * lightModelView * vec4(aPos, 1.0);
}