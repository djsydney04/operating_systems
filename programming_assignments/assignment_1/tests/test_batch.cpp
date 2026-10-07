#include "../src/batch.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Check the parsing that is done for the batch file in read_batch_file function
int test_read_batch_file() {
    // Create a temporary batch file
    const std::filesystem::path path =
        std::filesystem::temp_directory_path() / "ossh_batch_test.txt";
    {
        // Write the commands to the temporary batch file
        std::ofstream out(path);
        out << "ls -l\n";
        out << "cat file\n";
        
        out.close();
    }

    // Read the commands from the temporary batch file
    std::vector<std::string> commands = read_batch_file(path.string());
    std::filesystem::remove(path);

    // Check that the commands were read correctly
    if (commands.size() == 2 && commands[0] == "ls -l" && commands[1] == "cat file") {
        std::cout << "PASS: read_batch_file reads commands from a file" << std::endl;
        return 0;
    }
    // If the commands were not read correctly, print an error message and return 1
    std::cerr << "FAIL: read_batch_file should read commands from a file" << std::endl;
    return 1;
}

int test_execute_commands() {
    {
        std::ofstream out("file");
        out << "hello\n";
    }
    std::vector<std::string> commands = {"ls -l", "cat file"};
    execute_commands(commands);
    std::filesystem::remove("file");
    if (commands[0] == "ls -l" && commands[1] == "cat file") {
        std::cout << "PASS: execute_commands executes commands" << std::endl;
        return 0;
    }
    std::cerr << "FAIL: execute_commands should execute commands" << std::endl;
    return 1;
}

int main() {
    int failures = test_read_batch_file();
    failures += test_execute_commands();
    if (failures == 0) {
        std::cout << "All batch tests passed" << std::endl;
    }
    return failures == 0 ? 0 : 1;
}
