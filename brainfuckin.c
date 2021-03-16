#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define buf_size 1048

int main (void) {
	unsigned char *cells = (char*)malloc(30001);
	int cptr = 0;
	char buf[buf_size];

	char* stack[10];
	int curr = 0;

	if (cells == NULL) exit(1);

	memset(cells, 0, 30000);
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
					if (cptr<30000) {
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

			printf("read: %c, current cell's value: %d on position: %d\n", 
					*pc, (unsigned int)cells[cptr], cptr);
			
			pc++;
		}
		memset(buf, 0, buf_size);
	}

}
