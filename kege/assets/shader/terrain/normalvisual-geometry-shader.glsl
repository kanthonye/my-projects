#version 400 // GEOMETERY SHADER

layout(triangles) in;
// Three lines will be generated: 6 vertices
layout(line_strip, max_vertices=6) out;
//uniform float normal_length;
in vec4 normal[];

void main()
{
    float normal_length = 0.5f;
    
    int n;
    for(n=0; n<gl_in.length(); n++)
    {
        gl_Position = gl_in[n].gl_Position;
        EmitVertex();
        
        gl_Position = gl_in[n].gl_Position + normal_length * vec4(normalize(normal[n].xyz), 0.0f);
        EmitVertex();
        
        EndPrimitive();
    }
}