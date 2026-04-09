#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
int main(int argc, char *argv[])
{
  if (argc <= 1) {
        cout<<"\033[31mError:\033[0m lock: No Arguments Provided \n\ttry 'lock help' for -help"<<endl;
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
    string sfile = file;
    if (x == "-hid" || x == "hid") {
        if (argc < 4) {
                cout << "\033[31mError:\033[0m Missing filename for xml command" << endl;
                 return 1;
        }
        file = argv[3];
        sfile = "."+file;
    }
		string buf="mv ";
		buf += back;
		buf += file;
		buf += locker;
		buf += sfile;
		int result = system(buf.c_str());
    if (result != 0) {
        cout << "\033[31mError:\033[0m Command failed with code " << result << endl;
    }
	} else if (comma=="-xcl" || comma=="xcl") {
        if (argc < 3) {
                cout << "\033[31mError:\033[0m Missing filename for xcl command" << endl;
                 return 1;
        }
    string file = argv[2];
    string sfile = file;
    string x = argv[2];
    if (x == "-hid" || x == "hid") {
        if (argc < 4) {
                cout << "\033[31mError:\033[0m Missing filename for xcl command" << endl;
                 return 1;
        }
        file = argv[3];
        sfile = "."+file;
    }
		string buf="cp ";
		buf += back;
		buf += file;
		buf += locker;
		buf += sfile;
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
        if (file.find(".") == 1)
        file = "."+file;
    }
		string buf="mv ";
		buf += locker;
		buf += file;
		buf += back;
		buf += file;
		int result = system(buf.c_str());
    if (result != 0) {
        cout << "\033[31mError:\033[0m Command failed with code " << result << endl;
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
        if (file.find(".") == 1)
        file = "."+file;
    }
		string buf="cp ";
		buf += locker;
		buf += file;
		buf += back;
		buf += file;
		int result = system(buf.c_str());
    if (result != 0) {
        cout << "\033[31mError:\033[0m Command failed with code " << result << endl;
    }
	} else if (comma=="help" || comma=="-help" || comma=="-?") {
		string hel = "Lock: Usage:\n\t-xml [command] [file]\n\t\t*  move the file to the locker.\n\t-xcl [command] [file]\n\t\t* copy the file to the locker file.\n\t-xcb [command] [file]\n\t\t*  copy the file back to the home storage.\n\t-xmb [command] [file]\n\t\t* move the file back to the home storage.\n\t-hid [file]\n\t\t* to hid files placing '.' in file name.\n\t\t* used after aformentioned commands.\n\t-help \n\t\t* to print help doc.\n\n\tAuthor : Suryalal Singha\n\tContact : surya.geek.email@gmail.com\n";
		cout << hel;
	} else {
    cout << "\033[31mError:\033[0m Lock: Not a Recognised Argument '" << comma << ".'\n\ttry 'lock -help' for help" << endl;
	}
	return 0;
}
//run this command to make this a command in termux:
//g++ lock.cxx -o $PREFIX/bin/lock && chmod +x $PREFIX/bin/lock

/* this program is made for keeping some files hidden and safe from other users on a system (like file managers).
and this file will only work in termux (latest version from f-droid) and android 8+. I have made this project just for me.
	but it could demonstrate how command are made. */

