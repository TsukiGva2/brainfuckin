#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a,b) (a<b?a:b)
#define cell_max 1048
#define buf_size 1048

int main (void) {
	unsigned char *cells = (char*)malloc(cell_max); // qual o ponto de colocar aquele + 1? tirei fodase 😎
	int cptr = 0;                                   // tipo o cursor sla
	char buf[buf_size];                             // lixo
    

	char* stack[10];                                // bagulho de memoria
	int curr = 0;                                   // coisa de brainfuck tomanocu

	if (cells == NULL) exit(1);                     // se nao tem cells sai

	memset(cells, 0, cell_max);                     // faz o array das cells receber 0 em todos os indices?
	memset(buf, 0, buf_size);                       // faz o array do buf receber 0 em todos os indices?

	while (fgets(buf, buf_size, stdin)) {           // de algum jeito fica pegando o input aí

        char* pc = buf;                             // ponteiro que aponta pra string que o user colocou

		while (*pc != '\0' && *pc != '\n') {        // enquanto essa string nao ternminar ou o cara apertar enter
			
			switch (*pc) {
				case '+':                           
					*(cells+cptr) += 1;             // adiciona 1 a célula na posição cptr
				    break;

				case '-':
					*(cells+cptr) -= 1;             // faz o contrario
				    break;
                    
				case '>':							
					if (cptr<cell_max) {			// só faz isso se nao ultrapassar o valor maximo de celulas
						cptr++;						// aqui bota o "cursor" pra frente (cursor = qual celula tá)
					}
					else {							// se ultrapassar acabou a memoria haha lol
						printf("out of memory, exiting\n");
						exit(1);
					}
				    break;
				case '<':							// aqui faz o contrario da parada
					if (cptr>0) {					// aparentemente ele nao pode ser um valor negativo huh
						cptr--;	
					}
				    break;
				case '[':							// nao sei o que isso faz pq eu nao sei brainfuck e nem quero saber (na vdd eu sabia só nao lembro de mais nada pq faz muito tempo que eu vi)
					if (curr<10) {
						if (cells[cptr] != 0) {
							curr += 1;
							stack[curr] = pc;
						}
					}
					else {
						printf("stack overflow error, exiting\n");
						exit(1);
					}
				    break;
				case ']':
					if (curr>0) {
						if (cells[cptr] != 0) {
							pc = stack[curr];
						}
						else {
							curr--;
						}
					}
					else {
						printf("misplaced ]\n");
						exit(1);
					}
				    break;
			}

			//printf("read: %c, current cell's value: %d on position: %d\n", 
			//		*pc, (unsigned int)cells[cptr], cptr);
			
			cptr = min(cptr,cell_max);									// acho isso redundante, nao muda nada no programa (eu acho né) (mesmo que o ponteiro passe da ultima célula, o programa vai ser finalizado mesmo assim) (pelo menos eu só testei os >>>> e os ++++ ----- +++-+--+ -+-+ ><><><><>, não cheguei a testar os [] [] [[[[ [][] [] ][]]]], nem sei pra que serve lololololololol, eta porra comentario gigante slc blz parei)

			// printa os bagulho
			printf("cells: ");
			for (int i = min(0,cptr-2); i < cptr+3; i++)
				printf("%d ",cells[i]);

			putchar('\n');

			pc++;
		}
		memset(buf, 0, buf_size);										// tbm acho isso aqui desnecessario (ao meu ver, nao mudou nada no programa)
	}

}

/*
	Reject humanity, become monke 🐒
*/
