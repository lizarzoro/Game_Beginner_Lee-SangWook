#include<iostream>
#include<time.h>

using namespace std;
//Lotto
int main() 
{
	int P1, P2, P3;
	int C1, C2, C3;
	int count = 1;
	int strike = 0;
	int ball = 0;

	srand((unsigned int)time(0));
	C1 = rand() % 9 + 1;
	C2 = rand() % 9 + 1;
	C3 = rand() % 9 + 1;

	cout << "숫자 야구 게임 시작" << endl;

	while (true)
	{
		cout << "1~9의 숫자를 입력하세요" << endl;
		cin >> P1;
		cin >> P2;
		cin >> P3;

		if (C1 == P1)
			strike++;
		else if (C1 == P2)
			ball++;
		else if (C1 == P3)
			ball++;
		if (C2 == P2)
			strike++;
		else if (C2 == P3)
			ball++;

		cout << "Strike" << strike << endl;
		cout << "Ball" << ball << endl;

		if (strike == 3)
			break; 

		count++;
	}
	//system("pause");
	return 0;
}
