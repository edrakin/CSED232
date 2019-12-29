#include<iostream>
#include<fstream>
#include<string>
#include"Map.h"
#include"Object.h"
#include"Enum.h"
using namespace std;

int Map::width = 0;
int Map::height = 0;
Object* Map::head = nullptr;
int** Map::map = 0;
string** Map::s_map = 0;//static 변수들은 모두 초기화

bool Map::ReadMap(string str)//맵 읽어오기
{
	ifstream in(str);
	if (!in)
		return false;//실패하면 실패했다고 알려주고
	if(head != nullptr)
		reset();//받아둔 데이터가 있다면 삭제

	head = new Object(-1, -1);
	string x = "";
	int line = 0;
	
	while (getline(in, x))
	{
		if (width == 0)
			width = x.length();

		if (width != x.length())//map의 width가 일정하지 않으면 오류로 인식
			return false;

		for (int i = 0; i < x.length(); i++)
			if (x[i] != ' ')
			{
				if (head->GetX() == -1)//링크드 리스트 첫번째일때
				{
					Object* ptr = NULL;
					if (x[i] == 'b')
						ptr = new Baba(i, line, NULL, NULL);
					else if (x[i] == 'r')
						ptr = new Rock(i, line, NULL, NULL);
					else if (x[i] == 'w')
						ptr = new Wall(i, line, NULL, NULL);
					else if (x[i] == 'f')
						ptr = new Flag(i, line, NULL, NULL);
					else if (x[i] == 'B')
						ptr = new BabaText(i, line, NULL, NULL);
					else if (x[i] == 'R')
						ptr = new RockText(i, line, NULL, NULL);
					else if (x[i] == 'W')
						ptr = new WallText(i, line, NULL, NULL);
					else if (x[i] == 'F')
						ptr = new FlagText(i, line, NULL, NULL);
					else if (x[i] == 'I')
						ptr = new Is(i, line, NULL, NULL);
					else if (x[i] == 'Y')
						ptr = new You(i, line, NULL, NULL);
					else if (x[i] == 'G')
						ptr = new Win(i, line, NULL, NULL);
					else if (x[i] == 'S')
						ptr = new Stop(i, line, NULL, NULL);
					else if (x[i] == 'P')
						ptr = new Push(i, line, NULL, NULL);
					else if (x[i] == 'L')
						ptr = new Lose(i, line, NULL, NULL);
					else
						return false;//다른 문자가 있으면 오류로 인식
					delete(head);
					head = ptr;
					Object* tt = new Object(0, 0, head, NULL);
					head->SetNext(tt);//(tail->GetNext())->GetPrev()의 오류를 막기 위함.
				}
				else//첫 번째가 아닐 때
				{
					Object* ptr = NULL;
					if (x[i] == 'b')
						ptr = new Baba(i, line, NULL, head);
					else if (x[i] == 'r')
						ptr = new Rock(i, line, NULL, head);
					else if (x[i] == 'w')
						ptr = new Wall(i, line, NULL, head);
					else if (x[i] == 'f')
						ptr = new Flag(i, line, NULL, head);
					else if (x[i] == 'B')
						ptr = new BabaText(i, line, NULL, head);
					else if (x[i] == 'R')
						ptr = new RockText(i, line, NULL, head);
					else if (x[i] == 'W')
						ptr = new WallText(i, line, NULL, head);
					else if (x[i] == 'F')
						ptr = new FlagText(i, line, NULL, head);
					else if (x[i] == 'I')
						ptr = new Is(i, line, NULL, head);
					else if (x[i] == 'Y')
						ptr = new You(i, line, NULL, head);
					else if (x[i] == 'G')
						ptr = new Win(i, line, NULL, head);
					else if (x[i] == 'S')
						ptr = new Stop(i, line, NULL, head);
					else if (x[i] == 'P')
						ptr = new Push(i, line, NULL, head);
					else if (x[i] == 'L')
						ptr = new Lose(i, line, NULL, head);
					else
						return false;//다른 문자가 있으면 오류로 인식
					head->SetPrev(ptr);
					head = ptr;
				}
				//링크드 리스트 하나씩 추가하기.
			}
		line++;
	}
	height = line;
	map = NULL;
	s_map = NULL;
	Object* tt = new Object(0, 0, NULL, head);
	head->SetPrev(tt);//(head->prev)->GetNext의 오류를 막기 위함.
	return true;
}

void Map::PrintMap() //맵 출력하는 함수
{
	system("cls");
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
			cout << "+--";
		cout << "+" << endl;
		for (int k = 0; k < width; k++)
			cout << "|  ";
		cout << "|" << endl;
		for (int k = 0; k < width; k++)
			cout << "|  ";
		cout << "|" << endl;
	}
	for (int k = 0; k < width; k++)
		cout << "+--";
	cout << "+" << endl;							//여기까지 해서 틀 만들기


	for (Object* t = head; t; t = t->GetNext())//gotoxy함수를 이용해서 맵에 오브젝트 채우기.
	{
		if (t->ToString() == "Baba")
		{
			gotoxy(t->GetX() * 3 + 1, t->GetY() * 3 + 1);
			cout << "b";
		}
		else if (t->ToString() == "Rock")
		{
			gotoxy(t->GetX() * 3 + 2, t->GetY() * 3 + 1);
			cout << "r";
		}
		else if (t->ToString() == "Wall")
		{
			gotoxy(t->GetX() * 3 + 1, t->GetY() * 3 + 2);
			cout << "w";
		}
		else if (t->ToString() == "Flag")
		{
			gotoxy(t->GetX() * 3 + 2, t->GetY() * 3 + 2);
			cout << "f";
		}
		else if (t->ToString() == "BabaText")
		{
			gotoxy(t->GetX() * 3 + 1, t->GetY() * 3 + 1);
			cout << "B";
			gotoxy(t->GetX() * 3 + 2, t->GetY() * 3 + 1);
			cout << "A";
			gotoxy(t->GetX() * 3 + 1, t->GetY() * 3 + 2);
			cout << "B";
			gotoxy(t->GetX() * 3 + 2, t->GetY() * 3 + 2);
			cout << "A";
		}
		else if (t->ToString() == "RockText")
		{
			gotoxy(t->GetX() * 3 + 1, t->GetY() * 3 + 1);
			cout << "R";
			gotoxy(t->GetX() * 3 + 2, t->GetY() * 3 + 1);
			cout << "O";
			gotoxy(t->GetX() * 3 + 1, t->GetY() * 3 + 2);
			cout << "C";
			gotoxy(t->GetX() * 3 + 2, t->GetY() * 3 + 2);
			cout << "K";
		}
		else if (t->ToString() == "WallText")
		{
			gotoxy(t->GetX() * 3 + 1, t->GetY() * 3 + 1);
			cout << "W";
			gotoxy(t->GetX() * 3 + 2, t->GetY() * 3 + 1);
			cout << "A";
			gotoxy(t->GetX() * 3 + 1, t->GetY() * 3 + 2);
			cout << "L";
			gotoxy(t->GetX() * 3 + 2, t->GetY() * 3 + 2);
			cout << "L";
		}
		else if (t->ToString() == "FlagText")
		{
			gotoxy(t->GetX() * 3 + 1, t->GetY() * 3 + 1);
			cout << "F";
			gotoxy(t->GetX() * 3 + 2, t->GetY() * 3 + 1);
			cout << "L";
			gotoxy(t->GetX() * 3 + 1, t->GetY() * 3 + 2);
			cout << "A";
			gotoxy(t->GetX() * 3 + 2, t->GetY() * 3 + 2);
			cout << "G";
		}
		else if (t->ToString() == "Is")
		{
			gotoxy(t->GetX() * 3 + 1, t->GetY() * 3 + 1);
			cout << "I";
			gotoxy(t->GetX() * 3 + 2, t->GetY() * 3 + 2);
			cout << "S";
		}
		else if (t->ToString() == "You")
		{
			gotoxy(t->GetX() * 3 + 1, t->GetY() * 3 + 1);
			cout << "Y";
			gotoxy(t->GetX() * 3 + 2, t->GetY() * 3 + 1);
			cout << "O";
			gotoxy(t->GetX() * 3 + 2, t->GetY() * 3 + 2);
			cout << "U";
		}
		else if (t->ToString() == "Win")
		{
			gotoxy(t->GetX() * 3 + 1, t->GetY() * 3 + 1);
			cout << "W";
			gotoxy(t->GetX() * 3 + 2, t->GetY() * 3 + 1);
			cout << "I";
			gotoxy(t->GetX() * 3 + 2, t->GetY() * 3 + 2);
			cout << "N";
		}
		else if (t->ToString() == "Stop")
		{
			gotoxy(t->GetX() * 3 + 1, t->GetY() * 3 + 1);
			cout << "S";
			gotoxy(t->GetX() * 3 + 2, t->GetY() * 3 + 1);
			cout << "T";
			gotoxy(t->GetX() * 3 + 1, t->GetY() * 3 + 2);
			cout << "O";
			gotoxy(t->GetX() * 3 + 2, t->GetY() * 3 + 2);
			cout << "P";
		}
		else if (t->ToString() == "Push")
		{
			gotoxy(t->GetX() * 3 + 1, t->GetY() * 3 + 1);
			cout << "P";
			gotoxy(t->GetX() * 3 + 2, t->GetY() * 3 + 1);
			cout << "U";
			gotoxy(t->GetX() * 3 + 1, t->GetY() * 3 + 2);
			cout << "S";
			gotoxy(t->GetX() * 3 + 2, t->GetY() * 3 + 2);
			cout << "H";
		}
		else if (t->ToString() == "Lose")
		{
			gotoxy(t->GetX() * 3 + 1, t->GetY() * 3 + 1);
			cout << "L";
			gotoxy(t->GetX() * 3 + 2, t->GetY() * 3 + 1);
			cout << "O";
			gotoxy(t->GetX() * 3 + 1, t->GetY() * 3 + 2);
			cout << "S";
			gotoxy(t->GetX() * 3 + 2, t->GetY() * 3 + 2);
			cout << "E";
		}
	}
	gotoxy(0, 3 * height + 5);//그리고 밑으로 이동해서 이후 출력하는 것들 위치 조정.
}



void Map::PrintRules()//미리 만들어둔 s_map을 이용해 현재 존재하는 문장들 출력
{
	for (int i = 0; i < height - 2; i++)
		for (int k = 0; k < width - 2; k++)
			if (s_map[i][k] == "BABA" || s_map[i][k] == "ROCK"
				|| s_map[i][k] == "WALL" || s_map[i][k] == "FLAG")
			{
				if (s_map[i][k + 1] == "Is")
					if (s_map[i][k + 2] != "" && s_map[i][k + 2] != "Is")
						cout << s_map[i][k] << " " << s_map[i][k + 1] << " " << s_map[i][k + 2] << endl;
				if (s_map[i + 1][k] == "Is")
					if (s_map[i + 2][k] != "" && s_map[i + 2][k] != "Is")
						cout << s_map[i][k] << " " << s_map[i + 1][k] << " " << s_map[i + 2][k] << endl;
			}

	for (int i = 0; i < height; i++)//만들어둔 놈들 다 삭제
		delete[](s_map[i]);
	delete[](s_map);
	for (int i = 0; i < height; i++)//다 삭제
		delete[](map[i]);
	delete[](map);
}

Object* Map::GetHead()
{
	return head;
}

void Map::SetHead(Object* obj)
{
	head = obj;
}

int Map::GetWidth()
{
	return width;
}

int Map::GetHeight()
{
	return height;
}

void Map::YouMove(Direction dir)//You 특성 가진 놈들 찾아서 Object::YouMove 호출
{
	int a, b;
	for (Object* t = head; t; t = t->GetNext())
		if (t->GetProperty() & YOU)
		{
			a = t->GetX();
			b = t->GetY();
			MoveXY(a, b, dir);
			if (IsInBoundary(a, b))//얘가 움직일 수 있을 경우 호출
				t->Move(dir);
		}
}

bool Map::IsInBoundary(int x, int y)//맵 밖으로 나가면 0 리턴.
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return 0;
	return 1;
}

void Map::CheckRules()	//s_map, map은 printrules에서 할당 해제
{

	//////////룰 초기화하기
	Baba::InitRule();
	Rock::InitRule();
	Wall::InitRule();
	Flag::InitRule();

	s_map = new string * [height];						    //----맵 정보----
	map = new int* [height];
	for (int i = 0; i < height; i++)						
	{														
		map[i] = new int[width];
		s_map[i] = new string[width];						
		for (int k = 0; k < width; k++)						
		{
			s_map[i][k] = "";							
			map[i][k] = 0;
		}
	}//간이 맵을 만들어서 문장 찾기.

	for (Object* t = head; t; t = t->GetNext())//얘들은 겹칠 일 없으니까 걱정 안 해도 됨.
	{
		if (t->ToString() == "BabaText")
			s_map[t->GetY()][t->GetX()] = "BABA", map[t->GetY()][t->GetX()] = BABA;
		else if (t->ToString() == "RockText")
			s_map[t->GetY()][t->GetX()] = "ROCK", map[t->GetY()][t->GetX()] = ROCK;
		else if (t->ToString() == "WallText")
			s_map[t->GetY()][t->GetX()] = "WALL", map[t->GetY()][t->GetX()] = WALL;
		else if (t->ToString() == "FlagText")
			s_map[t->GetY()][t->GetX()] = "FLAG", map[t->GetY()][t->GetX()] = FLAG;
		else if (t->ToString() == "Is")
			s_map[t->GetY()][t->GetX()] = "Is";
		else if (t->ToString() == "You")
			s_map[t->GetY()][t->GetX()] = "You", map[t->GetY()][t->GetX()] = YOU;
		else if (t->ToString() == "Win")
			s_map[t->GetY()][t->GetX()] = "Win", map[t->GetY()][t->GetX()] = WIN;
		else if (t->ToString() == "Stop")
			s_map[t->GetY()][t->GetX()] = "Stop", map[t->GetY()][t->GetX()] = STOP;
		else if (t->ToString() == "Push")
			s_map[t->GetY()][t->GetX()] = "Push", map[t->GetY()][t->GetX()] = PUSH;
		else if (t->ToString() == "Lose")
			s_map[t->GetY()][t->GetX()] = "Lose", map[t->GetY()][t->GetX()] = LOSE;
	}//맵 만들기 완료

	
	for (int i = 0; i < height - 2; i++)
		for (int k = width - 2; k < width; k++)
		{
			if (s_map[i][k] == "BABA" || s_map[i][k] == "ROCK"
				|| s_map[i][k] == "WALL" || s_map[i][k] == "FLAG")
				if (s_map[i + 1][k] == "Is")
					if (s_map[i + 2][k] != "" && s_map[i + 2][k] != "Is")
					{
						if (map[i][k] == BABA)
							Baba::property += map[i + 2][k];
						else if (map[i][k] == ROCK)
							Rock::property += map[i + 2][k];
						else if (map[i][k] == WALL)
							Wall::property += map[i + 2][k];
						else if (map[i][k] == FLAG)
							Flag::property += map[i + 2][k];
					}
		}
	for (int k = 0; k < width - 2; k++)
		for (int i = height - 2; i < height; i++)
		{
			if (s_map[i][k] == "BABA" || s_map[i][k] == "ROCK"
				|| s_map[i][k] == "WALL" || s_map[i][k] == "FLAG")
				if (s_map[i][k + 1] == "Is")
					if (s_map[i][k + 2] != "" && s_map[i][k + 2] != "Is")
					{
						if (map[i][k] == BABA)
							Baba::property += map[i][k + 2];
						else if (map[i][k] == ROCK)
							Rock::property += map[i][k + 2];
						else if (map[i][k] == WALL)
							Wall::property += map[i][k + 2];
						else if (map[i][k] == FLAG)
							Flag::property += map[i][k + 2];
					}
		}
		

	for (int i = 0; i < height - 2; i++)
		for (int k = 0; k < width - 2; k++)
		{
			if (s_map[i][k] == "BABA" || s_map[i][k] == "ROCK"
				|| s_map[i][k] == "WALL" || s_map[i][k] == "FLAG")
			{
				if (s_map[i][k + 1] == "Is")
					if (s_map[i][k + 2] != "" && s_map[i][k + 2] != "Is")
					{
						if (map[i][k] == BABA)
							Baba::property += map[i][k + 2];
						else if (map[i][k] == ROCK)
							Rock::property += map[i][k + 2];
						else if (map[i][k] == WALL)
							Wall::property += map[i][k + 2];
						else if (map[i][k] == FLAG)
							Flag::property += map[i][k + 2];
					}

				if (s_map[i + 1][k] == "Is")
					if (s_map[i + 2][k] != "" && s_map[i + 2][k] != "Is")
					{
						if (map[i][k] == BABA)
							Baba::property += map[i + 2][k];
						else if (map[i][k] == ROCK)
							Rock::property += map[i + 2][k];
						else if (map[i][k] == WALL)
							Wall::property += map[i + 2][k];
						else if (map[i][k] == FLAG)
							Flag::property += map[i + 2][k];
					}
			}
		}//맵에 있는 문장들 모두 찾아서 property에 저장하기.
}

bool Map::WinCheck()//you와 win이 같은 공간에 있는지 찾기.
{
	for (Object* t = head; t; t = t->GetNext())
		if (t->GetProperty() & YOU)
			for (Object* pt = head; pt; pt = pt->GetNext())
				if (pt->GetProperty() & WIN)
					if (t->GetX() == pt->GetX() && t->GetY() == pt->GetY())	//YOU와 WIN이 같은 공간에 있으면
						return 1;											//승리!
	return 0;
}

bool Map::CantMoveCheck()//You가 없는지 찾기.
{
	for (Object* t = head; t; t = t->GetNext())
		if (t->GetProperty() & YOU)		//YOU가 하나라도 있으면
			return false;				//false 반환
	return true;
}

void Map::LoseCheck()//You와 Lose가 같은 칸에 있는지 체크.
{
	Object* nex, * pre;
	for (Object* t = head; t; t = t->GetNext())
		if (t->GetProperty() & YOU)
			for (Object* pt = head; pt; pt = pt->GetNext())
				if ((pt->GetProperty() & LOSE)&& (t->GetX() == pt->GetX() && t->GetY() == pt->GetY()))
				{
					nex = t->GetNext();
					nex->SetPrev(t->GetPrev());
					pre = t->GetPrev();
					pre->SetNext(t->GetNext());
					delete t;
					t = pre;
					break;
				}
}

void Map::ChangeEntity()//링크드 리스트를 돌면서 non-text들의 Object::ChangeEntity 호출
{
	string str;
	for (Object* t = head; t; t = t->GetNext())
	{
		str = t->ToString();
		if ((str == "Baba" || str == "Rock") || (str == "Wall" || str == "Flag"))
			t = t->ChangeEntity();
	}
}

void Map::reset()//readmap에서 호출. Map의 모든 멤버 변수 초기화.
{
	Object* tt = head->GetPrev();
	delete tt;
	map = 0;
	s_map = 0;
	width = 0;
	height = 0;
	Object* ptr;
	for (Object* t = head; t;)
	{
		ptr = t->GetNext();
		delete(t);
		t = ptr;
	}
}