/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 12:33:06 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/06 16:19:55 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	double_free(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (0);
}

void	free_all(t_shell *shell, int exit_p, char *str)
{
	if (shell->std_in > 0)
		close_error(shell->std_in);
	if (shell->std_out > 1)
		close_error(shell->std_out);
	free_cmd(shell->cmd);
	rl_clear_history();
	if (exit_p)
	{
		perror(str);
		exit(EXIT_FAILURE);
	}
}

void	free_struct(t_shell *shell)
{
	free(shell->cmdline);
	free(shell->prompt);
	shell->prompt = NULL;
}

void	d_free(char	*swap, t_vars *vars)
{
	if (swap)
		free(swap);
	free_vars(vars);
	exit(-1);
}
