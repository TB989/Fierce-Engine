#version 450

layout(set=1,binding = 0) uniform sampler2D texSampler;

layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec4 vs_color;

layout(location = 0) out vec4 outColor;

layout(push_constant) uniform PushConstants {
    float width;
    float edge;
} pushConstants;

void main() {
    float distance=1.0-texture(texSampler,fragTexCoord).a;
    float alpha=1-0-smoothstep(pushConstants.width,pushConstants.width+pushConstants.edge,distance);
    outColor = vec4(vs_color.rgb,alpha);
}