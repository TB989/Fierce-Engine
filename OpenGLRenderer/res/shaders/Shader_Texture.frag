#version 430 core

layout (location=0) in vec2 vs_textureCoordinate;

layout(location = 0) out vec4 outColor;

uniform sampler2D sampler;

void main() {
    //outColor = vec4(1,0,0,0);
    outColor=texture(sampler, vs_textureCoordinate);
    //outColor=vec4(vs_textureCoordinate,1,0);
}