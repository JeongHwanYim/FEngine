#include "FArray.h"
#include <Windows.h>
#include <tchar.h>

#include "FTestHelper.h"

TEST(FArraySimpleTest, "FArray�� �ǰ����� üũ�غ��ô�.")
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