#pragma once
#include<iostream>
#include<stdio.h>
#include<string>
#include<sstream>
#include<iomanip>
#include<vector>
#include<fstream>
#include<algorithm>
#include<filesystem>
using namespace std;
void Div2(string& X);
void Plus1(string& X);
void Mul2(string X);
string SolveDiv2Num(string X, string Y);
string Plus2Num(string X, string Y);
string Mul2Num(string X, string Y);
string Sub2Num(string X, string Y);
string Div2Num(string X, string Y);

int TakeMark(string X, string Y);
void Standard(string& chuoi);
bool isSmaller(string str1, string str2);
void FullBitInBin(string& num);
void FullBitInHex(string& num);
string ConBinToHex(string name);
string ConHexToBin(char name);
struct Data
{
	string index1;
	string index2;
	string index3;
	string index4;
};
Data ReadOneLine(string line_info);
string ConvertResult(string num1, string num2, string num3, string num4);
void ReadFile(string path, vector<string>& readed);
void WriteFile(string path, vector<string>written);

class QInt
{
private:
	char a[128];
public:
	QInt ConvertDectoBin(string num); //chuyen he 10 sang he 2 
	string ConvertBintoDec(string num); //chuyen he 2 sang he 10 

	string ConvertBintoHex(string num); //chuyen he 2 sang he 16 
	QInt ConvertHextoBin(string num); //chuyen he 16 sang he 2 

	string ConvertHextoDec(string num);	//chuyen he 16 sang he 10 
	string ConvertDectoHex(string num); //chuyen he 10 sang he 16 


	friend QInt operator+(const QInt& num1, const QInt& num2);// operator +
	friend QInt operator-(const QInt& num1, const QInt& num2);// operator -
	friend QInt operator*(const QInt& num1, const QInt& num2);// operator *
	friend QInt operator/(const QInt& num1, const QInt& num2);// operator / 

	friend QInt operator&(const QInt& num1, const QInt& num2);// operator & 
	friend QInt operator|(const QInt& num1, const QInt& num2);// operator |
	friend QInt operator^(const QInt& num1, const QInt& num2);// operator ^ 
	friend QInt operator~(const QInt& num1);// operator ~ 

	friend QInt operator<<(const QInt& num1, const string& pos); //dich trai
	friend QInt operator>>(const QInt& num1, const string& pos); //dich phai 

	QInt RotateLeft(const QInt& num1); //Xoay trai

	QInt RotateRight(const QInt& num1);	//Xoay phai

	QInt();
	QInt(string num, string mode);//Phat hien so va chuyen doi qua 2
	~QInt();
	char get_element(int i);// lay ki tu tai chi so i
};

