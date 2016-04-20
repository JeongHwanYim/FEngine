#pragma once

#include <vector>

class FTestRegistHelper;
class FTestExecutor;

class FTestRegister
{
	typedef bool (*TestElement)(void);
	typedef std::vector<TestElement> TestMap;
	static TestMap& GetInstance()
	{
		static TestMap _TestMap;
		return _TestMap;
	}
	friend FTestRegistHelper;
	friend FTestExecutor;
};

class FTestRegistHelper
{
	typedef bool(*TestElement)(void);
public:
	FTestRegistHelper(TestElement test)
	{
		FTestRegister::GetInstance().push_back(test);
	}
};

class FTestExecutor
{
public:
	static bool RunTest()
	{
		auto TestMap = FTestRegister::GetInstance();
		for (auto it = TestMap.cbegin(); it != TestMap.cend(); ++it)
		{
			if ((*it)() == false)
				return false;
		}

		return true;
	}
};


#define TEST(PrimaryTestName, Description) \
	bool __Test##PrimaryTestName();	\
	FTestRegistHelper __##PrimaryTestName(__Test##PrimaryTestName);	\
	bool __Test##PrimaryTestName()