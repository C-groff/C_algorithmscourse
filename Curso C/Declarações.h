#include <stdlib.h>
#include <stdio.h>
#ifndef _HAVE_SUPPORT_H
#define _HAVE_SUPPORT_H


typedef struct celula{ 
	char ch;
	struct celula *prox;
	struct celula *ant;
} celula;

typedef struct linha{
	celula* cabeça;
	struct linha *prox;
	struct linha *ant;
	int Numlinha;
} linha;

typedef struct{
	linha *começo;
	celula *cursor;
} pointer;

typedef struct pilha{
	celula *topo;
	struct pilha *ant;
} pilha;

int flag, MatrizColuna, MatrizLinha, ColunaMarcada, LinhaMarcada;
celula *M; 
pilha *G;

void insere_texto(char, pointer*);
pointer *cria_ponteiro_e_pilha();
linha *cria_linhazero(pointer*);
void mostralinha(pointer *);
char *ler_o_arquivo(char *);
linha *cria_nova_linha(pointer *, linha *);
void carrega_arquivo(char *, pointer* , linha *);
void move_cursor_F(pointer *);
void move_cursor_T(pointer *);
void move_cursor_O(pointer *);
void move_cursor_P(pointer *);
void move_cursor_Q(pointer *);
void move_cursor_S(pointer *);
void move_ultima_linha(pointer *);
void move_linha_x(pointer *, int );
void apaga_texto(pointer *);
void separa_linha(pointer *, linha *);
void atualiza_matriz(linha *);
void control_c(pointer *);
void control_x(pointer *, linha *);
void control_v(pointer *);
void uni_linha(pointer *, linha *);
void linha_ant(pointer *);
void exibe_pilha(pointer *);
int busca_linear(char *, pointer *);
void busca_substitui(char*, char*, pointer *);

#endif