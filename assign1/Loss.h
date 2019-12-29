#pragma once
#include<iostream>
#include<string>
using namespace std;

class Loss							//�ڵ� Ư¡1. init�Լ����� ���� �����Ϳ� �ʿ��� ������ ��� �Ҵ��ϰ� ������
{									//�ڵ� Ư¡2. Ư¡ 1�� ���ؼ� train�� validation�� ��ǲ �ƿ�ǲ�� ���� ������.
private:							//test�� Loss function�� ��ġ�� ����.
	float** train_logit;
	float** train_label;
	float** val_logit;
	float** val_label;
	float** train_gradient_y;		//L�� y�޿� ���� gradient. output layer�� back propagation�� ���δ�.
	int train_num, val_num, class_num;
public:
	Loss(float** _train_label = 0, float** _val_label = 0, int _train_num = 0, int _val_num = 0, int _class_num = 0)
		{	init(_train_label, _val_label, _train_num, _val_num, _class_num);	}


	void init(float** _train_label = 0, float** _val_label = 0, int _train_num = 0, int _val_num = 0, int _class_num = 0)
	{
		train_num = _train_num;								//������ ��� ���� �Ҵ��̶� ���̺� ���縸 ��.
		val_num = _val_num;
		class_num = _class_num;
		train_logit = new float* [_train_num];
		val_logit = new float* [_val_num];
		train_label = new float* [_train_num];
		val_label = new float* [_val_num];
		train_gradient_y = new float* [train_num];
		for (int i = 0; i < _train_num; i++)
		{
			train_logit[i] = new float[_class_num];
			train_label[i] = new float[_class_num];
			train_gradient_y[i] = new float[_class_num];
			for (int k = 0; k < class_num; k++)
				train_label[i][k] = _train_label[i][k];		//���̺� ���� 1
		}
		for (int i = 0; i < _val_num; i++)
		{
			val_logit[i] = new float[_class_num];
			val_label[i] = new float[_class_num];
			for (int k = 0; k < class_num; k++)
				val_label[i][k] = _val_label[i][k];			//���̺� ���� 2
		}
	}

	float train_forward(float** input)					//Loss�� ���ϴ� �Լ�
	{
		float sum = 0;
		for (int i = 0; i < train_num; i++)
			for (int k = 0; k < class_num; k++)
			{
				train_logit[i][k] = input[i][k];		//backward���� ���� ���� logit�� ���⼭ �����Ѵ�.

				sum += (train_logit[i][k] - train_label[i][k]) * (train_logit[i][k] - train_label[i][k]) / (float)2;
			}
		return sum / ((float)train_num * (float)class_num);
	}

	float val_forward(float** input)					//Loss�� ���ϴ� �Լ�
	{
		float sum = 0;
		for (int i = 0; i < val_num; i++)
			for (int k = 0; k < class_num; k++)
			{
				val_logit[i][k] = input[i][k];			//backward���� ���� ���� logit�� ���⼭ �����Ѵ�.

				sum += (val_logit[i][k] - val_label[i][k]) * (val_logit[i][k] - val_label[i][k]) / (float)2;
			}
		return sum / (float)val_num / (float)class_num;
	}
	void train_backward()								//y_gradient ���ϴ� �Լ�.
	{													//Ư���ϰ� output_layer�� y_gradient�� Loss class�� ����.
		for (int i = 0; i < train_num; i++)				//������ y_gradient�� Layer class�� back_gradient�� ����.
			for (int k = 0; k < class_num; k++)
				train_gradient_y[i][k] = train_logit[i][k] - train_label[i][k];
	}
	float** gradienty()
		{	return train_gradient_y;	}				//backward���� ���� y_gradient�� �������� �Լ�.
};