

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

extern t_node *nodes[];

int	matoi(char *str, int *count);
t_coef coadd(t_poly *poly, int val);
void printcoef(t_coef coef, int is_first);
void poly_op(t_poly *p1, t_poly *p2, int is_add);
void print_poly(t_poly *poly, int is_first);
t_poly *clone_poly(t_poly *poly);
t_poly *create_poly(char *s);
int  find_poly(t_node *nodes, int nindex, char c);

void handle_int(t_node *nodes, int nindex, char *cmd);
void handle_der(t_node *nodes, int nindex, char *cmd);
void handle_op(t_node *nodes, int nindex, char *cmd, int is_add);
void eval(t_node *nodes, int nindex, char *s);
void handle_set(t_node *nodes, int nindex, char *cmd);
void handle_let(t_node *nodes, int nindex, char *s);
int handle_mul(t_node *nodes, int nindex, char *s);
