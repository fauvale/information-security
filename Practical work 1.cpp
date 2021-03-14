#include <iostream>
#include <string>
#include <cmath>
using namespace std;

void firstSquare(string** arr, int size) {
    int count = 1;
    for (int i = 0; i < size / 2; i++) {
        for (int j = 0; j < size / 2; j++) {
            arr[i][j].push_back(count + '0');
            arr[i][j].push_back('*');
            count++;
        }
    }
}

void secondSquare(string** arr, int size) {
    int count = 1;
    for (int j = (size - 1); j >= size / 2; j--) {
        for (int i = 0; i < size / 2; i++) {
            arr[i][j].push_back(count + '0');
            arr[i][j].push_back('.');
            count++;
        }
    }
}

void thirdSquare(string** arr, int size) {
    int count = 1;
    for (int i = (size - 1); i >= size / 2; i--) {
        for (int j = (size - 1); j >= size / 2; j--) {
            arr[i][j].push_back(count + '0');
            arr[i][j].push_back('#');
            count++;
        }
    }
}

void fourthSquare(string** arr, int size) {
    int count = 1;
    for (int j = 0; j < size / 2; j++) {
        for (int i = (size - 1); i >= size / 2; i--) {
            arr[i][j].push_back(count + '0');
            arr[i][j].push_back('@');
            count++;
        }
    }
}

string** createArray(int size) {                     // заполнение квадрата
    string** array = new string * [size];
    for (int i = 0; i < size; i++) {
        array[i] = new string[size];
    }

    firstSquare(array, size);
    secondSquare(array, size);
    thirdSquare(array, size);
    fourthSquare(array, size);

    return array;
}

void encodeChar(string** arr, string code, char toCode, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (arr[i][j] == code) {
                arr[i][j] = toCode;
                return;
            }
        }
    }
}

string encodeString(string stringToEncode) {
    string encodedString;
    string lattice[] = { "1*", "2.", "3*", "4@" }; //ввод символов
    int lattSize = 4;


    int size = sqrt(stringToEncode.length());
    if (size % 2 != 0) {
        size++;
    }
    if (pow(2, size) < stringToEncode.length()) {
        size += 2;
    }
    string** grille = createArray(size); // вывод квадрата на консоль

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << grille[i][j] << " ";
            }
        cout << endl;
    }

    int codePos = 0;
    for (int i = 0; i < stringToEncode.length(); i++) {    // проходимся по каждому символу в строке
        encodeChar(grille, lattice[codePos], stringToEncode[i], size); // занос символов в решетку
        codePos++; // следующая позиция
        if (codePos == lattSize) {
            codePos = 0;
            for (int k = 0; k < lattSize; k++) { // поворот решетки
                if (lattice[k][1] == '*') {
                    lattice[k][1] = '.';
                }
                else if (lattice[k][1] == '.') {
                    lattice[k][1] = '#';
                }
                else if (lattice[k][1] == '#') {
                    lattice[k][1] = '@';
                }
                else if (lattice[k][1] == '@') {
                    lattice[k][1] = '*';
                }
            }
        }
    }

    for (int i = 0; i < size; i++) {                     // длина сообщения меньше кол-ва ячеек
        for (int j = 0; j < size; j++) {
            if (grille[i][j].length() > 1) {
                grille[i][j] = "A";
            }
        }
    }

    for (int i = 0; i < size; i++) {                     // возвращаем строку
        for (int j = 0; j < size; j++) {
            encodedString.push_back(grille[i][j][0]);
        }
    }

    delete[] grille;
    return encodedString;
}

char decodeChar(string** grille, string** encoded, string code, int size) {
    char character = 'O';
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (grille[i][j] == code) {
                return encoded[i][j][0];
            }
        }
    }
    return character;
}

string decodeString(string stringToDecode) {
    string decodedString;
    string lattice[] = { "1*", "2.", "3*", "4@" };
    int lattSize = 4;

    int size = sqrt(stringToDecode.length());
    if (size % 2 != 0) {
        size++;
    }
    if (pow(2, size) < stringToDecode.length()) {
        size += 2;
    }
    //cout << size << endl;
    string** grille = createArray(size);

    string** encoded = new string * [size];
    for (int i = 0; i < size; i++) {
        encoded[i] = new string[size];
    }

    int counter = 0;                                              // перенос строки в массив
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            encoded[i][j] = stringToDecode[counter];
            cout << encoded[i][j] << " ";                        // запись строки в массив
            counter++;
        }
        cout << endl;
    }

    cout << size << endl;

    int codePos = 0;


    for (int i = 0; i < 4 * lattSize; i++) {                    
        decodedString.push_back(decodeChar(grille, encoded, lattice[codePos], size));
        codePos++;
        if (codePos == lattSize) {
            codePos = 0;
            for (int k = 0; k < lattSize; k++) {
                if (lattice[k][1] == '*') {
                    lattice[k][1] = '.';
                }
                else if (lattice[k][1] == '.') {
                    lattice[k][1] = '#';
                }
                else if (lattice[k][1] == '#') {
                    lattice[k][1] = '@';
                }
                else if (lattice[k][1] == '@') {
                    lattice[k][1] = '*';
                }
            }
        }
    }

    return decodedString;
}

int main()
{
    string stringToEncode = "Hello, world!!!!";

    string encodedString = encodeString(stringToEncode);
    string decodedString = decodeString(encodedString);

    cout << encodedString << endl;
    cout << decodedString << endl;
}

