#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>
#include <math.h>
#include <random>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

void shiftRotors();
void generateRandomRotors();
void generateRandomPlugboard();
string plugboardSwap(string message);
string caesarCipher(string message);
string caesarDecipher(string message);
void setPlugboard();
void encrypt();
void decrypt();

#endif // ENIGMA_H