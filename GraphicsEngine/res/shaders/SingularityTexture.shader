#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 UV;

out vec2 vUv;

uniform mat4 MVP;

void main()
{
    vUv = UV;
    gl_Position = MVP * position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 vUv;

uniform float UvScale;
uniform float a;
uniform float b;
uniform float c;
uniform int sCase;

//case 1 = xy
//case 2 = xz
//case 3 = yz

void main()
{
	// main colors
	vec3 color = vec3(0.0f);

	// uv coordinates
	float x = 0;
	float y = 0;
	float z = 0;
	float res = 0;
	if (sCase == 1)
	{
		x = fract(vUv.x) * UvScale - UvScale / 2.0f;
		y = fract(vUv.y) * UvScale - UvScale / 2.0f;
		z = 0;
		res = -(2.0 * a + 2.0 * c + 2.0 * b - 3.0) + (2.0 - 8,0 * b +4.0*b*b + 4.0*b*c - 4*a*c + 4*a*b) * y * y +
			(-4*c*c -2 + 8*c - 4*a*c -4*b*c + 4*a*b) * x * x +
			(4.0 * b * c + 1.0 - 2.0 * c + 4.0 * a * b - 8.0 * a * b * c - 2.0 * a + 4.0 * a * c - 2.0 * b) *
			(x * x + y * y) * (x * x + y * y);
		color = vec3(1.0f, 0.5f, 0.5f);
	}
	else if (sCase == 2)
	{
		x = fract(vUv.x) * UvScale - UvScale / 2.0f;
		y = 0;
		z = fract(vUv.y) * UvScale - UvScale / 2.0f;
		res = -(2.0 * c + 2.0 * b + 2.0 * a - 3.0) + (-8.0 * a + 4.0 * a * b + 2.0 + 4.0 * a * a - 4.0 * a * b + 4.0 * a * c) * x * x +
			(-2.0 - 4.0 * a * b + 4.0 * a * c - 4.0 * b * c + 8.0 * b - 4.0 * b * b) * z * z +
			(4.0 * a * b + 1.0 - 2.0 * c + 4.0 * a * b - 8.0 * a * b * c - 2.0 * a + 4.0 * a * c - 2.0 * b) *
			(z * z + x * x) * (z * z + x * x);
		color = vec3(0.1f, 1.0f, 0.1f);
	}
	else if (sCase == 3)
	{
		x = 0;
		y = fract(vUv.y) * UvScale - UvScale / 2.0f;
		z = fract(vUv.x) * UvScale - UvScale / 2.0f;
		res = -(2.0 * b + 2.0 * a + 2.0 * c - 3.0) + (-8.0 * c + 4.0 * a * c + 2.0 + 4.0 * c * c - 4.0 * a * b + 4.0 * b * c) * z * z +
			(-2.0 - 4.0 * a * c + 4.0 * b * c - 4.0 * a * b + 8.0 * a - 4.0 * a * a) * y * y +
			(4.0 * b * c + 1.0 - 2.0 * c + 4.0 * a * b - 8.0 * a * b * c - 2.0 * a + 4.0 * a * c - 2.0 * b) *
			(y * y + z * z) * (y * y + z * z);
		color = vec3(0.5f, 0.5f, 1.0f);
	}
	// implicit function
	//float f = x*x + y*y;
	float edgeFactor = smoothstep(0.035, 0.035, abs(res));

	// final 
	if (edgeFactor > 0.99) discard;

	gl_FragColor = vec4(color, 1.0);
};