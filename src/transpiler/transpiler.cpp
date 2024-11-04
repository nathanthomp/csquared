#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

int main(int argc, char *argv[], char *env[]) {

    if (argc != 2) {
        std::cerr << "Usage: ./transpiler <source>" << std::endl;
        return 1;
    }

    std::string source = argv[1];
    std::string filename = source.substr(0, source.length() - 4);
    std::string extension = source.substr(source.length() - 4, source.length() - 1);

    if (!std::filesystem::exists(source)) {
        std::cerr << "Error: " << source << " file does not exist" << std::endl;
        return 1; 
    }

    std::ifstream sourceFile(source);

    if (!sourceFile.is_open()) {
        std::cerr << "Error: could not open file " << source << std::endl;
        return 1;
    }

    // Contents of source file
    std::vector<std::string> lines;

    std::string line;
    while (std::getline(sourceFile, line)) {
        std::cout << "read: " << line << std::endl;
        lines.push_back(line);
    }

    std::ofstream destinationFile(filename + ".c");
    for (size_t i = 0; i < lines.size(); i++) {
        destinationFile << lines.at(i) << std::endl;
    }

    std::string command = "gcc " + filename + ".c -o " + filename;

    system(command.c_str());
}

// How this file is supposed to work: 
//   1. Use the command line arguments to gather the souce code filename
//   2. Open and copy all text in the source code file
//   3. Pass all source text to the transpiler
//   4. Create a new file based on the source code filename
//   5. Stream all transpiled text to the new file
//   6. Compile the new file
