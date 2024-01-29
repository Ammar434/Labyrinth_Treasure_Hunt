// std::vector<std::string> assets, maze;
// std::ifstream file(filename);

// // Read file into vector of strings
// if (file.is_open())
// {
// 	bool input_assets = true;
// 	std::string line;
// 	while (std::getline(file, line))
// 	{
// 		// Check if the line contains the maze definition
// 		if (input_assets && line.find('+') != std::string::npos)
// 			input_assets = false;

// 		// Add input line to appropriate vector
// 		if (input_assets)
// 			assets.push_back(line);
// 		else
// 			maze.push_back(line);
// 	}
// 	file.close();
// 	message("Read %d asset lines, %d maze lines, first line: %s", assets.size(), maze.size(), maze[0].c_str());
// }
// else
// {
// 	message("Error! File cannot be opened");
// }

// parse_assets(assets);
// parse_maze(maze);

// printf("%d %d\n", width(), height());
// 1. allouer les tableaux pour les murs, les affiches et les caisses.

// Count the number of wall
// size_t numRows = maze.size();
// size_t numCols = maze[0].size();
// std::vector<std::string> mazeTranspose(numCols, std::string(numRows, ' '));

// for (int i = 0; i < height(); ++i)
// {
// 	std::cout << "Checking for wall on line " << i << std::endl;
// 	std::cout << countNumberOfWallHorizontal(maze[i]);
// 	printf("\n");
// }

// for (size_t i = 0; i < numCols; ++i)
// {
// 	for (size_t j = 0; j < numRows; ++j)
// 	{
// 		if (i < maze[j].length())
// 		{
// 			mazeTranspose[i][j] = maze[j][i];
// 		}
// 		else
// 		{
// 			std::cout << '-1'; // Padding if the string is shorter
// 		}
// 	}
// 	std::cout << std::endl;
// }

// for (int i = 0; i < height(); ++i)
// {
// 	std::cout << "Checking for wall on col " << i << std::endl;
// 	std::cout << countNumberOfWallHorizontal(mazeTranspose[i]);
// 	printf("\n");
// }