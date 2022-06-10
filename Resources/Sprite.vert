#version 410

layout(location=0) in vec3 vPosition;
layout(location=1) in vec2 vTexCoord;
layout(location=0) out vec2 outTexCoord;
uniform mat4x4 matVP;
uniform mat4x4 matModel;

void main()
{
  outTexCoord = vTexCoord;
  gl_Position = matVP * matModel * vec4(vPosition, 1.0);
}