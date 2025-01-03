#version 450

layout(set=0,binding = 0) uniform ViewProjection {
    mat4 view;
    mat4 proj;
} uboViewProjection;

layout(set=1,binding = 0) uniform Model {
    mat4 model;
} uboModel;

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;

void main() {
    gl_Position = uboViewProjection.proj * uboViewProjection.view * uboModel.model * vec4(inPosition, 0.0, 1.0);
    fragColor = inColor;
    fragTexCoord = inTexCoord;
}