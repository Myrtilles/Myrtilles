#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void distribution(string path1, string path2, string main_path) 
{
	ofstream f1, f2;
	ifstream mainf;
	string temp, cur;
	int itemp, icur;
	f1.open(path1);
	f2.open(path2);
	mainf.open(main_path);
	if (!f1.is_open() || !f2.is_open()) 
	{
		cout << "ERROR!" << endl;
	}
	else {
		bool firstfile = true;
		mainf >> cur;
		while (!mainf.eof()) 
		{
			if (firstfile) {
				f1 << cur << endl;
				temp = cur;
				mainf >> cur;
				if (mainf.eof()) {
					f1 << "/" << endl;
					return;
				}
				itemp = stoi(temp);
				icur = stoi(cur);
				while (itemp <= icur) 
				{
					if (mainf.eof()) 
					{
						f1 << "/" << endl;
						return;
					}
					f1 << cur << endl;
					temp = cur;
					mainf >> cur;
					itemp = stoi(temp);
					icur = stoi(cur);
				}
				f1 << "/" << endl;
				firstfile = false;
			}
			else {
				f2 << cur << endl;
				temp = cur;
				mainf >> cur;
				if (mainf.eof()) 
				{
					f2 << "/" << endl;
					return;
				}
				itemp = stoi(temp);
				icur = stoi(cur);
				while (itemp <= icur) 
				{
					if (mainf.eof()) 
					{
						f2 << "/" << "\n";
						return;
					}
					f2 << cur << "\n";
					temp = cur;
					mainf >> cur;
					itemp = stoi(temp);
					icur = stoi(cur);
				}
				f2 << "/" << "\n";
				firstfile = true;
			}
		}
	}
	f1.close();
	f2.close();
	mainf.close();
}

void merge(string path1, string path2, string main_path) 
{
	distribution(path1, path2, main_path);
	ifstream f1, f2;
	ofstream mainf;
	string temp1, temp2;
	int itemp1, itemp2;
	f1.open(path1);
	f2.open(path2);
	mainf.open(main_path);
	if (!f1.is_open() || !f2.is_open()) { cout << "ERROR!" << endl; }
	else {
		while (!(f1.eof())) 
		{
			f1 >> temp1;
			f2 >> temp2;
			if (temp2 == "") return;
			while (temp1 != "/" || temp2 != "/") 
			{
				if (temp1 == "/") 
				{
					mainf << temp2 << endl;
					f2 >> temp2;
				}
				else if (temp2 == "/") 
				{
					mainf << temp1 << endl;
					f1 >> temp1;
				}
				else {
					itemp1 = stoi(temp1);
					itemp2 = stoi(temp2);
					if (itemp1 <= itemp2) 
					{
						mainf << temp1 << endl;
						f1 >> temp1;
					}
					else {
						mainf << temp2 << endl;
						f2 >> temp2;
					}
				}
			}
		}
	}
	f1.close();
	f2.close();
	mainf.close();
	merge(path1, path2, main_path);
}

int main() {
	int size, current;
	string result = "result.txt", buff = "buffer.txt", datafile = "data.txt", temp;
	ofstream data;
	ifstream res;
	cout << "size of an array: ";
	cin >> size;
	cout << "unsorted data: " << endl;
	
	data.open(datafile);
	for (int i = 0; i < size; i++) 
	{
		current = rand() % 100;
		cout << current << " ";
		data << current << endl;
	}
	data.close();
	cout << endl << endl;
	merge(result, buff, datafile);
	cout << "sorted data: " << endl;
	res.open(result);
	for (int i = 0; i < size; i++) 
	{
		res >> temp;
		cout << temp << " ";
	}
	res.close();
	cout << endl;
	return 0;
}
