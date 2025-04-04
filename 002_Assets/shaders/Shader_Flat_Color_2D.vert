#version 450

const int NUM_MODEL_MATRICES = 100;

layout(set=0,binding = 0) uniform ViewProjection {
    mat4 perspectiveProjection;
    mat4 view;
    mat4 orthographicProjection;
} uboViewProjection;

layout(set=1,binding = 0) uniform Model {
    mat4 model[NUM_MODEL_MATRICES];
} uboModel;

layout(push_constant) uniform PushConstants {
    vec4 color;
    uint modelMatrixIndex;
} pushConstants;

layout(location = 0) in vec2 inPosition;

layout(location = 0) out vec4 vs_color;

void main() {
    gl_Position = uboViewProjection.orthographicProjection * uboModel.model[pushConstants.modelMatrixIndex] * vec4(inPosition, 0.0, 1.0);
    vs_color=pushConstants.color;
}