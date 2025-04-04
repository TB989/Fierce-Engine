#version 450

layout(set=0,binding = 0) uniform ViewProjection {
    mat4 perspectiveProjection;
    mat4 view;
    mat4 orthographicProjection;
} uboViewProjection;

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 color;

layout(location = 0) out vec4 vs_color;

void main() {
    gl_Position = uboViewProjection.orthographicProjection * vec4(inPosition, 0.0, 1.0);
    vs_color=vec4(color,1.0);
}