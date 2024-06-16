#include "../includes/f_grep.h"

#include <stdlib.h>
#include <string.h>

void reset_array_num(s_data *data_);
void reset_data(s_data **data);
void reset_regex(s_regex *regex);
void reset_error(s_error **error);

// -------------------------------------------------------

int is_repeated_pattern(s_deep2_array *patterns_, char const *str_) {
  unsigned n_pattern = patterns_->n_data;
  int res = 0;
  for (unsigned i = 0; i < n_pattern; ++i) {
    if (strcmp(patterns_->data[i], str_) == 0) {
      res = 1;
      break;
    }
  }
  return (res);
}

// -------------------------------------------------------

void sort_pattern(s_deep2_array **pattern) {
  char *tmp = NULL;
  if (*(*pattern)->data) {
    for (unsigned i = 0; i < (*pattern)->n_data - 1; ++i) {
      for (unsigned j = 0; j < (*pattern)->n_data - 1; ++j) {
        if (strcmp((*pattern)->data[j], (*pattern)->data[j + 1]) < 0) {
          tmp = (*pattern)->data[j];
          (*pattern)->data[j] = (*pattern)->data[j + 1];
          (*pattern)->data[j + 1] = tmp;
        }
      }
    }
  }
}

// -------------------------------------------------------

void swap_int(int *a, int *b) {
  *a = *a ^ *b;
  *b = *b ^ *a;
  *a = *a ^ *b;
}

// -------------------------------------------------------

void reset_array_num(s_data *data_) {
  if (data_->p_array_num) {
    free(data_->p_array_num);
  }
  data_->np_array_num = 0;
  data_->is_lock = 0;
}

// -------------------------------------------------------

void sort_array_int(int *array, s_data *data) {
  int n_array = data->np_array_num - 1;

  for (int i = 0; i < n_array - 2; i += 2) {
    for (int j = 0; j < n_array - i - 2; j += 2) {
      if (array[j] > array[j + 2]) {
        swap_int(&array[j], &array[j + 2]);
        swap_int(&array[j + 1], &array[j + 3]);
      }
    }
  }
}

// -------------------------------------------------------

void initialize_deep2(s_deep2_array **array) {
  (*array)->data = NULL;
  (*array)->n_data = 0;
  (*array)->n_col = 0;
  (*array)->n_row = 10;
  if (!((*array)->data =
            (char **)calloc((*array)->n_row, sizeof(*(*array)->data)))) {
    exit(13);
  }
  for (unsigned i = 0; i < (*array)->n_row; ++i) {
    (*array)->data[i] = NULL;
  }
}

// -------------------------------------------------------

void deep2_push(s_deep2_array **array, char *str) {
  if (str != NULL) {
    if ((*array)->n_data >= (*array)->n_row - 1) {
      (*array)->n_row *= 2;
      if (!((*array)->data = (char **)realloc(
                (*array)->data, sizeof(*(*array)->data) * (*array)->n_row))) {
        exit(13);
      }
    }
    (*array)->data[(*array)->n_data++] = str;
  }
}

// -------------------------------------------------------

void deep2_free(s_deep2_array **array) {
  if ((*array)->data) {
    for (unsigned i = 0; i < (*array)->n_data; ++i) {
      if ((*array)->data[i]) {
        free((*array)->data[i]);
      }
    }
    free((*array)->data);
  }
}

// -------------------------------------------------------

char *f_gets(FILE *file, int is_end_line) {
  char *p_str = NULL;
  char c = '\0';
  int i_step = 1;
  int is_find_let = 0;
  int is_stop = 1;

  if (file) {
    if (!(p_str = (char *)calloc(SIZE_BUFF + 1, sizeof(char)))) {
      fclose(file);
      exit(13);
    }
    for (unsigned i = 0; is_stop; ++i) {
      c = fgetc(file);
      if (!is_end_line) {
        if ((c == '\n' || (c == ' ' && is_find_let)) || c == EOF) {
          if (c == EOF) {
            p_str[i] = EOF;
          } else {
            p_str[i] = '\0';
          }
          is_stop = 0;
        } else {
          is_find_let = 1;
          p_str[i] = c;
        }
      } else if (is_end_line) {
        if (c == '\n' || c == EOF) {
          if (c == EOF) {
            p_str[i] = EOF;
          } else {
            p_str[i] = '\0';
          }
          is_stop = 0;
        } else {
          p_str[i] = c;
        }
      }

      if (i >= SIZE_BUFF) {
        if (!(p_str = (char *)realloc(p_str, SIZE_BUFF * (++i_step)))) {
          fclose(file);
          exit(13);
        }
      }
    }
  }
  return (p_str);
}

// -------------------------------------------------------

int read_patterns_from_file(s_data *data_, char const *filename_,
                            s_error *error_, s_deep2_array **p_patterns) {
  int is_error = 1;
  FILE *fin = fopen(filename_, "r");
  char *p_str = NULL;

  if (!fin) {
    is_error = 0;
    error_->error = ERROR_UNKNOWN_FILE;
    error_->p_error_name = f_strdup(filename_);
  } else {
    while ((p_str = f_gets(fin, 1)) && *p_str != EOF) {
      if (!is_repeated_pattern(*p_patterns, p_str)) {
        if (strlen(p_str) == 0) {
          data_->is_show_full = 1;
          free(p_str);
        } else {
          deep2_push(p_patterns, p_str);
        }
      }
    }
    if (p_str) {
      free(p_str);
    }
    fclose(fin);
  }

  return (is_error);
}

// -------------------------------------------------------

void reset_data(s_data **data) {
  (*data)->is_pattern = 0;
  (*data)->p_array_num = NULL;
  (*data)->np_array_num = 0;
  (*data)->i_filename = 0;
  (*data)->is_show_full = 0;
  s_deep2_array *p_patterns = &(*data)->patterns;
  s_deep2_array *p_filenames = &(*data)->filenames;
  initialize_deep2(&p_patterns);
  initialize_deep2(&p_filenames);

  for (int i = 0; i < SIZE_FLAGS; ++i) {
    (*data)->options[i] = 0;
  }
}

// -------------------------------------------------------

char *f_strdup_char(const char ch_) {
  char *str = NULL;

  if (!(str = (char *)calloc(3, sizeof(char)))) {
    exit(13);
  }
  str[0] = ch_;
  str[1] = '\0';
  str[2] = '\0';

  return (str);
}

// -------------------------------------------------------

char *f_strdup(const char *str_) {
  char *str = NULL;
  unsigned n_str = 0;

  if (str_ != NULL) {
    n_str = strlen(str_);
  }

  if (!(str = (char *)calloc(n_str + 1, sizeof(char)))) {
    exit(13);
  }
  memcpy(str, str_, n_str);

  return (str);
}

// -------------------------------------------------------

int option_assignment(s_data *data, const char *str) {
  int res = 1;

  if (strcmp("-e", str) == 0) {
    data->options[0] = 1;
  } else if (strcmp("-i", str) == 0) {
    data->options[1] = 1;
  } else if (strcmp("-v", str) == 0) {
    data->options[2] = 1;
  } else if (strcmp("-c", str) == 0) {
    data->options[3] = 1;
  } else if (strcmp("-l", str) == 0) {
    data->options[4] = 1;
  } else if (strcmp("-n", str) == 0) {
    data->options[5] = 1;
  } else if (strcmp("-h", str) == 0) {
    data->options[6] = 1;
  } else if (strcmp("-s", str) == 0) {
    data->options[7] = 1;
  } else if (strcmp("-f", str) == 0) {
    data->options[8] = 1;
  } else if (strcmp("-o", str) == 0) {
    data->options[9] = 1;
  } else {
    res = 0;
  }

  return (res);
}

// -------------------------------------------------------

int count_elements(int argc, char **argv) {
  int n_elements = 0;

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] != '-') {
      n_elements += 1;
    }
  }

  return (n_elements);
}

// -------------------------------------------------------

int processing_flags(s_data **data_, s_error *error_, int argc_, char **argv_) {
  char tmp[4] = {"\0"};
  int n_tmp_argv_ = 0;
  int is_pattern_found = 0;
  int is_read_from_file = 0;
  s_data *p_data = *data_;
  s_deep2_array *p_filenames = &p_data->filenames;
  s_deep2_array *p_patterns = &p_data->patterns;

  reset_data(&p_data);
  p_data->is_pattern = argv_[1][0] != '-' ? 1 : 0;

  for (int i = 1; i < argc_ && error_->error == ERROR_OK; ++i) {
    if (is_read_from_file) {
      read_patterns_from_file(p_data, argv_[i], error_, &p_patterns);
      is_read_from_file = 0;
      p_data->is_pattern = 0;
    } else if (argv_[i][0] != '-') {
      if (p_data->is_pattern || (is_pattern_found && i != 1)) {
        deep2_push(&p_patterns, f_strdup(argv_[i]));
        is_pattern_found = 0;
        if (argc_ - 1 > i) {
          if (argv_[i + 1][0] != '-') {
            p_data->is_pattern = 0;
          }
        }
      } else {
        deep2_push(&p_filenames, f_strdup(argv_[i]));
      }
    } else {
      if (strlen(argv_[i]) > 2) {
        n_tmp_argv_ = strlen(argv_[i]);
        for (int j = 1; j < n_tmp_argv_ && error_->error == ERROR_OK; ++j) {
          tmp[0] = '-';
          tmp[1] = argv_[i][j];
          tmp[2] = '\0';
          if (argv_[i][j] == 'e') {
            if (i == argc_ - 1) {
              is_read_from_file = 1;
            }
            option_assignment(p_data, "-e");
            option_assignment(p_data, tmp);
            if ((argv_[i][j + 1]) != '\0') {
              deep2_push(&p_patterns, f_strdup(argv_[i] + j + 1));
              p_data->is_pattern = 0;
              is_pattern_found = 0;
              break;
            } else {
              p_data->is_pattern = 1;
            }
          } else if (argv_[i][j] == 'f') {
            option_assignment(p_data, "-f");
            option_assignment(p_data, tmp);
            if ((argv_[i][j + 1]) != '\0') {
              read_patterns_from_file(p_data, argv_[i] + j + 1, error_,
                                      &p_patterns);
            } else {
              is_read_from_file = 1;
            }
          } else {
            if (!option_assignment(p_data, tmp)) {
              error_->error = ERROR_INVALID_OPTION;
              error_->p_error_name = f_strdup_char(tmp[1]);
            }
            p_data->is_pattern = 1;
          }
        }
      } else {
        if (argv_[i][1] == 'f') {
          is_read_from_file = 1;
        } else if (argv_[i][0] == '-') {
          p_data->is_pattern = 1;
        }
        if (!option_assignment(p_data, argv_[i])) {
          error_->error = ERROR_INVALID_OPTION;
          error_->p_error_name = f_strdup_char(argv_[i][strlen(argv_[i] - 1)]);
          exit(-1);
        }
      }
    }
  }

  return (1);
}

// -------------------------------------------------------

void display_chapter3(s_data *data_, s_line *line_, char *filename_) {
  if ((data_->options[4] && line_->n_match > 0) ||
      (data_->options[4] && data_->options[2])) {
    if (data_->options[2]) {
      if (line_->n_match > 2) {
        printf("%s\n", filename_);
      }
    } else {
      printf("%s\n", filename_);
    }
  }
  if (data_->options[3] && !data_->options[6] && !data_->options[4] &&
      data_->filenames.n_data > 1) {
    printf("%s:%d\n", filename_, line_->n_match);
  }
  if (data_->options[3] && !data_->options[6] && !data_->options[4] &&
      data_->filenames.n_data == 1) {
    printf("%d\n", line_->n_match);
  }
  if (data_->options[3] && data_->options[6] && !data_->options[4]) {
    printf("%d\n", line_->n_match);
  }
}

// -------------------------------------------------------

void display_error(s_data *data_, s_error *error_) {
  if (!data_->options[7]) {
    if (error_->error == ERROR_UNKNOWN_FILE) {
      fprintf(stderr, "grep: %s: No such file or directory\n",
              error_->p_error_name);
    } else if (error_->error == ERROR_INVALID_OPTION) {
      fprintf(stderr, "grep: --invalid option -- '%s'\n", error_->p_error_name);
    } else if (error_->error == ERROR_REGEX) {
      fprintf(stderr, "grep: -- %s --\n", error_->p_error_name);
    }
  }
  error_->error = ERROR_OK;

  if (error_->p_error_name) {
    free(error_->p_error_name);
    error_->p_error_name = NULL;
  }
}

// -------------------------------------------------------

void reset_regex(s_regex *regex) {
  regex->pmatch[0].rm_eo = 0;
  regex->pmatch[0].rm_eo = 0;
  regex->off = 0;
  regex->len = 0;
}

// -------------------------------------------------------

void display_o(s_data *data, s_line *line) {
  s_data *p_data = data;
  int len = 0;

  if (p_data->options[9] && !data->options[3] && !data->options[4]) {
    data->p_array_num[data->np_array_num++] = -1;
    sort_array_int(data->p_array_num, data);
    for (unsigned i = 0; i < data->np_array_num - 1 && !data->options[2];
         i += 2) {
      if (len <= data->p_array_num[i] && !data->options[3]) {
        if (!data->options[6] && data->filenames.n_data >= 2) {
          printf("%s:", data->filenames.data[data->i_filename]);
        }
        if (data->options[5]) {
          printf("%d:", line->n_line);
        }
        if (!data->options[2]) {
          printf("%.*s\n", data->p_array_num[i + 1],
                 line->p_str + data->p_array_num[i]);
        }
        len = data->p_array_num[i + 1] + data->p_array_num[i];
      }
    }
  }
}

// -------------------------------------------------------

void reset_line(s_line *line) {
  line->result = 0;
  line->p_str = NULL;
  line->n_line = 0;
  line->n_match = 0;
}

// -------------------------------------------------------

void processing_o(s_data *data, s_error *error_, s_line *line, s_regex *regex) {
  int result = 0;

  for (unsigned j = 0; j < data->patterns.n_data; ++j) {
    if (!data->options[1]) {
      line->result =
          regcomp(&regex->regex, data->patterns.data[j], REG_EXTENDED);
    } else {
      line->result = regcomp(&regex->regex, data->patterns.data[j], REG_ICASE);
    }

    if (line->result) {
      if (line->result == REG_ESPACE) {
        error_->error = ERROR_REGEX;
        error_->p_error_name = f_strdup("ERROR REGEX\n");
      }
    } else {
      result = regexec(&regex->regex, line->p_str, ARRAY_SIZE(regex->pmatch),
                       regex->pmatch, 0);

      if (data->is_show_full) {
        result = 0;
      }

      if (!result) {
        if (!data->options[4]) {
          handling_option_o(data, regex, line->p_str);
        }
        if (!data->is_lock) {
          if (!data->options[2]) {
            ++line->n_match;
          }
          data->is_lock = 1;
        }
      }
    }

    regfree(&regex->regex);
  }

  if (!data->is_lock && data->options[2]) {
    ++line->n_match;
    data->is_lock = 1;
  }
}

// -------------------------------------------------------

void display_chapter2(s_data *data, s_line *line_, char *filename) {
  ++line_->n_match;
  if (!data->options[4] && !data->options[3]) {
    if (!data->options[6] && data->filenames.n_data >= 2) {
      printf("%s:", filename);
    }

    if (data->options[5]) {
      printf("%d:", line_->n_line);
    }
    printf("%s\n", line_->p_str);
  }
}

// -------------------------------------------------------

void processing_flag(s_data *data_, s_error *error_, s_line *line_,
                     char *filename, s_regex *regex) {
  int result = 0;
  int is_lock_v = 0;

  if (data_->options[9]) {
    processing_o(data_, error_, line_, regex);
  } else {
    for (unsigned j = 0; j < data_->patterns.n_data; ++j) {
      if (!data_->options[1]) {
        line_->result =
            regcomp(&regex->regex, data_->patterns.data[j], REG_EXTENDED);
      } else {
        line_->result =
            regcomp(&regex->regex, data_->patterns.data[j], REG_ICASE);
      }

      if (line_->result) {
        if (line_->result == REG_ESPACE) {
          fprintf(stderr, "%s\n", "ERROR REG!!!!\n");
        } else {
          fprintf(stderr, "%s\n", "SYNTAX ERROR REG!!!!\n");
        }
      } else {
        result = regexec(&regex->regex, line_->p_str, 0, NULL, 0);

        if (data_->is_show_full) {
          result = 0;
        }

        if (data_->options[2]) {
          result = result == 1 ? 0 : 1;
        }

        if (data_->options[2] && result) {
          is_lock_v = 1;
        }

        if (!data_->is_lock) {
          if (!result) {
            if (!data_->options[2]) {
              display_chapter2(data_, line_, filename);
            }
            data_->is_lock = 1;
          }
        }
      }

      regfree(&regex->regex);
    }

    if (is_lock_v == 0 && data_->options[2]) {
      display_chapter2(data_, line_, filename);
    }
  }
}

// -------------------------------------------------------

void handling_option_o(s_data *data, s_regex *regex, char *text) {
  char *s = text;
  int *p_array_num = data->p_array_num;

  while (1) {
    if (regexec(&regex->regex, s, ARRAY_SIZE(regex->pmatch), regex->pmatch, 0))
      break;

    regex->off = regex->pmatch[0].rm_so + (s - text);
    regex->len = regex->pmatch[0].rm_eo - regex->pmatch[0].rm_so;
    p_array_num[data->np_array_num++] = regex->off;
    p_array_num[data->np_array_num++] = regex->len;
    s += regex->pmatch[0].rm_eo;
  }
}

// -------------------------------------------------------

void f_grep(int argc, char **argv) {
  s_data data;
  s_data *p_data = &data;
  s_deep2_array *p_filenames = &p_data->filenames;
  s_deep2_array *p_patterns = &p_data->patterns;
  s_regex regex;
  s_line line;
  s_error error;
  s_error *p_error = &error;

  FILE *fin = NULL;

  reset_line(&line);
  reset_regex(&regex);
  reset_error(&p_error);
  processing_flags(&p_data, &error, argc, argv);

  if (argc < 3) {
    error.error = ERROR_ARGUMENTS;
    error.p_error_name = f_strdup("grep: Few arguments.\n");
  } else if (error.error == ERROR_OK) {
    sort_pattern(&p_patterns);
    for (unsigned i = 0; i < p_filenames->n_data; ++i) {
      reset_line(&line);
      line.n_line = 1;
      p_data->is_lock = 0;
      p_data->i_filename = i;
      fin = fopen(p_filenames->data[i], "r");

      if (fin) {
        line.n_line = 1;
        while ((line.p_str = f_gets(fin, 1)) && *line.p_str != EOF) {
          if (!(data.p_array_num =
                    (int *)calloc(strlen(line.p_str) * 2 + 2, sizeof(int)))) {
            exit(13);
          }

          processing_flag(&data, &error, &line, p_filenames->data[i], &regex);

          display_o(&data, &line);
          free(line.p_str);
          ++line.n_line;
          reset_array_num(&data);
        }

        display_chapter3(p_data, &line, p_filenames->data[i]);
        free(line.p_str);
        fclose(fin);
      } else {
        error.error = ERROR_UNKNOWN_FILE;
        error.p_error_name = f_strdup(p_filenames->data[i]);
        display_error(p_data, &error);
      }
    }
  }

  display_error(p_data, p_error);
  deep2_free(&p_patterns);
  deep2_free(&p_filenames);
}

// -------------------------------------------------------

void reset_error(s_error **error_) {
  (*error_)->error = ERROR_OK;
  (*error_)->p_error_name = NULL;
}
