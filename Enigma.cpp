#include <iostream>
#include <math.h>
#include <random>
#include <string>
using namespace std;

const char rotors[][26] = { //all possible rotor orientations
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

const char reflectorOne[] = {'B', 'D', 'C', 'L', 'E', 'I', 'M', 'J', 'H', 'F', 'A', 'G', 'K'}; //a reflector divided in two
const char reflectorTwo[] = {'S', 'T', 'V', 'Y', 'X', 'W', 'Z', 'Q', 'R', 'N', 'O', 'P', 'U'};

const int rSize = sizeof(rotors[0])/sizeof(rotors[0][0]); //size of rotor


char plugOne[10]; //arrays of characters that will be swapped by the plugboard
char plugTwo[10];

char rotorOne[26]; //Tracks orientation of rotorOne
int rotorOneID; //Tracks orientation ID of rotorOne

char rotorTwo[26];
int rotorTwoID;

char rotorThree[26];
int rotorThreeID;

int charProcessed = 0; //keeps track of characters processed for rotor shifting

int OOBchecker(int index) { //keeps index values 0-25
  if (index < 0) {
    return index + 26;
  } else if (index > 25) {
    return index - 26;
  } else {
    return index;
  }
}

void shallowCopyArray(const char source[], char destination[], int size) {
    copy(source, source + size, destination);
}

void shiftRotorOne() { //should get called after each character is processed
  if (rotorOneID == 25) {
    rotorOneID = 0;
  } else {
    rotorOneID++;
  }

  shallowCopyArray(rotors[rotorOneID], rotorOne, rSize);

  charProcessed++; //Increment charProcessed

  if (charProcessed % 26 == 0)
    shiftRotorTwo();
  if (charProcessed % 676 == 0)
    shiftRotorThree();
}

void shiftRotorTwo() { //should get called after a full cycle of rotorOne (26 characters)
  if (rotorTwoID == 25) {
    rotorTwoID = 0;
  } else {
    rotorTwoID++;
  }

  shallowCopyArray(rotors[rotorTwoID], rotorTwo, rSize);
}

void shiftRotorThree() { //should get called after a full cycle of rotorTwo (676 characters)
  if (rotorThreeID == 25) {
    rotorThreeID = 0;
  } else {
    rotorThreeID++;
  }

  shallowCopyArray(rotors[rotorThreeID], rotorThree, rSize);
}

void generateRandomRotors() { //Grab randomized rotors
  int randomNumbers[26];
    for (int i = 0; i < 26; ++i) {
        randomNumbers[i] = i;  // Fill the array with numbers 0 to 25
    }

    random_device rd;
    mt19937 rng(rd());

    shuffle(randomNumbers, randomNumbers + 26, rng);  // Shuffle the array

    shallowCopyArray(rotors[randomNumbers[0]], rotorOne, rSize);
    rotorOneID = randomNumbers[0];
    shallowCopyArray(rotors[randomNumbers[1]], rotorTwo, rSize);
    rotorTwoID = randomNumbers[1];
    shallowCopyArray(rotors[randomNumbers[2]], rotorThree, rSize);
    rotorThreeID = randomNumbers[2];
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

string plugboardSwap(string message) { //make plugboard character swaps
  for (int i = 0; i < message.size(); i++) {
    for (int j = 0; j < 10; j++) {
      if (message[i] == plugOne[j]) { //if a letter matches in plugOne, swap it with plugTwo's letter
        message[i] = plugTwo[j];
        continue;
      }
      if (message[i] == plugTwo[j]) { //if a letter matches in plugTwo, swap it with plugOne's letter
        message[i] = plugOne[j];
        continue;
      }
    }
  }
  return message; //return swapped string
}

string caesarCipher(string message) {
  int alphr1 = OOBchecker(rotorOne[0] - rotors[0][0]); //diff between alphabet and rotorOne
  int r1r2 = OOBchecker(rotorTwo[0] - rotorOne[0]); //diff between rotorOne and rotorTwo
  int r2r3 = OOBchecker(rotorThree[0] - rotorTwo[0]); //diff between rotorThree and rotorTwo
  
  for (int i = 0; i < message.size(); i++) {
    
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
  generateRandomRotors();
  cout << "Randomized rotor settings have been created for you." << endl;
  cout << "The first rotor is set to: " << rotorOne[0] << endl;
  cout << "The second rotor is set to: " << rotorTwo[0] << endl;
  cout << "The third rotor is set to: " << rotorThree[0] << endl;
  cout << endl;

  cout << "What is the message you would like to encrypt?" << endl;
  string message;
  cin >> message;
  cout << endl;

  for (int i = 0; i < message.size(); i++) { //Catch any messages that contain non-letters
    if ( ((message[i] < 'a' || message[i] > 'z') && (message[i] < 'A' || message[i] > 'Z')) || cin.fail() ) {
      cin.clear();
      cout << "Please use letters only." << endl;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cin >> message;
      cout << endl;
      i = -1;
    }
  }

  for (int i = 0; i < message.size(); i++) { //capitalizes lowercase letters
    if (message[i] >= 'a' && message[i] <= 'z') {
      message[i] += 'A' - 'a'; 
    }
  }

  message = plugboardSwap(message);

  //cout << message << endl;

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
  }

    if (response == 1) {
        encrypt();
    } else {
        decrypt();
    }
    return 0;
}
//cout << "Checkpoint" << endl;