#include "shell.h"
#include "string_utils.h"

#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <sys/wait.h>
#include <unistd.h>

std::vector<std::string> split_commands(std::string line) {
    std::vector<std::string> commands;
    std::stringstream stream(line);
    std::string piece;
    while (std::getline(stream, piece, ';')) {
        commands.push_back(normalize(trim(piece)));
    }
    return commands;
}

std::vector<std::string> split_words(std::string command) {
    std::vector<std::string> command_words;
    std::stringstream stream(command);
    std::string word;
    while (stream >> word) {
        command_words.push_back(normalize(word));
    }
    return command_words;
}

namespace {

// Used only in this file. execute_line supplies at least one word.
void run_command(std::vector<std::string> command_words) {
    pid_t pid = fork();
    if (pid == 0) {
        std::vector<char*> argv;
        for (std::string& word : command_words) {
            argv.push_back(word.data());
        }
        argv.push_back(nullptr);
        // argv[0] is the program. The rest are its arguments.
        execvp(argv[0], argv.data());
        std::perror("execvp");
        std::exit(1);
    } else if (pid < 0) {
        std::perror("Fork failed to create a new process.");
        std::exit(1);
    }
    // Wait for the child process to finish.
    waitpid(pid, nullptr, 0);
}

// cd changes this process. A child cannot change the shell's directory so this function is used in the parent shell process to change the directory.
void change_directory(const std::vector<std::string>& words) {
    if (words.size() > 2) {
        std::fprintf(stderr, "cd: too many arguments\n");
        return;
    }

    const char* path = nullptr;
    if (words.size() == 1) {
        path = std::getenv("HOME");
        if (path == nullptr) {
            std::fprintf(stderr, "cd: HOME is not set\n");
            return;
        }
    } else {
        path = words[1].c_str();
    }

    if (chdir(path) != 0) {
        std::perror("cd");
    }
}

} // namespace

bool execute_line(std::string line) {
    std::vector<std::string> commands = split_commands(line);
    for (const std::string& command : commands) {
        if (command == "quit") {
            return true;
        }
        std::vector<std::string> words = split_words(command);
        if (words.empty()) {
            continue;
        }
        if (words[0] == "cd") {
            change_directory(words);
            continue;
        }
        run_command(words);
    }
    return false;
}
