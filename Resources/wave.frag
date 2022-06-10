#version 410

layout(location=0) in vec2 inTexCoord;
out vec4 fragColor;
uniform float time;
uniform vec4 baseColor;
uniform sampler2D texColor;

void main() {
	fragColor = baseColor * texture(texColor, inTexCoord + vec2(sin((inTexCoord.y + 0.5f) * time) * 0.5f, 0));
}