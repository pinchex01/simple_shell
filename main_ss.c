#include "shell.h"
/**
 * main - the main for the simple shell
 * @argc: total arguments passed to the shell.
 * @argv: Vector containing arguments passed.
 *
 * Return: 0 on success or 1 on failure.
 */
int main(int argc, char **argv)
{
	info_y info[] = {SET_INFO};
	int st = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(st)
		: "r"(st));

	if (argc == 2)
	{
		st = open(argv[1], O_RDONLY);
		if (st == -1)
		{
			if (errno == EACCES)
				exit(126);

			if (errno == ENOENT)
			{
				puts_err(argv[0]);
				puts_err(": 0: Can't open ");
				puts_err(argv[1]);
				putchar_err('\n');
				putchar_err(NEG_ONE);
				exit(127);
			}

			return (EXIT_FAILURE);
		}

		info->st_read = st;
	}

	gather_env(info);
	read_history(info);
	shell_main(info, argv);

	return (EXIT_SUCCESS);
}

