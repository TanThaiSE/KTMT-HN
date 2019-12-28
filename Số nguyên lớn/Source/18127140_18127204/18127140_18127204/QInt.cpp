#include"QInt.h"
//chia cho 2
void Div2(string& X)
{
	string result = "";
	if (X[0] == '-')
	{
		X.erase(X.begin() + 0);
	}
	int n = X.length();
	int pos = 0;
	int temp = X[pos] - '0';
	if (temp < 2 && X.size() == 1)
	{
		X = result;
		return;
	}
	while (temp < 2)
	{
		pos = pos + 1;
		temp = temp * 10 + (X[pos] - '0');
	}
	while (pos < n)
	{
		pos = pos + 1;
		result += (temp / 2) + '0';
		temp = (temp % 2) * 10 + (X[pos] - '0');
	}
	X = result;
}
//cong 1
void Plus1(string & X)
{
	int carry = 1;
	for (int i = 127; i >= 0; i--)
	{
		int temp = (X[i] - '0') + carry;
		if (temp == 2)
		{
			X[i] = '0';
			carry = 1;
		}
		else
		{
			X[i] = temp + '0';
			carry = 0;
		}
	}
}

//giai quyet chia 2 so
string SolveDiv2Num(string X, string Y) {
	string answer;
	string soDu = "";
	unsigned int countX;
	unsigned int countY;
	string tmp;
	countX = X.length();
	countY = Y.length();
	tmp = X.substr(0, countY); // tim so de chia
	if (isSmaller(tmp, Y)) tmp = X.substr(0, countY + 1); // nho hon so chia.
	unsigned int index1 = tmp.length();
	while (index1 <= countX) {
		soDu += tmp;
		int thuongso = 0;
		for (int i = 0; i <= 9; i++) {
			string ind = Mul2Num(to_string(i), Y);
			if ((!isSmaller(ind, soDu)) && (ind != soDu)) {
				break;
			}
			thuongso = i;
		}
		soDu = Sub2Num(soDu, Mul2Num(to_string(thuongso), Y));
		if (soDu == "0")
			soDu = "";
		tmp = X.substr(index1, 1);
		answer += to_string(thuongso);

		index1++;
	}
	return answer;
}
//cong 2 so
string Plus2Num(string X, string Y)
{
	Standard(X);
	Standard(Y);
	string dauX;
	string dauY;
	dauX = X[0];
	dauY = Y[0];
	int mark = TakeMark(X, Y);
	string Value = "";
	if (dauX[0] == '-' && dauY[0] != '-')
	{
		X.erase(X.begin() + 0);
		Value = Sub2Num(X, Y);
		if (mark == -1)
			Value.insert(Value.begin(), '-');
		return Value;
	}
	else if (dauX[0] != '-' && dauY[0] == '-')
	{
		Y.erase(Y.begin() + 0);
		Value = Sub2Num(X, Y);
		if (mark == -1)
			Value.insert(Value.begin(), '-');
		return Value;
	}
	if (dauX[0] == '-' && dauY[0] == '-')
	{
		X.erase(X.begin() + 0);
		Y.erase(Y.begin() + 0);
	}
	if (X.size() > Y.size())
		swap(X, Y);
	int len1 = X.size();
	int len2 = Y.size();
	reverse(X.begin(), X.end());
	reverse(Y.begin(), Y.end());
	int carry = 0;
	for (int i = 0; i < len1; i++)
	{
		int sum = (X[i] - '0') + (Y[i] - '0') + carry;
		carry = sum / 10;
		Value += ((sum % 10) + '0');
	}

	for (int i = len1; i < len2; i++)
	{
		int sum = (Y[i] - '0') + carry;
		carry = sum / 10;
		Value += ((sum % 10) + '0');
	}
	if (carry > 0)
		Value += (carry + '0');
	reverse(Value.begin(), Value.end());

	if (mark == -1)
	{
		Value.insert(Value.begin(), '-');
		return Value;
	}
	else if (mark == 1)
	{
		return Value;
	}
}
//nhan 2 so
string Mul2Num(string X, string Y)
{
	string dauX;
	string dauY;
	dauX = X[0];
	dauY = Y[0];
	if (dauX[0] == '-')
	{
		X.erase(X.begin() + 0);
	}
	if (dauY[0] == '-')
	{
		Y.erase(Y.begin() + 0);
	}
	int len1 = X.size();
	int len2 = Y.size();
	if (len1 == 0 || len2 == 0)
		return "0";
	vector<int> result(len1 + len2, 0); // all ele=0;
	int index1 = 0;
	int index2 = 0;
	for (int i = len1 - 1; i >= 0; i--)
	{
		int carry = 0;
		int n1 = X[i] - '0';
		index2 = 0;
		for (int j = len2 - 1; j >= 0; j--)
		{
			int n2 = Y[j] - '0';
			int sum = n1 * n2 + result[index1 + index2] + carry;
			carry = sum / 10;
			result[index1 + index2] = sum % 10;
			index2++;
		}
		if (carry > 0)
			result[index1 + index2] += carry;
		index1++;
	}
	int i = result.size() - 1;
	while (i >= 0 && result[i] == 0)
	{
		i--;
	}
	if (i == -1)
		return "0";
	string Value = "";
	while (i >= 0)
	{
		Value += to_string(result[i--]);
	}

	if (dauX[0] == '-' && dauY[0] != '-')
	{
		Value.insert(Value.begin(), '-');
	}
	else if (dauX[0] != '-' && dauY[0] == '-')
	{
		Value.insert(Value.begin(), '-');
	}
	return Value;
}
//tru 2 so
string Sub2Num(string X, string Y)
{
	if (isSmaller(X, Y))
		swap(X, Y);
	int len1 = X.size();
	int len2 = Y.size();
	reverse(X.begin(), X.end());
	reverse(Y.begin(), Y.end());
	string Value = "";
	int carry = 0;
	for (int i = 0; i < len2; i++)
	{
		int sub = (X[i] - '0') - (Y[i] - '0') - carry;
		if (sub < 0)
		{
			sub += 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		Value += (sub + '0');
	}
	for (int i = len2; i < len1; i++)
	{
		int sub = (X[i] - '0') - carry;
		if (sub < 0)
		{
			sub += 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		Value += (sub + '0');
	}
	reverse(Value.begin(), Value.end());
	Standard(Value);
	return Value;
}
//chia 2 so
string Div2Num(string X, string Y) {
	string dauX;
	dauX = X[0];
	string dauY;
	dauY = Y[0];
	string answer;
	if (dauX == "-") {
		X.erase(X.begin() + 0);
		if (dauY != "-") {
			answer = "-" + SolveDiv2Num(X, Y);
		}
		else {
			Y.erase(Y.begin() + 0);
			answer = SolveDiv2Num(X, Y);
		}
	}
	else { // dau X +
		if (dauY == "-") {
			Y.erase(Y.begin() + 0);
			answer = "-" + SolveDiv2Num(X, Y);
		}
		else {
			answer = SolveDiv2Num(X, Y);
		}
	}
	return answer;
}

//lay dau
int TakeMark(string X, string Y)
{
	Standard(X);
	Standard(Y);
	string dauX;
	string dauY;
	dauX = X[0];
	dauY = Y[0];
	if (dauX[0] == '-' && dauY[0] == '-')
		return -1; //dấu -
	else if (dauX[0] != '-' && dauY[0] != '-')
		return 1; //dấu +

	else if (dauX[0] == '-' && dauY[0] != '-')
	{
		if (X.size() - 1 > Y.size())
			return -1; //dấu -
		else if (X.size() - 1 < Y.size())
			return 1; //dấu +
		else if (X.size() - 1 == Y.size())
		{
			X.erase(X.begin() + 0);
			int n = X.size();
			for (int i = 0; i < n; i++)
			{
				if (X[i] > Y[i])
				{
					return -1; //dấu -
				}
				else if (X[i] < Y[i])
				{
					return 1; //dấu +
				}
			}
			return 1; //dấu +
		}
	}
	else if (dauX[0] != '-' && dauY[0] == '-')
	{
		if (X.size() > Y.size() - 1)
			return 1;//dấu +
		else if (X.size() < Y.size() - 1)
			return -1;//dấu -
		else if (X.size() == Y.size() - 1)
		{
			Y.erase(Y.begin() + 0);
			int n = X.size();
			for (int i = 0; i < n; i++)
			{
				if (X[i] > Y[i])
				{
					return 1; //dấu +
				}
				else if (X[i] < Y[i])
				{
					return -1;//dấu -
				}
			}
			return 1; //dấu +
		}
	}
}
//chuan hoa chuoi
void Standard(string & chuoi)
{
	int dem = 0;
	if (chuoi[0] == '-')
	{
		chuoi.erase(chuoi.begin() + 0);
		dem = 1;
	}
	reverse(chuoi.begin(), chuoi.end());
	for (int i = chuoi.size() - 1; i > 0; i--)
	{
		if (chuoi[i] != '0')
			break;
		else
			chuoi.pop_back();
	}
	if (dem == 1)
		chuoi += '-';
	reverse(chuoi.begin(), chuoi.end());
}
//ham so sanh 2 so
bool isSmaller(string str1, string str2)
{
	int n1 = str1.length(), n2 = str2.length();

	if (n1 < n2)
		return true;
	if (n2 < n1)
		return false;
	for (int i = 0; i < n1; i++)
		if (str1[i] < str2[i])
			return true;
		else if (str1[i] > str2[i])
			return false;
	return false;
}
//ham full bit cho he 2
void FullBitInBin(string & num)
{
	string fullbit = "";
	int n = num.size();
	for (int i = 0; i < 128 - n; i++)
	{
		fullbit += '0';
	}
	int j = 0;
	for (int i = 128 - n; i < 128; i++)
	{
		fullbit += num[j++];
	}
	num = fullbit;
}
//ham full bit cho he 16
void FullBitInHex(string & num)
{
	string fullbit = "";
	int n = num.size();
	for (int i = 0; i < 32 - n; i++)
	{
		fullbit += '0';
	}
	int j = 0;
	for (int i = 32 - n; i < 32; i++)
	{
		fullbit += num[j++];
	}
	num = fullbit;
}
//cac truong hop cua hex
string ConBinToHex(string name)
{
	if (name == "0000")
		return "0";

	else if (name == "0001")
		return "1";

	else if (name == "0010")
		return "2";

	else if (name == "0011")
		return "3";

	else if (name == "0100")
		return "4";

	else if (name == "0101")
		return "5";

	else if (name == "0110")
		return "6";

	else if (name == "0111")
		return "7";

	else if (name == "1000")
		return "8";

	else if (name == "1001")
		return "9";

	else if (name == "1010")
		return "A";

	else if (name == "1011")
		return "B";

	else if (name == "1100")
		return "C";

	else if (name == "1101")
		return "D";

	else if (name == "1110")
		return "E";

	else if (name == "1111")
		return "F";

}
//cac truong hop cua binary
string ConHexToBin(char name)
{
	if (name == '0')
		return "0000";

	else if (name == '1')
		return "0001";

	else if (name == '2')
		return "0010";

	else if (name == '3')
		return "0011";

	else if (name == '4')
		return "0100";

	else if (name == '5')
		return "0101";

	else if (name == '6')
		return "0110";

	else if (name == '7')
		return "0111";

	else if (name == '8')
		return "1000";

	else if (name == '9')
		return "1001";

	else if (name == 'A')
		return "1010";

	else if (name == 'B')
		return "1011";

	else if (name == 'C')
		return "1100";

	else if (name == 'D')
		return "1101";

	else if (name == 'E')
		return "1110";

	else if (name == 'F')
		return "1111";
}
// doc mot dong
Data ReadOneLine(string line_info)
{
	Data x;
	vector<string> tokens;
	string seperator = " ";

	int startpos = 0;
	size_t foundpos = line_info.find(seperator, startpos);

	while (foundpos != string::npos)
	{
		string token = line_info.substr(startpos, foundpos - startpos);
		tokens.push_back(token);
		startpos = foundpos + 1;
		foundpos = line_info.find(seperator, startpos);
	}
	string token = line_info.substr(startpos, line_info.length() - startpos);
	tokens.push_back(token);
	tokens.push_back("");
	x.index1 = tokens[0];
	x.index2 = tokens[1];
	x.index3 = tokens[2];
	x.index4 = tokens[3];
	return x;
}
// doc file
void ReadFile(string path, vector<string> & readed)
{
	ifstream fin;
	fin.open(path);
	if (!fin.is_open())
	{
		return;
	}
	else
	{
		while (!fin.eof())
		{
			string line;
			getline(fin, line, '\n');
			if (line == "")
				break;
			Data x = ReadOneLine(line);
			string Input = ConvertResult(x.index1, x.index2, x.index3, x.index4);
			readed.push_back(Input);
		}
	}
	fin.close();

}
//ghi file
void WriteFile(string path, vector<string>written)
{
	ofstream fout;
	fout.open(path);
	if (!fout.is_open())
	{

		return;
	}
	else
	{
		int n = written.size();
		for (int i = 0; i < n - 1; i++)
			fout << written[i] << endl;
		fout << written[n - 1];

	}

	fout.close();
}

QInt::QInt()
{
	for (int i = 0; i < 128; i++)
		a[i] = '0';
}
//Phat hien so va chuyen doi qua 2
QInt::QInt(string num, string mode)
{
	QInt x;
	if (mode == "10")
	{
		x = ConvertDectoBin(num);
		for (int i = 0; i < 128; i++)
			a[i] = x.a[i];
	}
	else if (mode == "16")
	{
		x = ConvertHextoBin(num);
		for (int i = 0; i < 128; i++)
			a[i] = x.a[i];
	}
	else if (mode == "2")
	{
		FullBitInBin(num);
		for (int i = 0; i < 128; i++)
			a[i] = num[i];
	}
}
//ham huy
QInt::~QInt()
{
}

//ham lay chi so
char QInt::get_element(int i)
{
	return a[i];
}
///////////////////////////////////////////////////////////////////

//chuyen tu he 10 sang he 2 //xong
QInt QInt::ConvertDectoBin(string num)
{
	QInt q;
	char a[128];
	int i = 127;
	string dau;
	dau = num[0];
	int len = num.length() - 1;
	while (num != "")
	{
		int bit = (num[len] - 48) % 2;
		a[i] = bit + '0';
		Div2(num);
		len = num.length() - 1;
		i = i - 1;
	}
	if (i > 0)
	{
		for (int n = 0; n <= i; n++)
			a[n] = '0';
	}
	string result = "";
	if (dau[0] == '-')
	{
		for (int j = 0; j < 128; j++)
		{
			if (a[j] == '0')
				a[j] = '1';
			else if (a[j] == '1')
				a[j] = '0';
		}
		for (int j = 0; j < 128; j++)
			result = result + a[j];
		Plus1(result);
	}
	else if (dau[0] != '-')
	{
		for (int j = 0; j < 128; j++)
			result = result + a[j];
	}
	for (int i = 0; i < 128; i++)
		q.a[i] = result[i];
	return q;
}

//chuyen tu he 2 sang he 10 //xong
string QInt::ConvertBintoDec(string num)
{
	FullBitInBin(num);
	int len = num.size() - 1;
	string Total = "0";
	for (int i = 0; i <= len; i++)
	{
		string tinh = "1";

		if (num[i] == '1' && len == 127 && i == 0)
		{
			for (int j = 0; j < 127; j++)
			{
				tinh = Mul2Num(tinh, "2");
			}
			tinh.insert(tinh.begin(), '-');
			Total = Plus2Num(Total, tinh);
		}
		else if (num[i] == '0' && len == 127 && i == 0)
		{
			Total = Plus2Num(Total, "0");
		}

		if (num[i] == '1' && i != 0)
		{
			for (int j = 0; j < len - i; j++)
			{
				tinh = Mul2Num(tinh, "2");
			}
			Total = Plus2Num(Total, tinh);
		}
	}
	return Total;
}

//chuyen tu he 2 sang he 16 //xong
string QInt::ConvertBintoHex(string num)
{
	string result = "";
	string c = "";
	FullBitInBin(num);
	int len = num.size() - 1;
	for (int i = len; i > 0; i = i - 4)
	{
		string temp = "";
		temp = temp + num[i - 3] + num[i - 2] + num[i - 1] + num[i];
		c += ConBinToHex(temp);
	}
	for (int i = c.size() - 1; i >= 0; i--)
		result += c[i];
	FullBitInHex(result);
	return result;
}

//chuyen tu he 16 sang he 2 //xong
QInt QInt::ConvertHextoBin(string num)
{
	string result = "";
	int n = num.size();
	for (int i = 0; i < n; i++)
	{
		result += ConHexToBin(num[i]);

	}
	FullBitInBin(result);
	QInt x;
	for (int i = 0; i < 128; i++)
		x.a[i] = result[i];
	return x;
}

//chuyen tu he 16 sang he 10 //xong
string QInt::ConvertHextoDec(string num)
{
	QInt value1 = ConvertHextoBin(num);
	string value2 = "";
	for (int i = 0; i < 128; i++)
		value2 += value1.a[i];
	string value3 = ConvertBintoDec(value2);
	return value3;
}

//chuyen tu he 10 sang he 16 //xong
string QInt::ConvertDectoHex(string num)
{
	QInt value1 = ConvertDectoBin(num);
	string value2 = "";
	for (int i = 0; i < 128; i++)
		value2 += value1.a[i];
	string value3 = ConvertBintoHex(value2);
	return value3;
}

////////////////////////////////////////////////////////////

//operator +
QInt operator+(const QInt & num1, const QInt & num2)
{
	QInt ex, q;
	string Number1 = "";
	string Number2 = "";
	string Number3 = "";
	string Number4 = "";
	string Sum = "";
	for (int i = 0; i < 128; i++)
		Number1 += num1.a[i];
	for (int i = 0; i < 128; i++)
		Number2 += num2.a[i];
	Number3 = ex.ConvertBintoDec(Number1);
	Number4 = ex.ConvertBintoDec(Number2);
	Sum = Plus2Num(Number3, Number4);
	q = ex.ConvertDectoBin(Sum);
	return q;
}
//operator -
QInt operator-(const QInt & num1, const QInt & num2)
{
	QInt ex, q;
	string Number1 = "";
	string Number2 = "";
	string Number3 = "";
	string Number4 = "";
	string Sub = "";
	string dauNum4 = "";
	for (int i = 0; i < 128; i++)
		Number1 += num1.a[i];
	for (int i = 0; i < 128; i++)
		Number2 += num2.a[i];
	Number3 = ex.ConvertBintoDec(Number1);
	Number4 = ex.ConvertBintoDec(Number2);
	dauNum4 = Number4[0];
	if (dauNum4 == "-")
		Number4.erase(Number4.begin() + 0);
	else if (dauNum4 != "-")
		Number4.insert(Number4.begin(), '-');
	Sub = Plus2Num(Number3, Number4);
	q = ex.ConvertDectoBin(Sub);
	return q;
}
//operator *
QInt operator*(const QInt & num1, const QInt & num2)
{
	QInt ex, q;
	string Number1 = "";
	string Number2 = "";
	string Number3 = "";
	string Number4 = "";
	string Mul = "";
	for (int i = 0; i < 128; i++)
		Number1 += num1.a[i];
	for (int i = 0; i < 128; i++)
		Number2 += num2.a[i];
	Number3 = ex.ConvertBintoDec(Number1);
	Number4 = ex.ConvertBintoDec(Number2);
	Mul = Mul2Num(Number3, Number4);
	q = ex.ConvertDectoBin(Mul);
	return q;

}
//operator /
QInt operator/(const QInt & num1, const QInt & num2)
{
	QInt ex, q;
	string Number1 = "";
	string Number2 = "";
	string Number3 = "";
	string Number4 = "";
	string Div = "";
	for (int i = 0; i < 128; i++)
		Number1 += num1.a[i];
	for (int i = 0; i < 128; i++)
		Number2 += num2.a[i];
	Number3 = ex.ConvertBintoDec(Number1);
	Number4 = ex.ConvertBintoDec(Number2);
	Div = Div2Num(Number3, Number4);
	q = ex.ConvertDectoBin(Div);
	return q;

}

////////////////////////////////////////////////////////////

//operator &
QInt operator&(const QInt & num1, const QInt & num2)
{
	QInt q;
	string Number1 = "";
	string Number2 = "";
	string result = "";
	for (int i = 0; i < 128; i++)
		Number1 += num1.a[i];
	for (int i = 0; i < 128; i++)
		Number2 += num2.a[i];
	for (int i = 0; i < 128; i++)
	{
		if (Number1[i] == '1' && Number2[i] == '1')
			result += '1';
		else
			result += '0';
	}
	for (int i = 0; i < 128; i++)
	{
		q.a[i] = result[i];
	}
	return q;
}
//operator |
QInt operator|(const QInt & num1, const QInt & num2)
{
	QInt q;
	string Number1 = "";
	string Number2 = "";
	string result = "";
	for (int i = 0; i < 128; i++)
		Number1 += num1.a[i];
	for (int i = 0; i < 128; i++)
		Number2 += num2.a[i];
	for (int i = 0; i < 128; i++)
	{
		if (Number1[i] == '0' && Number2[i] == '0')
			result += '0';
		else
			result += '1';
	}
	for (int i = 0; i < 128; i++)
	{
		q.a[i] = result[i];
	}
	return q;
}
//operator ^
QInt operator^(const QInt & num1, const QInt & num2)
{
	QInt q;
	string Number1 = "";
	string Number2 = "";
	string result = "";
	for (int i = 0; i < 128; i++)
		Number1 += num1.a[i];
	for (int i = 0; i < 128; i++)
		Number2 += num2.a[i];
	for (int i = 0; i < 128; i++)
	{
		if ((Number1[i] == '0' && Number2[i] == '0') || (Number1[i] == '1' && Number2[i] == '1'))
			result += '0';
		else if ((Number1[i] == '0' && Number2[i] == '1') || (Number1[i] == '1' && Number2[i] == '0'))
			result += '1';
	}
	for (int i = 0; i < 128; i++)
	{
		q.a[i] = result[i];
	}
	return q;
}
//operator ~
QInt operator~(const QInt & num1)
{
	QInt q;
	string Number1 = "";
	string result = "";
	for (int i = 0; i < 128; i++)
		Number1 += num1.a[i];
	for (int i = 0; i < 128; i++)
	{
		if (Number1[i] == '0')
			result += '1';
		else if (Number1[i] == '1')
			result += '0';
	}
	for (int i = 0; i < 128; i++)
	{
		q.a[i] = result[i];
	}
	return q;
}

/////////////////////////////////////////////////////////////////

//operator <<
QInt operator<<(const QInt & num1, const string & pos)
{
	QInt q;
	QInt a;
	string result = "";
	string Number1 = "";
	for (int i = 0; i < 128; i++)
		Number1 += num1.a[i];
	reverse(Number1.begin(), Number1.end());
	for (int i = 0; i < stoi(pos); i++)
	{
		Number1.pop_back();
	}
	reverse(Number1.begin(), Number1.end());

	for (int i = 0; i < stoi(pos); i++)
	{
		Number1 += "0";
	}
	result = Number1;
	for (int i = 0; i < 128; i++)
	{
		q.a[i] = result[i];
	}
	return q;
}
//operator >>
QInt operator>>(const QInt & num1, const string & pos)
{
	QInt q;
	string result = "";
	string Number1 = "";
	string dau = "";
	for (int i = 0; i < 128; i++)
		Number1 += num1.a[i];
	dau = Number1[0];
	for (int i = 0; i < stoi(pos); i++)
	{
		Number1.pop_back();
	}
	reverse(Number1.begin(), Number1.end());
	for (int i = 0; i < stoi(pos); i++)
	{
		if (dau == "0")
		{
			Number1 += "0";
		}
		else if (dau == "1")
		{
			Number1 += "1";
		}
	}
	reverse(Number1.begin(), Number1.end());
	result = Number1;
	for (int i = 0; i < 128; i++)
	{
		q.a[i] = result[i];
	}
	return q;
}

/////////////////////////////////////////////////////////

//rol
QInt QInt::RotateLeft(const QInt & num1)
{
	QInt q;
	string result = "";
	string Number1 = "";
	string pos = "";
	for (int i = 0; i < 128; i++)
		Number1 += num1.a[i];
	pos = Number1[0];
	Number1.erase(Number1.begin() + 0);
	Number1.push_back(pos[0]);
	result = Number1;
	for (int i = 0; i < 128; i++)
	{
		q.a[i] = result[i];
	}
	return q;
}
//ror
QInt QInt::RotateRight(const QInt & num1)
{
	QInt q;
	string result = "";
	string Number1 = "";
	string pos = "";
	for (int i = 0; i < 128; i++)
		Number1 += num1.a[i];
	int n = Number1.size();
	pos = Number1[n - 1];
	Number1.pop_back();
	Number1.insert(Number1.begin(), pos[0]);
	result = Number1;
	for (int i = 0; i < 128; i++)
	{
		q.a[i] = result[i];
	}
	return q;
}

////////////////////////////////////////////////////

//chuyen doi ra ket qua
string ConvertResult(string num1, string num2, string num3, string num4)
{
	QInt b;
	string x = "";
	string y = "";
	if (num1 == "10" && num2 == "2")
	{
		QInt Value = b.ConvertDectoBin(num3);
		for (int i = 0; i < 128; i++)
			x += Value.get_element(i);
		Standard(x);
		return x;
	}
	else if (num1 == "2" && num2 == "10")
	{
		QInt b;
		x = b.ConvertBintoDec(num3);
		Standard(x);
		return x;
	}
	else if (num1 == "2" && num2 == "16")
	{
		x = b.ConvertBintoHex(num3);
		Standard(x);
		return x;
	}
	else if (num1 == "16" && num2 == "2")
	{
		QInt Value = b.ConvertHextoBin(num3);
		for (int i = 0; i < 128; i++)
			x += Value.get_element(i);
		Standard(x);
		return x;
	}
	else if (num1 == "16" && num2 == "10")
	{
		x = b.ConvertHextoDec(num3);
		Standard(x);
		return x;
	}
	else if (num1 == "10" && num2 == "16")
	{
		x = b.ConvertDectoHex(num3);
		Standard(x);
		return x;
	}
	else if ((num1 == "10" && num2 == "10") || (num1 == "2" && num2 == "2") || (num1 == "16" && num2 == "16"))
	{
		Standard(num3);
		return num3;
	}
	else if (num3 == "+") //
	{
		QInt so1(num2, num1);
		QInt so2(num4, num1);
		QInt Value = so1 + so2;
		if (num1 == "2")
		{
			for (int i = 0; i < 128; i++)
				x += Value.get_element(i);
			Standard(x);
			return x;
		}
		else if (num1 == "10")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoDec(y);
			Standard(x);
			return x;
		}
		else if (num1 == "16")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoHex(y);
			Standard(x);
			return x;
		}
	}
	else if (num3 == "-") //
	{
		QInt so1(num2, num1);
		QInt so2(num4, num1);
		QInt Value = so1 - so2;
		if (num1 == "2")
		{
			for (int i = 0; i < 128; i++)
				x += Value.get_element(i);
			Standard(x);
			return x;
		}
		else if (num1 == "10")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoDec(y);
			Standard(x);
			return x;
		}
		else if (num1 == "16")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoHex(y);
			Standard(x);
			return x;
		}
	}
	else if (num3 == "*") //
	{
		QInt so1(num2, num1);
		QInt so2(num4, num1);
		QInt Value = so1 * so2;
		if (num1 == "2")
		{
			for (int i = 0; i < 128; i++)
				x += Value.get_element(i);
			Standard(x);
			return x;
		}
		else if (num1 == "10")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoDec(y);
			Standard(x);
			return x;
		}
		else if (num1 == "16")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoHex(y);
			Standard(x);
			return x;
		}
	}
	else if (num3 == "/") //
	{
		QInt so1(num2, num1);
		QInt so2(num4, num1);
		QInt Value = so1 / so2;
		if (num1 == "2")
		{
			for (int i = 0; i < 128; i++)
				x += Value.get_element(i);
			Standard(x);
			return x;
		}
		else if (num1 == "10")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoDec(y);
			Standard(x);
			return x;
		}
		else if (num1 == "16")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoHex(y);
			Standard(x);
			return x;
		}
	}
	else if (num3 == "&") //
	{
		QInt so1(num2, num1);
		QInt so2(num4, num1);
		QInt Value = so1 & so2;
		if (num1 == "2")
		{
			for (int i = 0; i < 128; i++)
				x += Value.get_element(i);
			Standard(x);
			return x;
		}
		else if (num1 == "10")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoDec(y);
			Standard(x);
			return x;
		}
		else if (num1 == "16")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoHex(y);
			Standard(x);
			return x;
		}
	}
	else if (num3 == "|") //
	{
		QInt so1(num2, num1);
		QInt so2(num4, num1);
		QInt Value = so1 | so2;
		if (num1 == "2")
		{
			for (int i = 0; i < 128; i++)
				x += Value.get_element(i);
			Standard(x);
			return x;
		}
		else if (num1 == "10")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoDec(y);
			Standard(x);
			return x;
		}
		else if (num1 == "16")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoHex(y);
			Standard(x);
			return x;
		}
	}
	else if (num3 == "^") //
	{
		QInt so1(num2, num1);
		QInt so2(num4, num1);
		QInt Value = so1 ^ so2;
		if (num1 == "2")
		{
			for (int i = 0; i < 128; i++)
				x += Value.get_element(i);
			Standard(x);
			return x;
		}
		else if (num1 == "10")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoDec(y);
			Standard(x);
			return x;
		}
		else if (num1 == "16")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoHex(y);
			Standard(x);
			return x;
		}
	}
	else if (num2 == "~") //
	{
		QInt so1(num3, num1);
		QInt Value = ~so1;
		if (num1 == "2")
		{
			for (int i = 0; i < 128; i++)
				x += Value.get_element(i);
			Standard(x);
			return x;
		}
		else if (num1 == "10")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoDec(y);
			Standard(x);
			return x;
		}
		else if (num1 == "16")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoHex(y);
			Standard(x);
			return x;
		}
	}
	else if (num3 == "<<") //
	{
		QInt so1(num2, num1);
		QInt Value = so1 << num4;
		if (num1 == "2")
		{
			for (int i = 0; i < 128; i++)
				x += Value.get_element(i);
			Standard(x);
			return x;
		}
		else if (num1 == "10")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoDec(y);
			Standard(x);
			return x;
		}
		else if (num1 == "16")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoHex(y);
			Standard(x);
			return x;
		}
	}
	else if (num3 == ">>") //
	{
		QInt so1(num2, num1);
		QInt Value = so1 >> num4;
		if (num1 == "2")
		{
			for (int i = 0; i < 128; i++)
				x += Value.get_element(i);
			Standard(x);
			return x;
		}
		else if (num1 == "10")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoDec(y);
			Standard(x);
			return x;
		}
		else if (num1 == "16")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoHex(y);
			Standard(x);
			return x;
		}
	}
	else if (num2 == "rol") //
	{
		QInt so1(num3, num1);
		QInt Value = b.RotateLeft(so1);
		if (num1 == "2")
		{
			for (int i = 0; i < 128; i++)
				x += Value.get_element(i);
			Standard(x);
			return x;
		}
		else if (num1 == "10")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoDec(y);
			Standard(x);
			return x;
		}
		else if (num1 == "16")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoHex(y);
			Standard(x);
			return x;
		}
	}
	else if (num2 == "ror") //
	{
		QInt so1(num3, num1);
		QInt Value = b.RotateRight(so1);
		if (num1 == "2")
		{
			for (int i = 0; i < 128; i++)
				x += Value.get_element(i);
			Standard(x);
			return x;
		}
		else if (num1 == "10")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoDec(y);
			Standard(x);
			return x;
		}
		else if (num1 == "16")
		{
			for (int i = 0; i < 128; i++)
				y += Value.get_element(i);
			x = b.ConvertBintoHex(y);
			Standard(x);
			return x;
		}
	}
}
