#include "polynome.h"
#include <stdlib.h>
#include <stdio.h>

void print_sign(int is_first, int d)
{
	if (is_first)
		printf("%d", d);
	else
		printf("%+d", d);
}

void print_poly(t_poly *poly, int is_first)
{
	if(poly == NULL || poly->coef.dec == 0)
		return;

	if(poly->coef.frac == 1 && poly->exp != 0)
	{
		if(poly->coef.dec == 1) 
		{
			printf("+X");
			return;
		}
		else if (poly->coef.dec == -1)
		{
			printf("-X");
			return;
		}
	}
	if (poly->coef.dec % poly->coef.frac == 0)
		print_sign(is_first, poly->coef.dec / poly->coef.frac);
	else
	{
		print_sign(is_first, poly->coef.dec);
		printf("/%d", poly->coef.frac);
	}
	
	int n = poly->exp;
	if (n != 0 && n != 1)
		printf("X^%d", poly->exp);
	else if (n == 1)
		printf("X");
	print_poly(poly->next, 0);
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

int  find_poly(t_node *nodes, char c)
{
	int i = 0;
	
	while(nodes[i].poly)
	{
		if (nodes[i].varname == c)
		{
			return i;
		}
		i++;
	}
	return -1;
}

t_poly *create_poly(char *s)
{
	int n;
	t_poly *poly = malloc(sizeof(t_poly));
	poly->next = NULL;
	poly->coef.dec = 1;
	poly->coef.frac = 1;
	poly->exp = 0;
	if (*s != 'X')
	{
		poly->coef.dec = matoi(s, &n);
		s += n;
		if (*s == '/')
		{
			s++;
			poly->coef.frac = matoi(s, &n);
			s += n;
		}
	}
	else {
		poly->coef.dec = 1;
	}
	if(*s == 'X')
	{
		poly->exp = 1;
		s++;
		if (*s == '^')
		{
			s++;
			poly->exp = matoi(s, &n);
			s += n;
		}
	}
	if(*s != '\n')
		poly->next = create_poly(s);
	return poly;
}

int count_poly(t_poly *poly)
{
	int count;

	while(poly)
	{
		poly = poly->next;
		count++;
	}
	return count;
}


t_poly *clone_poly(t_poly *poly)
{
	if(poly == NULL)
		return NULL;
	t_poly *npoly = malloc(sizeof(t_poly));
	npoly->coef = poly->coef; 
	npoly->exp = poly->exp; 
	npoly->next = clone_poly(poly->next); 

	return npoly;
}

t_poly *clone_monome(t_poly *poly)
{
	if(poly == NULL)
		return NULL;
	t_poly *npoly = malloc(sizeof(t_poly));
	npoly->coef = poly->coef; 
	npoly->exp = poly->exp; 
	npoly->next = NULL; 

	return npoly;
}

t_node *last_node(t_node *nodes)
{
	int i = 0;
	
	while(nodes[i].poly)
		i++;
	return nodes + i;
}

void add_monome(t_poly **head, t_poly *monome)
{
	if (*head == NULL)
		return;

	t_poly *cur = *head;
	if (cur->exp < monome->exp)
	{
		monome->next = cur;
		*head = monome;
		return ;
	}

	t_poly *last = cur;
	while (cur->exp >= monome->exp)
	{
		last = cur;
		if (cur->next == NULL)
			break ;
		cur = cur->next;
	}

	monome->next = last->next;
	last->next = monome;
}

