# IsOrderOfProcessingCorect
--

# Filename Dependency Manager

## Overview

This C++ project provides a system for managing dependencies among files. It includes functionalities for mapping filenames to numeric identifiers, detecting and managing file dependencies based on their content, and validating the correct order of file processing based on these dependencies.

## Features

- Filename Matcher: Maps filenames to numeric identifiers and vice versa, facilitating easier tracking and referencing.
- Dependency Provider: Analyzes file contents to extract dependencies, represented as #include statements, and maintains a record of these dependencies.
- Order Validator: Validates the order of file processing, ensuring that all dependencies are resolved correctly and there are no cyclic dependencies.

## Getting Started

### Prerequisites

- A C++ compiler (e.g., GCC, Clang)
- Basic understanding of C++ and file handling

### Installation

1. Clone the repository:
      git clone [repository-url]
   

2. Navigate to the project directory:
      cd [project-name]
   

3. Compile the project using your C++ compiler. For example, with GCC:
      g++ -o filename-dependency-manager main.cpp
   

### Usage

1. Modify the filenames and fileContents vectors in main.cpp to reflect your files and their dependencies.
2. Compile and run the program:
      ./filename-dependency-manager
   
3. The program will output whether the file processing order is correct.

## Contributing

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are greatly appreciated.

1. Fork the Project
2. Create your Feature Branch (git checkout -b feature/AmazingFeature)
3. Commit your Changes (git commit -m 'Add some AmazingFeature')
4. Push to the Branch (git push origin feature/AmazingFeature)
5. Open a Pull Request

---
