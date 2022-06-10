#version 410

layout(location=0) in vec2 inTexCoord;
out vec4 fragColor;
uniform vec4 baseColor;
uniform sampler2D texColor;

void main() {
	fragColor = baseColor * texture(texColor, inTexCoord);
}