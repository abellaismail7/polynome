#include<stdio.h>
#include<math.h>
#include"polynome.h"

t_coef _cosum(t_coef c1, t_coef c2, int is_add)
{
	c1.dec *= c2.frac;
	c2.dec *= c1.frac;
	c1.frac *= c2.frac;
	c2.frac = c1.frac;

	if(is_add == 1)
		c1.dec += c2.dec;
	else
		c1.dec -= c2.dec;
	return c1;
}


t_coef coadd(t_poly *poly, int val)
{
	t_coef coef;
	t_coef coef_cp;
	coef.dec = 0;
	coef.frac = 1;

	while (poly)
	{
		coef_cp = poly->coef;
		coef_cp.dec *= pow(val, poly->exp);

		coef_cp.dec *= coef.frac;
		coef.dec *= coef_cp.frac;
		coef_cp.frac *= coef.frac;
		coef.frac = coef_cp.frac;

		coef.dec += coef_cp.dec;

		poly = poly->next;
	}
	return coef;
}

void printcoef(t_coef coef, int is_first)
{
	if(coef.dec % coef.frac == 0)
	{
		if (is_first)
			printf("%d", (int)(coef.dec / coef.frac));
		else
			printf("%+d", (int)(coef.dec / coef.frac));
	}
	else {
		if (is_first)
			printf("%d/%d", coef.dec, coef.frac);
		else
			printf("%+d/%d", coef.dec, coef.frac);
	}
}

t_poly *find_exp(t_poly *poly, int exp)
{
	while (poly)
	{
		if (poly->exp == exp)
			return poly;
		poly = poly->next;
	}
	return NULL;
}

void poly_op(t_poly *p1, t_poly *p2, int is_add)
{
	int is_first = 1;
	t_coef coef;
	while(p1)
	{
		t_poly *p = find_exp(p2, p1->exp);	
		if (p == NULL)
			coef = p1->coef;
		else
			coef = _cosum(p1->coef, p->coef, is_add);
		printcoef(coef , is_first);
		if (p1->exp != 0)
			printf("X");
		if (p1->exp > 1)
			printf("^%d", p1->exp);
		is_first = 0;
		p1 = p1->next;
	}
}
