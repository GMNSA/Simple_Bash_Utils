# Simple_Bash_Utils
## Development of Bash text utilities: cat, grep.
## `cat` and `grep` Programs - Options Description

## Introduction

This project includes implementations of the `cat` and `grep` utilities, commonly used in Unix-like operating systems for reading and searching text files, respectively.

## `cat` Utility

The `cat` (short for "concatenate") utility is used to read and concatenate files, then output their contents to the standard output.

### Options

| №  | Option                                       | Description                                                 |
|----|----------------------------------------------|-------------------------------------------------------------|
| 1  | `-b` (GNU: `--number-nonblank`)              | Numbers only non-empty lines.                               |
| 2  | `-e` implies `-v` (GNU only: `-E`)           | Also displays end-of-line characters as `$`.                |
| 3  | `-n` (GNU: `--number`)                       | Numbers all output lines.                                   |
| 4  | `-s` (GNU: `--squeeze-blank`)                | Suppresses repeated adjacent blank lines.                   |
| 5  | `-t` implies `-v` (GNU: `-T`)                | Also displays tab characters as `^I`.                       |

### Usage Example

#### Example 1: Numbering all lines
cat -n file.txto

Example 2: Numbering only non-empty lines
cat -b file.txto

Example 3: Squeezing adjacent blank lines
cat -s file.txt

Example 4: Displaying end-of-line characters and tabs
cat -e -t file.txt


## grep Utility
The grep utility is used for searching text using patterns.

Options
№	Option	Description
1	-e	Pattern
2	-i	Ignores case distinctions.
3	-v	Inverts the sense of matching, to select non-matching lines.
4	-c	Prints only a count of matching lines per file.
5	-l	Prints only names of files with matching lines.
6	-n	Prefixes each line of output with the line number within its input file.
7	-h	Suppresses the prefixing of file names on output.
8	-s	Suppresses error messages about nonexistent or unreadable files.
9	-f file	Takes patterns from the specified file.
10	-o	Prints only the matched (non-empty) parts of matching lines.

Usage Example
Example 1: Searching for a pattern in a file

Example 2: Ignoring case distinctions
grep -i pattern file.txt

Example 3: Inverting the sense of matching
grep -v pattern file.txt

Example 4: Counting matching lines
grep -c pattern file.txt

## Project Structure
The project is structured to ensure modularity and clarity, following standard practices for organizing code and build files.

## cat Utility
* The source code, headers, and build files are located in the src/cat/ directory.
* The final executable is located in the src/cat/ directory and named s21_cat.
* The utility supports all specified options for enhanced text processing.

## grep Utility
* The source code, headers, and build files are located in the src/grep/ directory.
* The final executable is located in the src/grep/ directory and named s21_grep.
* The utility supports a comprehensive set of options for flexible pattern matching.

## Build and Installation
The build process is managed using a Makefile. To build the utilities, navigate to the project root directory and run:
This command will compile the source code and produce the executables s21_cat and s21_grep in their respective directories.

## Testing
Integration tests are included to ensure the correct functionality of all options and their combinations. These tests compare the output of s21_cat and s21_grep with the behavior of the standard utilities.

make test
