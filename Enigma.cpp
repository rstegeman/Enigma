#include "Enigma.h"
#include <iostream>
#include <math.h>
#include <random>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

//These two arrays will serve as a reflector and operate similarly to the plugboard
const char reflectorOne[] = {'B', 'D', 'C', 'L', 'E', 'I', 'M', 'J', 'H', 'F', 'A', 'G', 'K'};
const char reflectorTwo[] = {'S', 'T', 'V', 'Y', 'X', 'W', 'Z', 'Q', 'R', 'N', 'O', 'P', 'U'};

const int fullAlphaSquared = 676; //length of the alphabet squared
const int fullAlpha = 26; //length of the alphabet
const int halfAlpha = 13; //length of half of the alphabet

const int num_pairs = 10; //the number of plugboard pairs

//these two arrays make up the plugboard that would swap letters when typed in the keyboard
char plugOne[num_pairs + 1]; //arrays of characters that will be swapped by the plugboard
char plugTwo[num_pairs + 1]; //plus one for the null character

//Tracks orientation ID of rotorOne
//Each rotor is in alphabetical order, but the ID determines where the rotor starts
int rotorOneID;
int rotorTwoID;
int rotorThreeID;

int charProcessed = 0; //keeps track of characters processed for rotor shifting

void shiftRotors() {
  rotorOneID = (rotorOneID + 1) % fullAlpha;

  if (rotorOneID == rotorTwoID)
    rotorTwoID = (rotorTwoID + 1) % fullAlpha;

  rotorThreeID = (rotorThreeID + 1) % fullAlpha;
}


void generateRandomRotors() { //Grab randomized rotors
  int randomNumbers[fullAlpha];
    for (int i = 0; i < fullAlpha; ++i) {
        randomNumbers[i] = i;  // Fill the array with numbers 0 to 25
    }

    random_device rd;
    mt19937 rng(rd());

    shuffle(randomNumbers, randomNumbers + fullAlpha, rng);  // Shuffle the array

    rotorOneID = randomNumbers[0];
    rotorTwoID = randomNumbers[1];
    rotorThreeID = randomNumbers[2];
}

void generateRandomPlugboard() {
  int randomNumbers[fullAlpha];
    for (int i = 0; i < fullAlpha; ++i) {
        randomNumbers[i] = i;  // Fill the array with numbers 0 to 25
    }

    random_device rd;
    mt19937 rng(rd());

    shuffle(randomNumbers, randomNumbers + fullAlpha, rng);  // Shuffle the array

    // Use the first 20 numbers
    for (int i = 0; i < 20; ++i) {
        if (i <= 9) {
          plugOne[i] = randomNumbers[i] + 'A'; //fills plugIn with random chars
        } else {
          plugTwo[i % num_pairs] = randomNumbers[i] + 'A'; //fills plugOut with random chars; modulo to account for index over 10
        }
    }
}

string plugboardSwap(string message) { //make plugboard character swaps
  for (int i = 0; i < message.size(); i++) {
    for (int j = 0; j < num_pairs; j++) {
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
  for (int i = 0; i < message.size(); i++) {
    int t0 = rotorOneID;
    int t1 = (rotorTwoID - t0) % fullAlpha;
    int t2 = (rotorThreeID - t1) % fullAlpha;
    int t3 = (fullAlpha - t2) % fullAlpha;

    message[i] = (((message[i] - 'A') + t2) % fullAlpha) + 'A';

    for (int j = 0; j < halfAlpha; j++) { //reflector
      if (message[i] == reflectorOne[j]) {
        message[i] = reflectorTwo[j];
        continue;
      }
      if (message[i] == reflectorTwo[j]) {
        message[i] = reflectorOne[j];
        continue;
      }
    }

    message[i] = (((message[i] - 'A') + t3) % fullAlpha) + 'A';

    shiftRotors();
  }

  return message;
}

string caesarDecipher(string message) {
  for (int i = 0; i < message.size(); i++) {
    int t0 = rotorOneID;
    int t1 = (rotorTwoID - t0 + fullAlpha) % fullAlpha;
    int t2 = (rotorThreeID - t1 + fullAlpha) % fullAlpha;
    int t3 = (fullAlpha - t2) % fullAlpha;

    message[i] = (((message[i] - 'A') + t2) % fullAlpha) + 'A';

    for (int j = 0; j < 13; j++) {
      if (message[i] == reflectorOne[j]) {
        message[i] = reflectorTwo[j];
        continue;
      }
      if (message[i] == reflectorTwo[j]) {
        message[i] = reflectorOne[j];
        continue;
      }
    }

    message[i] = (((message[i] - 'A') + t3) % fullAlpha) + 'A';
    shiftRotors();
  }

  return message;
}


void setPlugboard() {
  cout << "-------------------Plugboard Settings-------------------" << endl << endl;
  cout << "Positive code: ";
  string upper;
  cin >> upper;

  for (int i = 0; i < upper.size(); i++) { //Catch any messages that contain non-letters
    if ( ((upper[i] < 'a' || upper[i] > 'z') && (upper[i] < 'A' || upper[i] > 'Z')) || cin.fail() || upper.size() != 10) {
      cin.clear();
      cout << "Please enter a valid positive code." << endl;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cin >> upper;
      cout << endl;
      i = -1;
    }
    for (int j = i + 1; j < upper.size(); j++) {
      if (upper[i] == upper[j]) {
        cin.clear();
        cout << "Please enter a valid positive code." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> upper;
        cout << endl;
        i = -1;
      }
    }
  }

  cout << "Negative code: ";
  string lower;
  cin >> lower;

  for (int i = 0; i < lower.size(); i++) { //Catch any messages that contain non-letters
    if ( ((lower[i] < 'a' || lower[i] > 'z') && (lower[i] < 'A' || lower[i] > 'Z')) || cin.fail() || lower.size() != 10) {
      cin.clear();
      cout << "Please enter a valid negative code." << endl;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cin >> lower;
      cout << endl;
      i = -1;
    }
    for (int j = i + 1; j < lower.size(); j++) {
      if (lower[i] == lower[j]) {
        cin.clear();
        cout << "Please enter a valid negative code." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> lower;
        cout << endl;
        i = -1;
      }
    }
  }
  cout << endl;

  for (int i = 0; i < num_pairs; i++) {
    plugOne[i] = upper[i];
    plugTwo[i] = lower[i];
  }
  
  
}

void encrypt() {
  cout << "-------------------Plugboard Settings-------------------" << endl;
  generateRandomPlugboard(); //create randomized plugboard settings
  cout << "Randomized plugboard settings have been created for you." << endl << endl;
  cout << "Positive code: ";
  for (int i = 0; i < num_pairs; i++) {
    cout << plugOne[i]; 
  }
  cout << endl;

  cout << "Negative code: ";
  for (int i = 0; i < num_pairs; i++) {
    cout << plugTwo[i]; 
  }
  cout << endl;

  cout << endl;
  generateRandomRotors();
  cout << "---------------------Rotor Settings--------------------" << endl;
  cout << "Randomized rotor settings have been created for you." << endl << endl;
  cout << "First rotor: " << (char)(rotorOneID + 'A') << endl;
  cout << "Second rotor: " << (char)(rotorTwoID + 'A') << endl;
  cout << "Third rotor: " << (char)(rotorThreeID + 'A') << endl;
  cout << endl;

  cout << "------------------------Message-------------------------" << endl;
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
  message = caesarCipher(message);

  cout << "------------------------Encrypted-----------------------" << endl;
  cout << "Your encrypted message: " << endl << message << endl;

}

void decrypt() {
    setPlugboard();
    cout << "---------------------Rotor Settings---------------------" << endl << endl;
    cout << "First rotor: ";
    char rotor;
    cin >> rotor;

    while(1) {
      if ( ((rotor < 'a' || rotor > 'z') && (rotor < 'A' || rotor > 'Z')) || cin.fail() ) {
        cin.clear();
        cout << "Please use letters only." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> rotor;
        cout << endl;
      }
      if ( ((rotor >= 'a' && rotor <= 'z') || (rotor >= 'A' && rotor <= 'Z')) && !cin.fail()) {
        break;
      }
    }
    if (rotor >= 'a' && rotor <= 'z') {
      rotor = rotor + 'A' - 'a';
    }

    rotorOneID = rotor - 'A';
    cout << "Second rotor: ";
    cin >> rotor;

    while(1) {
      if ( ((rotor < 'a' || rotor > 'z') && (rotor < 'A' || rotor > 'Z')) || cin.fail() ) {
        cin.clear();
        cout << "Please use letters only." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> rotor;
        cout << endl;
      }
      if ( ((rotor >= 'a' && rotor <= 'z') || (rotor >= 'A' && rotor <= 'Z')) && !cin.fail()) {
        break;
      }
    }
    if (rotor >= 'a' && rotor <= 'z') {
      rotor = rotor + 'A' - 'a';
    }

    rotorTwoID = rotor - 'A';
    cout << "Third rotor: ";
    cin >> rotor;

    while(1) {
      if ( ((rotor < 'a' || rotor > 'z') && (rotor < 'A' || rotor > 'Z')) || cin.fail() ) {
        cin.clear();
        cout << "Please use letters only." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> rotor;
        cout << endl;
      }
      if ( ((rotor >= 'a' && rotor <= 'z') || (rotor >= 'A' && rotor <= 'Z')) && !cin.fail()) {
        break;
      }
    }
    if (rotor >= 'a' && rotor <= 'z') {
      rotor = rotor + 'A' - 'a';
    }

    cout << endl;

    rotorThreeID = rotor - 'A';
    cout << "------------------------Message-------------------------" << endl;
    cout << "What is your encrypted message?" << endl;
    string message;
    cin >> message;

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

    cout << endl;


    message = caesarDecipher(message);
    message = plugboardSwap(message);

    cout << "------------------------Decrypted-----------------------" << endl;
    cout << "Your decrypted message: " << endl << message << endl;


}

int main() {
  while(1) {
    cout << endl;
    cout << "    ______      _                          __  ___           __    _          " << endl;
    cout << "   / ____/___  (_)___ _____ ___  ____ _   /  |/  /___ ______/ /_  (_)___  ___ " << endl;
    cout << "  / __/ / __ \\/ / __ `/ __ `__ \\/ __ `/  / /|_/ / __ `/ ___/ __ \\/ / __ \\/ _ \\" << endl;
    cout << " / /___/ / / / / /_/ / / / / / / /_/ /  / /  / / /_/ / /__/ / / / / / / /  __/" << endl;
    cout << "/_____/_/ /_/_/\\__, /_/ /_/ /_/\\__,_/  /_/  /_/\\__,_/\\___/_/ /_/_/_/ /_/\\___/ " << endl;
    cout << "              /____/                                                          " << endl;
    cout << "Which would you like to do?" << endl;
    cout << "1. Encrypt" << endl;
    cout << "2. Decrypt" << endl;
    cout << "3. Exit" << endl << endl;

    int response;
    cin >> response;
    cout << endl;

    while(1) {
      if ((response != 1 && response != 2 && response != 3) || cin.fail()) {
        cin.clear();
        cout << "Please enter either 1, 2, or 3." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> response;
        cout << endl;
      }
      if ((response == 1 || response == 2 || response == 3) && !cin.fail()) {
        break;
      }
    }

      if (response == 1) {
          encrypt();
      } else if (response == 2) {
          decrypt();
      } else if (response == 3) {
        return 0;
      } else {
        return 1;
      }
      
  }
  
}