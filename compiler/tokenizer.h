#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#include "lexer.h"

typedef enum { T_NUMBAR, T_YARN, T_BOOL, T_IDENT, T_KEYWORD } token_type;

typedef struct token {
	token_type type;
	unsigned int line;
	char* fname;
	union {
		double d;
		char* s;
		char* ident;
		bool b;
		int keyword;
	};
} token_t;

typedef struct tokenlist {
	token_t** tokens;
	unsigned int ntokens;
} tokenlist_t;

char* keywords[] = {
	"!",
	"!!",
	"\'Z",
	"?",
	"A",
	"BIGGR",
	"BRB",
	"BUT",
	"BUTTSECHS",
	"CAN",
	"DIAF",
	"DINO",
	"DUZ",
	"EATED",
	"EATIN",
	"FOUND",
	"GTFO",
	"HAI",
	"HAO",
	"HAS",
	"HAZ",
	"I",
	"IF",
	"IM",
	"IN",
	"ITZ",
	"IZ",
	"KTHX",
	"KTHXBAI",
	"LETZAGO!",
	"LIEK",
	"LOOP",
	"MAED",
	"NERF",
	"NERFIN",
	"NERFZ",
	"NOOB",
	"OMG",
	"OMGWTFBBQ",
	"OUTTA",
	"OVAR",
	"OVARZ",
	"PIZZA",
	"POPACAPINHISASS",
	"SAY",
	"SHIFLOL",
    "SHIFLOLIN",
    "SHIFLOLZ",
    "SHIFZOR",
    "SHIFZORZ",
    "SHIFZORZIN",
	"SLICIN",
	"SMALR",
	"SO",
	"SURPRIEZ",
	"TIEMZ",
	"TIEMZD",
	"TIEMZIN",
	"TILL",
	"UP",
	"UPPIN,
	"UPZ",
	"WIF",
	"WILE",
	"WTF",
	"YR"
};

const size_t nkwds = sizeof(keywords) / sizeof(char*);

#endif
