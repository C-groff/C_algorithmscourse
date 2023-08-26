#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Editorfunções.c"
#include "Declarações.h"


char* fila_de_comandos() /*transforma os comandos em um vetor de char, não suporta mais que 3000 comandos*/
{
	int ch;
	char *linha = malloc(sizeof(char)*3000);
	int n = 0;
	while((ch = getc( stdin )) != '\n') {
		linha[n++] = ch;

	}
	linha[n] = '\0';
	return linha;
}

void executa(pointer *p, char* comandos, linha *l){
	int a = 0;
	int i = 0;
	while (comandos[a] != '\0'){
		if (comandos[a] =='A'){ /* pega o resto do vetor */
			a++;
			i = 0;			
			char* arquivo;
			arquivo = (char*)calloc(1000, sizeof(char));
			for (int i=0; comandos[a] != '\0'; a++, i++) arquivo[i] = comandos[a];
			carrega_arquivo(arquivo, p, l);
			free(arquivo);
		}
		if (comandos[a] == 'E'){ /* pega o resto do vetor */
			a++;
			i = 0;			
			char* arquivo_final;
			arquivo_final = (char*)calloc(100, sizeof(char));
			for (int i=0; comandos[a] != '\0'; a++, i++) arquivo_final[i] = comandos[a];
			escreve_arquivo(arquivo_final, p, l);
			free(arquivo_final);
		}
		if (comandos[a] == 'I') { /* pega o resto do vetor */
			a++;
			i = 0;
			while (comandos[a] != '\0'){
			insere_texto(comandos[a++], p);	
			}
		}
		if (comandos[a] == 'F'){
			a++;
			i = 0;
			move_cursor_F(p);
		}
		if (comandos[a] == 'T'){
			a++;
			i = 0;
			move_cursor_T(p);
		}
		if (comandos[a] == 'O'){
			a++;
			i = 0;
			move_cursor_O(p);
		}
		if (comandos[a] == 'P'){
			a++;
			i = 0;
			move_cursor_P(p);
		}
		if (comandos[a] == 'Q'){
			a++;
			i = 0;
			move_cursor_Q(p);
		}
		if (comandos[a] == '$'){
			a++;
			i = 0;
			move_cursor_S(p);
		}
		if (comandos[a] == ':'){ /* pega o resto do vetor */
			a++;
			if (comandos[a] == 'F'){
				move_ultima_linha(p);
				return;
			}
			else{
				char numero[100];
				for (int i=0; comandos[a] != '\0'; a++, i++) numero[i] = comandos[a];
				int val = atoi(numero);
				move_linha_x(p,val);
			}
		}
		if (comandos[a] == 'D'){
			a++;
			i = 0;
			apaga_texto(p);
		}
		if (comandos[a] == 'M'){
			a++;
			i = 0;
			M = p->cursor;
			ColunaMarcada = MatrizColuna;
			LinhaMarcada = MatrizLinha;
		}
		if (comandos[a] == 'C'){
			a++;
			i = 0;
			control_c(p);
		}
		if (comandos[a] == 'X'){
			a++;
			i = 0;
			control_x(p, l);
		}
		if (comandos[a] == 'B'){ /* pega o resto do vetor */
			a++;
			char* padrao;
			padrao = (char*)calloc(1000, sizeof(char));
			for (int i=0; comandos[a] != '\0'; a++, i++) padrao[i] = comandos[a];
			busca_linear(padrao, p);
			free(padrao);
		}
		if (comandos[a] == 'S'){ /* pega o resto do vetor */
			a++; 
			char* padrao; 
			char* nova;
			padrao = (char*)calloc(1000, sizeof(char));
			nova = (char*)calloc(1000, sizeof(char));
			for (int i=0; comandos[a] != '/'; a++, i++) padrao[i] = comandos[a];
			a++;
			for (int i=0; comandos[a] != '\0'; a++, i++) nova[i] = comandos[a];
			busca_substitui(padrao, nova, p);
			free(padrao);
			free(nova);
		}
		if (comandos[a] == 'N'){
			a++;
			i = 0;
			separa_linha(p, l);
		}
		if (comandos[a] == '!'){
			flag = 0;
			printf(" \n****** FIM DO PROGRAMA E FELIZ NATAL :) ***** ");
			return;
		}
		if (comandos[a] == 'V'){
			control_v(p);
			a++;
			i = 0;
		}
		if (comandos[a] == 'U'){
			uni_linha(p, l);
			a++;
			i = 0;
		}
		if (comandos[a] == 'J'){
			prox_linha(p);
			a++;
			i = 0;
		}
		if (comandos[a] == 'H'){
			linha_ant(p);
			a++;
			i = 0;
		}
		if (comandos[a] == 'Z'){
			exibe_pilha(p);
			a++;
			i = 0;
		}
  /* explicado no relatório */
		i++;
		if (i>2){
			a++;
			i = 0;
		}
	}
	free (comandos);
}

int main()
{	
	M = NULL; /* definiçoes para começar o programa */
	flag = 1;
	pointer *p;
	p = cria_ponteiro_e_pilha();
	linha *l;
	l = cria_linhazero(p);
	while (flag){ /* lê os comandos, transforma em vetor de char e executa char por char enquanto o char nao for ! */
		printf("<%d,%d>", MatrizLinha, MatrizColuna);
		executa(p,fila_de_comandos(),l);
		mostralinha(p);
	}
	return 0;

}