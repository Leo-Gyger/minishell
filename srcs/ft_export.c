/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 09:46:58 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/06 17:40:22 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../incs/minishell.h"

void	ft_sort(t_env *env, int lenenv)
{
	int		j;
	char	*temp;
	char	*ntemp;

	j = 0;
	while (j < lenenv)
	{
		if (ft_strcmp(env->name, env->next->name) > 0)
		{
			ntemp = ft_strdup(env->value);
			temp = ft_strdup(env->name);
			env->name = ft_strdup(env->next->name);
			env->value = ft_strdup(env->next->value);
			env->next->name = ft_strdup(temp);
			env->next->value = ntemp;
		}
		env = env->next;
		j++;
	}
}

t_env	*sort(t_env *env, int lenenv)
{
	int	i;

	i = 0;
	while (i < lenenv)
	{
		ft_sort(env, lenenv - 1 - i);
		i++;
	}
	return (env);
}

int	isalreadyenv(char *name, char *val)
{
	t_env	*mem;

	mem = g_env;
	while (mem)
	{
		if (!ft_strncmp(name, mem->name, ft_strlen(name)))
		{
			mem->value = val;
			return (0);
		}
		mem = mem->next;
	}
	return (1);
}

void	add_varenv(t_shell *shell, char **cmd)
{
	unsigned int	i;
	char			**ret;
	t_env			*tmp;

	i = 1;
	while (cmd[i])
	{
		ret = ft_split(cmd[i], '=');
		if (isalreadyenv(ret[0], ret[1]))
		{
			tmp = new_env(ret[0], ret[1]);
			env_add_back(&shell->env, tmp);
		}
		free(ret);
		i++;
	}
}

int	ft_export(char **cmd, t_shell *shell)
{
	unsigned int	i;
	t_env			*tmp;

	i = 0;
	tmp = g_env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	if (cmd[1] == NULL)
	{
		tmp = g_env;
		tmp = sort(tmp, i);
		while (tmp)
		{
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
	}
	else
		add_varenv(shell, cmd);
	g_env = shell->env;
	return (1);
}
