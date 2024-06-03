# Enigma

## Description
Enigma is a one-to-one creation of an enigma eachine used during World War II to encrypt messages. It cna be used to both encrypt and decrypt messages like an enigma machine.

## Features
- Encrypt messages in the enigma style
- Display encryption settings (pseudo-plugboard and rotor configurations)
- Decrypt messages encrypted by enigma (given the appropriate plugboard and rotor configurations)

## Installation
1. Ensure that you have a C++ compiler installed on your system (e.g., GCC, Clang).
2. Clone this repository or download the source code as a ZIP file and unzip.

## Usage
1. Open a terminal or command prompt and navigate to the directory where the source code is located.
2. Compile the C++ files using the following command:
    ```bash
    g++ Enigma.cpp -o Enigma
    ```
3. Run the program using the following command:
    ```bash
    ./Enigma
    ```
4. Follow the on-screen prompts to either encrypt, decrypt, or exit.
5. Encrypting a message ask you for a message to encrypt and will output your encrypted message with the settings used to generate it. Decrypting a message will ask you for an encrypted message and the settings used to generate it and will output the decrypted message.