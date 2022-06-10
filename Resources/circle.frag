#version 410

layout(location=0) in vec2 inTexCoord;
out vec4 fragColor;
uniform float time;
uniform vec4 baseColor;
uniform sampler2D texColor;

void main() {
	vec2 coffset = inTexCoord - vec2(0.5f, 0.5f);
	float d = length(coffset);
	float cosa = cos(time * d * 6.28f);
	float sina = sin(time * d * 6.28f);
	vec2 uvoffset = vec2(
		coffset.x * cosa + coffset.y * -sina,
		coffset.x * sina + coffset.y * cosa
		);
	fragColor = baseColor * texture(texColor,
		vec2(0.5f, 0.5f) + uvoffset);
}