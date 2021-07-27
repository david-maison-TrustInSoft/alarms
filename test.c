#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <tis_builtin.h>

// ポイ https://ci.trust-in-soft.com 

float tis_float_interval(float, float);

void never_called_function() {
    printf("poi is sad.");
    return;
}

int called_but_never_reached_function() {
    int i=0;
    i++;
    i++;
    return i++;
}

struct S { int a; int b; int c; };
struct T { int p; struct S s; };
union U { struct S s; struct T t; };
union U u;

//  ͲͲͲͲͲͲͲͲͲ
int alarm_overflow_bis(int* x) {
    return *x * 2;
}

int alarm_overflow(int a_var_with_a_very_long_name_that_should_be_cut) {
    return a_var_with_a_very_long_name_that_should_be_cut * 2;
}

int alarm_invalid_shift(int x) {
    return x << 10;
}

int alarm_uninitialized(int x) {
    return x + 2;
}

int alarm_mem_access(char* x) {
    return *x;
}

int alarm_div_zero(int x) {
    return 15 / x;
}

int alarm_float_to_int() {
    float f1 = tis_float_interval(2e9, 3e9);
    return (int)f1;
}

int pouet(void);

int alarm_not_separated() {
    int x = pouet();
    int y = pouet();
    // use option -unspecified-access to trigger the alarm
    int *p = (x < y) ? &x : &y;
    return x + (*p)++;
}

int global_G;
int global_H;

int alarm_not_separated_bis() {
    int c = pouet();
    int *p;
    int *q;
    p = c?&global_G:&global_H;
    q = ~c?&global_G:&global_H;
    if (p<=q) return 1;
    return 0;
}

int alarm_pointer_comparable() {
    int c = pouet();
    int *p;
    int *q;
    p = c?&global_G:&global_H;
    q = ~c?&global_G:&global_H;
    if (p<=q) return 1;
    return 0;
}


int alarm_overlap(struct S *p, struct S *q) {
    *p = *q;
    return 0;
}

int* alarm_dangling_trick(int c) {
    int t = c;
    return &t;
}

int alarm_dangling() {
    int* p = alarm_dangling_trick(4);
    return *p;
}

double unknown_fun(void);

double alarm_is_nan_or_infinite() {
    double a = unknown_fun();
    return a + a;
}

int alarm_function_pointer() {
    int (*p)(void);
    p = & unknown_fun;
    return p();
}

int alarm_with_several_lval(int ia0, int ia1, int ia2, int ia3, int ia4, int ia5) {
    return (ia1 * ia2 + (ia3 << ia5- ia4)) + (INT_MAX - ia0 + ia0);
}

char s[10];
void alarm_printf() {
    printf("%s\n", &s);
}

// requires i > 0;
int alarm_in_one_callstack(int i) {
    return 100 / i;
}

int alarm_in_several_callstacks(int i) {
    return 100 / i;
}

int my_alarm(int x, char* y) {
    int top = tis_interval(INT_MIN, INT_MAX);
    int a[3];
    int b;
    switch (tis_interval(INT_MIN, INT_MAX)) {
    case 0:
        return alarm_uninitialized(a[2]);
    case 1:
        return alarm_mem_access(y+4);
    case 2:
        return alarm_div_zero(tis_interval(-10,10));
    case 3:
        return alarm_overflow(top);
    case 4:
        return alarm_invalid_shift(top);
    case 5:
        return alarm_float_to_int();
    case 6:
        return alarm_not_separated();
    case 7:
        u.s.b = 1;
        return alarm_overlap(&u.t.s, &u.s);
    case 8:
        return alarm_dangling();
    case 9:
        alarm_is_nan_or_infinite();
        return 0;
    case 10:
        return alarm_function_pointer();
    case 11:
        return alarm_overflow_bis(&top);
    case 12:
        return alarm_with_several_lval(1,2,3,4,5,6);
    case 13:
        return alarm_not_separated_bis();
    case 14:
        return alarm_pointer_comparable();
    case 15:
        alarm_printf();
        return 0;
    case 16:
        b = alarm_in_one_callstack(1);
        return b + alarm_in_one_callstack(0);
    case 17:
        b = alarm_in_several_callstacks(top);
        b += alarm_in_several_callstacks(20);
        return b + alarm_in_several_callstacks(0);
    default:
        return 0;
    }
}

int h(int x, int y) {
    int g1 = x + y;
    return g1;
}

int g(int x) {
    return h(x + 2, 1);
}

int f(int x) {
    return g(x);
}

int main(void) {
    int x;
    char* y = "abc pouet";
    int z = 1;
    printf("Poi is the best!");
    z = f(0);
    x = z + my_alarm(x, y);
    if ( z == 0 ) called_but_never_reached_function();
    return x;
}
