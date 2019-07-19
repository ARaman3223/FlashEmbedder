#include "flashembed.h"

char* remove_file_extension(char* file) {
  char *y; int i;
  asprintf(&y, "%s", file);
  
  for (i = 0; i < strlen(y); i++) {
    if (y[strlen(y) - i] == '.') {
      y[strlen(y) - i] = 0;
      break;
    }
  } return y;
}

int no_args_given(int argc) {
  if (argc == 1) PRINT_OPTIONS;
  return 0;
}

void open_html_file(char* htmlpath, char* browser) {
  char *open;
  asprintf(&open, "%s%s", browser, htmlpath);
  system(open);
}

void make_html_file(char* swfpath, char* htmlpath) {
  FILE *fp;
  fp = fopen(htmlpath, "w");

  fprintf(fp, "<object>\n");
  fprintf(fp, EMBED, swfpath);
  fprintf(fp, "\n</object>");
  fclose(fp);
}