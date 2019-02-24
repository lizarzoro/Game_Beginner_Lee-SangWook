#pragma once

//예외 처리
#include <assert.h>

//노드를 클래스로 만드는 이유 : 하나만 가지고 원터치로 처리할 수 있다. 굳이 노드를 외부에서 생성해서 넣어줄 필요없다.
template <typename T>
class CListNode
{
	//생성 소멸자를 private로 만들면 외부에서 노드 클래스를 생성하기 위해 변수를 생성하면 오류 뜸
private:
	//teplate class를 friend 처리 하기 위해
	template <typename T>
	friend class CLinkedList;
	//CListNode의 private나 protected에 접근 가능

	CListNode()
	{
		m_pNext = nullptr; // 포인터변수 초기화
		m_pPrev = nullptr; // 포인터변수 초기화
	}
	~CListNode()
	{

	}
private:
	T	m_Data; // 실제 데이터를 저장하는 변수
				//다음과 이전 노드의 주소를 저장하기 위한 변수
	CListNode<T>* m_pNext;
	CListNode<T>* m_pPrev;
};
template <typename T>
class CLinkedList
{
public:

	CLinkedList()
	{
		//시작과 끝 생성자에서 동적 할당
		m_pBegin = new NODE;
		m_pEnd = new NODE;

		//처음에는 추가된 노드가 없으므로 Begin의 다음 노드를 End로, End의 이전으로 Begin을 지정
		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;
	}

	~CLinkedList()
	{
		//할당된 메모리는 소멸자에서 자동으로 지워줄 수 있게 만든다
		clear(); //begin과 end노드 제외한 모든 노드 삭제
		delete m_pBegin;
		delete m_pEnd;
	}
private:
	//변수 선언의 편의성을 위해
	typedef CListNode<T>	NODE;
	typedef CListNode<T>*	PNODE;

private:
	PNODE	m_pBegin;
	PNODE	m_pEnd; // 반드시 존재해야 해서 생성자에서 동적 할당
					//PNODE	m_pData;
	int		m_iSize; // 노드가 몇개가 추가되었는지. 첨에는 0으로 초기화

public:
	void push_back(const T& data) //레퍼런스로 참조. 복사보다 빠른 속도로 인자 처리 가능.
								  //참조하는 대상의 값을 변경하지 못하게 하기 위해 const 사용
	{
		PNODE	pNode = new NODE;
		pNode->m_Data = data; //실제 데이터 입력
							  //뒤에 추가를 해야 하므로 end의 이전 노드를 얻어온다
		PNODE	pPrev = m_pEnd->m_pPrev;

		//얻어온 이전 노드와 end노드 사이에 새로 생성한 노드를 추가한다.
		pPrev->m_pNext = pNode;
		pNode->m_pPrev = pPrev;

		//end 노드에 새로 생성한 노드를 연결한다.
		pNode->m_pNext = m_pEnd; //새로 생성한 노드의 다음 노드를 end로 지정
		m_pEnd->m_pPrev = pNode; //end의 이전 노드를 새로 생성한 노드로 추가

		++m_iSize; //노드가 하나 추가映 때문에 사이즈 업

	}
	//새로운 노드를 앞에 추가
	void push_front(const T& data)
	{
		PNODE	pNode = new NODE;
		pNOde->m_Data = data;

		//begin과 begin사이에 새로 생성한 노드를 추가한다.
		PNODE	pNext = m_pBegin->m_pNext;
		//새로생성한 노드의 다음노드로 begin의 다음노드를 준다
		pNode->m_pNext = pNext;
		pNext->m_pPrev = pNode;

		//begin의 다음 노드로 새로 생성한 노드를 준다 / 새로 생성한 노드의 이전 노드로 begin을 준다
		m_pBegin->m_pNext = pNode;
		pNode->m_pPrev = m_pBegin;

		++m_iSize;
	}

	void pop_back() //가장 마지막 노드를 지워주기만 하기 때문에 인자를 받을 필요없다
	{
		if (empty())// 더 이상 지울게 없는 경우
			assert(false); // 에러 메시지 발생

						   //가장 마지막 노드를 지워야 하기 때문에 end 노드의 이전 노드를 가져온다
		PNODE pDeleteNode = m_pEnd->m_pPrev;

		//지울 노드의 이전 노드도 얻어와야 한다
		PNODE pPrev = pDeleteNode->m_pPrev;

		//이전노드의 다음으로 end노드를 주고 end노드의 전으로 이전노드를 준다
		pPrev->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pPrev;

		//이제 노드를 지워준다
		delete pDeleteNode;

		--m_iSize; //사이즈 1 감소
	}

	void pop_front() // 새로 추가된 맨 앞 노드를 삭제하는 기능
	{
		if (empty())// 더 이상 지울게 없는 경우
			assert(false); // 에러 메시지 발생

		PNODE pDeleteNode = m_pBegin->m_pNext; //지울 노드를 가져온다

											   //지울 노드의 다음 노드를 얻어오고 begin과 다은 노드를 연결해준다
		PNODE pNext = pDeleteNode->m_pNext;

		pNext->m_pPrev = m_pBegin;
		m_pBegin->m_pNext = pNext;

		delete pDeleteNode;

		--m_iSize;
	}

	T front() const //맨 앞의 데이터를 반환하는 기능
	{
		if (empty())// 더 이상 얻어올 게 없는 경우
			assert(false); // 에러 메시지 발생

		return m_pBegin->m_pNext->m_Data;
	}

	T back() const //맨 뒤의 데이터를 반환하는 기능
	{
		if (empty())// 더 이상 얻어올 게 없는 경우
			assert(false); // 에러 메시지 발생

		return m_pEnd->m_pPrev->m_Data;
	}

	//begin과 end를 제외한 실제 추가한 노드를 삭제하는 기능 clear
	void clear()
	{
		PNODE	pNode = m_pBegin->m_pNext;

		//실제 추가된 노드만 반복해서 방문
		while (pNode != m_pEnd)
		{
			PNODE pNext = pNode->m_pNext; //현제 노드의 다음 노드를 얻어온다
			delete pNode;//다음 노드를 받아왔으니 이제 현제 노드를 지워준다.
			pNode = pNext;//pNode에 다음 노드의 주소를 넣어준다
		}
		m_iSize = 0;
		//begin과 end를 서로 연결해준다
		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;
	}

	//const 객체에서도 호출할 수 있는 size함수 생성
	int size()		const //단, const가 있으니 맴버함수의 값을 변경할수는 없다.
	{
		return m_iSize;
	}
	//리스트가 비어있을 때 true 인 체크용 함수
	bool empty()	const
	{
		return m_iSize == 0;
	}
}