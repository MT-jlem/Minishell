/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:47:14 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/07 21:16:07 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_node(char *buff, t_env **lst)
{
	char	**tab;

	tab = ft_split(buff, '=');
	(*lst)->var = ft_strdup(tab[0]);
	if (tab[1])
		(*lst)->value = ft_strdup(tab[1]);
	else
		(*lst)->value = NULL;
	(*lst)->next = NULL;
	free_tab(tab);
}

t_env	*exprt_lstnew(char *buff)
{
	t_env	*res;

	if (!buff)
		return (NULL);
	res = (t_env *) malloc (sizeof(t_env));
	if (!res)
		return (NULL);
	if (!find_char(buff, '='))
		fill_node(buff, &res);
	else if (find_char(buff, '+')
		&& find_char(buff, '+') < find_char(buff, '='))
	{
		res->var = ft_strldup(buff, find_char(buff, '+'));
		res->value = ft_strdup(strchr_plus(buff, '='));
	}
	else
	{
		res->var = ft_strldup(buff, find_char(buff, '='));
		res->value = ft_strdup(strchr_plus(buff, '='));
	}
	return (res);
}

int	check_var(char *buf, t_env *lst)
{
	if (find_char(buf, '='))
	{
		if ((find_char(buf, '+')
				&& !ft_strcmp(lst->var, ft_strldup(buf, find_char(buf, '+')))))
			return (1);
		else if (find_char(buf, '=')
			&& !ft_strcmp(lst->var, ft_strldup(buf, find_char(buf, '='))))
			return (1);
	}
	else if (!ft_strcmp(lst->var, buf))
		return (1);
	return (0);
}

void	update_exp(char *buff, t_env **lst)
{
	char	*tmp;

	if (buff[find_char(buff, '=') - 1] == '+')
	{
		if ((*lst)->value)
		{
			tmp = ft_strdup((*lst)->value);
			free((*lst)->value);
			(*lst)->value = ft_strjoin(tmp, strchr_plus(buff, '='));
			free(tmp);
		}
		else
			(*lst)->value = ft_strdup(strchr_plus(buff, '='));
	}
	else
		(*lst)->value = ft_strdup(strchr_plus(buff, '='));
}
