#include<iostream>
#include"convolution.h"
#include<cstdlib>
#include<iomanip>
using namespace std;

Convolution::Convolution(int klength, int **ker)//생성자는 init함수로 대체
{	init(klength, ker);	}

void Convolution::init(int klength, int **ker)//객체 내 변수 모두 초기화, 커널 값 입력.
{
	this->kernal_length = klength;
	this->kernal = new int* [this->kernal_length];
	for (int i = 0; i < this->kernal_length; i++)
	{
		this->kernal[i] = new int[this->kernal_length];
		for (int k = 0; k < this->kernal_length; k++)
			this->kernal[i][k] = ker[i][k];
	}
	this->line = 0;
	this->row = 0;
	this->line_o = 0;
	this->row_o = 0;
	this->output = NULL;
}

void Convolution::convolution(int** input_, int line, int row)
{													//받아온 인풋값과 객체 내부 커널의 convolution 수행
	line_o = line - kernal_length + 1;
	row_o = row - kernal_length + 1;

	output = new int* [line - kernal_length + 1];


	for (int i = 0; i < line - kernal_length + 1; i++)
	{
		output[i] = new int[row - kernal_length + 1];
		for (int k = 0; k < row - kernal_length + 1; k++)
		{
			output[i][k] = 0;
			for (int x = 0; x < kernal_length; x++)
				for (int y = 0; y < kernal_length; y++)
					output[i][k] += input_[i + x][k + y] * kernal[x][y];
		}
	}
}
 
void Convolution::put(int _line, int _row)//객체 내부 행, 열 값 넣기
{
	line = _line;
	row = _row;
}

void Convolution::delete_output()			//convolution에서 만든 output 할당 해제
{
	for (int i = 0; i < line_o; i++)
		delete[](output[i]);
	delete[](output);
}

void Convolution::print()					//output 프린트
{
	for (int i = 0; i < line_o; i++)
	{
		for (int k = 0; k < row_o; k++)
			cout << setw(3) << output[i][k] << '.';
		cout << endl;
	}
}
