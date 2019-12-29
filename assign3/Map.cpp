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
string** Map::s_map = 0;//static �������� ��� �ʱ�ȭ

bool Map::ReadMap(string str)//�� �о����
{
	ifstream in(str);
	if (!in)
		return false;//�����ϸ� �����ߴٰ� �˷��ְ�
	if(head != nullptr)
		reset();//�޾Ƶ� �����Ͱ� �ִٸ� ����

	head = new Object(-1, -1);
	string x = "";
	int line = 0;
	
	while (getline(in, x))
	{
		if (width == 0)
			width = x.length();

		if (width != x.length())//map�� width�� �������� ������ ������ �ν�
			return false;

		for (int i = 0; i < x.length(); i++)
			if (x[i] != ' ')
			{
				if (head->GetX() == -1)//��ũ�� ����Ʈ ù��°�϶�
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
						return false;//�ٸ� ���ڰ� ������ ������ �ν�
					delete(head);
					head = ptr;
					Object* tt = new Object(0, 0, head, NULL);
					head->SetNext(tt);//(tail->GetNext())->GetPrev()�� ������ ���� ����.
				}
				else//ù ��°�� �ƴ� ��
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
						return false;//�ٸ� ���ڰ� ������ ������ �ν�
					head->SetPrev(ptr);
					head = ptr;
				}
				//��ũ�� ����Ʈ �ϳ��� �߰��ϱ�.
			}
		line++;
	}
	height = line;
	map = NULL;
	s_map = NULL;
	Object* tt = new Object(0, 0, NULL, head);
	head->SetPrev(tt);//(head->prev)->GetNext�� ������ ���� ����.
	return true;
}

void Map::PrintMap() //�� ����ϴ� �Լ�
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
	cout << "+" << endl;							//������� �ؼ� Ʋ �����


	for (Object* t = head; t; t = t->GetNext())//gotoxy�Լ��� �̿��ؼ� �ʿ� ������Ʈ ä���.
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
	gotoxy(0, 3 * height + 5);//�׸��� ������ �̵��ؼ� ���� ����ϴ� �͵� ��ġ ����.
}



void Map::PrintRules()//�̸� ������ s_map�� �̿��� ���� �����ϴ� ����� ���
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

	for (int i = 0; i < height; i++)//������ ��� �� ����
		delete[](s_map[i]);
	delete[](s_map);
	for (int i = 0; i < height; i++)//�� ����
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

void Map::YouMove(Direction dir)//You Ư�� ���� ��� ã�Ƽ� Object::YouMove ȣ��
{
	int a, b;
	for (Object* t = head; t; t = t->GetNext())
		if (t->GetProperty() & YOU)
		{
			a = t->GetX();
			b = t->GetY();
			MoveXY(a, b, dir);
			if (IsInBoundary(a, b))//�갡 ������ �� ���� ��� ȣ��
				t->Move(dir);
		}
}

bool Map::IsInBoundary(int x, int y)//�� ������ ������ 0 ����.
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return 0;
	return 1;
}

void Map::CheckRules()	//s_map, map�� printrules���� �Ҵ� ����
{

	//////////�� �ʱ�ȭ�ϱ�
	Baba::InitRule();
	Rock::InitRule();
	Wall::InitRule();
	Flag::InitRule();

	s_map = new string * [height];						    //----�� ����----
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
	}//���� ���� ���� ���� ã��.

	for (Object* t = head; t; t = t->GetNext())//����� ��ĥ �� �����ϱ� ���� �� �ص� ��.
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
	}//�� ����� �Ϸ�

	
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
		}//�ʿ� �ִ� ����� ��� ã�Ƽ� property�� �����ϱ�.
}

bool Map::WinCheck()//you�� win�� ���� ������ �ִ��� ã��.
{
	for (Object* t = head; t; t = t->GetNext())
		if (t->GetProperty() & YOU)
			for (Object* pt = head; pt; pt = pt->GetNext())
				if (pt->GetProperty() & WIN)
					if (t->GetX() == pt->GetX() && t->GetY() == pt->GetY())	//YOU�� WIN�� ���� ������ ������
						return 1;											//�¸�!
	return 0;
}

bool Map::CantMoveCheck()//You�� ������ ã��.
{
	for (Object* t = head; t; t = t->GetNext())
		if (t->GetProperty() & YOU)		//YOU�� �ϳ��� ������
			return false;				//false ��ȯ
	return true;
}

void Map::LoseCheck()//You�� Lose�� ���� ĭ�� �ִ��� üũ.
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

void Map::ChangeEntity()//��ũ�� ����Ʈ�� ���鼭 non-text���� Object::ChangeEntity ȣ��
{
	string str;
	for (Object* t = head; t; t = t->GetNext())
	{
		str = t->ToString();
		if ((str == "Baba" || str == "Rock") || (str == "Wall" || str == "Flag"))
			t = t->ChangeEntity();
	}
}

void Map::reset()//readmap���� ȣ��. Map�� ��� ��� ���� �ʱ�ȭ.
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