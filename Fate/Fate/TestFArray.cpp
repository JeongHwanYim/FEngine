#include "FArray.h"
#include <Windows.h>
#include <tchar.h>

#include "FTestHelper.h"

TEST(FArraySimpleTest, "FArray가 건강한지 체크해봅시다.")
{
	FArray<int> arr;
	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(3);

	for (auto it = arr.cbegin(); it != arr.end(); ++it)
	{
		TCHAR str[256];
		_stprintf_s(str, TEXT("value = %d\n"), *it);
		OutputDebugString(str);
	}

	return true;
}