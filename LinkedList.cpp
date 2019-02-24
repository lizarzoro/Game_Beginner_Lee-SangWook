#pragma once

//���� ó��
#include <assert.h>

//��带 Ŭ������ ����� ���� : �ϳ��� ������ ����ġ�� ó���� �� �ִ�. ���� ��带 �ܺο��� �����ؼ� �־��� �ʿ����.
template <typename T>
class CListNode
{
	//���� �Ҹ��ڸ� private�� ����� �ܺο��� ��� Ŭ������ �����ϱ� ���� ������ �����ϸ� ���� ��
private:
	//teplate class�� friend ó�� �ϱ� ����
	template <typename T>
	friend class CLinkedList;
	//CListNode�� private�� protected�� ���� ����

	CListNode()
	{
		m_pNext = nullptr; // �����ͺ��� �ʱ�ȭ
		m_pPrev = nullptr; // �����ͺ��� �ʱ�ȭ
	}
	~CListNode()
	{

	}
private:
	T	m_Data; // ���� �����͸� �����ϴ� ����
				//������ ���� ����� �ּҸ� �����ϱ� ���� ����
	CListNode<T>* m_pNext;
	CListNode<T>* m_pPrev;
};
template <typename T>
class CLinkedList
{
public:

	CLinkedList()
	{
		//���۰� �� �����ڿ��� ���� �Ҵ�
		m_pBegin = new NODE;
		m_pEnd = new NODE;

		//ó������ �߰��� ��尡 �����Ƿ� Begin�� ���� ��带 End��, End�� �������� Begin�� ����
		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;
	}

	~CLinkedList()
	{
		//�Ҵ�� �޸𸮴� �Ҹ��ڿ��� �ڵ����� ������ �� �ְ� �����
		clear(); //begin�� end��� ������ ��� ��� ����
		delete m_pBegin;
		delete m_pEnd;
	}
private:
	//���� ������ ���Ǽ��� ����
	typedef CListNode<T>	NODE;
	typedef CListNode<T>*	PNODE;

private:
	PNODE	m_pBegin;
	PNODE	m_pEnd; // �ݵ�� �����ؾ� �ؼ� �����ڿ��� ���� �Ҵ�
					//PNODE	m_pData;
	int		m_iSize; // ��尡 ��� �߰��Ǿ�����. ÷���� 0���� �ʱ�ȭ

public:
	void push_back(const T& data) //���۷����� ����. ���纸�� ���� �ӵ��� ���� ó�� ����.
								  //�����ϴ� ����� ���� �������� ���ϰ� �ϱ� ���� const ���
	{
		PNODE	pNode = new NODE;
		pNode->m_Data = data; //���� ������ �Է�
							  //�ڿ� �߰��� �ؾ� �ϹǷ� end�� ���� ��带 ���´�
		PNODE	pPrev = m_pEnd->m_pPrev;

		//���� ���� ���� end��� ���̿� ���� ������ ��带 �߰��Ѵ�.
		pPrev->m_pNext = pNode;
		pNode->m_pPrev = pPrev;

		//end ��忡 ���� ������ ��带 �����Ѵ�.
		pNode->m_pNext = m_pEnd; //���� ������ ����� ���� ��带 end�� ����
		m_pEnd->m_pPrev = pNode; //end�� ���� ��带 ���� ������ ���� �߰�

		++m_iSize; //��尡 �ϳ� �߰���� ������ ������ ��

	}
	//���ο� ��带 �տ� �߰�
	void push_front(const T& data)
	{
		PNODE	pNode = new NODE;
		pNOde->m_Data = data;

		//begin�� begin���̿� ���� ������ ��带 �߰��Ѵ�.
		PNODE	pNext = m_pBegin->m_pNext;
		//���λ����� ����� �������� begin�� ������带 �ش�
		pNode->m_pNext = pNext;
		pNext->m_pPrev = pNode;

		//begin�� ���� ���� ���� ������ ��带 �ش� / ���� ������ ����� ���� ���� begin�� �ش�
		m_pBegin->m_pNext = pNode;
		pNode->m_pPrev = m_pBegin;

		++m_iSize;
	}

	void pop_back() //���� ������ ��带 �����ֱ⸸ �ϱ� ������ ���ڸ� ���� �ʿ����
	{
		if (empty())// �� �̻� ����� ���� ���
			assert(false); // ���� �޽��� �߻�

						   //���� ������ ��带 ������ �ϱ� ������ end ����� ���� ��带 �����´�
		PNODE pDeleteNode = m_pEnd->m_pPrev;

		//���� ����� ���� ��嵵 ���;� �Ѵ�
		PNODE pPrev = pDeleteNode->m_pPrev;

		//��������� �������� end��带 �ְ� end����� ������ ������带 �ش�
		pPrev->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pPrev;

		//���� ��带 �����ش�
		delete pDeleteNode;

		--m_iSize; //������ 1 ����
	}

	void pop_front() // ���� �߰��� �� �� ��带 �����ϴ� ���
	{
		if (empty())// �� �̻� ����� ���� ���
			assert(false); // ���� �޽��� �߻�

		PNODE pDeleteNode = m_pBegin->m_pNext; //���� ��带 �����´�

											   //���� ����� ���� ��带 ������ begin�� ���� ��带 �������ش�
		PNODE pNext = pDeleteNode->m_pNext;

		pNext->m_pPrev = m_pBegin;
		m_pBegin->m_pNext = pNext;

		delete pDeleteNode;

		--m_iSize;
	}

	T front() const //�� ���� �����͸� ��ȯ�ϴ� ���
	{
		if (empty())// �� �̻� ���� �� ���� ���
			assert(false); // ���� �޽��� �߻�

		return m_pBegin->m_pNext->m_Data;
	}

	T back() const //�� ���� �����͸� ��ȯ�ϴ� ���
	{
		if (empty())// �� �̻� ���� �� ���� ���
			assert(false); // ���� �޽��� �߻�

		return m_pEnd->m_pPrev->m_Data;
	}

	//begin�� end�� ������ ���� �߰��� ��带 �����ϴ� ��� clear
	void clear()
	{
		PNODE	pNode = m_pBegin->m_pNext;

		//���� �߰��� ��常 �ݺ��ؼ� �湮
		while (pNode != m_pEnd)
		{
			PNODE pNext = pNode->m_pNext; //���� ����� ���� ��带 ���´�
			delete pNode;//���� ��带 �޾ƿ����� ���� ���� ��带 �����ش�.
			pNode = pNext;//pNode�� ���� ����� �ּҸ� �־��ش�
		}
		m_iSize = 0;
		//begin�� end�� ���� �������ش�
		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;
	}

	//const ��ü������ ȣ���� �� �ִ� size�Լ� ����
	int size()		const //��, const�� ������ �ɹ��Լ��� ���� �����Ҽ��� ����.
	{
		return m_iSize;
	}
	//����Ʈ�� ������� �� true �� üũ�� �Լ�
	bool empty()	const
	{
		return m_iSize == 0;
	}
};