#include <iostream>
#include <time.h>
#include <conio.h> // 콘솔창에서 입출력 기능 제공하는 헤더파일
// 퍼즐게임 만들기 실습
using namespace std;

int main()
{
	srand((unsigned int)time(0));

	int iNumber[25] = {};

	for (int i = 0; i < 24; ++i)
	{
		iNumber[i] = i + 1;
	}
	iNumber[24] = INT_MAX;

	int iStarIndex = 24;

	int iTemp, idx1, idx2;

	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 24;
		idx2 = rand() % 24;
	
		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;
	}

	while (true)
	{
		system("cls");


		for (int i = 0; i < 25; ++i)
		{
			cout << iNumber[i] << endl;
		}

		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (iNumber[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else
					cout << iNumber[i * 5 + j] << "\t";
			}

			cout << endl;
		}
		bool bWin = true;
		// 퍼즐을 맞추었는지 체크
		for (int i = 0; i < 24; ++i)
		{
			if (iNumber[i] != i + 1)
			{
				bWin = false;
				break;
			}
		}

		if (bWin == true)
		{
			cout << "숫자를 모두 맞췄습니다." << endl;
			break;
		}
		cout << "w : 위 s : 아래 a : 왼쪽 d : 오른쪽 q : 종료";
		char	cInput = _getch(); // 문자한개를 입력받음. 엔터 칠 필요없다
		if (cInput == 'q' || cInput == 'Q')
			break;

		switch (cInput)
		{
		case 'w':
		case 'W' :
			//temp를 이용해서 스왑해준다. 이 경우에는 바로 위와 위치를 바꾼다.
			if (iStarIndex > 4) // 가장 윗줄이 아닐때에만 동작하도록 함
			{
				iNumber[iStarIndex] = iNumber[iStarIndex - 5];
				iNumber[iStarIndex - 5] = INT_MAX;
				iStarIndex -= 5;
			}
			break;
		case 's':
		case 'S':
			if (iStarIndex < 20) // 가장 윗줄이 아닐때에만 동작하도록 함
			{
				iNumber[iStarIndex] = iNumber[iStarIndex + 5];
				iNumber[iStarIndex + 5] = INT_MAX;
				iStarIndex += 5;
			}
			break;
		case 'a':
		case 'A':
			if (iStarIndex %5 != 0) //가장 왼쪽일 시에는 동작하지 않도록 한다
			{
				iNumber[iStarIndex] = iNumber[iStarIndex - 1];
				iNumber[iStarIndex - 1] = INT_MAX;
				iStarIndex -= 1;
			}
			break;
		case 'd':
		case 'D':
			if (iStarIndex %5 != 4) //가장 왼쪽일 시에는 동작하지 않도록 한다
			{
				iNumber[iStarIndex] = iNumber[iStarIndex + 1];
				iNumber[iStarIndex + 1] = INT_MAX;
				iStarIndex += 1;
			}
			break;
		}

	}
	cout << "게임을 종료합니다." << endl;


	return 0;
}