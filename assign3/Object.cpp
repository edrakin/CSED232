#include<iostream>
#include<string>
#include"Object.h"
#include"Enum.h"
#include"Map.h"
using namespace std;

int Baba::property = 0;
int Rock::property = 0;
int Wall::property = 0;
int Flag::property = 0;//static 변수들은 모두 초기화

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
/////////////////////////////////////여기까진 공용 함수///////////////////////////////////////////////////////////
////////////////////////////////////////////////1. Baba

Baba::Baba(int x, int y, Object* prev, Object* next) : Object(x, y, prev, next) {}

void Baba::YouMove(Direction dir)//You 특성을 가지고 있으면 Move 함수 호출
{
	if (property & YOU)
		Move(dir);
}

bool Baba::Move(Direction dir)	//push 또는 stop 고려하기
{								//움직이면 1, 못 움직이면 0 반환
	int x = this->GetX();
	int y = this->GetY();

	MoveXY(x, y, dir);
	if (!(Map::IsInBoundary(x, y)))	//만약 맵 밖으로 움직이려 했으면
		return 0;					//당연히 안되지!

	for (Object* t = Map::GetHead(); t; t = t->GetNext())//링크드 리스트를 돌리면서
		if (t->GetX() == x && t->GetY() == y)				//움직이려는 자리에 뭔가 있으면
			if (t->GetProperty() & STOP)					//STOP이면
				return false;								//못 움직이므로 0 반환
			else if (t->GetProperty() & PUSH)				//PUSH면
				if (!(t->Move(dir)))						//움직일 수 있는지 보고 움직일 수 있으면
					return false;
	SetX(x);
	SetY(y);
	return true;
}

Object* Baba::ChangeEntity()
{
	Object* nex, * pre;
	if (property & BABA)//규칙 3에 의해 변하지 않음
		return this;
	if (property & ROCK)//그게 아니면 규칙 2 적용.
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

bool Rock::Move(Direction dir)	//push 또는 stop 고려하기
{								//움직이면 1, 못 움직이면 0 반환
	int x = this->GetX();
	int y = this->GetY();

	MoveXY(x, y, dir);
	if (!(Map::IsInBoundary(x, y)))	//만약 맵 밖으로 움직이려 했으면
		return 0;					//당연히 안되지!

	for (Object* t = Map::GetHead(); t; t = t->GetNext())//링크드 리스트를 돌리면서
		if (t->GetX() == x && t->GetY() == y)				//움직이려는 자리에 뭔가 있으면
			if (t->GetProperty() & STOP)			//STOP이면
				return false;							//못 움직이므로 0 반환
			else if (t->GetProperty() & PUSH)			//PUSH면
				if (!(t->Move(dir)))						//움직일 수 있는지 보고 움직일 수 있으면
					return false;
	SetX(x);
	SetY(y);
	return true;
}

Object* Rock::ChangeEntity()
{
	Object* nex, * pre;
	if (property & ROCK)//규칙 3에 의해 변하지 않음
		return this;
	if (property & BABA)//그게 아니면 규칙 2 적용.
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

bool Wall::Move(Direction dir)	//push 또는 stop 고려하기
{								//움직이면 1, 못 움직이면 0 반환
	int x = this->GetX();
	int y = this->GetY();

	MoveXY(x, y, dir);
	if (!(Map::IsInBoundary(x, y)))	//만약 맵 밖으로 움직이려 했으면
		return 0;					//당연히 안되지!

	for (Object* t = Map::GetHead(); t; t = t->GetNext())//링크드 리스트를 돌리면서
		if (t->GetX() == x && t->GetY() == y)				//움직이려는 자리에 뭔가 있으면
			if (t->GetProperty() & STOP)			//STOP이면
				return false;							//못 움직이므로 0 반환
			else if (t->GetProperty() & PUSH)			//PUSH면
				if (!(t->Move(dir)))						//움직일 수 있는지 보고 움직일 수 있으면
					return false;
	SetX(x);
	SetY(y);
	return true;
}

Object* Wall::ChangeEntity()
{
	Object* nex, * pre;
	if (property & WALL)//규칙 3에 의해 변하지 않음
		return this;
	if (property & BABA)//그게 아니면 규칙 2 적용.
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

bool Flag::Move(Direction dir)	//push 또는 stop 고려하기
{								//움직이면 1, 못 움직이면 0 반환
	int x = this->GetX();
	int y = this->GetY();

	MoveXY(x, y, dir);
	if (!(Map::IsInBoundary(x, y)))	//만약 맵 밖으로 움직이려 했으면
		return 0;					//당연히 안되지!

	for (Object* t = Map::GetHead(); t; t = t->GetNext())//링크드 리스트를 돌리면서
		if (t->GetX() == x && t->GetY() == y)				//움직이려는 자리에 뭔가 있으면
			if (t->GetProperty() & STOP)			//STOP이면
				return false;							//못 움직이므로 0 반환
			else if (t->GetProperty() & PUSH)			//PUSH면
				if (!(t->Move(dir)))						//움직일 수 있는지 보고 움직일 수 있으면
					return false;
	SetX(x);
	SetY(y);
	return true;
}

Object* Flag::ChangeEntity()
{
	Object* nex, * pre;
	if (property & FLAG)//규칙 3에 의해 변하지 않음
		return this;
	if (property & BABA)//그게 아니면 규칙 2 적용.
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

bool Text::Move(Direction dir)	//push 또는 stop 고려하기
{								//움직이면 1, 못 움직이면 0 반환
	int x = this->GetX();
	int y = this->GetY();

	MoveXY(x, y, dir);
	if (!(Map::IsInBoundary(x, y)))	//만약 맵 밖으로 움직이려 했으면
		return 0;					//당연히 안되지!

	for (Object* t = Map::GetHead(); t; t = t->GetNext())//링크드 리스트를 돌리면서
		if (t->GetX() == x && t->GetY() == y)				//움직이려는 자리에 뭔가 있으면
			if (t->GetProperty() & STOP)			//STOP이면
				return false;							//못 움직이므로 0 반환
			else if (t->GetProperty() & PUSH)			//PUSH면
				if (!(t->Move(dir)))					//움직일 수 있는지 보고 움직일 수 있으면
					return false;
	SetX(x);
	SetY(y);
	return true;
}