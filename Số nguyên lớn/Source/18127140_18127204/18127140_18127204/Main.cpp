#include"QInt.h"

int main(int argc, char* argv[])
{
	vector<string>x;
	if (argc != 3)
	{
		cout << "Can 3 doi so";
		return -1;
	}
	ReadFile(argv[1], x);
	WriteFile(argv[2], x);

	return 0;
}
