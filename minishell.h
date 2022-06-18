/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 10:59:51 by ilahyani          #+#    #+#             */
/*   Updated: 2022/06/18 12:19:22 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

int     my_echo(char **data);
int     my_cd(char **data);
int     my_pwd(char **data);
int     my_export(char **data, char **env);
void    my_exit(char **data);
void    my_env(char **env);
int     ft_strcmp(const char *s1, const char *s2);
int     sizeof_array(char **arr);
int     is_int(char *c);
int     ft_exec(char **data);
char	**sort_tab(char **tab);
char    **parser(char *line);
char	*strchr_plus(const char *s, int c);
void	env_print(char	*env);
size_t	ft_strcpy(char *dst, char *src);
size_t	find_char(char *s, char c);

# endif