#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

int instructionModifier(std::string str)
{
	int index = str.find(' ');
	std::string mod = str.substr(index+1, 1);

	return stringToInt(mod);
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

int main()
{
	std::vector<std::string> instructions = loadInputs("inputs.txt");
	int depth = 0;
	int horiz = 0;
	int aim = 0;

	for (int i = 0; i < instructions.size(); i++)
	{
		char let = instructions[i][0];
		int amount = instructionModifier(instructions[i]);
		switch (let)
		{
		case 'f':
			horiz += amount;
			depth += aim * amount;
			break;
		case 'd':
			aim += amount;
			break;
		case 'u':
			aim -= amount;
			break;
		default:
			std::cout << "Unknown operation: " << let << std::endl;
			break;
		}
	}

	std::cout << "Horizontal Pos: " << horiz << ", Depth: " << depth << std::endl;
	std::cout << "Product: " << horiz * depth;

	return 0;
}