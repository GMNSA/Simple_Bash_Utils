#include "../includes/f_cat.h"
#include <stdio.h>
#include <string.h>

void add_char(char *str, int n, char c) {
  int i = 0;
  while (i < n && *str != '\0') {
    ++str;
    ++i;
  }

  *str = c;
}

// -------------------------------------------------------

void reboot_step(s_step *step) {
  step->prev = '\n';
  step->now = '\0';
  step->n_empty_line = 0;
  step->line_num = 0;
  step->is_short = 0;

  for (int i = 0; i < SIZE_VAR; ++i) {
    step->variant[i] = 0;
  }
}

// -------------------------------------------------------

void reboot_do(s_step *step) {
  step->do_a = 0;
  step->do_b = 0;
  step->do_c = 0;
  step->do_d = 0;
  step->do_i = 0;
  step->do_f = 0;
  step->is_short = 0;

  if (step->variant[1]) {
    step->do_a = 1;
  }
  if (step->variant[2]) {
    step->do_b = 1;
    step->do_c = 1;
  }
  if (step->variant[3]) {
    step->do_a = 1;
    step->do_d = 1;
  }
  if (step->variant[4]) {
    step->do_b = 1;
  }
  if (step->variant[5]) {
    step->do_i = 1;
  }
  if (step->variant[6]) {
    step->do_a = 1;
    step->do_f = 1;
  }
  if (step->variant[7]) {
    step->do_d = 1;
  }
  if (step->variant[8]) {
    step->do_f = 1;
  }
}

// -------------------------------------------------------

char *handling_arguments(char **argv, int argc, s_step *step) {
  char *filename = NULL;
  int n_argv = 0;
  int size = 0;
  if (argc == 2 && argv[1][0] != '-') {
    filename = argv[1];
    step->variant[0] = 1;
  } else {
    for (int i = 1; i < argc; ++i) {
      n_argv = strlen(argv[i]);
      size = n_argv > 3 ? n_argv : 3;
      if (argv[i][0] == '-') {
        if ((strcmp(argv[i], "-v") == 0)) {
          step->variant[1] = 1;
        } else if ((strcmp(argv[i], "-b") == 0) ||
                   (strncmp("--number-nonblank", argv[i],
                            size < 9 ? 9 : size) == 0)) {
          step->variant[2] = 1;
        } else if (strcmp(argv[i], "-e") == 0) {
          step->variant[3] = 1;
        } else if ((strcmp(argv[i], "-n") == 0) ||
                   (strcmp("--number", argv[i]) == 0)) {
          step->variant[4] = 1;
        } else if ((strcmp(argv[i], "-s") == 0) ||
                   (strncmp("--squeeze-blank", argv[i], size < 3 ? 3 : size) ==
                    0)) {
          step->variant[5] = 1;
        } else if (strcmp(argv[i], "-t") == 0) {
          step->variant[6] = 1;
        } else if ((strcmp(argv[i], "-E") == 0)) {
          step->variant[7] = 1;
        } else if ((strcmp(argv[i], "-T") == 0)) {
          step->variant[8] = 1;
        }
      } else {
        filename = argv[i];
      }
    }
  }

  return (filename);
}

// -------------------------------------------------------

void step_a(s_step *step, char *c, char my_var[], unsigned n_my_var) {
  if (step->do_a) {
    if ((*c < 32 && *c != 10 && *c != 13 && *c != 9) || *c == 127) {
      if (*c == 127) {
        *c = '?';
      } else {
        *c += 64;
      }
      snprintf(my_var, n_my_var, "%s", "^");
    }
  }
}

// -------------------------------------------------------

void step_c(s_step *step) {
  if (step->do_c)
    step->is_short = 1;
}

// -------------------------------------------------------

void step_b(s_step *step, int *is_num, char spec[]) {
  if (step->do_b) {
    if (step->is_short) {
      if (step->prev == '\n' && step->now != '\n') {
        ++step->line_num;
        snprintf(spec, SIZE_VAR, "%s", "%6d\t");
        *is_num = 1;
      }
    } else {
      if (step->prev == '\n') {
        if (step->n_empty_line <= 2) {
          ++step->line_num;
        }
        snprintf(spec, SIZE_VAR, "%s", "%6d\t");
        *is_num = 1;
      }
    }
  }
}

// -------------------------------------------------------

void step_f(s_step *step, char *c, char my_var[], unsigned n_my_var) {
  if (step->do_f) {
    if (*c == '\t') {
      snprintf(my_var, n_my_var, "%s", "^");
      *c = 'I';
    }
  }
}

// -------------------------------------------------------

void display_processing(char c, s_step *step) {
  char spec[SIZE_VAR] = {"\0"};
  char my_var[SIZE_VAR] = {"\0"};
  int is_num = 0;

  step->now = c;
  reboot_do(step);

  step_a(step, &c, my_var, SIZE_VAR);
  step_c(step);
  step_b(step, &is_num, spec);
  step_f(step, &c, my_var, SIZE_VAR);

  if (step->do_d) {
    if (step->now == '\n') {
      strcat(my_var, "$");
    }
  }

  if (step->do_i) {
    if (c == '\n') {
      ++step->n_empty_line;
    }
  }

  if (c != '\n')
    step->n_empty_line = 0;

  strcat(my_var, "%c");
  strcat(spec, my_var);
  if (step->n_empty_line <= 2) {
    if (is_num) {
      printf(spec, step->line_num, c);
    } else {
      printf(spec, c);
    }
  }

  step->prev = step->now;
}
