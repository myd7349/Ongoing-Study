#ifndef RLGL_H_
#define RLGL_H_

// Matrix modes (equivalent to OpenGL)
#define RL_MODELVIEW                    0x1700      // GL_MODELVIEW
#define RL_PROJECTION                   0x1701      // GL_PROJECTION
#define RL_TEXTURE                      0x1702      // GL_TEXTURE

void rlMatrixMode(int mode);

#if defined(RLGL_IMPLEMENTATION)

static int currentMatrixMode = -1;

void rlMatrixMode(int mode)
{
    currentMatrixMode = mode;
}

#endif

#endif // RLGL_H_
