#pragma once
#include "Enum.h"
#include<iostream>
#include <string>

using namespace std;

class Object {
private:
	int x, y; //x, y 좌표
	Object* prev, * next; //이전 노드와 다음 노드
public:
	Object(int x = 0, int y = 0, Object * prev = nullptr, Object * next = nullptr); //생성자는 x, y좌표와 이전 노드와 다음 노드를 받는다. 자식 클래스들도 마찬가지
	void SetX(int x); //x좌표 지정
	void SetY(int y); //y좌표 지정
	int GetX(); //x좌표 리턴
	int GetY(); //y좌표 리턴
	Object* GetNext(); //다음 노드 리턴
	Object* GetPrev(); //이전 노드 리턴 좀 돌아가라 씨
	void SetNext(Object* obj); //다음 노드 지정
	void SetPrev(Object* obj); //이전 노드 지정
	virtual bool Move(Direction dir) { return false; } //오브젝트가 한 칸 dir 방향으로 (이동할 수 있다면) 이동
	virtual int GetProperty() { return PUSH; } //Non-Text인 클래스에 있는 property 값을 리턴
	virtual void YouMove(Direction dir) { return; } //Non-Text에서 YOU 속성을 가지고 있다면 dir 방향으로 이동 [조건 체크 후 Object::Move를 호출하는 것을 권장]
	virtual Object* ChangeEntity() { return false; } //Non-Text에서 현재 property 변수를 보고 다른 개체로 바뀌어야 한다면 바꾸는 작업을 수행
												//Object*로 바꾼 이유: 기존 Object를 delete하고 새 Object 주소를 반환
	virtual string ToString() { return ""; }//오브젝트의 종류에 따라 맵 상에 출력되는 string이 다르다
};

class Baba : public Object {
private:
public:
	static int property;
	Baba(int x, int y, Object* prev, Object* next);
	static void InitRule() { //맵에서 문장을 읽기 전에 모든 오브젝트의 속성을 초기화 해야한다.
		property = NULL;
	}
	string ToString() { return "Baba"; }
	int GetProperty() { return property; }
	void YouMove(Direction dir);
	bool Move(Direction dir);
	Object* ChangeEntity();
};

class Rock : public Object {
private:
public:
	static int property;
	Rock(int x, int y, Object* prev, Object* next);
	static void InitRule() {
		property = NULL;
	}
	string ToString() { return "Rock"; }
	int GetProperty() { return property; }
	void YouMove(Direction dir);
	bool Move(Direction dir);
	Object* ChangeEntity();
};

class Wall : public Object {
private:
public:
	static int property;
	Wall(int x, int y, Object* prev, Object* next);
	static void InitRule() {
		property = NULL;
	}
	string ToString() { return "Wall"; }
	int GetProperty() { return property; }
	void YouMove(Direction dir);
	bool Move(Direction dir);
	Object* ChangeEntity();
};

class Flag : public Object {
private:
public:
	static int property;
	Flag(int x, int y, Object* prev, Object* next);
	static void InitRule() {
		property = NULL;
	}
	string ToString() { return "Flag"; }
	int GetProperty() { return property; }
	void YouMove(Direction dir);
	bool Move(Direction dir);
	Object* ChangeEntity();
};

class Text : public Object {
public:
	Text(int x, int y, Object* prev, Object* next);
	bool Move(Direction dir);
};

class Entity : public Text {
public:
	Entity(int x, int y, Object* prev, Object* next) : Text(x, y, prev, next) {}
};

class BabaText : public Entity {
public:
	BabaText(int x, int y, Object* prev, Object* next) : Entity(x, y, prev, next) {}
	string ToString() { return "BabaText"; }
};

class RockText : public Entity {
public:
	RockText(int x, int y, Object* prev, Object* next) : Entity(x, y, prev, next) {}
	string ToString() { return "RockText"; }
};

class WallText : public Entity {
public:
	WallText(int x, int y, Object* prev, Object* next) : Entity(x, y, prev, next) {}
	string ToString() { return "WallText"; }
};

class FlagText : public Entity {
public:
	FlagText(int x, int y, Object* prev, Object* next) : Entity(x, y, prev, next) {}
	string ToString() { return "FlagText"; }
};

class Is : public Text {
public:
	Is(int x, int y, Object* prev, Object* next) : Text(x, y, prev, next) {}
	string ToString() { return "Is"; }
};

class Property : public Text {
public:
	Property(int x, int y, Object* prev, Object* next) : Text(x, y, prev, next) {}
};

class You : public Property {
public:
	You(int x, int y, Object* prev, Object* next) : Property(x, y, prev, next) {}
	string ToString() { return "You"; }
};

class Win : public Property {
public:
	Win(int x, int y, Object* prev, Object* next) : Property(x, y, prev, next) {}
	string ToString() { return "Win"; }
};

class Stop : public Property {
public:
	Stop(int x, int y, Object* prev, Object* next) : Property(x, y, prev, next) {}
	string ToString() { return "Stop"; }
};

class Push : public Property {
public:
	Push(int x, int y, Object* prev, Object* next) : Property(x, y, prev, next) {}
	string ToString() { return "Push"; }
};

class Lose : public Property {
public:
	Lose(int x, int y, Object* prev, Object* next) : Property(x, y, prev, next) {}
	string ToString() { return "Lose"; }
};