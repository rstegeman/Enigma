#include <iostream>
#include <math.h>
#include <random>
#include <string>
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

//should get called after each character is processed
void shiftRotors() { 
  if (rotorOneID == 25) {
    rotorOneID = 0;
  } else {
    rotorOneID++;
  }

  charProcessed++; //Increment charProcessed

  if (charProcessed % fullAlpha == 0) {
    if (rotorTwoID == 25) {
      rotorTwoID = 0;
    } else {
      rotorTwoID++;
    }
  }
  if (charProcessed % fullAlphaSquared == 0) {
    if (rotorThreeID == 25) {
      rotorThreeID = 0;
    } else {
      rotorThreeID++;
    }
  }
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

string caesarDecipher(string message) {
  for (int i = 0; i < message.size(); i++) {
    int t0 = rotorOneID;
    int t1 = (rotorTwoID - t0 + 26) % 26;
    int t2 = (rotorThreeID - t1 + 26) % 26;
    int t3 = 26 - t2;

    message[i] = (((message[i] - 'A') + t2) % 26) + 'A';

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

    message[i] = (((message[i] - 'A') + t3) % 26) + 'A';
    shiftRotors();
  }

  return message;
}

string caesarCipher(string message) {
  for (int i = 0; i < message.size(); i++) {
    int t0 = rotorOneID;
    int t1 = (rotorTwoID - t0) % fullAlpha;
    int t2 = (rotorThreeID - t1) % fullAlpha; //first pass
    int t3 = fullAlpha - t2; //second pass

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

void setPlugboard() {
  cout << "-----------------Plugboard Settings-----------------" << endl;
  cout << "Enter provide the upper reflection: " << endl;
  string upper;
  cin >> upper;

  cout << "Enter provide the lower reflection: " << endl;
  string lower;
  cin >> lower;

  for (int i = 0; i < num_pairs; i++) {
    plugOne[i] = upper[i];
    plugTwo[i] = lower[i];
  }
  
  
}

void encrypt() {
  cout << "-------------------Enigma Machine-------------------" << endl;
  cout << "-----------------Plugboard Settings-----------------" << endl;
  generateRandomPlugboard(); //create randomized plugboard settings
  cout << "A randomized plugboard pairings have been created for you." << endl; //default plugboard settings
  cout << "The following letters have been swapped:" << endl; //custom plugboard settings
  for (int i = 0; i < num_pairs; i++) {
    cout << plugOne[i]; 
  }
  cout << " <- Upper Reflection"<< endl;

  for (int i = 0; i < num_pairs; i++) {
    cout << plugTwo[i]; 
  }
  cout << " <- Lower Reflection"<< endl;

  cout << endl;
  generateRandomRotors();
  cout << "-------------------Rotor Settings-------------------" << endl;
  cout << "Randomized rotor settings have been created for you." << endl;
  cout << "The first rotor is set to: " << (char)(rotorOneID + 'A') << endl;
  cout << "The second rotor is set to: " << (char)(rotorTwoID + 'A') << endl;
  cout << "The third rotor is set to: " << (char)(rotorThreeID + 'A') << endl;
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
  message = caesarCipher(message);

  cout << "-------------------Enigma Machine-------------------" << endl;
  cout << "Your encrypted message: " << message << endl;

}

void decrypt() {
    cout << "-------------------Enigma Machine-------------------" << endl;
    setPlugboard();
    cout << "-------------------Rotor Settings-------------------" << endl;
    cout << "What letter should the first rotor be set to?"  << endl;
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
    cout << "What letter should the second rotor be set to?"  << endl;
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
    cout << "What letter should the third rotor be set to?"  << endl;
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

    rotorThreeID = rotor - 'A';
    cout << "----------------------Message-----------------------" << endl;
    cout << "What is your encrypted message?" << endl;
    string message;
    cin >> message;


    message = caesarDecipher(message);
    message = plugboardSwap(message);

    cout << "-------------------Enigma Machine-------------------" << endl;
    cout << "Your decrypted message: " << message << endl;


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
    if ((response == 1 || response == 2) && !cin.fail()) {
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