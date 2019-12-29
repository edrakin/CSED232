#pragma once
#include<iostream>
#include<string>
using namespace std;

class Loss							//코드 특징1. init함수에서 내부 데이터에 필요한 공간을 모두 할당하고 시작함
{									//코드 특징2. 특징 1을 위해서 train과 validation의 인풋 아웃풋을 따로 설정함.
private:							//test는 Loss function을 거치지 않음.
	float** train_logit;
	float** train_label;
	float** val_logit;
	float** val_label;
	float** train_gradient_y;		//L의 y햇에 대한 gradient. output layer에 back propagation에 쓰인다.
	int train_num, val_num, class_num;
public:
	Loss(float** _train_label = 0, float** _val_label = 0, int _train_num = 0, int _val_num = 0, int _class_num = 0)
		{	init(_train_label, _val_label, _train_num, _val_num, _class_num);	}


	void init(float** _train_label = 0, float** _val_label = 0, int _train_num = 0, int _val_num = 0, int _class_num = 0)
	{
		train_num = _train_num;								//길지만 모두 공간 할당이랑 레이블 복사만 함.
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
				train_label[i][k] = _train_label[i][k];		//레이블 복사 1
		}
		for (int i = 0; i < _val_num; i++)
		{
			val_logit[i] = new float[_class_num];
			val_label[i] = new float[_class_num];
			for (int k = 0; k < class_num; k++)
				val_label[i][k] = _val_label[i][k];			//레이블 복사 2
		}
	}

	float train_forward(float** input)					//Loss값 구하는 함수
	{
		float sum = 0;
		for (int i = 0; i < train_num; i++)
			for (int k = 0; k < class_num; k++)
			{
				train_logit[i][k] = input[i][k];		//backward에서 쓰기 위해 logit을 여기서 저장한다.

				sum += (train_logit[i][k] - train_label[i][k]) * (train_logit[i][k] - train_label[i][k]) / (float)2;
			}
		return sum / ((float)train_num * (float)class_num);
	}

	float val_forward(float** input)					//Loss값 구하는 함수
	{
		float sum = 0;
		for (int i = 0; i < val_num; i++)
			for (int k = 0; k < class_num; k++)
			{
				val_logit[i][k] = input[i][k];			//backward에서 쓰기 위해 logit을 여기서 저장한다.

				sum += (val_logit[i][k] - val_label[i][k]) * (val_logit[i][k] - val_label[i][k]) / (float)2;
			}
		return sum / (float)val_num / (float)class_num;
	}
	void train_backward()								//y_gradient 구하는 함수.
	{													//특이하게 output_layer의 y_gradient는 Loss class에 저장.
		for (int i = 0; i < train_num; i++)				//나머지 y_gradient는 Layer class의 back_gradient로 저장.
			for (int k = 0; k < class_num; k++)
				train_gradient_y[i][k] = train_logit[i][k] - train_label[i][k];
	}
	float** gradienty()
		{	return train_gradient_y;	}				//backward에서 만든 y_gradient를 가져오는 함수.
};