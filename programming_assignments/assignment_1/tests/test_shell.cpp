#include "shell.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

int test_split_commands() {
    std::string command = "ls -l; cat file";
    std::vector<std::string> commands = split_commands(command);
    if (commands.size() == 2 && commands[0] == "ls -l" && commands[1] == "cat file") {
        std::cout << "PASS: split_commands separates at semicolons" << std::endl;
        return 0;
    }
    std::cerr << "FAIL: split_commands should separate and trim commands" << std::endl;
    return 1;
}

int test_split_words() {
    std::vector<std::string> command_words = split_words("cat main.cpp");
    if (command_words.size() == 2 &&
        command_words[0] == "cat" &&
        command_words[1] == "main.cpp") {
        std::cout << "PASS: split_words separates program and arguments" << std::endl;
        return 0;
    }
    std::cerr << "FAIL: split_words should separate program and arguments" << std::endl;
    return 1;
}

int test_cd() {
    const std::filesystem::path before = std::filesystem::current_path();
    if (execute_line("cd ..")) {
        std::cerr << "FAIL: cd should keep the shell open" << std::endl;
        std::filesystem::current_path(before);
        return 1;
    }
    const std::filesystem::path after = std::filesystem::current_path();
    std::filesystem::current_path(before);
    if (after != before.parent_path()) {
        std::cerr << "FAIL: cd .. should move to the parent directory" << std::endl;
        return 1;
    }
    std::cout << "PASS: cd changes the shell's directory" << std::endl;
    return 0;
}

int main() {
    int failures = test_split_commands();
    failures += test_split_words();
    failures += test_cd();

    if (execute_line(" ; \t; ")) {
        std::cerr << "FAIL: empty commands should keep the shell open" << std::endl;
        ++failures;
    }
    if (!execute_line("  QuiT  ")) {
        std::cerr << "FAIL: quit should request a shell exit" << std::endl;
        ++failures;
    }

    if (failures == 0) {
        std::cout << "All shell tests passed" << std::endl;
    }
    return failures == 0 ? 0 : 1;
}
