#include <iostream>  
#include <windows.h>  
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

vector<WORD> key;

void simulateKeyPress(WORD key) {  
	INPUT input = {0};  
	input.type = INPUT_KEYBOARD;  
	input.ki.wVk = key;  
	
	// ģ�ⰴ�¼�  
	SendInput(1, &input, sizeof(INPUT));  
	
	// ģ���ͷż�  
	input.ki.dwFlags = KEYEVENTF_KEYUP;  
	SendInput(1, &input, sizeof(INPUT));  
}  

void readFile()
{
	ifstream ifs;
	ifs.open("keystroke.txt", ios::in);
	while(!(ifs.eof()))
	{
		string hexString="//";
		WORD hexValue;
		stringstream ss; // ʹ�� stringstream ��ת���ַ���
		ifs >> hexString;

		if (hexString.find("0x") == 0)
		{
			ss << hex << hexString; // ���ַ�����Ϊʮ������  
			ss >> hexValue; // ��ȡת�����ֵ  
		}
		else if(hexString.find("//") == string::npos)
			hexValue=WORD(hexString[0]);
		else
			break;
		
		if(hexValue!=0)
			key.push_back(hexValue);
	}		
	ifs.close();
}

int main() {  
	HANDLE hOutput;
	COORD coord = { 0,0 };
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	
	readFile();
	
	cout<<"����Ҫѭ������Ĵ���:"<<endl;
	int n;
	cin>>n;
	
	system("cls");
	SetConsoleCursorInfo(hOutput, &cci);
	// �ȴ�6���ӣ��Ա��û������л���Ŀ�괰��  
	for(int i=5;i>=0;i--)
	{
		SetConsoleCursorPosition(hOutput, coord);
		cout<<"���л���Ŀ�����봰��"<<endl;
		cout<<i;
		Sleep(1000);
	}
	
	system("cls");
	cout<<"�������롭��";
	
	
	
	
	for(int i=0;i<n;i++)
	{		
		for (int j = 0; j < key.size(); j++)
		{
			simulateKeyPress(key[j]);  
			Sleep(100); 
		}
		
	}
	
	system("cls");
	cout<<"�������"<<endl<<endl;
	
	system("pause");
	return 0;  
}
