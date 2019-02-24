#include <iostream>
#include <time.h>
#include <conio.h> // �ܼ�â���� ����� ��� �����ϴ� �������
/*
������� ����� �ǽ�1
*/
using namespace std;
// �����鿡�� 1���� �迭�� ���� ���� �� �ִ�. 2������ ū ���̴� ����.
// ��ü ��ȸ �� �� 2�����迭�� 2�� for���� ����ؾ� ��

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

	// ���� 1~25 �־���
	for (int i = 0; i < 25; ++i)
	{
		iNumber[i] = i + 1;
		iAINumber[i] = i + 1;
	}

	// ���� ������
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
		cout << "AI ��� ���� : ";
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

		//���� 5x5
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
		cout << "���ڸ� �Է��Ͻÿ�(0 : ����) : ";
		int iInput;
		cin >> iInput;

		// ����ó���� ���� ������ �ʼ�
		if (iInput == 0)
			break;

		else if (iInput < 1 || iInput > 25)
			continue;
		//�ߺ� üũ
		bool bAcc = true;

		// ��� ���ڸ� ���ʴ�� �˻��ؼ� �Է��� ���ڿ� ���� �� �ִ��� 
		for (int i = 0; i < 25; ++i)
		{
			if (iInput == iNumber[i])
			{
				// ���ڸ� ã���� ��� �ߺ� ���ڰ� �ƴϹǷ� ���� false
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

		// ���� 5�� ���� �־�� ����
		//iStar1 = ����
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