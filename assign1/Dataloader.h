#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Dataloader		//코드 특징. init함수에서 내부 데이터에 필요한 공간을 모두 할당하고 시작함.
{
private:
	string file_dir;
	string yo;				//read함수에서 사용하는 것. 별 의미는 없음.
	int feature_num;
	int class_num;
	float** data;
	float** label;
	int data_num;
	string mode;			//train, validation, test 중 1개

public:

	Dataloader(string _file_dir = "", string _mode = "",
		int _feature_num = 0, int _class_num = 0, int _data_num = 0)
			{	init(_file_dir, _mode, _feature_num, _class_num, _data_num);	}//생성자는 init으로 대체

	void init(string _file_dir = "", string _mode = "",	int _feature_num = 0, int _class_num = 0, int _data_num = 0)
	{
		file_dir = _file_dir;
		mode = _mode;
		feature_num = _feature_num;
		class_num = _class_num;
		data_num = _data_num;
		//////여기까지 그냥 들어갈 값들 입력.

		if (mode == "test")									//레이블 필요없는 경우
		{
			data = new float* [data_num + 1];
			for (int i = 0; i < data_num; i++)
				data[i] = new float[feature_num + 1];
			read();
			label = NULL;//레이블 공간은 필요 없다.
		}
		else												//레이블 공간 필요할 때.
		{
			data = new float* [data_num + 1];
			label = new float* [data_num + 1];
			for (int i = 0; i < data_num; i++)
			{
				data[i] = new float[feature_num + 1];
				label[i] = new float[feature_num + 1];
				for (int k = 0; k < feature_num; k++)
					label[i][k] = 0;						//일단 모두 0으로 맞추고 read함수에서 1로 바꿈.
			}
			read();
		}
	}

	void read()												//데이터 받아오는 함수.
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
						data[i][j] = stof(yo.substr(k, index - k)); //이전 스페이스바부터 현 스페이스바까지의 문자열
						k = index;
						j++;
					}
				}
				label[i][yo[yo.length() - 1] - 48] = 1;				//1로 바꿔주는 파트.
				i++;
			}
		}


		if (mode == "test")											//이하 동일(레이블 제외)
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
		{	return data;	}//Mlp에서 데이터 가져올때 필요함.
	float** read_label()
		{	return label;	}//Mlp에서 데이터 가져올때 필요함.
};