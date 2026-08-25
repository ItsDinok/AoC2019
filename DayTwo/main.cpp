#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <iostream>

void get_input(std::vector<int>& input, const std::string& file_path)
{
	std::ifstream file(file_path);
	std::string line;
	std::getline(file, line);

	// Parse into commands
	std::string buffer = "";
	for (size_t i = 0; i < line.size(); ++i)
	{
		if (line[i] == ',')
		{
			input.push_back(std::stoi(buffer));
			buffer = "";
			continue;
		}
		buffer += line[i];
	}
	// Assumes the input doesn't end on a comma
	input.push_back(std::stoi(buffer));
}

// This can be made a lot prettier
struct IntCodeVM
{
	IntCodeVM(const std::string& file_path)
	{
		get_input(memory, file_path);
	}

	// For use after the ICVM has been made
	void set_state(const std::string& file_path)
	{
		memory.clear();
		instruction_pointer = 0;

		get_input(memory, file_path);
	}

	void set_input(int noun, int verb)
	{
		memory[1] = noun;
		memory[2] = verb;
	}

	// Get the following two values from a unary operation
	std::pair<int, int> get_sentence_parameters()
	{
		std::pair<int, int> values;
		values.first = memory[memory[instruction_pointer + 1]];
		values.second = memory[memory[instruction_pointer + 2]];
		return values;
	}
	
	int run()
	{
		// Loop to handle all opcode logic
		while (true)
		{
			int opcode = memory[instruction_pointer];
			switch(opcode)
			{
				// Opcode one is addition
				case 1: 
					add();
					instruction_pointer += 4;
					break;
				// Opcode two is multiplication
				case 2:
					multiply();
					instruction_pointer += 4;
					break;
				// Opcode 99 is termination
				case 99:
					return terminate();
				default:
					// Unidentified opcode
					std::cout << "Unknown opcode: " << opcode 
						<< " ! AAAAAAAA!" << std::endl;
			}
		}
	}

	void add()
	{
		std::pair<int, int> noun_verb = get_sentence_parameters();
		int output_address = memory[instruction_pointer + 3];
		memory[output_address] = noun_verb.first + noun_verb.second;
	}

	void multiply()
	{
		std::pair<int, int> noun_verb = get_sentence_parameters();
		int output_address = memory[instruction_pointer + 3];
		memory[output_address] = noun_verb.first * noun_verb.second;
	}

	int terminate()
	{
		return memory[0];
	}

	std::vector<int> memory;
	int instruction_pointer = 0;
};

// This is the start of the legendary intcode challenges!
int task_one()
{
	IntCodeVM icvm("input.txt");
	// Hard-coded start parameters:
	icvm.set_input(12, 2);
	return icvm.run();
}

// Find the position one and two values that prodduce the output: 19690720
// Position one is called the noun, position two is called the verb
int task_two()
{
	IntCodeVM icvm("input.txt");
	for (size_t noun = 0; noun < 100; ++noun)
	{
		for (size_t verb = 0; verb < 100; ++verb)
		{
			icvm.set_state("input.txt");
			icvm.set_input(noun, verb);

			int output = icvm.run();

			if (output == 19690720)
			{
				return 100 * noun + verb;
			}
		}
	}

	return -1;
}

int main()
{
	std::cout << "Task one: " << task_one() << std::endl;
	std::cout << "Task two: " << task_two() << std::endl;
	return 0;
}
