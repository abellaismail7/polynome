#include "polynome.h"

void _mul(t_poly *npoly, t_poly *poly)
{
	npoly->coef.dec *= poly->coef.dec;
	npoly->coef.frac *= poly->coef.frac;
	npoly->exp += poly->exp;
}


// 10X^2+5X+4
// 3X^4-3X-3
//
// 30X^8-30X^3-30X


int handle_mul(t_node *nodes, int nindex, char *s)
{
	t_poly *p1 = nodes[find_poly(nodes, nindex, s[0])].poly;
	t_poly *p2 = nodes[find_poly(nodes, nindex, s[2])].poly;
	 	
	t_poly *npoly = clone_poly(p2);
	t_poly *cur = p1;
	while(cur)
	{
		_mul(npoly, p1);
		cur = cur->next;
	}
	print_poly(npoly, 1);
	return 1;
}
