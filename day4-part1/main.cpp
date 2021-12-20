// for (const auto &str : lines)
// {
// 	std::cout << str << std::endl;
// }

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <fstream>

class Board
{
private:
	std::array<int, 5 * 5> cells;

public:
	Board()
	{
		cells.fill(0);
	}

private:
	int xyToIndex(int x, int y)
	{
		return x + 5 * y;
	}

public:
	void setCellValueAt(int x, int y, int value)
	{
		cells[xyToIndex(x, y)] = value;
	}

	int getCellValueAt(int x, int y)
	{
		return cells[xyToIndex(x, y)];
	}

	bool isMarked(int x, int y)
	{
		return getCellValueAt(x, y) == -1;
	}

	void markCellAt(int x, int y)
	{
		setCellValueAt(x, y, -1);
	}

	void markCells(int value)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				int cellValue = getCellValueAt(j, i);
				if (cellValue == value)
					markCellAt(j, i);
			}
		}
	}

	bool hasWon()
	{
		// rows
		for (int i = 0; i < 5; i++)
		{
			int summation = 0;
			for (int j = 0; j < 5; j++)
			{
				if (isMarked(j, i))
					summation++;
			}
			if (summation == 5)
				return true;
		}
		// collumns
		for (int i = 0; i < 5; i++)
		{
			int summation = 0;
			for (int j = 0; j < 5; j++)
			{
				if (isMarked(j, i))
					summation++;
			}
			if (summation == 5)
				return true;
		}
		return false;
	}

	int sumUnmarked()
	{
		int sum = 0;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (!isMarked(j, i))
				{
					sum += getCellValueAt(j, i);
				}
			}
		}
		return sum;
	}

	void display()
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				std::cout << getCellValueAt(j, i) << " ";
			}
			std::cout << std::endl;
		}
	}
};

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

std::vector<int> loadNumbers(std::string pathToFile)
{
	std::ifstream inputFile(pathToFile);
	std::string readText;
	std::vector<int> output;

	std::getline(inputFile, readText);
	inputFile.close();

	std::string temp;
	for (int i = 0; i < readText.size(); i++)
	{
		if (readText[i] == ',')
		{
			output.push_back(stringToInt(temp));
			temp = "";
		}
		else
		{
			temp += readText[i];
		}
	}
	output.push_back(stringToInt(temp));

	return output;
}

std::vector<std::string> splitString(std::string input, std::string delimiter)
{
	std::vector<std::string> words{};

	size_t pos = 0;
	while ((pos = input.find(delimiter)) != std::string::npos)
	{
		words.push_back(input.substr(0, pos));
		input.erase(0, pos + delimiter.length());
	}
	return words;
}

std::vector<Board> loadBoards(std::string pathToFile)
{
	std::ifstream inputFile(pathToFile);
	std::string readText;
	std::string fullText;
	std::vector<Board> output;
	Board *board = new Board();

	while (std::getline(inputFile, readText))
	{
		fullText += readText + '\n';
	}
	std::vector<std::string> lines = splitString(fullText, "\n");
	lines.erase(lines.begin());
	lines.erase(lines.begin());

	int index = 0;
	for (int i = 0; i < lines.size(); i++)
	{
		std::string line = lines[i];
		for (int j = 0; j < line.length(); j += 3)
		{
			std::string sub = line.substr(j, 3);
			int value = stringToInt(sub);
			int x = index % 5;
			int y = index / 5;

			board->setCellValueAt(x, y, value);
			index++;

			if (index == 25)
			{
				output.push_back(*board);
				board = new Board();
				index = 0;
			}
		}
	}
	return output;
}

int main()
{
	std::string pathToFile = "inputs.txt";
	std::vector<int> numbers = loadNumbers(pathToFile);
	std::vector<Board> boards = loadBoards(pathToFile);

	for (auto num : numbers)
	{
		for (auto &board : boards)
		{
			board.markCells(num);
			if (board.hasWon())
			{
				board.display();
				int score = board.sumUnmarked() * num;
				std::cout << score << std::endl;
				return 0;
			}
		}
	}

	return 0;
}