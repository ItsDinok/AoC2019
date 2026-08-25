#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
#include <utility>
#include <limits>

// TODO: Don't check if they land on the same point, check if their paths cross
// NOTE: Much harder problem

void get_input(
		std::vector<std::string>& wire_one,
		std::vector<std::string>& wire_two,
		const std::string& file_path
		)
{
	std::ifstream file(file_path);
	std::string line;

	// NOTE: Objectively worst way to do this, I think
	bool is_first_wire = true;
	
	while (std::getline(file, line))
	{
		std::string buffer = "";
		
		// Parse each wire into its own vector
		for (size_t i = 0; i < line.size(); ++i)
		{
			if (line[i] == ',')
			{
				if (is_first_wire) wire_one.push_back(buffer);
				else wire_two.push_back(buffer);

				buffer = "";
				continue;
			}
			buffer += line[i];
		}

		is_first_wire = false;
	}
}

// Calculate manhattan distance of closest conflux of wires to origin
int task_one()
{
	int shortest_distance = std::numeric_limits<int>::max();
	std::vector<std::string> wire_one, wire_two;
	get_input(wire_one, wire_two, "input.txt");

	// Simulate the path of the two wires and find intersections

	assert (wire_one.size() == wire_two.size());
	std::pair<int, int> w_one_pos (0, 0);
	std::pair<int, int> w_two_pos (0, 0);

	for (size_t i = 0; i < wire_one.size(); ++i)
	{
		// First character is direction bit
		std::string w1_vec = wire_one[i];
		char w1_dir = w1_vec[0];
		w1_vec.erase(0, 1);

		std::string	w2_vec = wire_two[i];
		char w2_dir = w2_vec[0];
		w2_vec.erase(0, 1);

		// Get each wire's instruction, then add that to the coordinate
		switch (w1_dir)
		{
			case 'U':
				w_one_pos.second += std::stoi(w1_vec);
				break;
			case 'R':
				w_one_pos.first += std::stoi(w1_vec);
				break;
			case 'D':
				w_one_pos.second -= std::stoi(w1_vec);
				break;
			case 'L':
				w_one_pos.first -= std::stoi(w1_vec);
				break;
			default:
				std::cout << "Unexpected direction bit: " << w1_dir << "!" << std::endl;
		}
		
		switch (w2_dir)
		{
			case 'U':
				w_two_pos.second += std::stoi(w2_vec);
				break;
			case 'R':
				w_two_pos.first += std::stoi(w2_vec);
				break;
			case 'D':
				w_two_pos.second -= std::stoi(w2_vec);
				break;
			case 'L':
				w_two_pos.first -= std::stoi(w2_vec);
				break;
			default:
				std::cout << "Unexpected direction bit: " << w2_dir << "!" << std::endl;
		}

		// Check manhattan distance
		if (w_one_pos == w_two_pos)
		{
			int m_distance = w_one_pos.first + w_one_pos.second;
			if (m_distance < shortest_distance) shortest_distance = m_distance;
		}

	}
	return shortest_distance;
}

int main()
{
	std::cout << task_one() << std::endl;
	return 0;
}
