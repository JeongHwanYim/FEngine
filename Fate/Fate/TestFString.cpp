#include "FString.h"
#include "FTestHelper.h"

TEST(FStringSimpleTest1, "FString ���� �˻�")
{
	FString str(TEXT("ö��"));
	if (str != TEXT("ö��")) return false;
	if (str != FString(TEXT("ö��"))) return false;

	return true;
}

TEST(FStringSimpleTest2, "FString += �˻�")
{
	FString str(FString(FString(FString(TEXT("����")))));
	str += TEXT("��");
	str += TEXT(" ");
	str += FString(FString(TEXT("�μ�")));

	if (str != TEXT("����� �μ�")) return false;
	if (str != FString(TEXT("����� �μ�"))) return false;
	return true;
}

TEST(FStringSimpleTest3, "FString + �˻�")
{
	FString tmp(TEXT("����"));
	FString str;
	tmp = tmp + FString(TEXT("��"));
	str = tmp + TEXT(" ") + TEXT("�μ�");

	if (str != TEXT("����� �μ�")) return false;
	if (str != FString(TEXT("����� �μ�"))) return false;
	return true;
}