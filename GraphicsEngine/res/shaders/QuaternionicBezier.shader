#shader vertex
#version 330 core

layout(location = 0) in float time;

out vec4 v_color;

uniform vec4 u_Pq0;
uniform vec4 u_Pq1;
uniform vec4 u_Q;
uniform mat4 u_MVP;

vec4 getInverse(vec4 inV)
{
    return vec4(-inV.x, -inV.y, -inV.z, inV.w) / sqrt(inV.x * inV.x + inV.y * inV.y + inV.z * inV.z + inV.w * inV.w);
}

vec4 quat_mult(vec4 q1, vec4 q2)
{
    vec4 qr;
    qr.x = (q1.w * q2.x) + (q1.x * q2.w) + (q1.y * q2.z) - (q1.z * q2.y);
    qr.y = (q1.w * q2.y) - (q1.x * q2.z) + (q1.y * q2.w) + (q1.z * q2.x);
    qr.z = (q1.w * q2.z) + (q1.x * q2.y) - (q1.y * q2.x) + (q1.z * q2.w);
    qr.w = (q1.w * q2.w) - (q1.x * q2.x) - (q1.y * q2.y) - (q1.z * q2.z);
    return qr;
}

void main()
{
    vec4 w0 = getInverse(u_Q - u_Pq0); // make inverse
    vec4 w1 = getInverse(u_Pq1 - u_Q); // make inverse

    //vec4 newPoint = (u_Pq0 * w0 * (1 - time.x) + u_Pq1 * w1 * time.x) * getInverse(w0 * (1 - time.x) + w1 * time.x);
    vec4 newPoint = quat_mult((quat_mult(u_Pq0, w0) * (1 - time) + quat_mult(u_Pq1, w1) * time), getInverse(w0 * (1 - time) + w1 * time));
    //vec4 newPoint = u_Pq0 * (1 - time) + u_Pq1 * time;

    newPoint.w = 1.0f;

    gl_Position = u_MVP * vec4(newPoint.x, newPoint.y, newPoint.z, 1.0f);
    v_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_color;

void main()
{
	color = v_color;
};