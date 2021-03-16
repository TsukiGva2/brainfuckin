#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a,b) (a<b?a:b)
#define cell_max 1048
#define buf_size 1048

int main (void) {
	unsigned char *cells = (char*)malloc(cell_max+1);
	int cptr = 0;
	char buf[buf_size];

	char* stack[10];
	int curr = 0;

	if (cells == NULL) exit(1);

	memset(cells, 0, cell_max);
	memset(buf, 0, buf_size);

	while (fgets(buf, buf_size, stdin)) {
		char* pc = buf;
		while (*pc != '\0' && *pc != '\n') {
			
			switch (*pc) {
				case '+':
					*(cells+cptr) += 1;
				break;
				case '-':
					*(cells+cptr) -= 1;
				break;
				case '>':
					if (cptr<cell_max) {
						cptr++;
					}
					else {
						printf("out of memory, exiting\n");
						exit(1);
					}
				break;
				case '<':
					if (cptr>0) {
						cptr--;
					}
				break;
				case '[':
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
			
			cptr = min(cptr,cell_max);

			printf("cells: ");
			for (int i = min(0,cptr-2); i < cptr+3; i++) {
				printf("%d ",cells[i]);
			}
			putchar('\n');

			pc++;
		}
		memset(buf, 0, buf_size);
	}

}
