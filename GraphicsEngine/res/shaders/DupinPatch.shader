#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 UV;

out vec2 vUV;
out vec4 vecPos;
out vec4 vecNormal;

uniform mat4 MVP;
uniform vec3 p;
uniform int size;
uniform float angle;

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

	points[0].p = vec4(1.0, vec3(0.0));
	points[1].p = vec4(0.0, 1.0, vec2(0.0));
	points[2].p = vec4(p, 0.); //vec4(-0.6, -0.8, vec2(0.0)); 
	points[3].p = vec4(-1.0, vec3(0.0));

	vec4 v1 = vec4(15. / 17., 8. / 17., vec2(0.0));
	vec4 v2 = vec4(-40. / 221., 75. / 221., 12. / 13., 0.);
	vec3 nor0 = normalize(cross(v1.xyz, v2.xyz));
	vec4 q = vec4(sin(0.5 * angle) * nor0, cos(0.5 * angle));
	vec4 conq = vec4(q.xyz, -q.w);
	v1 = qMult(qMult(q, v1), conq);
	v2 = qMult(qMult(q, v2), conq);

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
	//nor0 = normalize(cross(v1.xyz,v2.xyz));
	//vec4 nor = qMult(denom, vec4(nor0, 0.));
	//nor = qMult(nor, inv_denom);

	//vecNormal = MVP * vec4(nor.xyz, 1.0);
	vecPos = MVP * vec4(surf.xyz, 1.0);
	gl_Position = vecPos;
	//vUV = UV;
};

#shader fragment
#version 330 core

in vec2 vUv;
in vec4 vecPos;
in vec4 vecNormal;

uniform int size;

layout(location = 0) out vec4 color;

vec3 checker(vec2 tex) {
	float Size = float(size);
	float res = mod(floor(Size * tex.x) + floor(Size * tex.y), 2.0);
	if (res < 1.0) {
		return vec3(0.0, 0.9, 0.9);  // turquiose
	}
	else {
		return vec3(0.9, 0.0, 0.9);  // magenta
	}
}

void main() {
	vec3 cyanColor = vec3(0.9, 0.9, 0.9);
	vec3 nNormal = normalize(vecNormal.xyz);
	vec3 ambColor = vec3(0.2, 0.2, 0.2);
	vec3 diffColor = vec3(0.8, 0.8, 0.8);
	vec3 specColor = vec3(1.0, 0.9, 0.9);
	float shininess = 32.0;
	vec3 lightDir = normalize(vec3(-0.4, -0.2, -1.0));
	float diffLightWeight = abs(dot(nNormal, -lightDir));
	vec3 eyeDir = normalize(-vecPos.xyz);
	vec3 reflDir = reflect(lightDir, nNormal);
	//vec3 halfVec = normalize(-lightDir + eyeDir);
	float specLightWeight = pow(max(dot(reflDir, eyeDir), 0.0), shininess);
	//float specLightWeight = pow(max(dot(halfVec, nNormal), 0.0), shininess);
	vec3 lightWeight = ambColor + diffColor * diffLightWeight
		+ specColor * specLightWeight;
	//color = vec4(lightWeight * checker(vUv), 1.0);
	//color = vec4(vecPos.x, vecPos.y, vecPos.z, 1.0);
	color = vec4(1.0, 1.0, 1.0, 1.0);
}