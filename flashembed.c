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

enum Modeset check_mode(int w, int h, int s) {
  enum Modeset mode;

  /* Width & Height take priority over Scale */
  if (w <= 0 || h <= 0) {
    if (s <= 0)
      mode = FULL_SIZE;
    else if (s > 0)
      mode = SCALE;
  } else if (w >= 0 && h >= 0)
    mode = WH;

  return mode;
}

void make_html_file_wh(char* swfpath, char* htmlpath, int w, int h) {
  FILE *fp;

  if (htmlpath != NULL) {
    fp = fopen(htmlpath, "w");
  } else {
    fprintf(stderr, "Error opening html file\n");
    exit(0);
  }

  fprintf(fp, EMBED_WH, swfpath, w, h);
  fclose(fp);
}

void make_html_file_scale(char* swfpath, char* htmlpath, int s) {
  FILE *fp;

  if (htmlpath != NULL) {
    fp = fopen(htmlpath, "w");
  } else {
    fprintf(stderr, "Error opening html file\n");
    exit(0);
  }

  fprintf(fp, EMBED_SCALE, swfpath, s, s);
  fclose(fp);
}

void make_html_file(char* swfpath, char* htmlpath) {
  FILE *fp;
 
  if (htmlpath != NULL) {
    fp = fopen(htmlpath, "w");
  } else {
    fprintf(stderr, "Error opening html file\n");
    exit(0);
  }
  
  fprintf(fp, EMBED_FULL, swfpath);
  fclose(fp);
}
