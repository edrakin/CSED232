#pragma once
#include<iostream>
#include<string>
#include<iomanip>
#include"convolution.h"
using namespace std;

class Reflect : public Convolution{
private:
public:
	Reflect(int klength = 0, int** ker = 0) :Convolution(klength, ker) {}

	void reflect(int** input)		//인풋값 받아서 padding을 만든 다음에 convolution까지 해주는 함수.
	{
		int pad = (this->kernal_length - 1) / 2;
		int a = line + 2 * pad + 1, b = row + 2 * pad + 1;

		int** input_reflect = new int* [a];//output 행렬 크기는 따로 내보내는 함수 만들자.

		for (int i = 0; i < a; i++)
			input_reflect[i] = new int[b];

		for (int i = pad; i < pad + line; i++)
			for (int k = pad; k < pad + row; k++)
				input_reflect[i][k] = input[i - pad][k - pad];//가운데 일단 복사

		for (int i = 0; i < pad; i++)
			for (int k = pad; k < pad + row; k++)
				input_reflect[i][k] = input[pad - i][k - pad];//위쪽 중앙

		for (int i = pad + line; i < pad + line + pad; i++)
			for (int k = pad; k < pad + row; k++)
				input_reflect[i][k] = input[line - (i - pad - line) - 2][k - pad];//아래쪽 중앙

		for (int i = pad; i < pad + line; i++)
		{
			for (int k = 0; k < pad; k++)
				input_reflect[i][k] = input[i - pad][pad - k];//왼쪽 중앙
			for (int k = pad + row; k < pad + row + pad; k++)
				input_reflect[i][k] = input[i - pad][row - (k - pad - row) - 2];//오른쪽 중앙
		}

		for (int i = 0; i < pad; i++)
		{
			for (int k = 0; k < pad; k++)
				input_reflect[i][k] = input[pad - i][pad - k];//위쪽 왼쪽
			for (int k = pad + row; k < pad + row + pad; k++)
				input_reflect[i][k] = input[pad - i][row - (k - pad - row) - 2];//위쪽 오른쪽
		}

		for (int i = pad + line; i < pad + line + pad; i++)
		{
			for (int k = 0; k < pad; k++)
				input_reflect[i][k] = input[line - (i - pad - line) - 2][pad - k];//아래쪽 왼쪽
			for (int k = pad + row; k < pad + row + pad; k++)
				input_reflect[i][k] = input[line - (i - pad - line) - 2][row - (k - pad - row) - 2];//아래쪽 오른쪽
		}

		for (int i = 0; i < a - 1; i++)
		{
			for (int k = 0; k < b - 1; k++)
				cout << setw(3) << input_reflect[i][k];
			cout << endl;
		}
		convolution(input_reflect, a - 1, b - 1);//아웃풋에 값 저장.

		for (int i = 0; i < a; i++)
			delete[](input_reflect[i]);
		delete[](input_reflect);
	}
};

