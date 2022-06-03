#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 UV;

out vec2 vUV;
out vec4 vecPos;
out vec4 vecNormal;

uniform mat4 MVP;
uniform vec3 p1;
uniform vec3 p2;
uniform vec3 p3;
uniform vec3 p4;
uniform vec3 v1;
uniform vec3 v2;

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

void main(void) {
	float s = 1. - UV.x; // changed s <-> t
	float t = UV.y;
	float sign_s = 1.;
	//sif (s > 1.) { s = 2.- s; sign_s = -1.;}  
	float sign_t = 1.;
	//if (t > 1.) { t = 2.- t; sign_t = -1.;}        

	// Surface: control points ant weights 
	vec4 pw[pointCount];
	vec4 nw[pointCount];
	Point points[pointCount];

	points[0].p = vec4(p1, 0.0);
	points[1].p = vec4(p2, 0.0);
	points[2].p = vec4(p3, 0.0);
	points[3].p = vec4(p4,0.0);

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

	vec4 A = mix(pw[0], pw[1], s);
	vec4 B = mix(pw[2], pw[3], s);
	vec4 numerator = mix(A, B, t);

	A = mix(points[0].w, points[1].w, s);
	B = mix(points[2].w, points[3].w, s);
	vec4 denom = mix(A, B, t);
	vec4 inv_denom = qInv(denom);
	vec4 surf = qMult(numerator, inv_denom);

	// Normals
	nor0 = normalize(cross(v1.xyz,v2.xyz));
	vec4 nor = qMult(denom, vec4(nor0, 0.));
	nor = qMult(nor, inv_denom);

	vecNormal = MVP * vec4(nor.xyz, 1.0);
	vecPos = MVP * vec4(surf.xyz, 1.0);
	gl_Position = vecPos;
	vUV = UV;
};

#shader fragment
#version 330 core

in vec2 vUv;
in vec4 vecPos;
in vec4 vecNormal;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

layout(location = 0) out vec4 color;

void main() {
	// ambient
	float ambientStrength = 0.7;
	vec3 ambient = ambientStrength * lightColor;

	// diffuse 
	vec3 norm = normalize(vecNormal.xyz);
	vec3 lightDir = normalize(lightPos - vecPos.xyz);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	// specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - vecPos.xyz);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;
	color = vec4(result, 1.0);
}