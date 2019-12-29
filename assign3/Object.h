#pragma once
#include "Enum.h"
#include<iostream>
#include <string>

using namespace std;

class Object {
private:
	int x, y; //x, y ��ǥ
	Object* prev, * next; //���� ���� ���� ���
public:
	Object(int x = 0, int y = 0, Object * prev = nullptr, Object * next = nullptr); //�����ڴ� x, y��ǥ�� ���� ���� ���� ��带 �޴´�. �ڽ� Ŭ�����鵵 ��������
	void SetX(int x); //x��ǥ ����
	void SetY(int y); //y��ǥ ����
	int GetX(); //x��ǥ ����
	int GetY(); //y��ǥ ����
	Object* GetNext(); //���� ��� ����
	Object* GetPrev(); //���� ��� ���� �� ���ư��� ��
	void SetNext(Object* obj); //���� ��� ����
	void SetPrev(Object* obj); //���� ��� ����
	virtual bool Move(Direction dir) { return false; } //������Ʈ�� �� ĭ dir �������� (�̵��� �� �ִٸ�) �̵�
	virtual int GetProperty() { return PUSH; } //Non-Text�� Ŭ������ �ִ� property ���� ����
	virtual void YouMove(Direction dir) { return; } //Non-Text���� YOU �Ӽ��� ������ �ִٸ� dir �������� �̵� [���� üũ �� Object::Move�� ȣ���ϴ� ���� ����]
	virtual Object* ChangeEntity() { return false; } //Non-Text���� ���� property ������ ���� �ٸ� ��ü�� �ٲ��� �Ѵٸ� �ٲٴ� �۾��� ����
												//Object*�� �ٲ� ����: ���� Object�� delete�ϰ� �� Object �ּҸ� ��ȯ
	virtual string ToString() { return ""; }//������Ʈ�� ������ ���� �� �� ��µǴ� string�� �ٸ���
};

class Baba : public Object {
private:
public:
	static int property;
	Baba(int x, int y, Object* prev, Object* next);
	static void InitRule() { //�ʿ��� ������ �б� ���� ��� ������Ʈ�� �Ӽ��� �ʱ�ȭ �ؾ��Ѵ�.
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