#include <iostream>
#include <vector>
#include <string>
#include <fstream>


int countIncreases(std::vector<int> sonarDepths)
{
	std::vector<int> runningTally;
	int increased = 0;

	for (int i = 0; i < sonarDepths.size(); i++)
	{
		runningTally.push_back(sonarDepths[i]);
		if (runningTally.size() < 4)
			continue;

		int totalA = runningTally[0] + runningTally[1] + runningTally[2];
		int totalB = runningTally[1] + runningTally[2] + runningTally[3];
		if (totalA < totalB)
			increased++;

		runningTally.erase(runningTally.begin());
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


int main()
{
	std::vector<int> sonarDepths = loadInputs("inputs.txt");
	int increased = countIncreases(sonarDepths);
	std::cout << increased << std::endl;

	return 0;
}