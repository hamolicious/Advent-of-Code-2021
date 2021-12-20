#include <iostream>
#include <vector>
#include <string>
#include <fstream>

int countIncreases(std::vector<int> vector)
{
	int increased = 0;
	for (int i = 1; i < vector.size(); i++)
	{
		if (vector[i] > vector[i - 1])
		{
			increased++;
		}
	}
	return increased;
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

std::vector<int> loadInputs(std::string pathToFile)
{
	std::ifstream inputFile(pathToFile);
	std::string readText;
	std::vector<int> output;

	while (std::getline(inputFile, readText))
	{
		output.push_back(stringToInt(readText));
	}

	inputFile.close();
	return output;
}

std::vector<int> sonarDepths;

int main()
{
	sonarDepths = loadInputs("inputs.txt");
	int increased = countIncreases(sonarDepths);
	std::cout << "Number of times depth increased: " << increased << std::endl;
	return 0;
}