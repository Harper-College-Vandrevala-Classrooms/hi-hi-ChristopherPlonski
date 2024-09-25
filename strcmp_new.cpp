#include <iostream>
#include <cassert>

using namespace std;

const int ASCII_VALUE_BETWEEN_UPPERCASE_AND_LOWERCASE_VALUES = 32;

void convert_char_to_lower_case(char *charToConvert) {
	// 65 - 90 = Uppercase Letter
	// 97 - 122 = Lowercase Letter
	int charToConvertIntValue = int(*charToConvert);

	// If this passes, then the char is not an Uppercase letter so there is no need to convert it.
	if(charToConvertIntValue < 65 || charToConvertIntValue > 90) {
		//cout << "Char: " << charToConvert << " is not an uppercase letter, no need to convert. " << endl;
		return;
	}

	// In order to convert to lowercase, just add 32 to the char's value.
	char lowercaseCharOfUppercaseCharToConvert = charToConvertIntValue + ASCII_VALUE_BETWEEN_UPPERCASE_AND_LOWERCASE_VALUES;

	cout << "Char: " << *charToConvert << " is an uppercase letter, converting to: " << lowercaseCharOfUppercaseCharToConvert << endl;

	*charToConvert = lowercaseCharOfUppercaseCharToConvert;
}

void convert_string_to_spaceless(string *stringToConvert) {
	for (int i = 0; i < stringToConvert->length(); i++) {
		char charAtIndex = stringToConvert->at(i);

		if (charAtIndex == ' ') {
			cout << "Converted spaced string: " << *stringToConvert << " to: ";
			*stringToConvert = stringToConvert->substr(0, i) + stringToConvert->substr(i + 1, stringToConvert->length() - i - 1);
			cout << *stringToConvert << "." << endl;
			i--;
		}
	}
}

int strcmp_case_insensitive(const string string1, const string string2, bool ignoreSpaces = false, int maxCharactersToCheck = -1) {
	cout << "Comparing string1: " << string1 << " with string2: " << string2 << " | Opt. Arguments: ignoreSpaces: " << ignoreSpaces 
		<< " maxCharactersToCheck: " << maxCharactersToCheck << endl;
	string convertedString1 = string1;
	string convertedString2 = string2;

	if (ignoreSpaces) {
		string *string1CopyPointer = &convertedString1;
		string *string2CopyPointer = &convertedString2;

		convert_string_to_spaceless(string1CopyPointer);
		convert_string_to_spaceless(string2CopyPointer);
	}

	const int STRING_1_LENGTH = convertedString1.length();
	const int STRING_2_LENGTH = convertedString2.length();

	bool hasMaxCharacterCheckingLimit = maxCharactersToCheck != -1;

	int i = 0;
	while (i < STRING_1_LENGTH && i < STRING_2_LENGTH && (!hasMaxCharacterCheckingLimit || i < maxCharactersToCheck)) {
		char charOfString1 = convertedString1[i];
		char charOfString2 = convertedString2[i];
		char* charOfString1Pointer = &charOfString1;
		char* charOfString2Pointer = &charOfString2;

		convert_char_to_lower_case(charOfString1Pointer);
		convert_char_to_lower_case(charOfString2Pointer);

		//cout << "Comparing '" << *charOfString1Pointer << "' with '" << *charOfString2Pointer << "'" << endl;

		if (*charOfString1Pointer < *charOfString2Pointer) {
			return -1;
		}
		else if (*charOfString1Pointer > *charOfString2Pointer) {
			return 1;
		}

		i++;
	}

	// Should only check the string length difference if there isn't a hasMaxCharacterCheckingLimit, or if there is,
	// if either of the string's length is greater than hasMaxCharacterCheckingLimit then their length being < or > won't matter as 
	// the characters past maxCharactersToCheck shouldn't matter.
	bool shouldCheckStringLengthDifference = !hasMaxCharacterCheckingLimit || ((STRING_1_LENGTH < maxCharactersToCheck && STRING_2_LENGTH < maxCharactersToCheck));

	// If all of the characters match of both strings, their lengths might not!
	if (shouldCheckStringLengthDifference && STRING_1_LENGTH < STRING_2_LENGTH) {
		return -1;
	}

	if (shouldCheckStringLengthDifference && STRING_2_LENGTH < STRING_1_LENGTH) {
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

	// Tests to cover Add-on #1 (removing spaces one).
	assert(strcmp_case_insensitive("abc", "bcd", true) == -1);
	assert(strcmp_case_insensitive("C", "B", true) == 1);
	assert(strcmp_case_insensitive("com put er", "computer", true) == 0);
	assert(strcmp_case_insensitive("h E l   l O", "H e lL  o   ", true) == 0);
	assert(strcmp_case_insensitive("hello ", " world", true) == -1);
	assert(strcmp_case_insensitive("he ll oo NO", " he   ll OO  n", true) == 1);
	assert(strcmp_case_insensitive("!@#$%", "!@#$%", true) == 0);
	assert(strcmp_case_insensitive("!@ # $ %", " !  @#$    % ", true) == 0);

	// Tests to cover Add-on #2 (max character coverage one).
	assert(strcmp_case_insensitive("abcdY", "abcdZ", false, 4) == 0);
	assert(strcmp_case_insensitive("abcdY", "abcdZ", false, 100) == -1);
	assert(strcmp_case_insensitive("abcdY", "abcdZ", false, -100) == 0);
	assert(strcmp_case_insensitive("abcdY", "abcdZ", false, 0) == 0);
	assert(strcmp_case_insensitive("abc", "ABC DEFGHIJKLMNOP", false, 3) == 0);
	assert(strcmp_case_insensitive("american", "americam", false, 7) == 0);
	assert(strcmp_case_insensitive("american", "americam", false, 8) == 1);

	// Testing Add-on #1 and Add-on #2 together
	assert(strcmp_case_insensitive("a  bcd   Y", "ab   c d Z", true, 4) == 0);
	assert(strcmp_case_insensitive("a  b c dY", "a b c d Z", true, 100) == -1);
	assert(strcmp_case_insensitive("ab c dY ", "a b   cdZ", true, -100) == 0);
	assert(strcmp_case_insensitive("a b cdY", "a bc d Z", true, 0) == 0);
	assert(strcmp_case_insensitive("   ab c ", "A   B C   DEFGHIJKLMNOP", true, 3) == 0);
	assert(strcmp_case_insensitive("amer  ican", "americam", true, 7) == 0);
	assert(strcmp_case_insensitive("american", " americam ", true, 8) == 1);

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