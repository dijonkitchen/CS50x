#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main (int argc, string argv[])
{
	if (argc != 2)
	{
		printf("Stop messing around! Type ONE word!\n");
		return 1;
	}

	for (int i = 0; i < strlen(argv[1]); i++)
	{
		if (!isalpha(argv[1][i]))
		{
			printf("Only letters please!\n");
			return 1;
		}	
	}

	if (argc == 2)
	{
		string text = GetString();

		int j = 0;
		int n = strlen(text);
		int rotate = 0;

		for (int i = 0; i < n; i++)
		{
			if (islower(text[i]))
			{
				if (islower(argv[1][j]))
					rotate = argv[1][j] - 'a';	
				else 
					rotate = argv[1][j] - 'A';	
				
				text[i] = 'a' + ((text[i] - 'a' + rotate) % ('z' - 'a' + 1));	
				j++;
			}
			
			else if (isupper(text[i]))
			{
				if (islower(argv[1][j]))
					rotate = argv[1][j] - 'a';	
				else 
					rotate = argv[1][j] - 'A';	

				text[i] = 'A' + ((text[i] - 'A' + rotate) % ('Z' - 'A' + 1));	
				j++;
			}

			if (j >= strlen(argv[1]))
			{
				j = 0;
			}

			printf("%c", text[i]);
		}

		printf("\n");

		return 0;
	}
}