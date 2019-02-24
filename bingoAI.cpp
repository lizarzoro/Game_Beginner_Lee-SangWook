#include <iostream>
#include <time.h>
#include <conio.h> // 콘솔창에서 입출력 기능 제공하는 헤더파일
/*
빙고게임 만들기 실습1
*/
using namespace std;
// 관리면에서 1차원 배열이 조금 나을 수 있다. 2차원과 큰 차이는 없다.
// 전체 순회 할 때 2차원배열은 2중 for문을 사용해야 함

enum AI_MODE
{
	AM_EASY = 1,
	AM_HARD
};
int main()
{
	srand((unsigned int)time(0));

	int iNumber[25] = {};
	int iAINumber[25] = {};

	// 숫자 1~25 넣어줌
	for (int i = 0; i < 25; ++i)
	{
		iNumber[i] = i + 1;
		iAINumber[i] = i + 1;
	}

	// 숫자 섞어줌
	int iTemp, idx1, idx2;
	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;

		idx1 = rand() % 25;
		idx2 = rand() % 25;
		iTemp = iAINumber[idx1];
		iAINumber[idx1] = iAINumber[idx2];
		iAINumber[idx2] = iTemp;
	}
	int iBingo = 0;
	int iAIBingo = 0;
	int iAIMode;

	while (true)
	{
		system("cls");
		cout << "1. EASY" << endl;
		cout << "2. Hard" << endl;
		cout << "AI 모드 선택 : ";
		cin >> iAIMode;

		if (iAIMode >= AM_EASY || iAIMode <= AM_HARD)
			break;
	}

	--iAIMode;
	int iNoneSelect[25] = {};
	int iNoneSelectCount = 0;

	while (true)
	{
		system("cls");
		cout << "=================Player===============" << endl;

		//숫자 5x5
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

		cout << "Bingo : " << iBingo << endl << endl;

		cout << "=================AI===============" << endl;

		switch (iAIMode)
		{
		case AM_EASY:
			cout << "AIMode : Easy" << endl;
			break;
		case AM_HARD:
			cout << "AIMode : Hard" << endl;
			break;
		}
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (iAINumber[i * 5 + j] == INT_MAX)
					cout << "*\t";

				else
					cout << iAINumber[i * 5 + j] << "\t";
			}

			cout << endl;
		}

		cout << "AIBingo : " << iAIBingo << endl;
		if (iBingo >= 5)
			break;
		cout << "숫자를 입력하시오(0 : 종료) : ";
		int iInput;
		cin >> iInput;

		// 예외처리에 대한 문장은 필수
		if (iInput == 0)
			break;

		else if (iInput < 1 || iInput > 25)
			continue;
		//중복 체크
		bool bAcc = true;

		// 모든 숫자를 차례대로 검사해서 입력한 숫자와 같은 수 있는지 
		for (int i = 0; i < 25; ++i)
		{
			if (iInput == iNumber[i])
			{
				// 숫자를 찾았을 경우 중복 숫자가 아니므로 변수 false
				bAcc = false;

				iNumber[i] = INT_MAX;
				break;
			}
		}
		/*
		if (bAcc)
			continue;
			*/
		switch (iAIMode) {
		case AM_EASY:
			iNoneSelectCount = 0;
			for (int i = 0; i < 25; ++i)
			{
				if (iAINumber[i] != INT_MAX)
				{
					iNoneSelect[iNoneSelectCount] = iAINumber[i];
					++iNoneSelectCount;
				}
			}
			iInput = iNoneSelect[rand() % iNoneSelectCount];
				break;
		case AM_HARD:
				break;
		}

		for (int i = 0; i < 25; ++i)
		{
			if (iNumber[i] = iInput)
			{
				iNumber[i] = INT_MAX;
				break;
			}
		}

		for (int i = 0; i < 25; ++i)
		{
			if (iAINumber[i] = iInput)
			{
				iAINumber[i] = INT_MAX;
				break;
			}
		}
		iBingo = 0;

		// 별이 5개 연속 있어야 빙고
		//iStar1 = 가로
		int iStar1 = 0, iStar2 = 0;
		for (int i = 0; i < 5; ++i)
		{
			iStar1 = iStar2 = 0;
			for (int j = 0; j < 5; ++j)
			{
				if (iNumber[i * 5 + j] == INT_MAX)
					++iStar1;

				if (iNumber[j * 5 + i] == INT_MAX)
					++iStar2;
			}

			if (iStar1 == 5)
				++iBingo;

			if (iStar2 == 5)
				++iBingo;
		}

		iStar1 = 0;
		for (int i = 0; i < 25; i += 6)
		{
			if (iNumber[i] == INT_MAX)
				++iStar1;
		}
		if (iStar1 == 5)
			++iBingo;

		iStar1 = 0;
		for (int i = 4; i <= 20; i += 4)
		{
			if (iNumber[i] == INT_MAX)
				++iStar1;
		}
		if (iStar1 == 5)
			++iBingo;
	}

	return 0;
}