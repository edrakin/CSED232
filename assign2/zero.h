#pragma once
#include<iostream>
#include<string>
#include<iomanip>
#include"convolution.h"
using namespace std;

class Zero : public Convolution {
private:
public:
	Zero(int klength = 0, int** ker = 0) :Convolution(klength, ker)	{}

	void zero(int** input)//인풋값 받아서 padding을 만든 다음에 convolution까지 해주는 함수.
	{
		int pad = (this->kernal_length - 1) / 2;
		int a = line + 2 * pad + 1, b = row + 2 * pad + 1;
		int** input_zero = new int* [line + 2 * pad + 1];//output 행렬 크기는 따로 내보내는 함수 만들자.

		for (int i = 0; i < line + 2 * pad + 1; i++)
			input_zero[i] = new int[row + 2 * pad + 1];

		for (int i = 0; i < pad; i++)
			for (int k = 0; k < row + 2 * pad; k++)
				input_zero[i][k] = 0;
		for (int i = pad; i < pad + line; i++)
		{
			for (int k = 0; k < pad; k++)
				input_zero[i][k] = 0;
			for (int k = pad; k < pad + row; k++)
				input_zero[i][k] = input[i - pad][k - pad];
			for (int k = pad + row; k < pad + row + pad; k++)
				input_zero[i][k] = 0;
		}
		for (int i = pad + line; i < pad + line + pad; i++)
			for (int k = 0; k < row + 2 * pad; k++)
				input_zero[i][k] = 0;

		for (int i = 0; i < pad + line + pad; i++)
		{
			for (int k = 0; k < pad + row + pad; k++)
				cout  << input_zero[i][k] << ".";
			cout << endl;
		}

		convolution(input_zero, a - 1, b - 1);//아웃풋에 값 저장.
		
		
		for (int i = 0; i < pad + pad + line + 1; i++)
			delete[](input_zero[i]);
		delete[](input_zero);

	}
	

};