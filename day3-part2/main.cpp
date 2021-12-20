#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <fstream>

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))

std::vector<std::string> copyVector(std::vector<std::string> a)
{
	std::vector<std::string> b;
	for (int i = 0; i < a.size(); i++)
	{
		b.push_back(a[i]);
	}
	return b;
}

int stringToInt(std::string str)
{
	int i;
	try
	{
		// string -> integer
		i = std::stoi(str);
	}
	catch (...)
	{
		std::cout << "Error Occured, inputted str: " << str << std::endl;
	}
	return i;
}

int binaryToInt(std::string str)
{
	return stoi(str, 0, 2);
}

std::vector<std::string> loadInputs(std::string pathToFile)
{
	std::ifstream inputFile(pathToFile);
	std::string readText;
	std::vector<std::string> output;

	while (std::getline(inputFile, readText))
	{
		output.push_back(readText);
	}

	inputFile.close();
	return output;
}

std::string getMostCommonBytes(std::vector<std::string> arr)
{
	std::vector<int> gammaBits;

	for (int i = 0; i < arr[0].size(); i++)
	{
		gammaBits.push_back(0);
	}

	for (int i = 0; i < gammaBits.size(); i++)
	{
		for (int j = 0; j < arr.size(); j++)
		{
			if (arr[j][i] == '0')
				gammaBits[i] += -1;
			else
				gammaBits[i] += 1;
		}
	}

	std::string result = "";
	for (auto bit : gammaBits)
	{
		if (bit > 0 || bit == 0)
			result += "1";
		else
			result += "0";
	}

	return result;
}

std::string flipAllBits(std::string str)
{
	std::string result_flipped = "";
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '0')
			result_flipped += "1";
		else
			result_flipped += "0";
	}

	return result_flipped;
}

int bitCriteriaOxygenGeneratorRating(std::vector<std::string> arr)
{
	std::vector<std::string> oldFilteredList = copyVector(arr);
	std::vector<std::string> newFilteredList;
	std::string commons = getMostCommonBytes(arr);

	for (int i = 0; i < arr[0].size(); i++)
	{
		commons = getMostCommonBytes(oldFilteredList);
		for (int j = 0; j < oldFilteredList.size(); j++)
		{
			if (oldFilteredList[j][i] == commons[i])
				newFilteredList.push_back(oldFilteredList[j]);
		}
		oldFilteredList = copyVector(newFilteredList);
		newFilteredList.clear();

		if (oldFilteredList.size() == 1)
			return binaryToInt(oldFilteredList[0]);
	}
	return -1;
}

int bitCriteriaCO2ScrubberRating(std::vector<std::string> arr)
{
	std::vector<std::string> oldFilteredList = copyVector(arr);
	std::vector<std::string> newFilteredList;
	std::string commons = flipAllBits(getMostCommonBytes(arr));

	for (int i = 0; i < arr[0].size(); i++)
	{
		commons = flipAllBits(getMostCommonBytes(oldFilteredList));
		for (int j = 0; j < oldFilteredList.size(); j++)
		{
			if (oldFilteredList[j][i] == commons[i])
				newFilteredList.push_back(oldFilteredList[j]);
		}
		oldFilteredList = copyVector(newFilteredList);
		newFilteredList.clear();

		if (oldFilteredList.size() == 1)
			return binaryToInt(oldFilteredList[0]);
	}
	return -1;
}

int main()
{
	std::vector<std::string> input = loadInputs("inputs.txt");
	int resultOxygenGeneratorRating = bitCriteriaOxygenGeneratorRating(input);
	int resultCO2ScrubberRating = bitCriteriaCO2ScrubberRating(input);

	std::cout << resultOxygenGeneratorRating << std::endl;
	std::cout << resultCO2ScrubberRating << std::endl;
	std::cout << "Result: " << resultCO2ScrubberRating * resultOxygenGeneratorRating << std::endl;

	return 0;
}