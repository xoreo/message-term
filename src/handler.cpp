#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Handler {
public:
    Handler(bool auto_install) {
        if (auto_install) {
            if (this->auto_install() <= 0) {
                cout << "installed" << endl;
            } else {
            cout << "error installing" << endl;
            }
        }
        
    }
    int write(string filename, string text) {
        try {
            ofstream file;
            file.open(filename);
            file << text;
            file.close();
            return 0;
        } catch (int e) {
            cout << "error writing to file. error code: " << e << endl;
            return 1;
        }
    }
    int auto_install() {
        try {
            system("bash install.sh");
            return 0;
        } catch (int e) {
            cout << "installation failed. error code: " << e << endl;
        }
        
    }
    int send(string number, string message) {
        cout << "send being called" << endl;
        string command = "bash ~/bin/SendMessage.sh \"" + number + "\" \"" + message + "\"";
        system(command.c_str());
        cout << "sent '" << message << "' to '" << number << "'" << endl;
        return 0;
    }
    int recieve(string name, string message) {
        string chat = "NAME: " + name + "\nMESSAGE: " + message;
        write("~/Desktop/" + message + ".log", chat);
        return 0;
    }

};

int main(int argc, char *argv[]) {
    Handler *handler = new Handler(true);

    if (strcmp(argv[1], "--send") == 0) {
        handler->send(argv[2], argv[3]);
    } else if (strcmp(argv[1], "--recieve") == 0) {
        handler->recieve(argv[2], argv[3]);
    }
}