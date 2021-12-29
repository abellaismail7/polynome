#include "polynome.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void display(char *s)
 {
	char c = *s;
	int i = 0;
	while(nodes[i]->poly)
	{
		if (nodes[i]->varname == c)
		{
			print_poly(nodes[i]->poly, 1);
			printf("\n");
			return ;
		}
		i++;
	}
	printf("Polynome not found\n");
}

void affect(char *s)
{
	int to = find_poly(s[0]);
	int from = find_poly(s[2]);

	nodes[to].poly = nodes[from].poly;
}

int handle_cmd(char *s)
{
	if (strncmp(s, "LET ", 4) == 0)
		handle_let(&nodes, nindex, s + 4);
	else if (strncmp(s, "DISPLAY ", 8) == 0)
		display(s + 8);
	else if (strncmp(s, "AFFECT ", 7) == 0)
		affect(s+7);
	else if(strncmp(s, "EVAL ", 5) == 0)
		eval(nodes, nindex, s + 5);
	else if(strncmp(s, "SET ", 4) == 0)
		handle_set(nodes, nindex, s + 4);
	else if(strncmp(s, "ADD ", 4) == 0)
		handle_op(nodes, nindex, s + 4, 1);
	else if(strncmp(s, "SUB ", 4) == 0)
		handle_op(nodes, nindex, s + 4, 0);
	else if(strncmp(s, "MUL ", 4) == 0)
		handle_mul(nodes, nindex, s + 4);
	else if(strncmp(s, "DER ", 4) == 0)
		handle_der(nodes, nindex, s + 4);
	else if(strncmp(s, "INT ", 4) == 0)
		handle_int(nodes, nindex, s + 4);
	else if(strcmp(s, "EXIT\n") == 0)
		return 1;
	return 0;
}

int show_prompt()
{
	char cmd[20000];

	printf("polynome> ");
	while((fgets(cmd, 20000, stdin)))
	{
		if(handle_cmd(cmd) == 1)
			break;
		printf("polynome> ");
	}
	return 0;
}

int main ()
{
	t_node _nodes[30];
	_nodes[0].poly = 0;
	nodes = &_nodes;
	show_prompt();
	return 0;
}
