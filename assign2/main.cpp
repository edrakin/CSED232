#include<iostream>
#include<iomanip>
#include"reflect.h"
#include"zero.h"
#include"symmetry.h"
#include"convolution.h"
using namespace std;

int main()
{
	int len, line, row;
	cout << "Enter the Kernal length : ";
	cin >> len;

	int** kernal = new int* [len];
	cout << "Enter the Kernal" << endl;
	for (int i = 0; i < len; i++)
	{
		kernal[i] = new int[len];
		for (int k = 0; k < len; k++)
			cin >> kernal[i][k];//커널 입력
	}

	cout << "Enter the input line : ";//인풋값 행 개수
	cin >> line;
	cout << "Enter the input row : ";//인풋값 열 개수
	cin >> row;
	cout << "Enter the input" << endl;//인풋 입력
	int** input = new int* [line];
	for (int i = 0; i < line; i++)
	{
		input[i] = new int[row];
		for (int k = 0; k < row; k++)
			cin >> input[i][k];
	}

							//각 padding을 만들고 convolution을 수행할 객체 생성
	Convolution C;
	C.init(len, kernal);
	Zero Z;
	Z.init(len, kernal);
	Reflect R;
	R.init(len, kernal);
	Symmetry S;	
	S.init(len, kernal);
	C.put(line, row);
	Z.put(line, row);
	R.put(line, row);
	S.put(line, row);
	

	int m = 1;
	while (m)//while 내부에서 명령어 계속 수행
	{
		cout << "mode\n0. quit\n1. print\n2. change kernal\n3. change input\n>> ";
		cin >> m;
		switch (m)
		{									//1. padding과 각 padding의 convolution 보여주기.
		case 1:
			cout << "===================== " << len << " x " << len << " kernal =====================" << endl;
			for (int i = 0; i < len; i++)
			{
				for (int k = 0; k < len; k++)
					cout << setw(3) << kernal[i][k] << '.';
				cout << endl;
			}
			cout << "======================= matrix =======================" << endl;
			for (int i = 0; i < line; i++)
			{
				for (int k = 0; k < row; k++)
					cout << setw(3) << input[i][k] << '.';
				cout << endl;
			}
			C.convolution(input, line, row);
			cout << "===================== convolution ====================" << endl;
			C.print();
			cout << "=============================== Zero padding convolution ==============================" << endl;

			cout << "======================= padded matrix =======================" << endl;
			Z.zero(input);
			cout << "===================== result ====================" << endl;
			Z.print();
			cout << "=============================== Reflect padding convolution ==============================" << endl;
			cout << "======================= padded matrix =======================" << endl;
			R.reflect(input);
			cout << "===================== result ====================" << endl;
			R.print();
			cout << "=============================== Symmetric padding convolution ==============================" << endl;
			cout << "======================= padded matrix =======================" << endl;
			S.symmetry(input);
			cout << "===================== result ====================" << endl;
			S.print();
			C.delete_output();
			Z.delete_output();
			R.delete_output();
			S.delete_output();
			break;


												//커널 값 변경하기
		case 2:
			for (int i = 0; i < len; i++)
				delete [] (kernal[i]);
			delete [] (kernal);
			cout << "Enter the Kernal length : ";
			cin >> len;
			cout << "Enter the Kernal" << endl;
			kernal = new int* [len];
			for (int i = 0; i < len; i++)
			{
				kernal[i] = new int[len];
				for (int k = 0; k < len; k++)
					cin >> kernal[i][k];
			}
			C.change_ker(len, kernal);
			Z.change_ker(len, kernal);
			R.change_ker(len, kernal);
			S.change_ker(len, kernal);
			break;

													//인풋값 변경하기.
		case 3:
			for (int i = 0; i < line; i++)
				delete[](input[i]);
			delete[](input);
			cout << "Enter the input line : ";
			cin >> line;
			cout << "Enter the input row : ";
			cin >> row;
			cout << "Enter the input" << endl;
			input = new int* [line];
			for (int i = 0; i < line; i++)
			{
				input[i] = new int[row];
				for (int k = 0; k < row; k++)
					cin >> input[i][k];
			}
			C.put(line, row);
			Z.put(line, row);
			R.put(line, row);
			S.put(line, row);
			break;
		}
		

	}
}