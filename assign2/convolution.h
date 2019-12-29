#pragma once
#include<iostream>
#include<string>


class Convolution
{
protected:
	int kernal_length;	//Ŀ�� �� ���� ����
	int** kernal;		//Ŀ�� ��
	int** output;		//convolution �� ��
	int line, row;		//��ǲ�� ��, �� ��
	int line_o, row_o;	//�ƿ�ǲ�� ��, �� ��
public:
	Convolution(int klength = 0, int** ker = 0);
	void put(int _line, int _row);
	void convolution(int** input, int line, int row);
	void init(int klength = 0, int** ker = 0);
	int length() { return kernal_length; }
	void delete_output();
	void change_ker(int len, int** ker)			//Ŀ�� �� �����ϴ� �Լ�
	{
		for (int i = 0; i < kernal_length; i++)
			delete[](kernal[i]);
		delete[](kernal);

		this->kernal_length = len;
		this->kernal = new int* [this->kernal_length];
		for (int i = 0; i < this->kernal_length; i++)
		{
			this->kernal[i] = new int[this->kernal_length];
			for (int k = 0; k < this->kernal_length; k++)
				this->kernal[i][k] = ker[i][k];
		}
	}
	void print();
};