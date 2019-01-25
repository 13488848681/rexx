
#ifndef GOST_PARAMSET_H
# define GOST_PARAMSET_H
typedef struct R3410 {
    int nid;
    char *a;
    char *p;
    char *q;
} R3410_params;

extern R3410_params R3410_paramset[];

typedef struct R3410_2001 {
    int nid;
    char *a;
    char *b;
    char *p;
    char *q;
    char *x;
    char *y;
} R3410_2001_params;

extern R3410_2001_params R3410_2001_paramset[];

#endif
