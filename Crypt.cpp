
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int moreArgumentsRequired = 5;
const int missingInput = 1;
const int wrongGivenFunction = 2;
const int outRangedKey = 3;
const int keyIsNotANumber = 4;

int getbits(int x, int first, int amount)
{
	return (x >> first) & ~(~0 << amount);
}

int crypt(ifstream &fin, ofstream &fout, int key)
{
	char ch;
	while (fin >> noskipws >> ch)
	{
		int outByte = 0;
		ch = ch ^ key;
		outByte += (getbits(ch, 0, 1) << 2);
		outByte += (getbits(ch, 1, 1) * 2 << 2);
		outByte += (getbits(ch, 2, 1) * 4 << 2);
		outByte += (getbits(ch, 3, 1) * 8 << 3);
		outByte += (getbits(ch, 4, 1) * 16 << 3);
		outByte += (getbits(ch, 5, 1) * 32 >> 5);
		outByte += (getbits(ch, 6, 1) * 64 >> 5);
		outByte += (getbits(ch, 7, 1) * 128 >> 2);
		fout << ((char)outByte);
	}
	return 0;
}

int decrypt(ifstream &fin, ofstream &fout, int key)
{
	char ch;
	while (fin >> noskipws >> ch)
	{
		char ch;
		while (fin >> noskipws >> ch)
		{
			int outByte = 0;
			outByte += getbits(ch, 0, 1) << 5;
			outByte += getbits(ch, 1, 1) * 2 << 5;
			outByte += getbits(ch, 2, 1) * 4 >> 2;
			outByte += getbits(ch, 3, 1) * 8 >> 2;
			outByte += getbits(ch, 4, 1) * 16 >> 2;
			outByte += getbits(ch, 5, 1) * 32 << 2;
			outByte += getbits(ch, 6, 1) * 64 >> 3;
			outByte += getbits(ch, 7, 1) * 128 >> 3;
			outByte = outByte ^ key;
			fout << ((char)outByte);
		}
	}
	return 0;
}

bool isUnsignedIntegerNumber(string in)
{
	char ch;
	while (!in.empty())
	{
		ch = in.front();
		in.pop_back();
		if ('0' > ch or ch > '9')
		{
			return false;
		}
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (argc < 5) 
	{
		cout << "4 Arguments required\n";
		return moreArgumentsRequired;
	}

	string function(argv[1]);
	string inputFile(argv[2]);
	string outputFile(argv[3]);
	string strKey(argv[4]);

	if (!isUnsignedIntegerNumber(strKey))
	{
		cout << "Key must be a number\n";
		return keyIsNotANumber;
	}
	int key = stoi(strKey);

	ifstream fin(inputFile);
	ofstream fout(outputFile);

	if (!fin.is_open()) 
	{
		cout << "Failed to open Input for reding\n";
		return missingInput;
	}

	if (key < 0 or key > 255)
	{
		cout << "Invalid key, must be between 0 - 255\n";
		return outRangedKey;
	}

	if (function == "crypt")
	{
		crypt(fin, fout, key);
	}
	else if (function == "decrypt")
	{
		decrypt(fin, fout, key);
	}
	else
	{
		cout << "Appling functions are 'crypt', 'decrypt'\n";
		return wrongGivenFunction;
	}
	return 0;
}
