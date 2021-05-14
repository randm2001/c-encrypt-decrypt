#include <string>
#include <string.h>
#include <stdio.h>
#include "aes.h"
#include "base64.h"
#include <iostream>

int main()
{
    uint8_t key[] = "secret key 123";
    std::string in = "my message";
    uint8_t iv[16] = { 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff };

    printf("Plain: %s", &in[0]);
    printf("\nLength: %lu", in.length());

    std::string encoded;
    encoded.resize(Base64encode_len(in.length()));
    Base64encode(&encoded[0], in.data(), in.length());
    printf("\nEncoded: %s", &encoded[0]);

    struct AES_ctx ctx;
    uint8_t *encodedCharArr = reinterpret_cast<uint8_t*>(&encoded[0]);
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CTR_xcrypt_buffer(&ctx, encodedCharArr, strlen((char*)encodedCharArr));
    printf("\nEncrypted: %s", (char*)encodedCharArr);

    AES_init_ctx_iv(&ctx, key, iv);
    AES_CTR_xcrypt_buffer(&ctx, encodedCharArr, strlen((char*)encodedCharArr));
    printf("\nDecrypted: %s", (char*)encodedCharArr);
    
     std::string decoded;
     decoded.resize(Base64decode_len((char*)encodedCharArr));
     size_t actualSize = Base64decode(&decoded[0], (char*)encodedCharArr);
     decoded.resize(actualSize);
     printf("\nDecoded: %s", &decoded[0]);
    return 0;
}