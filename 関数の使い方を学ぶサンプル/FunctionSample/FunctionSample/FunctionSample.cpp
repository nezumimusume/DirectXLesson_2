// FunctionSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int main()
{
	int score[6];
	for (int i = 0; i < 6; i++) {
		std::cout << "あなたの成績を入力してください。";
		std::cin >> score[i] ;
		std::cout << "\n";
	}
	//平均を求める。
	int totalScore = 0;
	for (int i = 0; i < 6; i++) {
		totalScore += score[i];
	}
	std::cout << "平均点は" << totalScore / 6 << "です\n";
    return 0;
}

