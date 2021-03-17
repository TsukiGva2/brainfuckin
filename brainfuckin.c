#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define min(a,b) (a<b?a:b)
#define cell_max 1048
#define buf_size 1048

#define skip 0
#define eval 1

int main (void) {
	unsigned char *cells = (char*)malloc(cell_max);
	int cptr = 0; // memory pointer
	char buf[buf_size]; // input buffer
    
	int state = eval;

	char* stack[10]; // loop stack
	int curr = 0; // current position on stack
	bool ignore = false;

	if (cells == NULL) exit(1); // exit if malloc error
	
	memset(cells, 0, cell_max); // zero out all cells

	while (fgets(buf, buf_size, stdin)) { // get a string from stdin to buf

        char* pc = buf; // program counter

		while (*pc != '\0' && *pc != '\n') { // while ! end of string and ! EOL
			
			if (state != skip || *pc == ']' || *pc == '[') {

			switch (*pc) {
				case '+':
					*(cells+cptr) += 1; // increment cell
				    break;

				case '-':
					*(cells+cptr) -= 1; // decrement cell
				    break;
                    
				case '>':							
					if (cptr<cell_max) { // if on cell range
						cptr++; // increment memory pointer
					}
					else { // die if not on cell range (currently 1048)
						printf("out of memory, exiting\n");
						exit(1);
					}
				    break;
				case '<':
					if (cptr>0) { // prevent memory pointer from being < 0 and giving us a delightful segfault
						cptr--; // decrement memory pointer
					}
				    break;
				case '[': // start loop
					if (state == skip) {
						ignore = true;
						break;
					}
					if (curr<10) {
						curr += 1; // increment "stack" position
						stack[curr] = pc; // "pushing" program counter to "stack"
						state = skip;
					}
					else {
						printf("stack overflow error, exiting\n");
						exit(1);
					}
				    break;
				case ']':
					if (ignore) {
						ignore = false;
						break;
					}
					if (curr>0) {
						if (cells[cptr] != 0) {
							pc = stack[curr];
						}
						else {
							curr--;
						}
						state = eval;
					}
					else {
						printf("misplaced ]\n");
						exit(1);
					}
				break;
				case '.':
					putchar(cells[cptr]);
				break;
			}
			}

			//printf("\nread: %c, current cell's value: %d on position: %d, state = %d\n", 
			//		*pc, (unsigned int)cells[cptr], cptr, state);
			
			// print stuff
			printf("\ncells: ");
			for (int i = min(0,cptr-2); i < min(cptr+3,cell_max); i++)
				printf("%d ",cells[i]);

			putchar('\n');

			pc++;
		}
	}
	free(cells);
	return 0;
}
