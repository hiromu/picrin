#include <stdio.h>

#include "picrin.h"

void
test_object_creation(pic_state *pic)
{
  pic_value v;

  {
    v = pic_intern_cstr(pic, "symbol");
    pic_debug(pic, v);
    puts(" [should be `symbol`]");
  }
  {
    v = pic_nil_value();
    pic_debug(pic, v);
    puts(" [should be `()`]");
  }
  {
    v = pic_cons(pic, pic_intern_cstr(pic, "foo"), pic_intern_cstr(pic, "bar"));
    pic_debug(pic, v);
    puts(" [should be `(foo . bar)`]");
  }
}

#define LINE_MAX_LENGTH 256

int
main()
{
  pic_state *pic;
  char line[LINE_MAX_LENGTH], last_char;
  int char_index;
  pic_value v;

  pic = pic_open();

  test_object_creation(pic);

  while (1) {
    printf("> ");

    char_index = 0;
    while ((last_char = getchar()) != '\n') {
      if (last_char == EOF)
	goto eof;
      if (char_index == LINE_MAX_LENGTH)
	goto overflow;
      line[char_index++] = last_char;
    }
    line[char_index] = '\0';

    /* echo */
    v = pic_parse(pic, line);

    pic_debug(pic, pic_eval(pic, v, pic->global_env));
    printf("\n");
  }

 eof:
  puts("");
  goto exit;

 overflow:
  puts("** [fatal] line input overflow");
  goto exit;

 exit:
  pic_close(pic);

  return 0;
}
