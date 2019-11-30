#include "GLSnapshot.h"

#include <GL/gl.h>

// In VS2010, I find that `GL_BGR_EXT` is defined in `GL/gl.h` and `GL/glext.h`
// isn't available. In Code::Blocks 17.12 with MinGW 8.1.0, we should include
// `GL/glext.h` to import the definition of `GL_BGR_EXT`.
#ifndef GL_BGR_EXT
#include <GL/glext.h>
#endif

// flushes the OpenGL error queue and
// counts the total number of errors
int flushGLErrors(void) {
  int i = 0;
  while (glGetError() != GL_NO_ERROR) i++;

  return i;
}

// returns a HBITMAP or NULL.
// The HBITMAP must be freed using DeleteObject
HBITMAP ReadPixelsToHBITMAP(HDC hdc, int x, int y, int width, int height,
                            BOOL bUseBackBuffer) {
  void *pdata = NULL;

  /* Note that this values only makes sense if we know a target
   * output size like if we put the image to paper. */
  // const int physical_resolution = 2835; /* 72 DPI */

  BITMAPINFOHEADER bmih = {
      /* .biSize          = */ sizeof(bmih),
      /* .biWidth         = */ width,
      /* .bi.Height       = */ height,
      /* .biPlanes        = */ 1,      /* mandatory */
      /* .biBitCount      = */ 24,     /* 8 bits per pixel */
      /* .biCompression   = */ BI_RGB, /* uncompressed */
      /* .biSizeImage     = */ 0,      /* implicit */
      /* .biXPelsPerMeter = */ 0,      // physical_resolution, /* ignored */
      /* .biYPelsPerMeter = */ 0,      // physical_resolution, /* ignored */
      /* .biClrUsed       = */ 0,      /* no palette */
      /* .biClrImportant  = */ 0};

  HBITMAP hbm = CreateDIBSection(
      hdc,                /* may be different than the DC used for OpenGL */
      (PBITMAPINFO)&bmih, /* can do this cast, because no palette is used */
      DIB_RGB_COLORS, &pdata, NULL, 0);

  if (!hbm) return NULL;

  flushGLErrors();

  glPixelStorei(GL_PACK_SWAP_BYTES, GL_FALSE);
  glPixelStorei(GL_PACK_LSB_FIRST, GL_TRUE);
  glPixelStorei(GL_PACK_ROW_LENGTH, 0);
  // The definition of GL_PACK_IMAGE_HEIGHT can be found in glew.h.
  // glPixelStorei(GL_PACK_IMAGE_HEIGHT, 0);
  glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
  glPixelStorei(GL_PACK_SKIP_ROWS, 0);
  // I change the second argument from 1 to 4(GL_PACK_ALIGNMENT's default) here.
  glPixelStorei(GL_PACK_ALIGNMENT, 4);

  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    DeleteObject(hbm);
    return NULL;
  }

  // For some Intel cards, using GL_FRONT here may got a full black image:
  // https://gamedev.stackexchange.com/questions/38008/why-does-using-glreadbuffer-glreadpixels-returns-black-image-on-intel-cards
  glReadBuffer(bUseBackBuffer ? GL_BACK : GL_FRONT);

  glReadPixels(x, y, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, pdata);

  error = glGetError();
  if (error != GL_NO_ERROR) {
    DeleteObject(hbm);
    return NULL;
  }

  return hbm;
}

// References:
// OpenGL Programming Guide
// http://stackoverflow.com/questions/14908743/opengl-render-directly-to-bitmap
// https://www.opengl.org/discussion_boards/showthread.php/142378-glReadPixels-gives-only-black
// https://www.opengl.org/discussion_boards/showthread.php/122861-GL_BGR
// https://stackoverflow.com/questions/18255082/render-to-fbo-glreadpixels-all-black
// https://www.codeproject.com/Articles/585/Printing-and-Print-Preview-OpenGL-with-MFC
// https://www.codeproject.com/articles/41/a-win32-class-support-opengl-printing
// https://www.gamedev.net/forums/topic/130431-what-is-wrong-with-gl_bgr-pixel-format/
