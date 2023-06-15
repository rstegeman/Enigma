#include <iostream>
#include <math.h>
#include <random>
using namespace std;
char plugOne[10];
char plugTwo[10];

const char rotors[][26] = {
    {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'},
    {'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A'},
    {'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B'},
    {'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C'},
    {'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D'},
    {'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E'},
    {'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F'},
    {'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G'},
    {'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
    {'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'},
    {'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'},
    {'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'},
    {'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'},
    {'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M'},
    {'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N'},
    {'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O'},
    {'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'},
    {'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q'},
    {'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R'},
    {'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S'},
    {'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T'},
    {'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U'},
    {'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V'},
    {'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W'},
    {'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'},
    {'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y'}
};

char rotorOne[];
char rotorTwo[];
char rotorThree[];

void shallowCopyArray(const char source[], char destination[], int size) {
    copy(source, source + size, destination);
}

void generateRandomRotors() { //Grab randomized rotors
  int randomNumbers[3];
    for (int i = 0; i < 3; ++i) {
        randomNumbers[i] = i;  // Fill the array with numbers 0 to 25
    }

    random_device rd;
    mt19937 rng(rd());

    shuffle(randomNumbers, randomNumbers + 3, rng);  // Shuffle the array

    // Use the first 20 numbers
    for (int i = 0; i < 3; ++i) {
        if (i <= 9) {
          plugOne[i] = randomNumbers[i] + 'A'; //fills plugIn with random chars
        } else {
          plugTwo[i % 10] = randomNumbers[i] + 'A'; //fills plugOut with random chars; modulo to account for index over 10
        }
    }

    int size = sizeof(rotors[0])/sizeof(rotors[0][0]);
    shallowCopyArray(rotors[randomNumbers[0]], rotorOne, size);
    shallowCopyArray(rotors[randomNumbers[1]], rotorTwo, size);
    shallowCopyArray(rotors[randomNumbers[2]], rotorThree, size);
}

void generateRandomPlugboard() {
  int randomNumbers[26];
    for (int i = 0; i < 26; ++i) {
        randomNumbers[i] = i;  // Fill the array with numbers 0 to 25
    }

    random_device rd;
    mt19937 rng(rd());

    shuffle(randomNumbers, randomNumbers + 26, rng);  // Shuffle the array

    // Use the first 20 numbers
    for (int i = 0; i < 20; ++i) {
        if (i <= 9) {
          plugOne[i] = randomNumbers[i] + 'A'; //fills plugIn with random chars
        } else {
          plugTwo[i % 10] = randomNumbers[i] + 'A'; //fills plugOut with random chars; modulo to account for index over 10
        }
    }
}

void encrypt() {
  cout << "-------------------Enigma Machine-------------------" << endl;
  cout << "-----------------Plugboard Settings-----------------" << endl;
  generateRandomPlugboard(); //create randomized plugboard settings
  cout << "A randomized plugboard pairings have been created for you." << endl; //default plugboard settings
  cout << "The following letters have been swapped:" << endl; //custom plugboard settings
  for (int i = 0; i < 10; i++) {
    cout << plugOne[i] << "/" << plugTwo[i] << endl; //Print swapped letters
  }
  
  cout << endl;
  cout << "Randomized rotor settings have been created for you." << endl;
  cout << "The first rotor is set to: " << rotorOne[0] << endl;
  cout << "The second rotor is set to: " << rotorTwo[0] << endl;
  cout << "The third rotor is set to: " << rotorThree[0] << endl;
  cout << endl;
}

void decrypt() {
    cout << "-------------------Enigma Machine-------------------" << endl;
    cout << "-----------------Plugboard Settings-----------------" << endl;
}

int main() {
  cout << "-------------------Enigma Machine-------------------" << endl;
  cout << "Which would you like to do?:" << endl;
  cout << "1. Encrypt" << endl;
  cout << "2. Decrypt" << endl;
  cout << endl;

  int response;
  cin >> response;
  cout << endl;

  while(1) {
    if ((response != 1 && response != 2) || cin.fail()) {
      cin.clear();
      cout << "Please enter either 1 or 2." << endl;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cin >> response;
      cout << endl;
    }
    if (response == 1 || response == 2 || !cin.fail()) {
      break;
    }

    if (response == 1) {
        encrypt();
    } else {
        decrypt();
    }
    return 0;
  }
}