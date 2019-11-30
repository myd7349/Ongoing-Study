// Copied from: https://github.com/openglredbook/examples/blob/master/include/vgl.h
#ifndef __VGL_H__
#define __VGL_H__

#ifdef _glfw3_h_
# error You must include vgl.h before including any other headers.
#endif

#if 0
# include <GL3/gl3.h>
# include <GL3/gl3w.h>
#else
# include <GL/gl3w.h>
#endif

#include <GLFW/glfw3.h>

#define BUFFER_OFFSET(a) ((void*)(a))

#endif /* __VGL_H__ */
