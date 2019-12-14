// Copied from: https://github.com/openglredbook/examples/blob/master/include/vgl.h
#ifndef __VGL_H__
#define __VGL_H__

#ifdef _glfw3_h_
# error You must include vgl.h before including any other headers.
#endif

#if 0
// https://github.com/openglredbook/examples/blob/master/include/GL3/gl3.h
# include <GL3/gl3.h>
#else
// https://github.com/KhronosGroup/OpenGL-Registry
# include <GL/glcorearb.h>
#endif
#include <GL/gl3w.h>

#include <GLFW/glfw3.h>

#define BUFFER_OFFSET(a) ((void*)(a))

#endif /* __VGL_H__ */

// References:
// [Cannot find GL3/gl3.h](https://www.reddit.com/r/opengl/comments/6khedu/cannot_find_gl3gl3h)
