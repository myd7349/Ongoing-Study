#include <stdio.h>
#include <stdlib.h>

#include <sodium.h>

#define MESSAGE (const unsigned char *)"test"
#define MESSAGE_LEN 4
#define CIPHERTEXT_LEN (crypto_box_MACBYTES + MESSAGE_LEN)

int main(void) {
  int res = sodium_init();
  if (res < 0) {
    fprintf(stderr, "sodium_init failed: %d\n", res);
    return EXIT_FAILURE;
  }

  unsigned char alice_publickey[crypto_box_PUBLICKEYBYTES];
  unsigned char alice_secretkey[crypto_box_SECRETKEYBYTES];

  crypto_box_keypair(alice_publickey, alice_secretkey);

  unsigned char bob_publickey[crypto_box_PUBLICKEYBYTES];
  unsigned char bob_secretkey[crypto_box_SECRETKEYBYTES];

  crypto_box_keypair(bob_publickey, bob_secretkey);

  unsigned char nonce[crypto_box_NONCEBYTES];
  unsigned char ciphertext[CIPHERTEXT_LEN];

  randombytes_buf(nonce, sizeof nonce);

  if ((res = crypto_box_easy(ciphertext, MESSAGE, MESSAGE_LEN, nonce,
                             bob_publickey, alice_secretkey)) != 0) {
    fprintf(stderr, "crypto_box_easy failed: %d\n", res);
    return EXIT_FAILURE;
  }

  unsigned char decrypted[MESSAGE_LEN + 1];
  if (crypto_box_open_easy(decrypted, ciphertext, CIPHERTEXT_LEN, nonce,
                           alice_publickey, bob_secretkey) != 0) {
    fprintf(stderr,
            "Message for Bob pretending to be from Alice has been forged!\n");
    return EXIT_FAILURE;
  } else {
    decrypted[MESSAGE_LEN] = '\0';
    printf("Alice said: %s\n", decrypted);
  }

  return 0;
}

// References:
// https://github.com/microsoft/vcpkg/issues/7308
// https://github.com/microsoft/vcpkg/issues/8956
// https://github.com/valbendan/LibsodiumVcpkg
// https://download.libsodium.org/doc/public-key_cryptography/authenticated_encryption
