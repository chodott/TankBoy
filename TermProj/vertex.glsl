#version 330 core

layout(location=0) in vec3 vPos;
layout(location=1) in vec3 vNormal;
layout(location=2) in vec2 vTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projection;

out mat4 modelTrans;

void main()
{
	gl_Position = projection * viewTransform * modelTransform * vec4(vPos,1.0);
	FragPos = vec3(modelTransform * vec4(vPos,1.0));
	Normal = vec3(modelTransform * vec4(vNormal,1.0));
	TexCoord = vTexCoord;
	modelTrans = modelTransform;
}