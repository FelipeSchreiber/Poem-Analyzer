#include <iostream>
#include <string>
#include <dirent.h>

using namespace std;

int ls(string path){
	struct dirent *entry;
	DIR *dir = opendir(path.c_str());
	if (!dir){
		cout << "Failed to open directory" << endl;
		return 1;
	}
	cout << "Files: " << endl;
	unsigned i = 0;
	while(entry = readdir(dir))
		cout << (*entry).d_name <<
			((i++ % 5 == 0) ? "\n" : "\t\t");
	cout << endl;
	closedir(dir);
	return 0;
}

int
main(void){
	ls(".");
	return 0;
}
