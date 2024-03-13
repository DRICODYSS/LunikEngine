#pragma once

class ITest
{
public:
	virtual bool Init() = 0;
	virtual void Run() = 0;
	virtual void Shutdown() = 0;

	virtual ~ITest() {}
};

