#include<iostream>
#include"Dataloader.h"
#include"Mlp.h"
#include<string>
#include<stdlib.h>
#include<fstream>
using namespace std;
/*
dataset_type[str](two moon 또는 iris)           0
 feature_num[int]                               1
 class_num[int]                                 2
 hidden_layer_num[int]                          3
 hidden_layer_neurons[str] ex) “10 10 10"      4
 epochs[int]                                    5
 learning_rate[float]                           6
 train_data_dir[str]                            7
 train_data_num[int]                            8
 validation_data_dir[str]                       9
 validation_data_num[int]                      10
 test_data_dir[str]                            11
 test_data_num[int]                            12
 test_output_dir[str]                          13
*/

int main(int argc, char* argv[])
{
	int feature_num, class_num, train_num, val_num, test_num, epochs, layer_num;
									//val은 validation의 축약. 이후의 validation은 모두 축약한다.
	float learning_rate;
	string train_dir, val_dir, test_dir, output_dir;//출력경로는 output.dir에 저장한다.
	int neuron[3000] = { 0 };							//각 layer의 뉴런 개수 3000개까지로 한정

	string temp = argv[2];							//char* 문자열 형식을 string으로 변환 후 stoi 사용.
	feature_num = stoi(temp);
	temp = argv[3];
	class_num = stoi(temp);

	temp = argv[4];
	layer_num = stoi(temp);//hidden layer 개수

	int i = 0;
	for (int x = 0; x < strlen(argv[5]); x++)		//뉴런 개수를 받는다.
	{
		if (argv[5][x] == '_')	i++;
		else	neuron[i] = 10 * neuron[i] + argv[5][x] - 48;
	}

	temp = argv[6];
	epochs = stoi(temp);
	temp = argv[7];
	learning_rate = stof(temp);
	train_dir = argv[8];
	val_dir = argv[10];
	test_dir = argv[12];
	output_dir = argv[14];
	temp = argv[9];
	train_num = stoi(temp);
	temp = argv[11];
	val_num = stoi(temp);
	temp = argv[13];
	test_num = stoi(temp);
	/////////////////////////////////////여기까지 해서 모든 인자를 받는다.
	
	Mlp M(feature_num, class_num, layer_num, neuron, epochs,
		learning_rate, train_num, val_num, test_num, train_dir, val_dir);//Mlp 내부에서 train, test 데이터를 받는다.
	
	Dataloader test(test_dir, "test", feature_num, class_num, test_num);//얘는 메인에서 돌린다.

	
	int m = 1;
	while (m)													//모드 결정.		
	{
		cout << "mode\n0. exit\n1. visualize_layer\n2. train\n3. validation\n4. test\n\n>> ";
		cin >> m;
		switch (m)
		{
		case 1:
			M.visualize_layer();
			cout << endl;
			break;
		case 2:
			M.train();
			cout << "train complete!" << endl;
			break;
		case 3:
			M.validation();
			cout << endl;
			break;
		case 4:
			M.predict(test.read_data(), output_dir, test_num);
			cout << "test complete!" << endl;
			break;
		}
	}
}