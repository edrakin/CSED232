#pragma once
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<math.h>
using namespace std;

class Layer				//코드 특징1. init함수에서 내부 데이터에 필요한 공간을 모두 할당하고 시작함.
						//코드 특징2. 특징 1을 위해서 train과 validation, test의 인풋 아웃풋을 따로 설정함.
{
private:				//많은 변수들이 있는데, pdf에서 나오지 않은 변수만 설명할게요
	float** train_input;
	float** train_output;
	float** test_output;
	float** val_input;
	float** val_output;
	float** weigh;
	float* bias;
	float** gradient_a;			//L의 a에 대한 gradient 값.
	float** transpose_input;	//train input의 전치행렬
	float** transpose_w;		//weigh의 전치행렬
	float* gradient_b;			//L의 bias에 대한 gradient 값.
	float** gradient_w;			//L의 weigh에 대한 gradient 값.
	float** gradient_back;		//L의 h에 대한 gradient 값.
	int in_dimention;
	int out_dimention;
	int train_num, val_num, test_num;
public:
	Layer(int _in_dimention = 0, int _out_dimention = 0, int train_data_num = 0, int val_data_num = 0, int test_data_num = 0)
		{	init(_in_dimention, _out_dimention, train_data_num, val_data_num, test_data_num);	}

	//init함수로 생성자를 대신한다.

	void init(int _in_dimention = 0, int _out_dimention = 0, int train_data_num = 0, int val_data_num = 0, int test_data_num = 0)
	{
		train_num = train_data_num;
		val_num = val_data_num;				//함수가 꽤 긴데 전부 할당하는 내용이라 볼 필요 없다.
		test_num = test_data_num;
		in_dimention = _in_dimention;
		out_dimention = _out_dimention;
		train_input = new float* [train_data_num];
		train_output = new float* [train_data_num];
		val_input = new float* [val_data_num];
		val_output = new float* [val_data_num];
		test_output = new float* [test_data_num];
		weigh = new float* [_in_dimention];
		bias = new float[_out_dimention];

		gradient_a = new float* [train_data_num];
		transpose_input = new float* [in_dimention];
		transpose_w = new float* [out_dimention];
		gradient_b = new float[out_dimention];
		gradient_w = new float* [in_dimention];
		gradient_back = new float* [train_data_num];

		for (int i = 0; i < train_data_num; i++)
		{
			train_input[i] = new float[in_dimention];
			train_output[i] = new float[out_dimention];
			gradient_a[i] = new float[out_dimention];
			gradient_back[i] = new float[in_dimention];
		}

		for (int i = 0; i < val_data_num; i++)
		{
			val_input[i] = new float[in_dimention];
			val_output[i] = new float[out_dimention];
		}
		for (int i = 0; i < test_data_num; i++)
			test_output[i] = new float[out_dimention];

		srand(time(NULL));
		for (int i = 0; i < in_dimention; i++)
		{
			weigh[i] = new float[out_dimention];
			for (int k = 0; k < out_dimention; k++)
				weigh[i][k] = (float)(rand() % 32761 + 1) / (float)32763;	//weigh는 0과 1 사이 난수
			gradient_w[i] = new float[out_dimention];
			transpose_input[i] = new float[train_data_num];
		}

		for (int i = 0; i < out_dimention; i++)
		{
			bias[i] = 0;													//bias는 초기값 0
			transpose_w[i] = new float[in_dimention];
			gradient_b[i] = 1;												//L에 대한 bias 그라디언트는 1로 고정.
		}
	}

	//데이터 개수 때문에 forward함수도 3개로 나누었음.(val과 test에선 주석 생략)


	float** train_forward(float** input)									//weigh와 bias로 class를 계산하는 함수
	{
		for (int i = 0; i < train_num; i++)
			for (int k = 0; k < in_dimention; k++)
				train_input[i][k] = input[i][k];							//받아온 인풋을 Layer class에 저장.

		matmul(train_output, train_input, weigh, train_num, in_dimention, out_dimention);		//output 계산
		for (int i = 0; i < train_num; i++)
			for (int k = 0; k < out_dimention; k++)
			{
				train_output[i][k] += bias[k];													//output 계산
				train_output[i][k] = (float)1 / (exp(-train_output[i][k]) + (float)1);			//output 계산
			}
		return train_output;
	}

	float** train_backward(float** y_gradient, float learning_rate, int data_num)
	{
		for (int i = 0; i < data_num; i++)
			for (int k = 0; k < out_dimention; k++)
				gradient_a[i][k] = y_gradient[i][k] * train_output[i][k] * ((float)1 - train_output[i][k]);

																								//gradient_a값 계산

		transpose(train_input, transpose_input, train_num, in_dimention);						//transpose_input계산
		transpose(weigh, transpose_w, in_dimention, out_dimention);								//transpose_w계산
		matmul(gradient_w, transpose_input, gradient_a, in_dimention, data_num, out_dimention); //gradient_w 계산
		for (int i = 0; i < out_dimention; i++)
		{
			gradient_b[i] = 0;
			for (int k = 0; k < data_num; k++)
				gradient_b[i] += gradient_a[k][i];												//gradient_b 계산
		}

		matmul(gradient_back, gradient_a, transpose_w, data_num, out_dimention, in_dimention);	//gradient_back 계산

		for (int i = 0; i < in_dimention; i++)
			for (int k = 0; k < out_dimention; k++)
				weigh[i][k] -= learning_rate * gradient_w[i][k];								//weigh 업데이트

		for (int i = 0; i < out_dimention; i++)
			bias[i] -= learning_rate * gradient_b[i];											//bias 업데이트

		return gradient_back;
	}

	float** val_forward(float** input)
	{
		for (int i = 0; i < val_num; i++)
			for (int k = 0; k < in_dimention; k++)
				val_input[i][k] = input[i][k];

		matmul(val_output, val_input, weigh, val_num, in_dimention, out_dimention);
		for (int i = 0; i < val_num; i++)
			for (int k = 0; k < out_dimention; k++)
			{
				val_output[i][k] += bias[k];
				val_output[i][k] = (float)1 / (exp(-val_output[i][k]) + (float)1);
			}
		return val_output;
	}

	float** test_forward(float** input)
	{
		matmul(test_output, input, weigh, test_num, in_dimention, out_dimention);
		for (int i = 0; i < test_num; i++)
			for (int k = 0; k < out_dimention; k++)
			{
				test_output[i][k] += bias[k];
				test_output[i][k] = (float)1 / (exp(-test_output[i][k]) + (float)1);
			}
		return test_output;
	}

	void matmul(float** output, float** a, float** b, int line1, int row1, int row2)
	{																	//행렬곱. row1과 line2는 같은 값이라 생략
		for (int i = 0; i < line1; i++)
			for (int k = 0; k < row2; k++)
			{
				output[i][k] = 0;
				for (int h = 0; h < row1; h++)
					output[i][k] = output[i][k] + a[i][h] * b[h][k];
			}
	}

	void transpose(float** input, float** output, int line, int row)	//전치행렬 만들기
	{
		for (int i = 0; i < row; i++)
			for (int k = 0; k < line; k++)
				output[i][k] = input[k][i];
	}

	int in_d()
		{	return in_dimention;	}									//필요할 곳이 있음


	int out_d()
		{	return out_dimention;	}									//필요할 곳이 있음.
};