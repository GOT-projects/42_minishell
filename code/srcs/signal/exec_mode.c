#include "../../includes/mini_shell.h"

void	handler_exec_main(int signum)
{
	if (signum == SIGINT || signum == SIGQUIT)
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
}

void	exec_mode(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = &handler_exec_main;
	if (sigaction(SIGINT, &sa, NULL) == -1
			|| sigaction(SIGQUIT, &sa, NULL) == -1)
		ft_putstr_fd("Error sigaction\n", 2);
}

void	exec_mode_sub_process(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &sa, NULL) == -1
			|| sigaction(SIGQUIT, &sa, NULL) == -1)
		ft_putstr_fd("Error sigaction\n", 2);
}
