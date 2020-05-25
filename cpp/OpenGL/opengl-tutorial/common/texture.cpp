#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "nv_dds.h"
#include "texture.hpp"

GLuint loadBMP_custom(const char *path) {
  printf("Reading image %s\n", path);

  unsigned char header[54];
  unsigned int dataPos;
  unsigned int imageSize;
  unsigned int width, height;
  unsigned char *data = NULL;

  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "Failed to open file for reading. File path: %s\n", path);
    return 0;
  }

  if (fread(header, 1, sizeof(header), file) != sizeof(header) ||
      header[0] != 'B' || header[1] != 'M') {
    fprintf(stderr, "Unexpected BMP header.\n");
    fclose(file);
    return 0;
  }

  if (*(int *)&header[0x1E] != 0) {
    fprintf(
        stderr,
        "Unsupported BMP format (Currently only 24bpp format is supported).\n");
    fclose(file);
    return 0;
  }

  if (*(int *)&header[0x1C] != 24) {
    fprintf(
        stderr,
        "Unsupported BMP format (Currently only 24bpp format is supported).\n");
    fclose(file);
    return 0;
  }

  dataPos = *(int *)&header[0x0A];
  imageSize = *(int *)&header[0x22];
  width = *(int *)&header[0x12];
  height = *(int *)&header[0x16];

  // Some BMP files are misformatted, guess missing information.
  if (imageSize == 0) imageSize = width * height * 3;
  if (dataPos == 0) dataPos = 54;

  data = (unsigned char *)malloc(imageSize);
  if (data == NULL) {
    fprintf(stderr, "Out of memory.\n");
    fclose(file);
    return 0;
  }

  if (fread(data, 1, imageSize, file) != imageSize) {
    fprintf(stderr, "Unexpected end of file.\n");
    fclose(file);
    free(data);
    return 0;
  }

  fclose(file);

  GLuint textureID;
  glGenTextures(1, &textureID);

  // Bind newly created texture, all future texture functions will modify this
  // texture.
  glBindTexture(GL_TEXTURE_2D, textureID);

  // Give the image to OpenGL
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR,
               GL_UNSIGNED_BYTE, data);

  // OpenGL has now copied the data, free our own version
  free(data);

  // Poor filtering, or ...
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  // ... Nice trilinear filtering ...
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  // ... which requires mipmaps. Generate them automatically.
  glGenerateMipmap(GL_TEXTURE_2D);

  return textureID;
}

// Since GLFW 3, glfwLoadTexture2D() has been removed. You have to use another
// texture loading library, or do it yourself (just like loadBMP_custom and
// loadDDS)
#if 0
GLuint loadTGA_glfw(const char *imagepath) {
  // Create one OpenGL texture
  GLuint textureID;
  glGenTextures(1, &textureID);

  // "Bind" the newly created texture : all future texture functions will modify
  // this texture
  glBindTexture(GL_TEXTURE_2D, textureID);

  // Read the file, call glTexImage2D with the right parameters
  glfwLoadTexture2D(imagepath, 0);

  // Nice trilinear filtering.
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glGenerateMipmap(GL_TEXTURE_2D);

  // Return the ID of the texture we just created
  return textureID;
}
#endif

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

GLuint loadDDS(const char *path) {
  unsigned char header[124];

  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "Failed to open file for reading. File path: %s\n", path);
    return 0;
  }

  char magic[4];
  if (fread(magic, 1, sizeof(magic), file) != sizeof(magic) ||
      strncmp(magic, "DDS ", sizeof(magic)) != 0) {
    fprintf(stderr, "Unexpected DDS header.\n");
    fclose(file);
    return 0;
  }

  // Get the surface desc
  size_t readBytes;
  // `fread` returns number of objects read, not number of bytes.
  // if ((readBytes = fread(header, sizeof(header), 1, file)) != sizeof(header)) { // Oops!
  if ((readBytes = fread(header, sizeof(header), 1, file)) != 1) {
    fprintf(stderr, "Unexpected DDS header size: %zu: ", readBytes);
    if (feof(file)) {
      fprintf(stderr, "End of file.\n");
    } else if (ferror(file)) {
      fprintf(stderr, "Error.\n");
    }
    fclose(file);
    return 0;
  }

  unsigned int height = *(unsigned int *)&(header[8]);
  unsigned int width = *(unsigned int *)&(header[12]);
  unsigned int linearSize = *(unsigned int *)&(header[16]);
  unsigned int mipMapCount = *(unsigned int *)&(header[24]);
  unsigned int fourCC = *(unsigned int *)&(header[80]);

  // How big is it going to be including all mipmaps?
  unsigned int bufferSize = mipMapCount > 1 ? linearSize * 2 : linearSize;
  unsigned char *buffer = (unsigned char *)malloc(bufferSize);
  if (buffer == NULL) {
    fprintf(stderr, "Out of memory.\n");
    fclose(file);
    return 0;
  }

  if (fread(buffer, 1, bufferSize, file) != bufferSize) {
    //fprintf(stderr, "Unexpected end of file.\n");
    //fclose(file);
    //free(buffer);
    //return 0;
  }

  fclose(file);

  unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
  unsigned int format;

  switch (fourCC) {
    case FOURCC_DXT1:
      format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
      break;
    case FOURCC_DXT3:
      format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
      break;
    case FOURCC_DXT5:
      format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
      break;
    default:
      fprintf(stderr, "Unexpected compressed format.\n");
      free(buffer);
      return 0;
  }

  GLuint textureID;
  glGenTextures(1, &textureID);

  glBindTexture(GL_TEXTURE_2D, textureID);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  unsigned int blockSize =
      (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
  unsigned int offset = 0;

  // Load the mipmaps.
  for (unsigned int level = 0; level < mipMapCount && (width || height);
       ++level) {
    unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
    glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size,
                           buffer + offset);

    offset += size;
    width /= 2;
    height /= 2;

    // Deal with Non-Power-Of-Two textures.
    if (width < 1) width = 1;
    if (height < 1) height = 1;
  }

  free(buffer);

  return textureID;
}

static GLuint LoadCompressedDDS(nv_dds::CDDSImage &image) {
  if (!image.is_valid() || !image.is_compressed()) {
    fprintf(stderr, "Invalid compressed DDS file.\n");
    return 0;
  }

  GLuint texture;
  glGenTextures(1, &texture);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);

  glCompressedTexImage2DARB(GL_TEXTURE_2D, 0, image.get_format(),
                            image.get_width(), image.get_height(), 0,
                            image.get_size(), image);

  for (unsigned int i = 0; i < image.get_num_mipmaps(); i++) {
    const nv_dds::CSurface &mipmap = image.get_mipmap(i);

    glCompressedTexImage2DARB(GL_TEXTURE_2D, i + 1, image.get_format(),
                              mipmap.get_width(), mipmap.get_height(), 0,
                              mipmap.get_size(), mipmap);
  }

  return texture;
}

static GLuint LoadUncompressedDDS(nv_dds::CDDSImage &image) {
  if (!image.is_valid() || image.is_compressed()) {
    fprintf(stderr, "Invalid uncompressed DDS file.\n");
    return 0;
  }

  GLuint texture;
  glGenTextures(1, &texture);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexImage2D(GL_TEXTURE_2D, 0, image.get_components(), image.get_width(),
               image.get_height(), 0, image.get_format(), GL_UNSIGNED_BYTE,
               image);

  for (unsigned int i = 0; i < image.get_num_mipmaps(); i++) {
    glTexImage2D(GL_TEXTURE_2D, i + 1, image.get_components(),
                 image.get_mipmap(i).get_width(),
                 image.get_mipmap(i).get_height(), 0, image.get_format(),
                 GL_UNSIGNED_BYTE, image.get_mipmap(i));
  }

  return texture;
}

GLuint loadDDSEx(const char *path) {
  nv_dds::CDDSImage image;
  image.load(path, true);
  if (!image.is_valid()) {
    fprintf(stderr, "Invalid DDS file.\n");
    return 0;
  }

  return image.is_compressed() ? LoadCompressedDDS(image)
                               : LoadUncompressedDDS(image);
}


// References:
// https://github.com/opengl-tutorials/ogl/blob/master/common/texture.cpp
// [DDS File Reference](https://docs.microsoft.com/en-us/previous-versions//bb172993(v=vs.85)?redirectedfrom=MSDN)
// https://github.com/paroj/nv_dds/blob/master/nv_dds.cpp
