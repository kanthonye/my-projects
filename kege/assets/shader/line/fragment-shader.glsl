#version 400 core
out vec4 fragcolor;
in vec3 color;
void main( void )
{
    fragcolor = vec4(color, 1.0);
}


