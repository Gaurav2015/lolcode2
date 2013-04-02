#pragma once
#include "lexer.h"

#define NEW(x) (malloc(sizeof((x))))

typedef enum { T_NUMBAR, T_YARN, T_BOOL, T_IDENT, T_KEYWORD } token_type;

typedef struct token {
	token_type type;
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
	"!"
	"!!"
	"\'Z",
	"?"
	"A",
	"BIGGR",
	"BRB",
	"BUKKIT",
	"BUT",
	"BUTTSECHS",
	"CAN",
	"COOKEH"
	"DIAF",
	"DINO",
	"DUZ",
	"EAT",
	"EATED",
	"EATIN",
	"FOUND",
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
	"JAR",
	"KTHX",
	"KTHXBAI",
	"LETZAGO!",
	"LIEK",
	"LOOP",
	"MAED",
	"MAEK",
	"MAH",
	"ME",
	"NERF",
	"NERFIN",
	"NERFZ",
	"NOOB",
	"O",
	"OF",
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
	"SURPRIZE",
	"TIEMZ",
	"TIEMZD",
	"TIEMZIN",
	"TILL",
	"U",
	"UP",
	"UPPIN",
	"UPZ",
	"WIF",
	"WILE",
	"WTF",
	"YR"
};

const size_t nkwds = sizeof(keywords) / sizeof(char*);
