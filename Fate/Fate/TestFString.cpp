#include "FString.h"
#include "FTestHelper.h"

TEST(FStringSimpleTest1, "FString ´ëÀÔ °Ë»ç")
{
	FString str(TEXT("Ã¶¼ö"));
	if (str != TEXT("Ã¶¼ö")) return false;
	if (str != FString(TEXT("Ã¶¼ö"))) return false;

	return true;
}

TEST(FStringSimpleTest2, "FString += °Ë»ç")
{
	FString str(FString(FString(FString(TEXT("¿µÈñ")))));
	str += TEXT("¿Í");
	str += TEXT(" ");
	str += FString(FString(TEXT("¹Î¼ö")));

	if (str != TEXT("¿µÈñ¿Í ¹Î¼ö")) return false;
	if (str != FString(TEXT("¿µÈñ¿Í ¹Î¼ö"))) return false;
	return true;
}

TEST(FStringSimpleTest3, "FString + °Ë»ç")
{
	FString tmp(TEXT("¿µÈñ"));
	FString str;
	tmp = tmp + FString(TEXT("¿Í"));
	str = tmp + TEXT(" ") + TEXT("¹Î¼ö");

	if (str != TEXT("¿µÈñ¿Í ¹Î¼ö")) return false;
	if (str != FString(TEXT("¿µÈñ¿Í ¹Î¼ö"))) return false;
	return true;
}