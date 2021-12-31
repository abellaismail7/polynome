

typedef struct coef {
	int dec;
	int frac;
} t_coef;


typedef struct polynome {
	t_coef coef;
	int exp;
	struct polynome *next;
} t_poly;

typedef struct s_node
{
	char varname;
	t_poly *poly;
} t_node;


int	matoi(char *str, int *count);
t_coef coadd(t_poly *poly, int val);
t_coef _cosum(t_coef c1, t_coef c2, int is_add);
void printcoef(t_coef coef, int is_first);
void poly_op(t_poly *p1, t_poly *p2, int is_add);
void print_poly(t_poly *poly, int is_first);
t_poly *clone_poly(t_poly *poly);
t_poly *create_poly(char *s);
int  find_poly(t_node *nodes, char c);
t_node *last_node(t_node *nodes);
t_poly *clone_monome(t_poly *poly);

void handle_int(t_node *nodes, char *cmd);
void handle_der(t_node *nodes, char *cmd);
void handle_op(t_node *nodes, char *cmd, int is_add);
void eval(t_node *nodes, char *s);
void handle_set(t_node *nodes, char *cmd);
void handle_let(t_node *nodes, char *s);
int handle_mul(t_node *nodes, char *s);
