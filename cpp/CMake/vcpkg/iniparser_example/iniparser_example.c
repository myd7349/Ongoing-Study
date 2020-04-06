// clang-format off
#include <stdio.h>

#include <iniparser.h>
// clang-format on

int main(void) {
  dictionary *ini = iniparser_load("account.ini");
  if (ini == NULL) {
    fprintf(stderr, "Failed to load INI file.\n");
    return -1;
  }

  printf("account-name: %s\n",
         iniparser_getstring(ini, "account:account-name", "<nul>"));
  printf("primary-key: %s\n",
         iniparser_getstring(ini, "account:primary-key", "<nul>"));
  printf("secondary-key: %s\n",
         iniparser_getstring(ini, "account:secondary-key", "<nul>"));
  printf("end-point: %s\n",
         iniparser_getstring(ini, "account:end-point", "<nul>"));
  printf("use-https: %d\n",
         iniparser_getboolean(ini, "account:use-https", -1));

  iniparser_freedict(ini);

  return 0;
}
