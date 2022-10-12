#pragma once

// 모든 클래스의 추상 클래스
class CRoot
{
private:
	// 각 클래스 init 이후 실행할 함수
	virtual void Enter() = 0; 

public:
	CRoot() {};
	~CRoot() {};
};


