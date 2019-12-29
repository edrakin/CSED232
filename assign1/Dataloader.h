#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Dataloader		//�ڵ� Ư¡. init�Լ����� ���� �����Ϳ� �ʿ��� ������ ��� �Ҵ��ϰ� ������.
{
private:
	string file_dir;
	string yo;				//read�Լ����� ����ϴ� ��. �� �ǹ̴� ����.
	int feature_num;
	int class_num;
	float** data;
	float** label;
	int data_num;
	string mode;			//train, validation, test �� 1��

public:

	Dataloader(string _file_dir = "", string _mode = "",
		int _feature_num = 0, int _class_num = 0, int _data_num = 0)
			{	init(_file_dir, _mode, _feature_num, _class_num, _data_num);	}//�����ڴ� init���� ��ü

	void init(string _file_dir = "", string _mode = "",	int _feature_num = 0, int _class_num = 0, int _data_num = 0)
	{
		file_dir = _file_dir;
		mode = _mode;
		feature_num = _feature_num;
		class_num = _class_num;
		data_num = _data_num;
		//////������� �׳� �� ���� �Է�.

		if (mode == "test")									//���̺� �ʿ���� ���
		{
			data = new float* [data_num + 1];
			for (int i = 0; i < data_num; i++)
				data[i] = new float[feature_num + 1];
			read();
			label = NULL;//���̺� ������ �ʿ� ����.
		}
		else												//���̺� ���� �ʿ��� ��.
		{
			data = new float* [data_num + 1];
			label = new float* [data_num + 1];
			for (int i = 0; i < data_num; i++)
			{
				data[i] = new float[feature_num + 1];
				label[i] = new float[feature_num + 1];
				for (int k = 0; k < feature_num; k++)
					label[i][k] = 0;						//�ϴ� ��� 0���� ���߰� read�Լ����� 1�� �ٲ�.
			}
			read();
		}
	}

	void read()												//������ �޾ƿ��� �Լ�.
	{
		ifstream in(file_dir);

		if (mode == "train" || mode == "val")
		{
			int i = 0, index, j, k;
			while (getline(in, yo))
			{
				index = 0, j = 0, k = 0;
				for (int x = 0; x < yo.length(); x++)
				{
					index++;
					if (yo[x] == ' ')
					{
						data[i][j] = stof(yo.substr(k, index - k)); //���� �����̽��ٺ��� �� �����̽��ٱ����� ���ڿ�
						k = index;
						j++;
					}
				}
				label[i][yo[yo.length() - 1] - 48] = 1;				//1�� �ٲ��ִ� ��Ʈ.
				i++;
			}
		}


		if (mode == "test")											//���� ����(���̺� ����)
		{
			int i = 0, index, j, k;
			while (getline(in, yo))
			{
				index = 0, j = 0, k = 0;
				for (int x = 0; x < yo.length(); x++)
				{
					index++;
					if (yo[x] == ' ')
					{
						data[i][j++] = stof(yo.substr(k, index - k));
						k = index;
					}
				}
				data[i][j] = stof(yo.substr(k, index - k + 1));
				i++;
			}
		}
	}

	float** read_data()
		{	return data;	}//Mlp���� ������ �����ö� �ʿ���.
	float** read_label()
		{	return label;	}//Mlp���� ������ �����ö� �ʿ���.
};