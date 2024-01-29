// /*
// Get dimension of the labyrinthe
// */

// size_t longest_line(FILE *fi)
// {
//     size_t largest = 0, current = 0;
//     int ch;

//     if (fi)
//     {
//         while ((ch = fgetc(fi)) != EOF)
//         {
//             if (ch == '\n')
//             {
//                 if (current > largest)
//                     largest = current;
//                 current = 0;
//             }
//             else
//             {
//                 current++;
//             }
//         }
//         if (current > largest)
//             largest = current;
//     }
//     return largest;
// }

// /*
// Parse labyrinth
// */

// void parse_assets(const std::vector<std::string> &input)
// {
//     // Iterate over input lines ignoring everything after # sign
//     for (std::string line : input)
//     {
//         // Skip comments
//         auto comment = line.find('#');
//         if (comment != std::string::npos)
//             line = line.substr(0, comment);

//         // Skip empty lines
//         if (line.empty())
//             continue;

//         // Split line into tokens
//         std::istringstream iss(line);
//         std::vector<std::string> tokens;
//         std::copy(std::istream_iterator<std::string>(iss),
//                   std::istream_iterator<std::string>(),
//                   std::back_inserter(tokens));

//         // Parse tokens
//         message("%s", tokens[0].c_str());
//         // sleep(2);
//     }
// }

// void parse_maze(const std::vector<std::string> &input)
// {
//     // Find the size of the maze
//     unsigned int height = input.size();
//     unsigned int width = 0;

//     for (std::string line : input)
//     {
//         width = std::max((unsigned int)line.length(), width);
//     }

//     // Initialize the maze data
//     this->_height = height;
//     this->_width = width;

//     // Create new array of size height and width
//     this->_data = new char *[this->_height];
//     for (int x = 0; x < this->_height; x++)
//     {
//         this->_data[x] = new char[this->_width];
//     }

//     // Copy data to maze definition array
//     for (int x = 0; x < this->_height; x++)
//     {
//         // Copy the line contents
//         for (int y = 0; y < input[x].length(); y++)
//         {
//             this->_data[x][y] = input[x][y];
//         }
//         // Fill out the missing elements with ' '
//         for (int y = input[x].length(); y < this->_width; y++)
//         {
//             this->_data[x][y] = ' ';
//         }
//     }
// }