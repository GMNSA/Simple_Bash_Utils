/**
 * @file main.c
 * @brief   The grep utility is used for searching text using patterns.
 *               -e pattern
 *               -i Ignore uppercase vs. lowercase.
 *               -v Invert match.
 *               -c Output count of matching lines only.
 *               -l Output matching files only.
 *               -n Precede each matching line with a line number.
 *               -h Output matching lines without preceding them by file names.
 *               -s Suppress error messages about nonexistent or unreadable
 files.
 *               -f file Take regexes from a file.
 *               -o Output the matched parts of a matching line.

 *                Usage: grep [OPTION]... PATTERNS [FILE]...
 * @author GMNS
 * @version https://github.com/GMNSA
 */

#include "../includes/f_grep.h"

// -------------------------------------------------------

int main(int argc, char *argv[]) {
  f_grep(argc, argv);

  return 0;
}
