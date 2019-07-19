//
//  FlashEmbedder
//
//  Created by John Connery on 7/16/19.
//  Copyright © 2019 John Connery. All rights reserved.
//
//  Make an .html file embedding an .swf file
//

#include "flashembed.h"
enum output{ UNUSED, LINK_ONLY, OUTPUT_ONLY, BOTH };

int main(int argc, char *argv[]) {
  int opt;
  char* swf_path = NULL;
  char* html_path = NULL;
  char* browser = NULL;
  int print_flag = 0;
  enum output is_output_given = UNUSED;

  no_args_given(argc);

  while ((opt = getopt(argc, argv,":i:l:o:b:p")) != -1) {
    switch (opt) {
      case 'l': // link arg
        is_output_given = LINK_ONLY;
      case 'i': // input file arg
        swf_path = optarg;
        break;
      case 'o': // output file arg
        html_path = optarg;
        is_output_given += 2;
        break;
      case 'b': // browser arg
        if (optarg[0] != '-')
          asprintf(&browser, BROWSER, optarg);
        else {
          browser = DEFAULT;
          optind -= 1;
        }
        break;
      case 'p': // print arg
        print_flag ^= 1;
        break;
      case ':':
        switch (optopt) {
          case 'b':
              browser = DEFAULT;
              break;
          default:
              fprintf(stderr, "Option -%c is missing a required argument\n", optopt);
              return EXIT_FAILURE;
        }
        break;
      case '?': // error
        fprintf(stderr, "Invalid option: -%c\n", optopt);
        return EXIT_FAILURE;
      default: ;
    }
  }

  /* An error is thrown if an output file is not given to a link */
  switch (is_output_given) {
    case LINK_ONLY: // l is just called
        fprintf(stderr, "Option -l requires an output file\n");
        return EXIT_FAILURE;
    case UNUSED: // none are called
    case OUTPUT_ONLY: // o is just called
    case BOTH: // l & o are called
    default:
        break;
  }

  char *default_html_path;
  asprintf(&default_html_path, "%s%s", remove_file_extension(swf_path), ".html");
  
  html_path = (html_path == NULL) ? default_html_path : html_path;
  if (print_flag == 1) printf("%s", html_path);

  make_html_file(swf_path, html_path);
  if (browser != NULL) open_html_file(html_path, browser);

  return 0;
}
