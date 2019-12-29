#pragma once
#include<iostream>
#include<string>
#include<iomanip>
#include"convolution.h"
using namespace std;

class Symmetry : public Convolution {
private:
public:
	Symmetry(int klength = 0, int** ker = 0) :Convolution(klength, ker) {}

	void symmetry(int** input)//��ǲ�� �޾Ƽ� padding�� ���� ������ convolution���� ���ִ� �Լ�.
	{
		int pad = (this->kernal_length - 1) / 2;
		int a = line + 2 * pad + 1, b = row + 2 * pad + 1;

		int** input_symmetry = new int* [a];//output ��� ũ��� ���� �������� �Լ� ������.

		for (int i = 0; i < a; i++)
			input_symmetry[i] = new int[b];

		for (int i = pad; i < pad + line; i++)
			for (int k = pad; k < pad + row; k++)
				input_symmetry[i][k] = input[i - pad][k - pad];//��� �ϴ� ����

		for (int i = 0; i < pad; i++)
			for (int k = pad; k < pad + row; k++)
				input_symmetry[i][k] = input[pad - i - 1][k - pad];//���� �߾�

		for (int i = pad + line; i < pad + line + pad; i++)
			for (int k = pad; k < pad + row; k++)
				input_symmetry[i][k] = input[line - (i - pad - line) - 1][k - pad];//�Ʒ��� �߾�

		for (int i = pad; i < pad + line; i++)
		{
			for (int k = 0; k < pad; k++)
				input_symmetry[i][k] = input[i - pad][pad - k - 1];//������ �߾�
			for (int k = pad + row; k < pad + row + pad; k++)
				input_symmetry[i][k] = input[i - pad][row - (k - pad - row) - 1];//���� �߾�
		}

		for (int i = 0; i < pad; i++)
		{
			for (int k = 0; k < pad; k++)
				input_symmetry[i][k] = input[pad - i - 1][pad - k - 1];//���� ����
			for (int k = pad + row; k < pad + row + pad; k++)
				input_symmetry[i][k] = input[pad - i - 1][row - (k - pad - row) - 1];//���� ������
		}

		for (int i = pad + line; i < pad + line + pad; i++)
		{
			for (int k = 0; k < pad; k++)
				input_symmetry[i][k] = input[line - (i - pad - line) - 1][pad - k - 1];//�Ʒ��� ����
			for (int k = pad + row; k < pad + row + pad; k++)
				input_symmetry[i][k] = input[line - (i - pad - line) - 1][row - (k - pad - row) - 1];//�Ʒ��� ������
		}

		for (int i = 0; i < a - 1; i++)
		{
			for (int k = 0; k < b - 1; k++)
				cout << setw(3) << input_symmetry[i][k];
			cout << endl;
		}
		convolution(input_symmetry, a - 1, b - 1);//�ƿ�ǲ�� �� ����.
		
		for (int i = 0; i < a; i++)
			delete [](input_symmetry[i]);
		delete [](input_symmetry);
	}
};