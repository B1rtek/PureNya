#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void nyaError(const string &line, int lineNum, unsigned int charNum, const string &message, bool &impure) {
    if(impure) {
        cout<<"Warning: Your nya~ is impure. ";
    }
    cout << "Line " << +lineNum << ", " << charNum + 1 << ": \n";
    unsigned int charsBefore = min(unsigned(10), charNum);
    unsigned int charsAfter = min(line.size() - 1 - charNum, unsigned(10));
    cout << line.substr(charNum - charsBefore, charsBefore + 1 + charsAfter) << '\n';
    string arrowLine;
    for (int i = 0; i < charsBefore; i++) arrowLine += ' ';
    arrowLine += '^';
    for (int i = 0; i < charsAfter; i++) arrowLine += '~';
    cout << arrowLine << '\n' << message << '\n' << "Compilation terminated.";
    if(!impure) {
        exit(0);
    }
}


string evaluateNya(int lineNum, unsigned int startChar, string nya, const string &line, bool &impure) {
    int n = 0, y = 0, a = 0, tilde = 0;
    for (int i = 0; i < nya.size(); i++) {
        if (nya[i] == 'n' || nya[i] == 'N') {
            if (y == 0 && a == 0 && tilde == 0) {
                n++;
            } else {
                nyaError(line, lineNum, startChar + i, "\'n\' found in an invalid place inside nya~", impure);
            }
        } else if (nya[i] == 'y' || nya[i] == 'Y') {
            if (((n > 0 || impure) && a == 0 && tilde == 0)) {
                y++;
            } else {
                nyaError(line, lineNum, startChar + i, "\'y\' found in an invalid place inside nya~", impure);
            }
        } else if (nya[i] == 'a' || nya[i] == 'A') {
            if ((n > 0 && y > 0 && tilde == 0) || (tilde == 0 && impure)) {
                a++;
            } else {
                nyaError(line, lineNum, startChar + i, "\'a\' found in an invalid place inside nya~", impure);
            }
        } else if (nya[i] == '~') {
            if ((n > 0 && y > 0 && a > 0) || impure) {
                tilde++;
            } else {
                nyaError(line, lineNum, startChar + i, "\'~\' found in an invalid place inside nya~", impure);
            }
        } else {
            string message = "Invalid character found inside nya~: ";
            message += nya[i];
            nyaError(line, lineNum, startChar + i, message, impure);
        }
    }
    int asciiCharNum = y - n;
    while (asciiCharNum < 0) {
        asciiCharNum += 256;
    }
    asciiCharNum %= 256;
    string lineOfCpp;
    for (int i = 0; i < a; i++) {
        lineOfCpp += "o+=char(" + to_string(asciiCharNum) + ");";
    }
    return lineOfCpp;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Usage: nyac <yourfile.nya>\n"
                "Options: \n"
                "-o <filename>: define output filename\n"
                "-impure: allows for code that has invalid \"nya\"s, like \"na~\"";
        return 0;
    }

    bool impure = false;
    bool customFilename = false, here = false;
    string coolFilename;
    if (argc >= 3) {
        string arg2 = argv[2];
        if (arg2 == "-o") {
            here = true;
        } else if (arg2 == "-impure") {
            impure = true;
        }
    }
    if (argc >= 4) {
        string arg3 = argv[3];
        if (arg3 == "-impure") {
            impure = true;
        } else if (here) {
            coolFilename = argv[3];
            customFilename = true;
            here = false;
        } else if (arg3 == "-o") {
            here = true;
        }
    }
    if (argc >= 5) {
        string arg4 = argv[4];
        if (arg4 == "-impure") {
            impure = true;
        } else if (here) {
            coolFilename = argv[4];
            customFilename = true;
        }
    }

    fstream nyaInput;
    nyaInput.open(argv[1], ios::in);
    if (!nyaInput.good()) {
        cout << "Couldn't access " << argv[1];
        return 0;
    }

    string line;
    string code = "#include <iostream>\nusing namespace std;int main(){string o;";
    int lineCounter = 1;
    while (getline(nyaInput, line)) {
        line += ' ';
        for (unsigned int i = 0; i < line.size(); i++) {
            if (line[i] == ' ') {
                continue;
            }

            unsigned int endOfNya = line.find(' ', i);
            if (endOfNya == -1) {
                endOfNya = line.size();
            }

            string nya = line.substr(i, endOfNya - i);
            code += evaluateNya(lineCounter, i, nya, line, impure);
            i += nya.size();
        }
        lineCounter++;
    }
    nyaInput.close();
    code += "cout<<o;return 0;}";

    string filename = argv[1];
    while (filename.back() != '.') {
        filename.pop_back();
    }
    filename.pop_back();
    string outputFilename;
    if (customFilename) {
        outputFilename = coolFilename;
    } else {
        outputFilename = filename;
    }

    filename += ".nyac";
    fstream cppOutput;
    cppOutput.open(filename.c_str(), ios::out);
    if (!cppOutput.good()) {
        cout << "Couldn't create " << filename << ".nyac";
        return 0;
    }
    cppOutput << code;
    cppOutput.close();

    string gppCommand = "g++ -x c++ " + filename + " -o " + outputFilename;
    system(gppCommand.c_str());
    remove(filename.c_str());

    cout << argv[1] << " was successfully compiled into " << outputFilename << '\n' << "Nyaaa~~";
    return 0;
}
