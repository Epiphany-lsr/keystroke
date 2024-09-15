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
	
	// 模拟按下键  
	SendInput(1, &input, sizeof(INPUT));  
	
	// 模拟释放键  
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
		stringstream ss; // 使用 stringstream 来转换字符串
		ifs >> hexString;

		if (hexString.find("0x") == 0)
		{
			ss << hex << hexString; // 将字符串视为十六进制  
			ss >> hexValue; // 读取转换后的值  
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
	
	cout<<"输入要循环输入的次数:"<<endl;
	int n;
	cin>>n;
	
	system("cls");
	SetConsoleCursorInfo(hOutput, &cci);
	// 等待6秒钟，以便用户可以切换到目标窗口  
	for(int i=5;i>=0;i--)
	{
		SetConsoleCursorPosition(hOutput, coord);
		cout<<"请切换至目标输入窗口"<<endl;
		cout<<i;
		Sleep(1000);
	}
	
	system("cls");
	cout<<"正在输入……";
	
	
	
	
	for(int i=0;i<n;i++)
	{		
		for (int j = 0; j < key.size(); j++)
		{
			simulateKeyPress(key[j]);  
			Sleep(100); 
		}
		
	}
	
	system("cls");
	cout<<"输入完成"<<endl<<endl;
	
	system("pause");
	return 0;  
}
