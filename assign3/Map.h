#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include"Object.h"
#include"Enum.h"
using namespace std;

class Map {
private:
	static int width, height; //맵의 너비와 높이
	static Object* head; //오브젝트들을 관리하는 링크트 리스트의 시작
	static string** s_map;//문장 출력을 위한 string 배열 text만 있음
	static int** map;//문장 이해와 처리를 위한 map text만 있음.
	Map() {}
public:
	static bool ReadMap(string str); //파일이름으로부터 맵 생성
	static void PrintMap(); //현재 맵을 출력
	static void PrintRules(); //존재하는 문장들을 출력
	static Object* GetHead(); //head 리턴
	static void SetHead(Object* obj); //head 설정
	static int GetWidth(); //width 리턴
	static int GetHeight(); //height 리턴
	static void YouMove(Direction dir); //YOU 개체들을 dir 방향으로 한칸 움직임
	static bool IsInBoundary(int x, int y); //주어진 x, y 좌표가 맵의 범위를 벗어나지 않는지 체크
	static void CheckRules(); //존재하는 문장들을 읽는다
	static bool WinCheck(); //YOU 개체가 WIN 개체와 같은 칸에 있는지 체크
	static bool CantMoveCheck(); //YOU 속성을 가진 개체가 있는지 체크
	static void LoseCheck(); //YOU 개체가 LOSE 개체와 같은 칸에 있으면 YOU 개체를 없앤다
	static void ChangeEntity(); //개체 IS 개체 문장 처리
	static void reset();
};

