#ifndef SRC_MODULE_INPUT_H_
#define SRC_MODULE_INPUT_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256

typedef struct stack {
  char *arr;
  int top;
} stack;

typedef struct stack_for_nums {
  double *arr;
  int top;
} stack_for_nums;

double s21_smart_calc(char *string, int *error, double number_x);
void validator(char *str, char *exit);
void notation(char *exit, char *polk);
int check(char *exit);
int priority(char a);
int schet(const char *polk, double *res, double number_x);
int math_operations(const char *polk, int i, stack_for_nums *a);

stack *init(int size);
char pop(stack *s);
void push(stack *s, char elem);
char find(stack *s);
void cleaner(stack *s);

stack_for_nums *init_nums(int size);
double pop_nums(stack_for_nums *a);
double push_nums(stack_for_nums *a, double elem);
void cleaner_nums(stack_for_nums *s);

#endif  // SRC_MODULE_INPUT_H_