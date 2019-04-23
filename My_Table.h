#ifndef MY_TABLE_H_INCLUDED
#define MY_TABLE_H_INCLUDED
#include <iostream>
#include <fstream>
#include <ostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <cmath>
#include <conio.h>
#include <windows.h>
using namespace std;
enum err{INNCORECT_DATA=1,EMPTY_TABLE=2,ERR_FILE=3,EMPTY_FILE=4};
typedef int TElem;
template<typename T>
class table{
private:
	int row,col;
	T **body;
	int errcode;

	template<typename T1>friend int Keys(table<T1>&);
	template<typename T1>friend int redact_printf(table<T1>&,int,int,int,int);
    template<typename T1>friend int Redact(table<T1>&);
	template<typename T1>friend int Quick_Sort(table<T1>&,int*,int,int);
	template<typename T1>friend int getfile(std::ifstream&,table<T1>&);
public:
	table();
	int Save(std::ostream&);
	int Set(int,int,T);
	int Get(int,int,T&);
	int create(int,int);
	int get_row();
	int get_col();
	void del();
	~table();
};

#endif // MY_TABLE_H_INCLUDED
