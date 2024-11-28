// signal.c 

#include "minishell.h"

static void	sig_init(void)
{
	sig.sigint = 0;
	sig.sigquit = 0;
	sig.child = 0;
	sig.exit_status = 0;
}

void	handle_signals(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	sig_init();

	// Handle SIGINT (Ctrl+C)
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);

	// Ignore SIGQUIT (Ctrl+\)
	sa_quit.sa_handler = handle_sigquit;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	handle_sigint(int signal)
{
	(void)signal;
	// If a child process is not running
	if (!sig.child)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		sig.exit_status = 1;
	}
	else
	{
		printf("\n");
		sig.exit_status = 130;
	}
	sig.sigint = 1;
}

void	handle_sigquit(int signal)
{
	(void)signal;
}

