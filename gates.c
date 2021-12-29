#include "polynome.h"
#include <stdlib.h>
#include <stdio.h>

void handle_let(t_node *nodes, int nindex, char *s)
{
	t_poly *poly = create_poly(s + 4);
	nodes[nindex].varname = *s;
	nodes[nindex].poly = poly;
	nindex++;
}

void handle_set(t_node *nodes, int nindex, char *cmd)
{
	int i = find_poly(nodes, nindex, *cmd);
	free(nodes[i].poly);
	nodes[i].poly = create_poly(cmd + 4);
}

void eval(t_node *nodes, int nindex, char *s)
{
	int i = find_poly(nodes, nindex, s[0]);
	t_poly *p = nodes[i].poly;

	s += 10;
	int x = atoi(s);
	t_coef coef = coadd(p, x);
	printcoef(coef, 0);
	puts("");
}

void handle_op(t_node *nodes, int nindex, char *cmd, int is_add)
{
	t_poly *p1 = nodes[find_poly(nodes, nindex, cmd[0])].poly;
	t_poly *p2 = nodes[find_poly(nodes, nindex, cmd[2])].poly;

	poly_op(p1, p2, is_add);
	puts("");
}

void handle_der(t_node *nodes, int nindex, char *cmd)
{
	t_poly *p = nodes[find_poly(nodes, nindex, cmd[0])].poly;

	while (p)
	{
		if (p->exp == 0)
			p->coef.dec = 0;
		else
			p->exp -= 1;
		p->coef.dec *= p->exp +1;
		p = p->next;
	}
}

void handle_int(t_node *nodes, int nindex, char *cmd)
{
	t_poly *p = nodes[find_poly(nodes, nindex, cmd[0])].poly;

	while (p)
	{
		p->exp++;
		p->coef.frac *= p->exp;
		p = p->next;
	}
}
