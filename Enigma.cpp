#include <iostream>
#include <math.h>
using namespace std;
char plugIn[6];
char plugOut[6];

void encrypt() {
    cout << "-----------------------Plugboard-----------------------" << endl;
    cout << "1. Use default" << endl;
    cout << "2. Use custom" << endl;
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
      *(plugIn) = 'A';
      *(plugIn + 1) = 'P';
      *(plugIn + 2) = 'T';
      *(plugIn + 3) = 'B';
      *(plugIn + 4) = 'K';
      *(plugIn + 5) = 'O';

      *(plugOut) = 'L';
      *(plugOut + 1) = 'R';
      *(plugOut + 2) = 'D';
      *(plugOut + 3) = 'W';
      *(plugOut + 4) = 'F';
      *(plugOut + 5) = 'Y';
    } else {
      for (int i = 0; i < 6; i++) {
        cout << "Please enter a unique capital letter." << endl;
        char letterIn;
        cin >> letterIn;
      }
    }
}

void decrypt() {
    
}

int main() {
    cout << "-------------------Password Manager-------------------" << endl;
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