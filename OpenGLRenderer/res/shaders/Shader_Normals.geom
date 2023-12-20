#version 430 core

layout(triangles) in;

layout(line_strip, max_vertices=6) out;

uniform float normal_length;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

in Vertex
{
  vec3 normal;
} vertex[];

void main()
{
  int i;
  for(i=0; i<gl_in.length(); i++)
  {
    vec3 P = gl_in[i].gl_Position.xyz;
    vec3 N = vertex[i].normal;
    
    gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(P, 1.0);
    EmitVertex();
    
    gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(P + N * normal_length, 1.0);
    EmitVertex();
    
    EndPrimitive();
  }
}