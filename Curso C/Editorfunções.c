#include <stdlib.h>
#include <stdio.h>
#ifndef _HAVE_SUPPORT_C
#define _HAVE_SUPPORT_C
#include "Declarações.h"

/* funções de apoio */
pointer *cria_ponteiro_e_pilha() /* // cria o cursor e a pilha de memória // */ {
	pointer *p = malloc(sizeof(pointer));
	p->cursor = malloc(sizeof(celula));
	G = malloc(sizeof(pilha));
	G->topo = malloc(sizeof(celula));
	return p;
}

linha *cria_linhazero(pointer* p)  /* cria a linha 0 */  {
	linha *l = malloc(sizeof(linha));
	l->prox = NULL;
	l->cabeça = p->cursor;
	l->cabeça->ant = NULL;
	p->começo = l;
	l->Numlinha = MatrizLinha = 0;
	return l;
}

celula *cria_celula() /* // função auxilar // */ {
	celula *C = malloc(sizeof(celula));
	return C; 
}

void mostralinha(pointer *p) /*  */ {
	celula* c;
	if (p->começo->cabeça != NULL){
		for (c = p->começo->cabeça->prox; c != NULL; c = c->prox)
		printf("%c", c->ch);
		printf("\n");

	}
	for (int k = 0; k < MatrizColuna; k++)
		printf(" ");
		printf("^\n");
	
	if (M != NULL){
		for (int k = 0; k < ColunaMarcada; k++)
			printf(" ");
			printf("M (l:%d,c:%d)\n", LinhaMarcada, ColunaMarcada);
	} 
}

linha *cria_nova_linha(pointer *p, linha *l) /* // função executada no Main, que printa a linha // */ {
	linha *nova = malloc(sizeof(linha));
	nova->prox = NULL;
	if (l->prox != NULL) {
		l->prox->ant = nova;
		nova->prox = l->prox;
	}
	l->prox = nova;
	nova->ant = l;
	MatrizLinha = nova->Numlinha = (l->Numlinha + 1);
	nova->cabeça = malloc(sizeof(celula));
	nova->cabeça->prox = NULL;
	nova->cabeça->ant = NULL;
	p->cursor = nova->cabeça;
	p->começo = nova;
	MatrizColuna = 0;
	return nova; 
}

void atualiza_matriz(linha *l) /* // função que varre todas as linhas atualizando o numero contido nelas // */ {
	for (linha *ref = l->prox; ref != NULL; ref = ref->prox) ref->Numlinha = (ref->ant->Numlinha + 1);// função que varre todas as linhas atualizando o numero contido nelas //
}


/* funções mínimas */
void insere_texto(char c, pointer* p) /* // inserção em lista encadeada // */ {
	celula *nova;
	nova = malloc(sizeof(celula));
	if (p->cursor->prox != NULL) p->cursor->prox->ant = nova;
	nova->ant = p->cursor;
	nova->ch = c;                               // o caracter novo é c	
	nova->prox = p->cursor->prox;				// o novo aponta pra frente
	p->cursor->prox = nova;						// o de trás aponta pro novo
	p->cursor = nova;							// o cursor fica no novo

	if (MatrizColuna < ColunaMarcada) ColunaMarcada++;
	MatrizColuna++; 
}

char *ler_o_arquivo(char *nomedoaqruivo) /* // abre em modo de leitura // */ {
	FILE *file = fopen(nomedoaqruivo,"r");
	if (file == NULL){
	printf("Ocorreu um erro na abertura do arquivo");
	char *nulo = malloc(sizeof(char));
	nulo[0] = '\0';
	return nulo;
	}
	fseek(file, 0, SEEK_END);
	int tamanho = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *texto = malloc(sizeof(char)*(tamanho+1));
	char c; int i;
	for (i = 0; (c = fgetc(file)) != EOF; i++){
		texto[i] = c;
	}
	texto[i] = '\0';
	fclose(file);
	return texto; 
}

void carrega_arquivo(char *nomedoaqruivo, pointer* p, linha *l) /* // lê e insere // */ {
	char *texto = ler_o_arquivo(nomedoaqruivo);
	int i = 0;
	while (texto[i] != '\0'){
		if (texto[i] == '\n') {
			apaga_texto(p);
			l = cria_nova_linha(p, l);
			i++;
		}
		else insere_texto(texto[i++], p);

	} 
}

void escreve_arquivo (char *nomedoaqruivo, pointer* p, linha *l) /* // função que cria um novo arquivo e preenche com o conteudo do editor, apagando tudo do editor // */ {
	FILE *farq;
	if((farq = fopen(nomedoaqruivo,"w")) == NULL){
  		printf( "Erro na abertura do arquivo");
  		exit(1);
	}
	p->cursor = l->cabeça->prox;
	p->começo = l;
	while (p->cursor != NULL || p->começo->prox != NULL){
		if (p->cursor == NULL){
			if (p->começo->prox != NULL){
				p->começo = p->começo->prox;
				p->cursor = p->começo->cabeça->prox;
				fputc('\n', farq);
			}
		}
		else {
			celula *c = p->cursor;
			fputc(p->cursor->ch, farq);
			p->cursor = p->cursor->prox;
			free(c);
		}
	}
	fclose(farq);
	l->cabeça->prox = NULL;
	l->prox = NULL;
	p->cursor = l->cabeça;
	p->começo = l; 
	MatrizColuna = 0;
	MatrizLinha = 0;
	M = NULL;
}

void control_v(pointer *p) /* / cola na posição do cursor, criando nova linha em caso de '\n' // */ {
	celula *C;
	if (G->topo != NULL){
		pilha *O = G;
		for (C = O->topo->prox; C != NULL; C = C->prox){
			if (C->ch == '\n'){
				p->começo = cria_nova_linha(p, p->começo);
			}
			else insere_texto(C->ch, p);
		}
		if (G->ant == NULL){
			G->ant = malloc(sizeof(pilha));
			G->ant->topo = malloc(sizeof(celula));
		}
		G = G->ant;
	}
}

void move_cursor_F(pointer *p) /* // move cursor pra frente // */ {
	if(p->cursor->prox != NULL){
		p->cursor = p->cursor->prox;
		MatrizColuna++;
	} 
}

void move_cursor_T(pointer *p) /* // move cursor pra tras // */ {
	if(p->cursor->ant != NULL){
		p->cursor = p->cursor->ant;
		MatrizColuna--;
	} 
}

void move_cursor_O(pointer *p) /* // move cursor pro inicio da linha // */ {
	p->cursor = p->começo->cabeça;
	MatrizColuna = 0; 
}

void move_cursor_P(pointer *p) /* // move cursor pro inicio da proxima palavra // */ {
	while (p->cursor->prox != NULL && p->cursor->ch != ' '){
		MatrizColuna++;
		p->cursor = p->cursor->prox;
	}
	while (p->cursor->prox != NULL && p->cursor->prox->ch == ' '){
		MatrizColuna++;
		p->cursor = p->cursor->prox;
	} 
}

void move_cursor_Q(pointer *p) /* // move cursor pro inicio da palavra atual // */ {
	while (p->cursor->ant != NULL && p->cursor->ch != ' '){
		MatrizColuna--;
		p->cursor = p->cursor->ant;
	} 
}

void move_cursor_S(pointer *p) /* // move cursor pro final da linha // */ {
	while (p->cursor->prox != NULL){
		p->cursor = p->cursor->prox;
		MatrizColuna++;
	} 
}

void move_linha_x(pointer *p, int x) /* // move cursor pro inicio da linha de número x // */ {
	while (p->começo->Numlinha < x && p->começo->prox != NULL)
		p->começo = p->começo->prox;
	while (p->começo->Numlinha > x && p->começo->ant != NULL)
		p->começo = p->começo->ant;
	p->cursor = p->começo->cabeça;
	MatrizColuna = 0;
	MatrizLinha = p->começo->Numlinha;
}

void move_ultima_linha(pointer *p) /* // move cursor pro inicio da ultima linha // */ {
	pointer *ref = malloc(sizeof(pointer));
	ref->começo = p->começo;
	ref->cursor = p->cursor;
	while (ref->começo->prox != NULL)
		ref->começo = ref->começo->prox;
	p->cursor = ref->começo->cabeça;
	p->começo = ref->começo;
	MatrizColuna = 0;
	MatrizLinha = ref->começo->Numlinha;
	free(ref); 	
}

void exibe_pilha(pointer *p) /* // mostra a pilha de memória // */ {
	celula* c;
	if (G->topo != NULL){
		printf("\n ----------------------------- \n");
		pilha *O = G;
		for (c = O->topo->prox; c != NULL; c = c->prox){
			printf("%c", c->ch);
			if (c->prox == NULL && O->ant != NULL){
				O = O->ant;
				c = O->topo;
				printf("\n -------------------------- \n");
			}
		}
		printf("\n ------------------------------------- \n"); 
	}  
}

void prox_linha(pointer *p) /* // vai para a proxima linha // */ {
	if (p->começo->prox != NULL){
		p->começo = p->começo->prox;
		p->cursor = p->começo->cabeça;
		MatrizLinha++;
	}
	for (int i = 0; p->cursor != NULL && i != MatrizLinha; i++, p->cursor = p->cursor->prox); 
}

void linha_ant(pointer *p) /* vai para a linha anterior */{
	if (p->começo->ant != NULL){
		p->começo = p->começo->ant;
		p->cursor = p->começo->cabeça;
		MatrizLinha--;
	}
	for (int i = 0; p->cursor != NULL && i != MatrizLinha; i++, p->cursor = p->cursor->prox); 

}

void uni_linha(pointer *p, linha *l) /* junta linha atual e a proxima na posição atual do cursor */{
	move_cursor_S(p);
	p->cursor->prox = p->começo->prox->cabeça->prox;
	if (p->cursor->prox != NULL) p->cursor->prox->ant = p->cursor;
	p->começo->prox = p->começo->prox->prox;
	free(p->começo->prox->ant);
	p->começo->prox->ant = p->começo;
	atualiza_matriz(l); 
}

void separa_linha(pointer *p, linha *l) /* // separa linha na posição atual do cursor // */ {
	p->cursor = p->cursor->prox;
	celula *ref = p->cursor;
	p->começo = cria_nova_linha(p, p->começo);
	if (ref == NULL){
		atualiza_matriz(l);
		return;
	}
	if (ref->ant != NULL) {
		ref->ant->prox = NULL;
		p->cursor->prox = ref;
	}
	else {
		p->começo->cabeça->prox = ref->prox;
		ref->prox = NULL;
	}
	p->cursor = p->começo->cabeça;
	atualiza_matriz(l);
}

void busca_substitui(char *s, char *r, pointer *p) /* // busca e substitui as ocorrencias // */ {
	char *padrao = s;
	int Tam_s = strlen(s);
	int Tam_r = strlen(r);
	while(busca_linear(s, p)){
		for (int i = 0; i < Tam_s; i++){
			apaga_texto(p);
		}
		for (int i = 0; i < Tam_r; i++){
			insere_texto(r[i] ,p);
		}
	} 
}

int busca_linear(char *padrao, pointer *p) /* // busca as ocorrencias // */ {
	int Tam_string = strlen(padrao);
	int m = MatrizColuna;
	int n = MatrizLinha;
	celula *c = p->cursor;
	linha *l = p->começo;
	while (c->prox != NULL || l->prox != NULL){
		for (int i = 0; c->prox != NULL && c->ch == padrao [i]; i++, c = c->prox, MatrizColuna++){ 
			if (i + 1 == Tam_string){
				p->cursor = c;
				p->começo = l; 
				return 1;
			}
		}
		if (c->prox == NULL){
			l = l->prox;
			c = l->cabeça;
			MatrizColuna = 0;
			MatrizLinha++;
		}	
		else{
			MatrizColuna++;
			c = c->prox;
		}
	}
	MatrizLinha = n;
	MatrizColuna = m;
	return 0; 
}
	
void apaga_texto(pointer *p) /* // apaga na posição do cursor // */ {
	celula *ref = p->cursor;
	if (ref = M) M = NULL;

	if (p->cursor->ant == NULL){
		return;
	}

	 if (p->cursor->prox != NULL){
	 p->cursor->ant->prox = p->cursor->prox;
	 p->cursor->prox->ant = p->cursor->ant;
	 p->cursor = p->cursor->prox;
	 	 free(ref);
	}
	else{
		p->cursor = p->cursor->ant;
		p->cursor->prox = NULL;
		free(ref);
	}
	move_cursor_T(p); 
}

void control_c(pointer *p) /* // copia sem deletar // */ {
	if (M == NULL){

		printf("\n**M não definido**\n");
		return;
	}
	if (G->topo->prox != NULL){

	pilha *V = malloc(sizeof(pilha));
	V->topo = malloc(sizeof(celula));
	V->ant = G;
	G = V;
}
	pointer *ref = malloc(sizeof(pointer));
	ref->cursor = p->cursor;
	ref->começo = p->começo;
	if (ref->cursor == ref->começo->cabeça) ref->cursor = ref->cursor->prox;
	celula *ref2 = G->topo;
	while (ref->cursor != M){
		while (ref->cursor == NULL && ref->começo->prox != NULL){
			ref2->prox = cria_celula();
			ref2->prox->ch = '\n';
			ref2 = ref2->prox;
			ref->começo = ref->começo->prox;
			ref->cursor = ref->começo->cabeça->prox;
		}
		ref2->prox = cria_celula();
		ref2->prox->ch = ref->cursor->ch;
		ref2 = ref2->prox;
		ref->cursor = ref->cursor->prox;

		}
	ref2->prox = cria_celula();
	ref2->prox->ch = M->ch;
	free(ref); 
}

void control_x(pointer *p, linha *l) /*// copia deletando //*/ {
	if (M == NULL){
		printf("\n**M não definido**\n");
		return;
	}
	control_c(p);
	pointer *ref = malloc(sizeof(pointer));
	ref->começo = p->começo;
	ref->cursor = p->cursor;
	if (ref->cursor == ref->começo->cabeça) ref->cursor = ref->cursor->prox;
	while (ref->cursor != M){
		while (ref->cursor == NULL && ref->começo->prox != NULL){
			
			linha *lin = ref->começo;
			if (ref->começo->ant != NULL) {
				lin->ant->prox = lin->prox;
				lin->prox->ant = lin->ant;
			}
			ref->começo = ref->começo->prox;
			ref->cursor = ref->começo->cabeça->prox;
		}

		while (ref->cursor != NULL && ref->cursor != M){

			celula *c = ref->cursor;
	 		ref->cursor->ant->prox = ref->cursor->prox;
	 		if (ref->cursor->prox != NULL) ref->cursor->prox->ant = ref->cursor->ant;
	 		ref->cursor = ref->cursor->prox;
	 	 	free(c);

		}

}

	if (M->ant != NULL) M->ant->prox = M->prox;
	if (M->prox != NULL) M->prox->ant = M->ant;
	free(M);
	M = NULL;
	atualiza_matriz(l);
	int x = p->começo->Numlinha;
	move_ultima_linha(p);
	move_linha_x(p, x); 
}


#endif
