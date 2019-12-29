#pragma once
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<math.h>
using namespace std;

class Layer				//�ڵ� Ư¡1. init�Լ����� ���� �����Ϳ� �ʿ��� ������ ��� �Ҵ��ϰ� ������.
						//�ڵ� Ư¡2. Ư¡ 1�� ���ؼ� train�� validation, test�� ��ǲ �ƿ�ǲ�� ���� ������.
{
private:				//���� �������� �ִµ�, pdf���� ������ ���� ������ �����ҰԿ�
	float** train_input;
	float** train_output;
	float** test_output;
	float** val_input;
	float** val_output;
	float** weigh;
	float* bias;
	float** gradient_a;			//L�� a�� ���� gradient ��.
	float** transpose_input;	//train input�� ��ġ���
	float** transpose_w;		//weigh�� ��ġ���
	float* gradient_b;			//L�� bias�� ���� gradient ��.
	float** gradient_w;			//L�� weigh�� ���� gradient ��.
	float** gradient_back;		//L�� h�� ���� gradient ��.
	int in_dimention;
	int out_dimention;
	int train_num, val_num, test_num;
public:
	Layer(int _in_dimention = 0, int _out_dimention = 0, int train_data_num = 0, int val_data_num = 0, int test_data_num = 0)
		{	init(_in_dimention, _out_dimention, train_data_num, val_data_num, test_data_num);	}

	//init�Լ��� �����ڸ� ����Ѵ�.

	void init(int _in_dimention = 0, int _out_dimention = 0, int train_data_num = 0, int val_data_num = 0, int test_data_num = 0)
	{
		train_num = train_data_num;
		val_num = val_data_num;				//�Լ��� �� �䵥 ���� �Ҵ��ϴ� �����̶� �� �ʿ� ����.
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
				weigh[i][k] = (float)(rand() % 32761 + 1) / (float)32763;	//weigh�� 0�� 1 ���� ����
			gradient_w[i] = new float[out_dimention];
			transpose_input[i] = new float[train_data_num];
		}

		for (int i = 0; i < out_dimention; i++)
		{
			bias[i] = 0;													//bias�� �ʱⰪ 0
			transpose_w[i] = new float[in_dimention];
			gradient_b[i] = 1;												//L�� ���� bias �׶���Ʈ�� 1�� ����.
		}
	}

	//������ ���� ������ forward�Լ��� 3���� ��������.(val�� test���� �ּ� ����)


	float** train_forward(float** input)									//weigh�� bias�� class�� ����ϴ� �Լ�
	{
		for (int i = 0; i < train_num; i++)
			for (int k = 0; k < in_dimention; k++)
				train_input[i][k] = input[i][k];							//�޾ƿ� ��ǲ�� Layer class�� ����.

		matmul(train_output, train_input, weigh, train_num, in_dimention, out_dimention);		//output ���
		for (int i = 0; i < train_num; i++)
			for (int k = 0; k < out_dimention; k++)
			{
				train_output[i][k] += bias[k];													//output ���
				train_output[i][k] = (float)1 / (exp(-train_output[i][k]) + (float)1);			//output ���
			}
		return train_output;
	}

	float** train_backward(float** y_gradient, float learning_rate, int data_num)
	{
		for (int i = 0; i < data_num; i++)
			for (int k = 0; k < out_dimention; k++)
				gradient_a[i][k] = y_gradient[i][k] * train_output[i][k] * ((float)1 - train_output[i][k]);

																								//gradient_a�� ���

		transpose(train_input, transpose_input, train_num, in_dimention);						//transpose_input���
		transpose(weigh, transpose_w, in_dimention, out_dimention);								//transpose_w���
		matmul(gradient_w, transpose_input, gradient_a, in_dimention, data_num, out_dimention); //gradient_w ���
		for (int i = 0; i < out_dimention; i++)
		{
			gradient_b[i] = 0;
			for (int k = 0; k < data_num; k++)
				gradient_b[i] += gradient_a[k][i];												//gradient_b ���
		}

		matmul(gradient_back, gradient_a, transpose_w, data_num, out_dimention, in_dimention);	//gradient_back ���

		for (int i = 0; i < in_dimention; i++)
			for (int k = 0; k < out_dimention; k++)
				weigh[i][k] -= learning_rate * gradient_w[i][k];								//weigh ������Ʈ

		for (int i = 0; i < out_dimention; i++)
			bias[i] -= learning_rate * gradient_b[i];											//bias ������Ʈ

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
	{																	//��İ�. row1�� line2�� ���� ���̶� ����
		for (int i = 0; i < line1; i++)
			for (int k = 0; k < row2; k++)
			{
				output[i][k] = 0;
				for (int h = 0; h < row1; h++)
					output[i][k] = output[i][k] + a[i][h] * b[h][k];
			}
	}

	void transpose(float** input, float** output, int line, int row)	//��ġ��� �����
	{
		for (int i = 0; i < row; i++)
			for (int k = 0; k < line; k++)
				output[i][k] = input[k][i];
	}

	int in_d()
		{	return in_dimention;	}									//�ʿ��� ���� ����


	int out_d()
		{	return out_dimention;	}									//�ʿ��� ���� ����.
};