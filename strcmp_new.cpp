#include <iostream>
#include <cassert>

using namespace std;

const int ASCII_VALUE_BETWEEN_UPPERCASE_AND_LOWERCASE_VALUES = 32;

void convert_char_to_lower_case(char& charToConvert) {
	// 65 - 90 = Uppercase Letter
	// 97 - 122 = Lowercase Letter
	int charToConvertIntValue = int(charToConvert);

	// If this passes, then the char is not an Uppercase letter so there is no need to convert it.
	if(charToConvertIntValue < 65 || charToConvertIntValue > 90) {
		//cout << "Char: " << charToConvert << " is not an uppercase letter, no need to convert. " << endl;
		return;
	}

	// In order to convert to lowercase, just add 32 to the char's value.
	char lowercaseCharOfUppercaseCharToConvert = charToConvertIntValue + ASCII_VALUE_BETWEEN_UPPERCASE_AND_LOWERCASE_VALUES;

	//cout << "Char: " << charToConvert << " is an uppercase letter, converting to: " << lowercaseCharOfUppercaseCharToConvert << endl;

	charToConvert = lowercaseCharOfUppercaseCharToConvert;
}

int strcmp_case_insensitive(const string string1, const string string2) {
	int string1Length = string1.length();
	int string2Length = string2.length();

	int i = 0;
	while (i < string1Length && i < string2Length) {
		char charOfString1 = string1[i];
		char charOfString2 = string2[i];

		convert_char_to_lower_case(charOfString1);
		convert_char_to_lower_case(charOfString2);

		if (charOfString1 < charOfString2) {
			return -1;
		}
		else if (charOfString1 > charOfString2) {
			return 1;
		}

		i++;
	}

	// If all of the characters match of both strings, their lengths might not!
	if (string1Length < string2Length) {
		return -1;
	}

	if (string2Length < string1Length) {
		return 1;
	}

	return 0;
}

void test_driver() {
	cout << "-- Starting tests." << endl;

	assert(strcmp_case_insensitive("hello", "hello") == 0);
	assert(strcmp_case_insensitive("Hello", "hello") == 0);
	assert(strcmp_case_insensitive("hello", "Hello") == 0);
	assert(strcmp_case_insensitive("abc", "bcd") == -1);
	assert(strcmp_case_insensitive("bcd", "abc") == 1);
	assert(strcmp_case_insensitive("Z", "A") == 1);
	assert(strcmp_case_insensitive("a", "z") == -1);
	assert(strcmp_case_insensitive("abcdefG", "abcdefH") == -1);
	assert(strcmp_case_insensitive("ABCDEg", "ABCDEf") == 1);
	assert(strcmp_case_insensitive("hello", "helloo") == -1);
	assert(strcmp_case_insensitive("hellooooo", "hello") == 1);
	assert(strcmp_case_insensitive("abDef", "abCdjeflfjflij") == 1);
	assert(strcmp_case_insensitive("aBc", "aZejilfeifjelifj") == -1);
	assert(strcmp_case_insensitive("!@#$%", "!@#$%") == 0);

	// Test to make sure the original strings aren't altered
	string test1 = "HELLO";
	string test2 = "BYEBYE";
	assert(strcmp_case_insensitive(test1, test2) == 1);
	assert(test1 == "HELLO" && test2 == "BYEBYE");
	//

	cout << "-- Tests completed successfully!" << endl;
}

int main() {
	test_driver();

	return 0;
}