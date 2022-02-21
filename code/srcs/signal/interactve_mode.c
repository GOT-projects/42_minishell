#include "../../includes/mini_shell.h"

void	handler_interative(int signum)
{
	if (signum == SIGINT || signum == SIGQUIT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	interactive_mode(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = &handler_interative;
	if (sigaction(SIGINT, &sa, NULL) == -1
			|| sigaction(SIGQUIT, &sa, NULL) == -1)
		ft_putstr_fd("Error sigaction\n", 2);
}
