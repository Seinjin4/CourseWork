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
uniform vec3 p1;
uniform vec3 p2;
uniform vec3 p3;
uniform vec3 p4;
uniform vec3 v1;
uniform vec3 v2;
uniform float a;
uniform float b;
uniform float c;
uniform int sCase;

//case 1 = xy
//case 2 = xz
//case 3 = yz

const int pointCount = 4;
const float PI = 3.1415926535897932384626433832795;

struct Point {
	vec4 p;
	vec4 w;
};

vec4 qMult(vec4 q0, vec4 q1) {
	float r0 = q0.w;
	float r1 = q1.w;

	vec3 v0 = q0.xyz;
	vec3 v1 = q1.xyz;

	vec4 product;
	product.w = r0 * r1 - dot(v0, v1);
	product.xyz = r0 * v1 + r1 * v0 + cross(v0, v1);

	return product;
};

vec4 qInv(vec4 q) {
	float dot = dot(q, q);
	float invdot = (0.0 != dot) ? (1.0 / dot) : 0.0;

	q.xyz *= -invdot;
	q.w *= invdot;

	return q;
};

float len(vec4 x) {
	float Dot = dot(x, x);
	return sqrt(Dot);
};

void main()
{
	// main colors
	vec3 color = vec3(0.0f);

	// uv coordinates
	float x = 0;
	float y = 0;
	float z = 0;
	float res = 0;

	// Surface: control points ant weights 
	vec4 pw[pointCount];
	vec4 nw[pointCount];
	Point points[pointCount];

	points[0].p = vec4(p1, 0.0);
	points[1].p = vec4(p2, 0.0);
	points[2].p = vec4(p3, 0.0);
	points[3].p = vec4(p4, 0.0);

	vec4 v1 = vec4(v1, 0.0);
	vec4 v2 = vec4(v2, 0.0);
	vec3 nor0 = normalize(cross(v1.xyz, v2.xyz));

	vec4 p10 = points[1].p - points[0].p;
	vec4 p20 = points[2].p - points[0].p;
	vec4 p21 = points[2].p - points[1].p;
	vec4 p30 = points[3].p - points[0].p;
	vec4 p32 = points[3].p - points[2].p;
	float L = -(len(p10) / len(p32)) * (len(p21) / len(p30));

	points[0].w = vec4(vec3(0.), 1.);
	points[1].w = qMult(p10, v1);
	points[2].w = qMult(p20, v2);
	vec4 pp = qMult(p32, p20);
	vec4 vv = qMult(v1, v2);
	points[3].w = L * qMult(pp, vv);

	for (int i = 0; i < pointCount; i++)
	{
		pw[i] = qMult(points[i].p, points[i].w);
	}

	if (sCase == 1)
	{
		x = fract(vUv.x) * UvScale - UvScale / 2.0f;
		y = 0.0f;
		z = fract(vUv.y) * UvScale - UvScale / 2.0f;

		vec4 xy = vec4(x, y, z, 0.0f);
		vec4 F[pointCount];
		vec4 Fm[pointCount];


		for (int i = 0; i < pointCount; i++)
		{
			F[i] = qMult(xy, points[i].w) - pw[i];
			Fm[i] = vec4(F[i].w, F[i].x, F[i].y, F[i].z);
		}

		mat4 M = mat4(Fm[0], Fm[1], Fm[2], Fm[3]);

		float Eq = determinant(M) *16 * c * c * (-1 + b) * (-1 + b) -(2.0 * c + 2.0 * b + 2.0 * a - 3.0);

		res = Eq;
		color = vec3(1.0f, 0.5f, 0.5f);
	}
	else if (sCase == 2)
	{
		x = fract(vUv.x) * UvScale - UvScale / 2.0f;
		y = 0.0f;
		z = fract(vUv.y) * UvScale - UvScale / 2.0f;

		vec4 xz = vec4(x, y, z, 0.0f);
		vec4 F[pointCount];
		vec4 Fm[pointCount];

		for (int i = 0; i < pointCount; i++)
		{
			F[i] = qMult(xz, points[i].w) - pw[i];
			Fm[i] = vec4(F[i].w, F[i].x, F[i].y, F[i].z);
		}

		mat4 M = mat4(Fm[0], Fm[1], Fm[2], Fm[3]);

		float Eq = determinant(M) *16 * b * b * (-1 + a) * (-1 + a) -(2.0 * c + 2.0 * b + 2.0 * a - 3.0);

		res = Eq;
		color = vec3(0.1f, 1.0f, 0.1f);
	}
	else if (sCase == 3)
	{
		x = 0.0f;
		y = fract(vUv.y) * UvScale - UvScale / 2.0f;
		z = fract(vUv.x) * UvScale - UvScale / 2.0f;

		vec4 yz = vec4(x, y, z, 0.0f);
		vec4 F[pointCount];
		vec4 Fm[pointCount];

		for (int i = 0; i < pointCount; i++)
		{
			F[i] = qMult(yz, points[i].w) - pw[i];
			Fm[i] = vec4(F[i].w, F[i].x, F[i].y, F[i].z);
		}

		mat4 M = mat4(Fm[0], Fm[1], Fm[2], Fm[3]);

		float Eq = determinant(M) *16 * a * a * (-1 + c) * (-1 + c) -(2.0 * c + 2.0 * b + 2.0 * a - 3.0);

		res = Eq;

		color = vec3(0.5f, 0.5f, 1.0f);
	}
	// implicit function
	//float f = x*x + y*y;
	float edgeFactor = smoothstep(0.035, 0.035, abs(res));

	// final 
	if (edgeFactor > 0.99) discard;

	gl_FragColor = vec4(color, 1.0);
};