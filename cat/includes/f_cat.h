#ifndef CAT_INCLUDES_F_CAT_H_
#define CAT_INCLUDES_F_CAT_H_

#define SIZE_VAR 9
#define SIZE_ARRAY 10

/*
 * Arch Linux 5.15.40-1-lts GNU/Linux
 *
 * 0  -b (GNU: --number-nonblank) numbers only non-empty lines
 * 1  -e implies -v (GNU only: -E the same, but without implying v)
 *                   but also display end-of-line characters as $
 * 2  -n (GNU: --number) number all output lines
 * 3  -s (GNU: --squeeze-blank) squeeze multiple adjacent blank lines
 * 4  -t implies -v (GNU: -T the same, but without implying -v)
 *                   but also display tabs as ^I
 */

typedef struct s_step {
  char prev;
  char now;
  int n_empty_line;
  int line_num;
  int variant[SIZE_VAR];
  int do_a;
  int do_b;
  int do_c;
  int do_d;
  int do_i;
  int do_f;
  int is_short;
} s_step;

void add_char(char *str, int n, char c);
void reboot_step(s_step *step);
void reboot_do(s_step *step);
char *handling_arguments(char **argv, int argc, s_step *step);
// void step_a(char *c, char my_var[], unsigned size_my_var, s_step *step);
void step_a(s_step *step, char *c, char my_var[], unsigned n_my_var);
void step_c(s_step *step);
void step_b(s_step *step, int *is_num, char spec[]);
void step_f(s_step *step, char *c, char my_var[], unsigned n_my_var);

void display_processing(char c, s_step *step);

#endif // CAT_INCLUDES_F_CAT_H_
