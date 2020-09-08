#ifndef FLASH_EMBED
  #define FLASH_EMBED

  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <string.h>

  /* Each OS launches application differently */
  #if defined(__APPLE__)
    #define DEFAULT "open "
    #define BROWSER "open -a \"%s\" "
  #elif defined(__linux__)
    #define DEFAULT "xdg-open "
    #define BROWSER "%s "
  #endif


  #define EMBED_FULL "<object>\n\t<embed src=\"%s\" width=\"100%%\" height=\"100%%\"></embed>\n</object>"
  #define EMBED_WH "<object>\n\t<embed src=\"%s\" width=\"%d\" height=\"%d\"></embed>\n</object>"
  #define EMBED_SCALE "<object>\n\t<embed src=\"%s\" width=\"%d%%\" height=\"%d%%\"></embed>\n</object>"
  
  #define SET(x) x = (int) strtol(optarg, (char **)NULL, 10);
  #define PRINT_OPTIONS printf(" \
    -i: input file name\n \
    -l: link to file (output file name must be specified)\n \
    -o: output file name (optional)\n \
    -b: browser (if no argument, launch default browser)\n \
    -w: set embed width\n \
    -h: set embed height\n \
    -s: set embed scale\n \
    -p: print path to HTML file\n" \
  );

  enum Modeset { FULL_SIZE, WH, SCALE };
  int no_args_given(int argc);
  char* remove_file_extension(char* file);
  void open_html_file(char* htmlpath, char* browser);
  void make_html_file(char* swfpath, char* htmlpath);
  void make_html_file_wh(char* swfpath, char* htmlpath, int w, int h);
  void make_html_file_scale(char* swfpath, char* htmlpath, int s);
  enum Modeset check_mode(int w, int h, int s);

#endif

