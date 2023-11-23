#include "s21_SmartCalc.h"

// int main() {
//   char *arr = "1.0 =";
//   int err = 0;
//   double x = 0.0;
//   double res = s21_smart_calc(arr, &err, x);
//   printf("%lf", res);
//   return 0;
// }

double s21_smart_calc(char *string, int *error, double number_x) {
  double res = 0.0;
  char exit[MAX_SIZE] = {0};
  validator(string, exit);
  *error = check(exit);
  if (*error == 0) {
    char polk[MAX_SIZE] = {0};
    notation(exit, polk);
    *error = schet(polk, &res, number_x);
  }
  return res;
}

void validator(char *str, char *exit) {
  int k = 0;
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    if (strncmp(str + i, "acos", 4) == 0) {
      exit[k++] = 'o';
      i += 3;
    } else if (strncmp(str + i, "asin", 4) == 0) {
      exit[k++] = 'n';
      i += 3;
    } else if (strncmp(str + i, "atan", 4) == 0) {
      exit[k++] = 'a';
      i += 3;
    } else if (strncmp(str + i, "cos", 3) == 0) {
      exit[k++] = 'c';
      i += 2;
    } else if (strncmp(str + i, "sin", 3) == 0) {
      exit[k++] = 's';
      i += 2;
    } else if (strncmp(str + i, "tan", 3) == 0) {
      exit[k++] = 't';
      i += 2;
    } else if (strncmp(str + i, "mod", 3) == 0) {
      exit[k++] = 'm';
      i += 2;
    } else if (strncmp(str + i, "sqrt", 4) == 0) {
      exit[k++] = 'q';
      i += 3;
    } else if (strncmp(str + i, "ln", 2) == 0) {
      exit[k++] = 'l';
      i++;
    } else if (strncmp(str + i, "log", 3) == 0) {
      exit[k++] = 'g';
    } else if (i == 0 && str[i] == '-') {
      exit[k++] = '0';
      exit[k++] = '-';
    } else if (str[i] == '(' && str[i + 1] == '-') {
      exit[k++] = '(';
      exit[k++] = '0';
    } else if ((str[i] >= '0' && str[i] <= '9') &&
               (str[i + 1] == '(' || str[i + 1] == 'a' || str[i + 1] == 'c' ||
                str[i + 1] == 's' || str[i + 1] == 't' || str[i + 1] == 'm' ||
                str[i + 1] == 'l')) {
      exit[k++] = str[i];
      exit[k++] = '*';
    } else {
      exit[k++] = str[i];
    }
  }
}

int check(char *exit) {
  int flag = 2;
  int count_open_brackets = 0;
  for (int i = 0; exit[i] != '\0'; i++) {
    if ((exit[i] >= 48 && exit[i] <= 57) || exit[i] == 'x') flag = 0;
    if (exit[0] == ')') flag = 2;
    if ((strchr("cosatnqlg", exit[i]) != NULL) && exit[i + 1] == '(' &&
        (exit[i + 2] == '\0' || exit[i + 2] == ')'))
      flag = 2;
    if (exit[i] == '(') {
      count_open_brackets++;
    } else if (exit[i] == ')') {
      if (count_open_brackets == 0) {
        flag = 2;
      } else {
        count_open_brackets--;
      }
    }
  }
  if (count_open_brackets != 0) {
    flag = 2;
  }
  return flag;
}

stack *init(int size) {
  stack *s = malloc(sizeof(stack));
  if (s != NULL) {
    s->arr = malloc(size * sizeof(char));
    s->top = 0;
  }
  return s;
}

stack_for_nums *init_nums(int size) {
  stack_for_nums *s = malloc(sizeof(stack_for_nums));
  if (s != NULL) {
    s->arr = malloc(size * sizeof(double));
    s->top = 0;
  }
  return s;
}

char pop(stack *s) {
  char elem_char = '0';
  if (s->top != 0) {
    elem_char = s->arr[s->top - 1];
    s->top--;
  }
  return elem_char;
}

double pop_nums(stack_for_nums *s) {
  double elem_char = 0.0;
  if (s->top != 0) {
    elem_char = s->arr[s->top - 1];
    s->top--;
  }
  return elem_char;
}

void push(stack *s, char elem) {
  s->arr[s->top] = elem;
  s->top++;
}

double push_nums(stack_for_nums *a, double elem) {
  a->arr[a->top] = elem;
  a->top++;
  return 0;
}

void cleaner(stack *s) {
  if (s != NULL) {
    if (s->arr != NULL) {
      free(s->arr);
      s->top = 0;
    }
    free(s);
  }
}

void cleaner_nums(stack_for_nums *a) {
  if (a != NULL) {
    if (a->arr != NULL) {
      free(a->arr);
      a->top = 0;
    }
    free(a);
  }
}

char find(stack *s) {
  char flag = '0';
  if (s->top != 0) {
    flag = s->arr[s->top - 1];
  }
  return flag;
}

void notation(char *exit, char *polk) {  
  stack *s = init(MAX_SIZE);
  int k = 0;
  for (int i = 0; exit[i] != '\0'; i++) {
    if (priority(exit[i]) == 0) {
      polk[k++] = exit[i];
      if (priority(exit[i + 1]) != 0) {
        polk[k++] = ' ';
      }
    } else if (priority(exit[i]) >= 2 && priority(exit[i]) <= 4) {
      if (priority(find(s)) < priority(exit[i])) {
        push(s, exit[i]);
      } else if (priority(find(s)) >= priority(exit[i])) {
        while (priority(find(s)) >= priority(exit[i])) {
          polk[k++] = pop(s);
        }
        push(s, exit[i]);
      }
    } else if (exit[i] == 'x') {
      polk[k++] = exit[i];
    } else if (exit[i] == '(') {
      push(s, exit[i]);
    } else if (exit[i] == ')') {
      while (find(s) != '(') {
        polk[k++] = pop(s);
      }
      pop(s);
    }
  }
  while (s->top != 0) {
    polk[k++] = pop(s);
  }
  cleaner(s);
}

int priority(char a) {
  int res = 1;
  if ((a >= 48 && a <= 57) || a == 46) res = 0;
  if (a == '(' || a == ')') res = 1;
  if (a == '+' || a == '-') res = 2;
  if (a == '*' || a == '/' || a == 'm') res = 3;
  if (a == 'c' || a == 's' || a == 't' || a == 'g' || a == 'q' || a == 'l' ||
      a == '^' || a == 'a' || a == 'o' || a == 'n')
    res = 4;
  return res;
}

int schet(const char *polk, double *res, double number_x) {
  int flag = 0;
  stack_for_nums *a = init_nums(MAX_SIZE);
  for (int i = 0; polk[i] != '\0'; i++) {
    if (polk[i] == 'x')
      push_nums(a, number_x);
    else if ((polk[i] >= 48 && polk[i] <= 57) || polk[i] == 46) {
      push_nums(a, atof(&polk[i]));
      while (polk[i] != ' ') i++;
    } else if (flag == 0 &&
               !((polk[i] == '-' || polk[i] == '*' || polk[i] == '/') &&
                 a->top == 1)) {
      flag = math_operations(polk, i, a);
    }
  }
  *res = pop_nums(a);
  cleaner_nums(a);
  return flag;
}

int math_operations(const char *polk, int i, stack_for_nums *a) {
  int flag = 0;
  double a1 = 0;
  switch (polk[i]) {
    case '+':
      push_nums(a, pop_nums(a) + pop_nums(a));
      break;
    case '-':
      a1 = pop_nums(a);
      push_nums(a, pop_nums(a) - a1);
      break;
    case '*':
      push_nums(a, pop_nums(a) * pop_nums(a));
      break;
    case '/':
      a1 = pop_nums(a);
      if (a1 != 0)
        push_nums(a, pop_nums(a) / a1);
      else
        flag = 1;
      break;
    case 'm':
      a1 = pop_nums(a);
      if (a->top == 0)
        flag = 2;
      else
        push_nums(a, fmodl(pop_nums(a), a1));
      break;
    case 't':
      push_nums(a, tan(pop_nums(a)));
      break;
    case 'c':
      push_nums(a, cos(pop_nums(a)));
      break;
    case 's':
      push_nums(a, sin(pop_nums(a)));
      break;
    case 'o':
      push_nums(a, acos(pop_nums(a)));
      break;
    case 'n':
      push_nums(a, asin(pop_nums(a)));
      break;
    case 'a':
      push_nums(a, atan(pop_nums(a)));
      break;
    case 'q':
      push_nums(a, sqrt(pop_nums(a)));
      break;
    case 'l':
      push_nums(a, log(pop_nums(a)));
      break;
    case 'g':
      push_nums(a, log10(pop_nums(a)));
      break;
    case '^':
      a1 = pop_nums(a);
      if (a->top == 0)
        flag = 2;
      else
        push_nums(a, pow(pop_nums(a), a1));
      break;
  }
  return flag;
}