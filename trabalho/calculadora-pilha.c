#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct tKey
{
  int n;
  char op;
} tKey;

typedef struct aux
{
  tKey key;
  struct aux *next;
} node;

typedef struct stack
{
  node *topo;
} stack;

void insere(stack *s, tKey key)
{
  node *new = (node *)malloc(sizeof(node));
  new->key = key;

  if (s->topo == NULL)
  {
    s->topo = new;
    new->next = NULL;
  }
  else
  {
    new->next = s->topo;
    s->topo = new;
  }
}

void pop_stack(stack *s, tKey *k)
{
  if (s->topo != NULL)
  {
    *k = s->topo->key;
    node *tmp = s->topo;
    s->topo = s->topo->next;
    free(tmp);
  }
}

void print_stack(stack *s, int type)
{
  // type == 0 -> int | type == 1 -> chat
  node *pt = s->topo;
  while (pt != NULL)
  {
    printf("%d ", pt->key.n);
    pt = pt->next;
  }
  puts("");
}

void free_stack(stack *s)
{
  while (s->topo != NULL)
  {
    node *tmp = s->topo;
    s->topo = s->topo->next;
    free(tmp);
  }
  free(s);
}

int isOperator(char c)
{
  return c == '+' || c == '-' || c == '*' || c == '/';
}

int doMath(int n1, int n2, char op)
{
  switch (op)
  {
  case '+':
    return n1 + n2;
  case '-':
    return n1 - n2;
  case '*':
    return n1 * n2;
  case '/':
    return n1 / n2;
  default: return 0;
  }
}

int main(int argc, char *argv[])
{
  stack *nums = (stack *)malloc(sizeof(stack));
  nums->topo = NULL;

  stack *operations = (stack *)malloc(sizeof(stack));
  operations->topo = NULL;

  char exp[100];
  fgets(exp, 100, stdin);

  for (int i = 0; i < strlen(exp); i++)
  {
    if (exp[i] == ')')
    {
      tKey n1, n2, op;
      pop_stack(nums, &n1);
      pop_stack(nums, &n2);
      pop_stack(operations, &op);

      tKey result;
      result.n = doMath(n2.n, n1.n, op.op);
      insere(nums, result);
    }
    else if (isdigit(exp[i]))
    {
      int n = atoi(&exp[i]);
      tKey numKey;
      numKey.n = n;
      numKey.op = '\0';
      insere(nums, numKey);
      while (isdigit(exp[i]))
      {
        i++;
      }
      i--;
    }
    else if (isOperator(exp[i]))
    {
      tKey opKey;
      opKey.op = exp[i];
      opKey.n = 0;
      insere(operations, opKey);
    }
  }

  print_stack(nums, 1);

  return 0;
}
