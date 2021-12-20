#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <fstream>

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))

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
		if (bit > 0)
			result += "1";
		else
			result += "0";
	}

	return result;
}

int getGamma(std::vector<std::string> arr)
{
	std::string result = getMostCommonBytes(arr);
	return binaryToInt(result);
}

int getEpsilon(std::vector<std::string> arr)
{
	std::string result = getMostCommonBytes(arr);
	std::string result_flipped = "";
	for (int i = 0; i < result.size(); i++)
	{
		if (result[i] == '0')
			result_flipped += "1";
		else
			result_flipped += "0";
	}

	return binaryToInt(result_flipped);
}

int main()
{
	std::vector<std::string> input = loadInputs("inputs.txt");
	int gamma = getGamma(input);
	int epsilon = getEpsilon(input);
	int powerConsumption = gamma * epsilon;
	std::cout << gamma << std::endl;
	std::cout << epsilon << std::endl;
	std::cout << powerConsumption << std::endl;

	return 0;
}