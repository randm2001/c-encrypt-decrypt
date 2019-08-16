# Run the following steps to encrypt your strings
# cd to/the/path/of/this/project
# cmake .
# make
# ./encrypt-decrypt
cmake_minimum_required(VERSION 3.4.1)
project (encrypt-decrypt)
add_executable(encrypt-decrypt encrypt-decrypt.cpp aes.h aes.hpp aes.c base64.h base64.c)