#pragma once
#include<iostream>
#include<string>
#include"Dataloader.h"
#include"Layer.h"
#include"Mlp.h"
#include"Loss.h"
using namespace std;
int find_max_index(int num, float* value)					//accuracy를 측정할 때 쓰는 함수.
{															//value 하나를 받아서 그 label이 어디인지 알려준다.
	float max = value[0];
	int in = 0;

	for (int k = 1; k < num; k++)
		if (max < value[k])
			{	in = k;		max = value[k];		}
	return in;
}

class Mlp {											// 얘는 다른 class와 다르게 초기화를 생성자에 넣었다.
private:											// init함수를 쓸 일이 없다. Mlp는 main에서만 호출함.
	Layer* layers;
	Loss loss;
	Dataloader train_data_set;
	float** train_data;
	float** train_label;
	Dataloader val_data_set;
	float** val_data;
	float** val_label;
	int epochs;
	float learning_rate;
	int layer_num;									//layer_num은 hidden_layer_num으로, 총 layer는 layer_num+1개이다.
	int train_num, class_num, val_num, test_num;

public:
	Mlp(int _feature_num = 0, int _class_num = 0, int _layer_num = 0, int* neuron = 0,
		int _epochs = 0, float _learning_rate = 0, int _train_num = 0, int _val_num = 0, int _test_num = 0,
		string train_dir = 0, string val_dir = 0)
	{												//생성자에서는 train, val 데이터로더를 만든다.
		class_num = _class_num;						//Layer들 모두 만든다.
		epochs = _epochs;							//Loss도 만든다.
		train_num = _train_num;						//그리고 내부 값들을 모두 채운다.
		val_num = _val_num;
		test_num = _test_num;
		layer_num = _layer_num;
		learning_rate = _learning_rate;
		train_data_set.init(train_dir, "train", _feature_num, class_num, train_num);
		val_data_set.init(val_dir, "val", _feature_num, class_num, val_num);
															//test는 main에서 받아서 main에서 풀어서 사용.
		
		layers = new Layer[layer_num + 2];
		layers[0].init(_feature_num, neuron[0], train_num, val_num, test_num);
		for (int i = 1; i < layer_num; i++)
			layers[i].init(neuron[i - 1], neuron[i], train_num, val_num, test_num);
		layers[layer_num].init(neuron[layer_num - 1], class_num, train_num, val_num, test_num);
					//1번 hidden과 output layer는 각각 feature_num과 class_num이 필요해서 for문에 넣지 않았다.

		train_data = train_data_set.read_data();
		train_label = train_data_set.read_label();
		val_data = val_data_set.read_data();
		val_label = val_data_set.read_label();
		loss.init(train_label, val_label, train_num, val_num, class_num);
	}

	void train()
	{
		int static count = 1;
		for (int x = 1; x <= epochs; x++, count++)									//epoch만큼 반복함.
		{
			float** input = train_data;
			for (int i = 0; i <= layer_num; i++)
				input = layers[i].train_forward(input);								//output을 얻는 과정

			float train_loss = loss.train_forward(input);							//train_loss값 추출
			float train_accuracy = accuracy(input, train_label, train_num, class_num);//accuracy값 추출

			loss.train_backward();													//gradient_y값 계산
			float** gradient_y = loss.gradienty();									//gradient_y값 가져오기

			for (int i = layer_num; i >= 0; i--)
				gradient_y = layers[i].train_backward(gradient_y, learning_rate, train_num);
																					//backward로 모든 w, b 업데이트
			cout.precision(16);														//pdf에서 본 자리수 맞추기
			cout << "epoch: " << count << " train_loss: " << train_loss;
			cout.precision(7);														//믿을 수 있는 자리수까지만 출력
			cout << " train accuracy: " << train_accuracy << endl;
		}
	}

	float accuracy(float** logit, float** label, int data_num, int class_num)		//accuracy 계산하는 함수.
	{
		float sum = 0;
		int index;
		for (int i = 0; i < data_num; i++)
		{
			index = find_max_index(class_num, logit[i]);							//한 data의 label값 찾고
			if (label[i][index])													//답이 맞으면 accuracy 상승
				sum++;
		}
		return (float)sum / (float)data_num;
	}
	void visualize_layer()															//그냥 layer 정보 출력하는 함수
	{																				//Mlp과정에 영향 전혀 없음
		cout << "====================================================" << endl;
		for (int i = 0; i <= layer_num; i++)
			cout << "dense layer " << i + 1 << " in_dimention: " << layers[i].in_d()
			<< "  out_dimention: " << layers[i].out_d() << endl;
		cout << "====================================================" << endl;
	}


	void validation()																//validation data로 forward하는 함수.
	{																				//accuracy 구하는 게 목표
		float** input = val_data;
		for (int i = 0; i <= layer_num; i++)
			input = layers[i].val_forward(input);//output을 얻는 과정

		float val_accuracy = accuracy(input, val_label, val_num, class_num);
		float val_loss = loss.val_forward(input);
		cout.precision(16);
		cout << "validation_loss: " << val_loss << " validation_accuracy: " << val_accuracy << endl;
	}


	void predict(float** input, string file_dir, int test_num)						//test data로 forward를 수행하는 함수
	{																				//text파일로 답을 출력하는 함수
		for (int i = 0; i <= layer_num; i++)
			input = layers[i].test_forward(input);//output을 얻는 과정

		ofstream out(file_dir);
		for (int i = 0; i < test_num; i++)
			out << find_max_index(class_num, input[i]) << endl;
		out.close();
	}



};