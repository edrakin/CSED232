#include<iostream>
#include<Windows.h>
#include<conio.h>
#include "Enum.h"
#include "Object.h"
#include "Map.h"

using namespace std;

Direction KeyInput()
{
	int key;
	key = _getch();
	switch (key)
	{
	case 'w':
		return UP;
	case 'a':
		return LEFT;
	case 'd':
		return RIGHT;
	case 's':
		return DOWN;
	case 'r':
		return RESTART;
	case 'e':
		return EXIT;
	}
}

int main()
{
	string filename;

	Map::SetHead(NULL);
	while (true) {
		cout << "Read Stage File: ";
		cin >> filename;
		if (!Map::ReadMap(filename)) {
			cout << "The file cannot be open. Please enter again." << endl;
			continue;//파일을 못 읽었으면 다시 입력하게 한다.
		}
		Map::PrintMap();
		cout << filename << " Load Complete. Press Any Key to Continue...";
		KeyInput();
		while (true) {
			Map::CheckRules();//object들에게 특징 부여하기
			Map::ChangeEntity();// 개체 is 개체 다 처리
			Map::LoseCheck();//you 개체 삭제
			Map::PrintMap();//맵 보여주고
			Map::PrintRules();//현재 특징들 보여주고
			if (Map::CantMoveCheck()) { //YOU 개체가 없을 시 패배
				cout << "YOU does not exist. You Lose" << endl;
				break;
			}
			if (Map::WinCheck()) { //승리 조건 만족시 승리
				cout << "YOU WIN!" << endl;
				break;
			}
			cout << "Key Input: w=up, s=down, a=left, d=right, r=restart, e=exit" << endl;
			Direction dir = KeyInput(); //키 입력을 받는다.
			if (dir == RESTART) {
				Map::ReadMap(filename);
			}
			if (dir == EXIT) {
				system("cls");
				break;
			}
			Map::YouMove(dir);
		}
	}

	return 0;
}