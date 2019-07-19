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

  #define EMBED "\t<embed src=\"%s\" width=\"100%%\" height=\"100%%\"></embed>"
  
  #define PRINT_OPTIONS printf(" \
    -i: input file name\n \
    -l: link to file (output file name must be specified)\n \
    -o: output file name (optional)\n \
    -b: browser (if no argument, launch default browser)\n \
    -p: print path to HTML file\n" \
    );

  int no_args_given(int argc);
  char* remove_file_extension(char* file);
  void open_html_file(char* htmlpath, char* browser);
  void make_html_file(char* swfpath, char* htmlpath);

#endif