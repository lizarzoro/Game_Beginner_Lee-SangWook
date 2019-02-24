#include <iostream>
#include <time.h>
#include <conio.h> // �ܼ�â���� ����� ��� �����ϴ� �������
// ������� ����� �ǽ�
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
		// ������ ���߾����� üũ
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
			cout << "���ڸ� ��� ������ϴ�." << endl;
			break;
		}
		cout << "w : �� s : �Ʒ� a : ���� d : ������ q : ����";
		char	cInput = _getch(); // �����Ѱ��� �Է¹���. ���� ĥ �ʿ����
		if (cInput == 'q' || cInput == 'Q')
			break;

		switch (cInput)
		{
		case 'w':
		case 'W' :
			//temp�� �̿��ؼ� �������ش�. �� ��쿡�� �ٷ� ���� ��ġ�� �ٲ۴�.
			if (iStarIndex > 4) // ���� ������ �ƴҶ����� �����ϵ��� ��
			{
				iNumber[iStarIndex] = iNumber[iStarIndex - 5];
				iNumber[iStarIndex - 5] = INT_MAX;
				iStarIndex -= 5;
			}
			break;
		case 's':
		case 'S':
			if (iStarIndex < 20) // ���� ������ �ƴҶ����� �����ϵ��� ��
			{
				iNumber[iStarIndex] = iNumber[iStarIndex + 5];
				iNumber[iStarIndex + 5] = INT_MAX;
				iStarIndex += 5;
			}
			break;
		case 'a':
		case 'A':
			if (iStarIndex %5 != 0) //���� ������ �ÿ��� �������� �ʵ��� �Ѵ�
			{
				iNumber[iStarIndex] = iNumber[iStarIndex - 1];
				iNumber[iStarIndex - 1] = INT_MAX;
				iStarIndex -= 1;
			}
			break;
		case 'd':
		case 'D':
			if (iStarIndex %5 != 4) //���� ������ �ÿ��� �������� �ʵ��� �Ѵ�
			{
				iNumber[iStarIndex] = iNumber[iStarIndex + 1];
				iNumber[iStarIndex + 1] = INT_MAX;
				iStarIndex += 1;
			}
			break;
		}

	}
	cout << "������ �����մϴ�." << endl;


	return 0;
}