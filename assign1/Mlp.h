#pragma once
#include<iostream>
#include<string>
#include"Dataloader.h"
#include"Layer.h"
#include"Mlp.h"
#include"Loss.h"
using namespace std;
int find_max_index(int num, float* value)					//accuracy�� ������ �� ���� �Լ�.
{															//value �ϳ��� �޾Ƽ� �� label�� ������� �˷��ش�.
	float max = value[0];
	int in = 0;

	for (int k = 1; k < num; k++)
		if (max < value[k])
			{	in = k;		max = value[k];		}
	return in;
}

class Mlp {											// ��� �ٸ� class�� �ٸ��� �ʱ�ȭ�� �����ڿ� �־���.
private:											// init�Լ��� �� ���� ����. Mlp�� main������ ȣ����.
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
	int layer_num;									//layer_num�� hidden_layer_num����, �� layer�� layer_num+1���̴�.
	int train_num, class_num, val_num, test_num;

public:
	Mlp(int _feature_num = 0, int _class_num = 0, int _layer_num = 0, int* neuron = 0,
		int _epochs = 0, float _learning_rate = 0, int _train_num = 0, int _val_num = 0, int _test_num = 0,
		string train_dir = 0, string val_dir = 0)
	{												//�����ڿ����� train, val �����ͷδ��� �����.
		class_num = _class_num;						//Layer�� ��� �����.
		epochs = _epochs;							//Loss�� �����.
		train_num = _train_num;						//�׸��� ���� ������ ��� ä���.
		val_num = _val_num;
		test_num = _test_num;
		layer_num = _layer_num;
		learning_rate = _learning_rate;
		train_data_set.init(train_dir, "train", _feature_num, class_num, train_num);
		val_data_set.init(val_dir, "val", _feature_num, class_num, val_num);
															//test�� main���� �޾Ƽ� main���� Ǯ� ���.
		
		layers = new Layer[layer_num + 2];
		layers[0].init(_feature_num, neuron[0], train_num, val_num, test_num);
		for (int i = 1; i < layer_num; i++)
			layers[i].init(neuron[i - 1], neuron[i], train_num, val_num, test_num);
		layers[layer_num].init(neuron[layer_num - 1], class_num, train_num, val_num, test_num);
					//1�� hidden�� output layer�� ���� feature_num�� class_num�� �ʿ��ؼ� for���� ���� �ʾҴ�.

		train_data = train_data_set.read_data();
		train_label = train_data_set.read_label();
		val_data = val_data_set.read_data();
		val_label = val_data_set.read_label();
		loss.init(train_label, val_label, train_num, val_num, class_num);
	}

	void train()
	{
		int static count = 1;
		for (int x = 1; x <= epochs; x++, count++)									//epoch��ŭ �ݺ���.
		{
			float** input = train_data;
			for (int i = 0; i <= layer_num; i++)
				input = layers[i].train_forward(input);								//output�� ��� ����

			float train_loss = loss.train_forward(input);							//train_loss�� ����
			float train_accuracy = accuracy(input, train_label, train_num, class_num);//accuracy�� ����

			loss.train_backward();													//gradient_y�� ���
			float** gradient_y = loss.gradienty();									//gradient_y�� ��������

			for (int i = layer_num; i >= 0; i--)
				gradient_y = layers[i].train_backward(gradient_y, learning_rate, train_num);
																					//backward�� ��� w, b ������Ʈ
			cout.precision(16);														//pdf���� �� �ڸ��� ���߱�
			cout << "epoch: " << count << " train_loss: " << train_loss;
			cout.precision(7);														//���� �� �ִ� �ڸ��������� ���
			cout << " train accuracy: " << train_accuracy << endl;
		}
	}

	float accuracy(float** logit, float** label, int data_num, int class_num)		//accuracy ����ϴ� �Լ�.
	{
		float sum = 0;
		int index;
		for (int i = 0; i < data_num; i++)
		{
			index = find_max_index(class_num, logit[i]);							//�� data�� label�� ã��
			if (label[i][index])													//���� ������ accuracy ���
				sum++;
		}
		return (float)sum / (float)data_num;
	}
	void visualize_layer()															//�׳� layer ���� ����ϴ� �Լ�
	{																				//Mlp������ ���� ���� ����
		cout << "====================================================" << endl;
		for (int i = 0; i <= layer_num; i++)
			cout << "dense layer " << i + 1 << " in_dimention: " << layers[i].in_d()
			<< "  out_dimention: " << layers[i].out_d() << endl;
		cout << "====================================================" << endl;
	}


	void validation()																//validation data�� forward�ϴ� �Լ�.
	{																				//accuracy ���ϴ� �� ��ǥ
		float** input = val_data;
		for (int i = 0; i <= layer_num; i++)
			input = layers[i].val_forward(input);//output�� ��� ����

		float val_accuracy = accuracy(input, val_label, val_num, class_num);
		float val_loss = loss.val_forward(input);
		cout.precision(16);
		cout << "validation_loss: " << val_loss << " validation_accuracy: " << val_accuracy << endl;
	}


	void predict(float** input, string file_dir, int test_num)						//test data�� forward�� �����ϴ� �Լ�
	{																				//text���Ϸ� ���� ����ϴ� �Լ�
		for (int i = 0; i <= layer_num; i++)
			input = layers[i].test_forward(input);//output�� ��� ����

		ofstream out(file_dir);
		for (int i = 0; i < test_num; i++)
			out << find_max_index(class_num, input[i]) << endl;
		out.close();
	}



};