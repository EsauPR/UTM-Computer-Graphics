#include <stdio.h>

int main()
{
	for(int i=0; i<26; i++)
		printf("case: '%c': x=i; y = i; break;\n", '0'+i );
}