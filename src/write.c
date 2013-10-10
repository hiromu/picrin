#include <stdio.h>
#include <stdlib.h>

#include "picrin.h"

void
pic_debug(pic_state *pic, pic_value obj)
{
  switch (pic_type(obj)) {
  case PIC_TT_NIL:
    printf("()");
    break;
  case PIC_TT_PAIR:
    printf("(");
    pic_debug(pic, pic_car(pic, obj));
    printf(" . ");
    pic_debug(pic, pic_cdr(pic, obj));
    printf(")");
    break;
  case PIC_TT_SYMBOL:
    printf("%s", pic_symbol_ptr(obj)->name);
    break;
  default:
    abort();
  }
}