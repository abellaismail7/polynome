#include "polynome.h"
#include <stdio.h>
#include <stdlib.h>

int handle_pow(t_node *nodes, char *s)
{
	t_poly *p1 = nodes[find_poly(nodes, s[0])].poly;
	int exp = atoi(s + 2);
	int i = 0;
	t_poly *res = p1;

	while (i < exp -1)
	{
		res = handle__mul(res, p1);
		i++;
	}
	print_poly(res, 1);
	puts("");
	return 1;
}
