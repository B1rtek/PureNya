#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string convertToNya(char n) {
    string nya = "n";
    for (int i = -1; i < n; i++) nya += 'y';
    nya += "a~";
    return nya;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Usage: nyac <some file>\n"
                "Options: \n"
                "-o <filename>: define output filename\n";
        return 0;
    }

    string inputFilename = argv[1];
    string outputFilename = inputFilename;
    bool customName = false;
    if (argc >= 3) {
        string arg2 = argv[2];
        if (arg2 == "-o") {
            customName = true;
        }
    }

    if (argc >= 4) {
        string arg3 = argv[3];
        if (customName) {
            outputFilename = arg3;
        }
    }

    fstream inputFile;
    inputFile.open(inputFilename.c_str(), ios::in);

    if (!inputFile.good()) {
        cout << "Couldn't access " << inputFilename << '\n';
        return 0;
    }

    string line, nya;
    while (getline(inputFile, line)) {
        for (char &i: line) {
            nya += convertToNya(i);
            nya += ' ';
        }
        nya += convertToNya(char(13));
        nya += ' ';
        nya += convertToNya(char(10));
        nya += '\n';
    }
    inputFile.close();

    if (!customName) {
        if (outputFilename.find('.') != -1) {
            while (outputFilename.back() != '.') {
                outputFilename.pop_back();
            }
            outputFilename.pop_back();
        }
        outputFilename += ".nya";
    } else {
        if (outputFilename.find(".nya") != outputFilename.size() - 4) {
            outputFilename += ".nya";
        }
    }

    fstream nyaOutput;
    nyaOutput.open(outputFilename.c_str(), ios::out);
    if (!nyaOutput.good()) {
        cout << "Couldn't create " << outputFilename << '\n';
        return 0;
    }

    nyaOutput << nya;
    nyaOutput.close();
    cout << "Successfully converted " << inputFilename << " to " << outputFilename << "\nNyaaa~~\n";
    return 0;
}
