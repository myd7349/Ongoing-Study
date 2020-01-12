#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <MemoryModule.h>

typedef void (*FooFunc)(const char *name);

unsigned char *ReadAllBytes(const char *filePath, size_t *size) {
  assert(filePath != NULL);
  assert(size != NULL);

  FILE *fp;
  fopen_s(&fp, filePath, "rb");
  if (fp == NULL) return NULL;

  if (fseek(fp, 0, SEEK_END) != 0) {
    fclose(fp);
    return NULL;
  }

  *size = (size_t)ftell(fp);
  if (*size == EOF) {
    fclose(fp);
    return NULL;
  }

  unsigned char *bytes = malloc(*size);
  if (bytes == NULL) {
    fclose(fp);
    return NULL;
  }

  if (fseek(fp, 0, SEEK_SET) != 0 || fread(bytes, 1, *size, fp) != *size) {
    free(bytes);
    fclose(fp);
    return NULL;
  }

  fclose(fp);

  return bytes;
}

int main(void) {
  size_t size;
  void *dll = ReadAllBytes("mylib.dll", &size);
  if (dll == NULL) {
    fprintf(stderr, "Failed to read DLL data into memory.\n");
    return EXIT_FAILURE;
  }

  HMEMORYMODULE hMM = MemoryLoadLibrary(dll, size);
  if (hMM == NULL) {
    fprintf(stderr, "Failed to load DLL from memory.\n");
    free(dll);
    return EXIT_FAILURE;
  }

  FooFunc foo = (FooFunc)MemoryGetProcAddress(hMM, "Foo");
  if (foo == NULL) {
    fprintf(stderr, "Failed to get procedure address.\n");
    MemoryFreeLibrary(hMM);
    free(dll);
    return EXIT_FAILURE;
  }

  foo("Sam");

  MemoryFreeLibrary(hMM);

  free(dll);

  return 0;
}


// References:
// https://github.com/fancycode/MemoryModule/blob/master/tests/LoadDll.cpp
