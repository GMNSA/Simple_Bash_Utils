#ifndef SRC_GREP_INCLUDES_F_GREP_H_
#define SRC_GREP_INCLUDES_F_GREP_H_

#include <regex.h>
#include <stdio.h>

#define SIZE_FLAGS 10
#define SIZE_BUFF 512
#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

typedef enum e_error {
  ERROR_OK = 0,
  ERROR_INVALID_OPTION,
  ERROR_UNKNOWN_FILE,
  ERROR_ARGUMENTS,
  ERROR_REGEX
} e_error;

// -------------------------------------------------------

typedef struct s_regex {
  regex_t regex;
  regmatch_t pmatch[1];
  regoff_t off;
  regoff_t len;
} s_regex;

// -------------------------------------------------------

typedef struct s_error {
  e_error error;
  char *p_error_name;
} s_error;

// -------------------------------------------------------

typedef struct s_line {
  int result;
  char *p_str;
  int n_line;
  unsigned n_match;
} s_line;

// -------------------------------------------------------

typedef struct s_deep2_array {
  char **data;
  unsigned n_data;
  unsigned n_col;
  unsigned n_row;
} s_deep2_array;

// -------------------------------------------------------

typedef struct s_data {
  int options[SIZE_FLAGS];
  s_deep2_array patterns;
  s_deep2_array filenames;
  int is_pattern;
  int is_lock;
  int *p_array_num;
  int is_show_full;
  unsigned np_array_num;
  int i_filename;
} s_data;

// -------------------------------------------------------

char *f_gets(FILE *file, int is_end_line);
char *f_strdup(const char *str_);
int option_assignment(s_data *data, const char *str);
int read_patterns_from_file(s_data *data_, char const *filename_,
                            s_error *error_, s_deep2_array **p_patterns);
int processing_flags(s_data **data_, s_error *error_, int argc_, char **argv_);
void display_chapter3(s_data *p_data_, s_line *line_, char *filename_);
void display_error(s_data *p_data, s_error *error);
void initialize_deep2(s_deep2_array **array);
void deep2_push(s_deep2_array **array, char *str);
void deep2_free(s_deep2_array **array);
void handling_option_o(s_data *data, s_regex *regex, char *text);

// -------------------------------------------------------

/*
 * -e pattern
 * -i Ignore uppercase vs. lowercase.
 * -v Invert match.
 * -c Output count of matching lines only.
 * -l Output matching files only.
 * -n Precede each matching line with a line number.
 * -h Output matching lines without preceding them by file names.
 * -s Suppress error messages about nonexistent or unreadable files.
 * -f file Take regexes from a file.
 * -o Output the matched parts of a matching line.

 * Usage: grep [OPTION]... PATTERNS [FILE]...
*/
void f_grep(int argc, char **argv);

#endif // SRC_GREP_INCLUDES_F_GREP_H_
