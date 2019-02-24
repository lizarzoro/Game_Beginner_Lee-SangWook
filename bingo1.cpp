#include <iostream>
#include <time.h>
#include <conio.h> // �ܼ�â���� ����� ��� �����ϴ� �������
/*
������� ����� �ǽ�1
*/
using namespace std;
// �����鿡�� 1���� �迭�� ���� ���� �� �ִ�. 2������ ū ���̴� ����.
// ��ü ��ȸ �� �� 2�����迭�� 2�� for���� ����ؾ� ��
int main()
{
	srand((unsigned int)time(0));

	int iNumber[25] = {};

	// ���� 1~25 �־���
	for (int i = 0; i < 25; ++i)
	{
		iNumber[i] = i + 1;
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
	}
	int iBingo = 0;

	while (true)
	{
		system("cls");

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
		
		cout << "Bingo : " << iBingo << endl;

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
		if (bAcc)
			continue;
		
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