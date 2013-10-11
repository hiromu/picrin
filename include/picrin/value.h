#ifndef VALUE_H__
#define VALUE_H__

enum pic_vtype {
  PIC_VTYPE_NIL,
  PIC_VTYPE_HEAP
};

typedef struct {
  enum pic_vtype type;
  union {
    void *data;
  } u;
} pic_value;

enum pic_tt {
  /* immediate */
  PIC_TT_NIL,
  /* heap */
  PIC_TT_PAIR,
  PIC_TT_SYMBOL
};

#define PIC_OBJECT_HEADER			\
  enum pic_tt tt;

struct pic_object {
  PIC_OBJECT_HEADER
};

struct pic_pair {
  PIC_OBJECT_HEADER
  pic_value car;
  pic_value cdr;
};

struct pic_symbol {
  PIC_OBJECT_HEADER
  char *name;
};

#define pic_pair_ptr(o) ((struct pic_pair *)o.u.data)
#define pic_symbol_ptr(o) ((struct pic_symbol *)o.u.data)

enum pic_tt pic_type(pic_value);

pic_value pic_nil_value();
pic_value pic_obj_value(void *);

#define pic_nil_p(v) (pic_type(v) == PIC_TT_NIL)

#endif
