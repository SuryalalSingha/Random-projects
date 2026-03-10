#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
int main(int argc, char *argv[])
{
	if (3 > argc) {
		cout<<"No args. type for help:\n lock help"<<endl;
		return 1;
	}
	string comma = argv[1];
	string locker = " ~/locker/";
	string back = " /storage/emulated/0/station/";
	if (comma == "xml") {
		string buf="mv ";
		buf += back;
		buf += argv[2];
		buf += locker;
		buf += argv[2];
		system(buf.c_str());
	} else if (comma=="xcl") {
		string buf="cp ";
		buf += back;
		buf += argv[2];
		buf += locker;
		buf += argv[2];
		system(buf.c_str());
	} else if (comma=="xmb") {
		string buf="mv ";
		buf += locker;
		buf += argv[2];
		buf += back;
		buf += argv[2];
		system(buf.c_str());
	} else if (comma=="xcb") {
		string buf="cp ";
		buf += locker;
		buf += argv[2];
		buf += back;
		buf += argv[2];
		system(buf.c_str());
	} else if (comma=="help") {
		string hel = "Help For genr:\n\txml = move the file to the locker.\n\txcl = copy the file to the locker file.\n\txcb = copy the file back to the home storage with '.' carrecter for hiding.\n\txmb = move the file back to the home storage.\n\thelp = to print help doc.\n\t\nAuthor : Suryalal Singha\n Contact : surya.geek.email@gmail.com\n";
		cout << hel;
	} else {
		cout << "error occured. \n type 'genr help'"<<endl;
	}
	return 0;
}
//g++ test.cxx -o $PREFIX/bin/lock
//chmod +x $PREFIX/bin/lock