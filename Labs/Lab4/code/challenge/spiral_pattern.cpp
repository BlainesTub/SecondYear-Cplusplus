#include <iostream>
#include <vector>

using matrix_type = std::vector<std::vector<int>>;


void draw_spiral(matrix_type& matrix) {
	int n = matrix.size();  //declare the size of the square matrix
	int tracer = n;
	int rend = n;
	int bend = n;
	int lend = 0;
	int tend = 1;
	int i = 0;
	int j = 0;
	//go RIGHT

	while (tracer >=1){
		while(i<rend){
			matrix.at(j).at(i) = tracer;
			++i;
		}
		rend = --i - 1; //cancel out the last i iteration
		++j;
		tracer -= 1;
		//go DOWN
		while(j<bend){
			matrix.at(j).at(i) = tracer;
			++j;
		}
		bend = --j - 1;
		--i;
		tracer -= 1;
		//go LEFT
		while(i>lend){
			matrix.at(j).at(i) = tracer;
			--i;
		}
		lend = ++i + 1;
		--j;
		tracer -= 1;
		//go UP
		while(j>tend){
			matrix.at(j).at(i) = tracer;
			--j;
		}
		tend = ++j + 1;
		++i;
		tracer -=1;
	}



}

// helper function which prints the provided matrix
void print(const matrix_type& matrix) {
	for (auto& row : matrix) {
		for (auto value : row) {
			std::cout << value << ' ';
		}
		std::cout << std::endl;
	}
}

int main(int argc, char** argv) {
	// check that the user provided a command line argument
	if (argc != 2) {
		std::cout << "One integer command line argument must be provided\n";
		return EXIT_FAILURE;
	}

	size_t dimension {0};

	// attempt to convert the command line argument into an integer
	try {
		int test {std::stoi(argv[1])};

		if (test < 0) {
			throw std::invalid_argument("Command line argument was negative");
		}
		dimension = static_cast<int>(test);
	} catch (std::invalid_argument& e) {
		std::cout << "The command line argument must be a positive integer\n";
		return EXIT_FAILURE;
	}

	// create an "empty" square matrix from the dimension
	matrix_type matrix {dimension, std::vector<int>(dimension, 0)};

	// student implements this function
	draw_spiral(matrix);

	print(matrix);

	return EXIT_SUCCESS;
}
