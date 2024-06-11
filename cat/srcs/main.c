#include "../includes/s21_cat.h"
#include <stdio.h>

int main(int argc, char **argv) {
  char *filename = NULL;
  FILE *file = NULL;
  char c;
  s_step step;

  reboot_step(&step);
  if (argc >= 2) {
    filename = handling_arguments(argv, argc, &step);

    file = fopen(filename, "r");

    if (file) {
      while ((c = fgetc(file)) != EOF) {
        display_processing(c, &step);
      }
      fclose(file);
    }
  }
  return 0;
}
