// https://github.com/openglredbook/examples/blob/master/bin/media/shaders/triangles/triangles.vert
#version 400 core

layout( location = 0 ) in vec4 vPosition;

void
main()
{
    gl_Position = vPosition;
}
