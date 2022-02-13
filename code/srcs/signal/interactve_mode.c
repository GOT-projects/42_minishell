#include "../../includes/mini_shell.h"

void	handler_interative(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
		return ;
}

void	interactive_mode(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = &handler_interative;
    sigemptyset(&(sa.sa_mask));
	sigaddset(&(sa.sa_mask), SIGINT);
	sigaddset(&(sa.sa_mask), SIGQUIT);
	if (sigaction(SIGINT, &sa, NULL) == -1
			|| sigaction(SIGQUIT, &sa, NULL) == -1)
		ft_putstr_fd("Error sigaction\n", 2);
}
