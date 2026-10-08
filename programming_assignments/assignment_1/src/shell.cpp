#include "shell.h"
#include "string_utils.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <sys/wait.h>
#include <unistd.h>

std::vector<std::string> split_commands(std::string line) {
    std::vector<std::string> commands;
    std::stringstream stream(line);
    std::string piece;
    while (std::getline(stream, piece, ';')) {
        commands.push_back(trim(piece));
    }
    return commands;
}

std::vector<std::string> split_words(std::string command) {
    std::vector<std::string> command_words;
    std::stringstream stream(command);
    std::string word;
    while (stream >> word) {
        command_words.push_back(word);
    }
    return command_words;
}

namespace {

// Run one command in a child process.
void run_command(std::vector<std::string> command_words) {
    pid_t pid = fork();
    if (pid == 0) {
        std::vector<char*> argv;
        for (std::string& word : command_words) {
            argv.push_back(word.data());
        }
        argv.push_back(nullptr);
        // Replace the child with the requested program.
        execvp(argv[0], argv.data());
        // execvp only returns if it fails.
        std::cerr << argv[0] << ": command not found or cannot be executed\n";
        _exit(1);
    } else if (pid < 0) {
        std::cerr << "failed to start a new process\n";
        return;
    }
    // Wait for the child to finish.
    int status = 0;
    if (waitpid(pid, &status, 0) < 0) {
        std::cerr << "failed to wait for the command to finish\n";
    }
}

// Change the shell's current directory.
void change_directory(const std::vector<std::string>& words) {
    // cd accepts at most one path.
    if (words.size() > 2) {
        std::cerr << "cd: too many arguments\n";
        return;
    }

    const char* path = nullptr;
    // cd without a path uses HOME.
    if (words.size() == 1) {
        path = std::getenv("HOME");
        if (path == nullptr) {
            std::cerr << "cd: HOME is not set\n";
            return;
        }
    } else {
        path = words[1].c_str();
    }

    if (chdir(path) != 0) {
        std::cerr << "cd: cannot change directory\n";
    }
}

}

bool execute_line(std::string line) {
    std::vector<std::string> commands = split_commands(line);
    bool should_exit = false;
    for (const std::string& command : commands) {
        std::vector<std::string> words = split_words(command);
        if (words.empty()) {
            continue;
        }
        // quit is a built-in. Finish the rest of this line before leaving the shell.
        if (normalize(words[0]) == "quit") {
            should_exit = true;
            continue;
        }
        if (normalize(words[0]) == "cd") {
            change_directory(words);
            continue;
        }
        run_command(words);
    }
    return should_exit;
}
