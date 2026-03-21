#include <iostream>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

void list_all(const string& dir) {
    path p(dir);
    if (!exists(p) || !is_directory(p)) {
        cerr << "Invalid directory: " << dir << endl;
        return;
    }
    for (auto& entry : directory_iterator(p)) {
        cout << entry.path().filename().string() << endl;
    }
}
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
int main(int argc, char *argv[])
{
  if (argc <= 1) {
        cout<<"\033[31mError:\033[0m: lock: no arguments given \n\tUse 'lock help' for help"<<endl;
        return 1;
  }
	string locker = " ~/locker/";
  string comma = argv[1];
	string back = " /storage/emulated/0/station/";
	if (comma == "-xml" || comma=="xml") {
        if (argc < 3) {
                cout << "\033[31mError:\033[0m Missing filename for xml command" << endl;
                 return 1;
        }
    string x = argv[2];
    string file = argv[2];
    if (x == "-hid" || x == "hid") {
        if (argc < 4) {
                cout << "\033[31mError:\033[0m Missing filename for xml command" << endl;
                 return 1;
        }
        file = argv[3];
        file = "."+file;
    }
		string buf="mv ";
		buf += back;
		buf += file;
		buf += locker;
		buf += file;
		int result = system(buf.c_str());
    if (result != 0) {
        cout << "\033[31mError:\033[0m:: Command failed with code " << result << endl;
    }
	} else if (comma=="-xcl" || comma=="xcl") {
        if (argc < 3) {
                cout << "\033[31mError:\033[0m Missing filename for xcl command" << endl;
                 return 1;
        }
    string file = argv[2];
    string x = argv[2];
    if (x == "-hid" || x == "hid") {
        if (argc < 4) {
                cout << "\033[31mError:\033[0m Missing filename for xcl command" << endl;
                 return 1;
        }
        file = argv[3];
        file = "."+file;
    }
		string buf="cp ";
		buf += back;
		buf += file;
		buf += locker;
		buf += file;
		int result = system(buf.c_str());
    if (result != 0) {
        cout << "\033[31mError:\033[0m:: Command failed with code " << result << endl;
    }
	} else if (comma=="-xmb" || comma=="xmb") {
        if (argc < 3) {
                cout << "\033[31mError:\033[0m Missing filename for xmb command" << endl;
                 return 1;
        }
    string file = argv[2];
    string x = argv[2];
    if (x == "-hid" || x == "hid") {
        if (argc < 4) {
                cout << "\033[31mError:\033[0m Missing filename for xmb command" << endl;
                 return 1;
        }
        file = argv[3];
        file = "."+file;
    }
		string buf="mv ";
		buf += locker;
		buf += file;
		buf += back;
		buf += file;
		int result = system(buf.c_str());
    if (result != 0) {
        cout << "\033[31mError:\033[0m:: Command failed with code " << result << endl;
    }
	} else if (comma=="-xcb" || comma=="xcb" ) {
        if (argc < 3) {
                cout << "\033[31mError:\033[0m Missing filename for xcb command" << endl;
                 return 1;
        }
    string file = argv[2];
    string x = argv[2];
    if (x == "-hid" || x == "hid") {
        if (argc < 4) {
                cout << "\033[31mError:\033[0m Missing filename for xcb command" << endl;
                 return 1;
        }
        file = argv[3];
        file = "."+file;
    }
		string buf="cp ";
		buf += locker;
		buf += file;
		buf += back;
		buf += file;
		int result = system(buf.c_str());
    if (result != 0) {
        cout << "\033[31mError:\033[0m:: Command failed with code " << result << endl;
    }
	} else if (comma=="help" || comma=="-help" || comma=="-?") {
		string hel = "Help doc For Lock:\n\t-xml = move the file to the locker.\n\t-xcl = copy the file to the locker file.\n\t-xcb = copy the file back to the home storage.\n\t-xmb = move the file back to the home storage.\n\t-help = to print help doc.\n\n\tAuthor : Suryalal Singha\n\tContact : surya.geek.email@gmail.com\n";
		cout << hel;
	} else {
    cout << "\033[31mError:\033[0m Lock: Not a Recognised Argument '" << comma << "'\n\tUse 'lock help'" << endl;
	}
	return 0;
}
//run this command to make this a command in termux:
//g++ lock.cxx -o $PREFIX/bin/lock && chmod +x $PREFIX/bin/lock

/* this program is made for keeping some files hidden and safe from other users in a system (like file managers).
and this file will only work in termux (latest version from f-droid) and android 8+. I have made this project just for me.
	but it could demonstrate how command are made. */
