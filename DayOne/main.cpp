#include <string>
#include <vector>
#include <fstream>
#include <iostream>

void get_input(std::vector<int>& input, const std::string& file_path)
{
	std::ifstream file(file_path);
	std::string line;
	while (std::getline(file, line))
	{
		input.push_back(std::stoi(line));
	}
}

// To calculate the fuel requirements you take a value, divide it by three and then 
// subtract two.
int task_one()
{
	int total = 0;

	std::vector<int> values;
	get_input(values, "input.txt");

	for (size_t i = 0; i < values.size(); ++i)
	{
		// int division in c++ only keeps integral value
		total += (values[i] / 3) - 2;
	}

	return total;
}

// Fuel requires fuel, when the required value becomes negative that is the total fuel
// required for that value.
int task_two()
{
	int total = 0;

	std::vector<int> values;
	get_input(values, "input.txt");

	for (size_t i = 0; i < values.size(); ++i)
	{
		int sub_total = (values[i] / 3) - 2;
		while (sub_total > 0)
		{
			total += sub_total;
			sub_total = (sub_total / 3) - 2;
		}
	}

	return total;
}

int main()
{
	std::cout << "Task one:" << task_one() << std::endl;
	std::cout << "Task two:" << task_two() << std::endl;

	return 0;
}
