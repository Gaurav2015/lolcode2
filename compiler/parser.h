typedef struct expr_t expr;
typedef struct binop_expr_t binop_expr;

typedef enum
{
	T_NUMBR,
	T_NUMBAR,
	T_YARN,
	T_TROOF,
	T_BINOP
} etype_t;

struct expr_t
{
	etype_t type;

	union {
		long l;
		double d;
		char* s;
		bool b;
		binop_expr* binop;
	};
};

struct binop_expr_t
{
	char op;
	expr* lhs;
	expr* rhs;
};

