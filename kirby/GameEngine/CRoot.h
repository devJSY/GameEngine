#pragma once

// 모든 클래스의 추상 클래스
class CRoot
{
private:
	// 추상 클래스용 순수 가상 함수
	virtual void Root() = 0; 

public:
	CRoot() {};
	~CRoot() {};
};


