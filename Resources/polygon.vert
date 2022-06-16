#version 410

layout(location=0) in vec3 v_vartex;

uniform mat4x4 matVP;

void main() {
  gl_Position = matVP * vec4(v_vartex, 1);
}