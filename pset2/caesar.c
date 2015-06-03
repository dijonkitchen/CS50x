#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main (int argc, string argv[])
{
	if (argc !=2)
	{
		printf("Stop messing around! Type a number!\n");
		return 1;
	}

	int rotate = atoi(argv[1]);

	string text = GetString();

	int n = strlen(text);

	for (int i = 0; i < n; i++)
	{
		if (islower(text[i]))
		{
			text[i] = 'a' + ((text[i] - 'a' + rotate) % ('z' - 'a' + 1));	
		}
		
		else if (isupper(text[i]))
		{
			text[i] = 'A' + ((text[i] - 'A' + rotate) % ('Z' - 'A' + 1));	
		}

		else text[i] = text[i];

		printf("%c", text[i]);
	}

	printf("\n");

	return 0;
}