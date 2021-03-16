#include <stdio.h>
#include <stdlib.h>

int main (void) {
	unsigned char *cptr = (char*)malloc(30000);
	char buf[1048];
	if (cptr == NULL) exit(1);
	fgets(buf, 1048, stdin);
	printf("%s\n", buf);
}
