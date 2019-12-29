#include<iostream>
#include<string>
#include"Object.h"
#include"Enum.h"
#include"Map.h"
using namespace std;

int Baba::property = 0;
int Rock::property = 0;
int Wall::property = 0;
int Flag::property = 0;//static �������� ��� �ʱ�ȭ

Object::Object(int x, int y, Object* prev, Object* next)
{
	this->x = x;
	this->y = y;
	this->prev = prev;
	this->next = next;
}

void Object::SetX(int x)
{
	this->x = x;
}

void Object::SetY(int y)
{
	this->y = y;
}

int Object::GetX()
{
	return this->x;
}

int Object::GetY()
{
	return this->y;
}

Object* Object::GetNext()
{
	return this->next;
}

Object* Object::GetPrev()
{
	return this->prev;
}

void Object::SetNext(Object* obj)
{
	this->next = obj;
}

void Object::SetPrev(Object* obj)
{
	this->prev = obj;
}
/////////////////////////////////////������� ���� �Լ�///////////////////////////////////////////////////////////
////////////////////////////////////////////////1. Baba

Baba::Baba(int x, int y, Object* prev, Object* next) : Object(x, y, prev, next) {}

void Baba::YouMove(Direction dir)//You Ư���� ������ ������ Move �Լ� ȣ��
{
	if (property & YOU)
		Move(dir);
}

bool Baba::Move(Direction dir)	//push �Ǵ� stop ����ϱ�
{								//�����̸� 1, �� �����̸� 0 ��ȯ
	int x = this->GetX();
	int y = this->GetY();

	MoveXY(x, y, dir);
	if (!(Map::IsInBoundary(x, y)))	//���� �� ������ �����̷� ������
		return 0;					//�翬�� �ȵ���!

	for (Object* t = Map::GetHead(); t; t = t->GetNext())//��ũ�� ����Ʈ�� �����鼭
		if (t->GetX() == x && t->GetY() == y)				//�����̷��� �ڸ��� ���� ������
			if (t->GetProperty() & STOP)					//STOP�̸�
				return false;								//�� �����̹Ƿ� 0 ��ȯ
			else if (t->GetProperty() & PUSH)				//PUSH��
				if (!(t->Move(dir)))						//������ �� �ִ��� ���� ������ �� ������
					return false;
	SetX(x);
	SetY(y);
	return true;
}

Object* Baba::ChangeEntity()
{
	Object* nex, * pre;
	if (property & BABA)//��Ģ 3�� ���� ������ ����
		return this;
	if (property & ROCK)//�װ� �ƴϸ� ��Ģ 2 ����.
	{
		int x = this->GetX();
		int y = this->GetY();
		pre = this->GetPrev();
		nex = this->GetNext();
		delete this;

		Object* ptr = new Rock(x, y, pre, nex);
		pre->SetNext(ptr);
		nex->SetPrev(ptr);
		return ptr;
	}
	else if (property & WALL)
	{
		int x = this->GetX();
		int y = this->GetY();
		pre = this->GetPrev();
		nex = this->GetNext();
		delete this;

		Object* ptr = new Wall(x, y, pre, nex);
		pre->SetNext(ptr);
		nex->SetPrev(ptr);
		return ptr;
	}
	else if (property & FLAG)
	{
		int x = this->GetX();
		int y = this->GetY();
		pre = this->GetPrev();
		nex = this->GetNext();
		delete this;

		Object* ptr = new Flag(x, y, pre, nex);
		pre->SetNext(ptr);
		nex->SetPrev(ptr);;
		return ptr;
	}
	return this;
}
////////////////////////////////////////////////////////2. ROCK
Rock::Rock(int x, int y, Object* prev, Object* next) : Object(x, y, prev, next) {}

void Rock::YouMove(Direction dir)
{
	if (property & YOU)
		Move(dir);
}

bool Rock::Move(Direction dir)	//push �Ǵ� stop ����ϱ�
{								//�����̸� 1, �� �����̸� 0 ��ȯ
	int x = this->GetX();
	int y = this->GetY();

	MoveXY(x, y, dir);
	if (!(Map::IsInBoundary(x, y)))	//���� �� ������ �����̷� ������
		return 0;					//�翬�� �ȵ���!

	for (Object* t = Map::GetHead(); t; t = t->GetNext())//��ũ�� ����Ʈ�� �����鼭
		if (t->GetX() == x && t->GetY() == y)				//�����̷��� �ڸ��� ���� ������
			if (t->GetProperty() & STOP)			//STOP�̸�
				return false;							//�� �����̹Ƿ� 0 ��ȯ
			else if (t->GetProperty() & PUSH)			//PUSH��
				if (!(t->Move(dir)))						//������ �� �ִ��� ���� ������ �� ������
					return false;
	SetX(x);
	SetY(y);
	return true;
}

Object* Rock::ChangeEntity()
{
	Object* nex, * pre;
	if (property & ROCK)//��Ģ 3�� ���� ������ ����
		return this;
	if (property & BABA)//�װ� �ƴϸ� ��Ģ 2 ����.
	{
		int x = this->GetX();
		int y = this->GetY();
		pre = this->GetPrev();
		nex = this->GetNext();
		delete this;

		Object* ptr = new Baba(x, y, pre, nex);
		pre->SetNext(ptr);
		nex->SetPrev(ptr);
		return ptr;
	}
	else if (property & WALL)
	{
		int x = this->GetX();
		int y = this->GetY();
		pre = this->GetPrev();
		nex = this->GetNext();
		delete this;

		Object* ptr = new Wall(x, y, pre, nex);
		pre->SetNext(ptr);
		nex->SetPrev(ptr);
		return ptr;
	}
	else if (property & FLAG)
	{
		int x = this->GetX();
		int y = this->GetY();
		pre = this->GetPrev();
		nex = this->GetNext();
		delete this;

		Object* ptr = new Flag(x, y, pre, nex);
		pre->SetNext(ptr);
		nex->SetPrev(ptr);
		return ptr;
	}
	return this;
}

////////////////////////////////////////////////////////3. WALL
Wall::Wall(int x, int y, Object* prev, Object* next) : Object(x, y, prev, next) {}

void Wall::YouMove(Direction dir)
{
	if (property & YOU)
		Move(dir);
}

bool Wall::Move(Direction dir)	//push �Ǵ� stop ����ϱ�
{								//�����̸� 1, �� �����̸� 0 ��ȯ
	int x = this->GetX();
	int y = this->GetY();

	MoveXY(x, y, dir);
	if (!(Map::IsInBoundary(x, y)))	//���� �� ������ �����̷� ������
		return 0;					//�翬�� �ȵ���!

	for (Object* t = Map::GetHead(); t; t = t->GetNext())//��ũ�� ����Ʈ�� �����鼭
		if (t->GetX() == x && t->GetY() == y)				//�����̷��� �ڸ��� ���� ������
			if (t->GetProperty() & STOP)			//STOP�̸�
				return false;							//�� �����̹Ƿ� 0 ��ȯ
			else if (t->GetProperty() & PUSH)			//PUSH��
				if (!(t->Move(dir)))						//������ �� �ִ��� ���� ������ �� ������
					return false;
	SetX(x);
	SetY(y);
	return true;
}

Object* Wall::ChangeEntity()
{
	Object* nex, * pre;
	if (property & WALL)//��Ģ 3�� ���� ������ ����
		return this;
	if (property & BABA)//�װ� �ƴϸ� ��Ģ 2 ����.
	{
		int x = this->GetX();
		int y = this->GetY();
		pre = this->GetPrev();
		nex = this->GetNext();
		delete this;

		Object* ptr = new Baba(x, y, pre, nex);
		pre->SetNext(ptr);
		nex->SetPrev(ptr);
		return ptr;
	}
	else if (property & ROCK)
	{
		int x = this->GetX();
		int y = this->GetY();
		pre = this->GetPrev();
		nex = this->GetNext();
		delete this;

		Object* ptr = new Rock(x, y, pre, nex);
		pre->SetNext(ptr);
		nex->SetPrev(ptr);
		return ptr;
	}
	else if (property & FLAG)
	{
		int x = this->GetX();
		int y = this->GetY();
		pre = this->GetPrev();
		nex = this->GetNext();
		delete this;

		Object* ptr = new Flag(x, y, pre, nex);
		pre->SetNext(ptr);
		nex->SetPrev(ptr);
		return ptr;
	}
	return this;
}

////////////////////////////////////////////////////////4. FLAG
Flag::Flag(int x, int y, Object* prev, Object* next) : Object(x, y, prev, next) {}

void Flag::YouMove(Direction dir)
{
	if (property & YOU)
		Move(dir);
}

bool Flag::Move(Direction dir)	//push �Ǵ� stop ����ϱ�
{								//�����̸� 1, �� �����̸� 0 ��ȯ
	int x = this->GetX();
	int y = this->GetY();

	MoveXY(x, y, dir);
	if (!(Map::IsInBoundary(x, y)))	//���� �� ������ �����̷� ������
		return 0;					//�翬�� �ȵ���!

	for (Object* t = Map::GetHead(); t; t = t->GetNext())//��ũ�� ����Ʈ�� �����鼭
		if (t->GetX() == x && t->GetY() == y)				//�����̷��� �ڸ��� ���� ������
			if (t->GetProperty() & STOP)			//STOP�̸�
				return false;							//�� �����̹Ƿ� 0 ��ȯ
			else if (t->GetProperty() & PUSH)			//PUSH��
				if (!(t->Move(dir)))						//������ �� �ִ��� ���� ������ �� ������
					return false;
	SetX(x);
	SetY(y);
	return true;
}

Object* Flag::ChangeEntity()
{
	Object* nex, * pre;
	if (property & FLAG)//��Ģ 3�� ���� ������ ����
		return this;
	if (property & BABA)//�װ� �ƴϸ� ��Ģ 2 ����.
	{
		int x = this->GetX();
		int y = this->GetY();
		pre = this->GetPrev();
		nex = this->GetNext();
		delete this;

		Object* ptr = new Baba(x, y, pre, nex);
		pre->SetNext(ptr);
		nex->SetPrev(ptr);
		return ptr;
	}
	else if (property & ROCK)
	{
		int x = this->GetX();
		int y = this->GetY();
		pre = this->GetPrev();
		nex = this->GetNext();
		delete this;

		Object* ptr = new Rock(x, y, pre, nex);
		pre->SetNext(ptr);
		nex->SetPrev(ptr);
		return ptr;
	}
	else if (property & WALL)
	{
		int x = this->GetX();
		int y = this->GetY();
		pre = this->GetPrev();
		nex = this->GetNext();
		delete this;

		Object* ptr = new Wall(x, y, pre, nex);
		pre->SetNext(ptr);
		nex->SetPrev(ptr);
		return ptr;
	}
	return this;
}
//////////////////////////////////////////////////////5. Text

Text::Text(int x, int y, Object* prev, Object* next) : Object(x, y, prev, next) {}

bool Text::Move(Direction dir)	//push �Ǵ� stop ����ϱ�
{								//�����̸� 1, �� �����̸� 0 ��ȯ
	int x = this->GetX();
	int y = this->GetY();

	MoveXY(x, y, dir);
	if (!(Map::IsInBoundary(x, y)))	//���� �� ������ �����̷� ������
		return 0;					//�翬�� �ȵ���!

	for (Object* t = Map::GetHead(); t; t = t->GetNext())//��ũ�� ����Ʈ�� �����鼭
		if (t->GetX() == x && t->GetY() == y)				//�����̷��� �ڸ��� ���� ������
			if (t->GetProperty() & STOP)			//STOP�̸�
				return false;							//�� �����̹Ƿ� 0 ��ȯ
			else if (t->GetProperty() & PUSH)			//PUSH��
				if (!(t->Move(dir)))					//������ �� �ִ��� ���� ������ �� ������
					return false;
	SetX(x);
	SetY(y);
	return true;
}