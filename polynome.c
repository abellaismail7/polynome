#include "polynome.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_node nodes[30];

void display(char *s)
 {
	char c = *s;
	int i = 0;
	while(nodes[i].poly)
	{
		if (nodes[i].varname == c)
		{
			print_poly(nodes[i].poly, 1);
			printf("\n");
			return ;
		}
		i++;
	}
	printf("Polynome not found\n");
}

void affect(char *s)
{
	int to = find_poly(nodes, s[0]);
	int from = find_poly(nodes, s[2]);

	nodes[to].poly = nodes[from].poly;
}

int handle_cmd(char *s)
{
	if (strncmp(s, "LET ", 4) == 0)
		handle_let(nodes, s + 4);
	else if (strncmp(s, "DISPLAY ", 8) == 0)
		display(s + 8);
	else if (strncmp(s, "AFFECT ", 7) == 0)
		affect(s+7);
	else if(strncmp(s, "EVAL ", 5) == 0)
		eval(nodes, s + 5);
	else if(strncmp(s, "SET ", 4) == 0)
		handle_set(nodes, s + 4);
	else if(strncmp(s, "ADD ", 4) == 0)
		handle_op(nodes, s + 4, 1);
	else if(strncmp(s, "SUB ", 4) == 0)
		handle_op(nodes, s + 4, 0);
	else if(strncmp(s, "MUL ", 4) == 0)
		handle_mul(nodes, s + 4);
	else if(strncmp(s, "POW ", 4) == 0)
		handle_pow(nodes, s + 4);
	else if(strncmp(s, "DER ", 4) == 0)
		handle_der(nodes, s + 4);
	else if(strncmp(s, "INT ", 4) == 0)
		handle_int(nodes, s + 4);
	else if(strcmp(s, "EXIT\n") == 0)
		return 1;
	else
		printf("Polynome: Command Not Found\n");
	return 0;
}

int show_prompt()
{
	char cmd[20000];

	handle_cmd("LET P = 2X^3+5X^2+4\n");
	handle_cmd("LET X = 3X^2\n");
	handle_cmd("ADD P,X\n");
	printf("(polynome) ");
	while((fgets(cmd, 20000, stdin)))
	{
		if(handle_cmd(cmd) == 1)
			break;
		printf("(polynome) ");
	}
	return 0;
}

int main ()
{
	nodes[0].poly = NULL;
	show_prompt();
	return 0;
}
