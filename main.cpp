
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <list>
#include <stdexcept>

class FilenameMatcher {
private:
    std::unordered_map<std::string, int> filenameToNumberMap;
    std::vector<std::string> numberToFilenameVector;

public:
    FilenameMatcher(const std::vector<std::string>& filenames) {
        int number = 0;
        for (const auto& filename : filenames) {
            filenameToNumberMap[filename] = number;
            numberToFilenameVector.push_back(filename);
            number++;
        }
    }

    int filenameToNumber(const std::string& filename) {
        auto it = filenameToNumberMap.find(filename);
        if (it != filenameToNumberMap.end()) {
            return it->second;
        }
        throw std::runtime_error("Filename not found");
    }

    std::string numberToFilename(int number) {
        if (number >= 0 && number < numberToFilenameVector.size()) {
            return numberToFilenameVector[number];
        }
        throw std::runtime_error("Number out of range");
    }
};

class DependencyProvider {
private:
    FilenameMatcher& matcher;
    std::unordered_map<int, std::set<int>> fileDependencies;

public:
    DependencyProvider(const std::vector<std::string>& fileContents, FilenameMatcher& matcher)
        : matcher(matcher) {
        for (int i = 0; i < fileContents.size(); ++i) {
            std::set<int> dependencies;
            const auto& content = fileContents[i];
            size_t pos = 0;
            while ((pos = content.find("#include", pos)) != std::string::npos) {
                size_t start = content.find("\"", pos + 1) + 1;
                size_t end = content.find("\"", start);
                std::string filename = content.substr(start, end - start);
                dependencies.insert(matcher.filenameToNumber(filename));
                pos = end + 1;
            }
            fileDependencies[i] = dependencies;
        }
    }

    const std::unordered_map<int, std::set<int>>& getDependencies() const {
        return fileDependencies;
    }
};

class OrderValidator {
private:
    const std::unordered_map<int, std::set<int>>& dependencies;

    bool dfs(int node, std::unordered_set<int>& visited, std::unordered_set<int>& recStack) {
        if (visited.find(node) == visited.end()) {
            visited.insert(node);
            recStack.insert(node);

            for (int dep : dependencies.at(node)) {
                if (recStack.find(dep) != recStack.end()) {
                    return false; // Found a cycle
                }
                if (!dfs(dep, visited, recStack)) {
                    return false; // Cycle in subsequent calls
                }
            }
        }
        recStack.erase(node);
        return true;
    }

public:
    OrderValidator(const std::unordered_map<int, std::set<int>>& deps) : dependencies(deps) {}

    bool isOrderCorrect(const std::vector<int>& order) {
        std::unordered_set<int> visited;
        std::unordered_set<int> recStack;

        for (int fileNumber : order) {
            if (!dfs(fileNumber, visited, recStack)) {
                return false; // Cycle detected
            }
        }
        return true;
    }
};

int main() {
    // Example usage
    std::vector<std::string> filenames = {"header1.h", "header2.h", "header3.h"};
    std::vector<std::string> fileContents = {
        "#include \"header2.h\"",
        "#include \"header3.h\"",
        "" // header3.h has no dependencies
    };

    FilenameMatcher matcher(filenames);
    DependencyProvider provider(fileContents, matcher);
    
    OrderValidator validator(provider.getDependencies());

    std::vector<int> order = {2, 1, 0}; // Example order of processing

    if (validator.isOrderCorrect(order)) {
        std::cout << "File processing order is correct." << std::endl;
    } else {
        std::cout << "Incorrect file processing order." << std::endl;
    }

    return 0;
}
