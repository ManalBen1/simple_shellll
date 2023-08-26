#include "shell.h"

/**
 *print_input_string - prints string entered
 * @str: string to print
 */
void print_input_string(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		write_char(str[i]);
		i++;
	}
}

/**
 * write_char - writes the character c to stderr
 * @c: The character to print
 * Return: On success 1.on error, -1 is returned, error number is set
 */
int write_char(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

//wtite_file_descr - writes the character c to given file_descr

int wtite_file_descr(char c, int file_descr)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(file_descr, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfile_descr - prints an input string
 * @str: the string to be printed
 * @file_descr: the filedescriptor to write to
 * Return: the number of chars put
 */
int _putsfile_descr(char *str, int file_descr)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += wtite_file_descr(*str++, file_descr);
	}
	return (i);
}

