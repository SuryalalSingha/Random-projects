#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
int main() {
	string qn, comm;
	cout<<"  Cpp SubShell (v1.12)"<<endl
	    <<"Author: Suryalal Singha"<<endl
	    <<"\tPress Enter To Start"<<endl;
	getline(cin, qn);
	if (!qn.empty()) {
		cout<<"QUITING!\n";
		return 0;
	}
	while (1)  {
		system("pwd")
		cout<<"$ ";
		getline(cin, comm);
		if (comm == "exit") {
			cout<<"Press CTRL+C for exit\n";
		}
		//system(comm);
		if (!comm.ignore()) {
			system(comm);
		}
	}
	return 0;
}
