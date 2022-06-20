/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:28:30 by ilahyani          #+#    #+#             */
/*   Updated: 2022/06/18 12:59:13 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int my_echo(char **data)
{
    int i;
    int args;
    int new_line;

    args = sizeof_array(data);
    if (args == 1)
    {
        printf("\n");
        return (0);
    }
    i = 1;
    if (!ft_strcmp(data[1], "-n"))
    {
        new_line = 0;
        i++;
    }
    while (i < args)
    {
        printf("%s", data[i]);
        if (i++ != args - 1)
            printf(" ");
    }
    if (new_line)
        printf("\n");
    return (0);
}

int my_pwd(char **data)
{
    char    *cwd;
    int     args;

    args = sizeof_array(data);
    if (args > 1)
    {
        printf("too many arguments\n");
        return (2);
    }
    cwd = NULL;
    cwd = getcwd(cwd, 1000);
    if (!cwd)
        printf("error\n");
    printf("%s\n", cwd);
    return (0);
}


int my_cd(char **data)
{
    int args;

    args = sizeof_array(data);
    if (args == 1)
    {
        if (chdir(getenv("HOME")) != 0)
            perror("minishell: cd: ");
    }
    else if (chdir(data[1]) != 0)
        perror("minishell: cd: ");
    return (0);
}

void    my_exit(char **data)
{
    if (sizeof_array(data)  == 1)
        exit(1);
    else
    {
        if (is_int(data[1]) && data[2])
            printf("too many arguments\n");
        else
            exit(1);
    }
}

int my_export(char **data, char **env)
{
    char    **sorted;
    int     args;
    int     i;
    int     j;

    args = sizeof_array(data);
    sorted = sort_tab(env);
    if (args == 1)
    {
        i = -1;
        while (sorted[++i])
        {
            if (find_char(sorted[i], '=') == -1)
                printf("%s\n", sorted[i]);
            else
                env_print(sorted[i]);
        }
    }
    else
    {
        i = 0;
        while (env[i] && ft_strncmp(env[i], data[1], find_char(data[1], '=')))
            i++;
        if (env[i])
        {
            if (data[1][find_char(data[1], '=') - 1] == '+')
            {
                // printf("+=\n");
                env[i] = ft_strjoin(env[i], data[1] + find_char(data[1], '=') + 1);
                // printf("|%s|\n", env[i]);
            }
            else
            {
                //printf("=\n");
                env[i] = data[1];
                //printf ("|%s|\n", env[i]);
            }
        }
        else
        {
            //printf("!\n");
            j = -1;
            while(env[++j]);
            env[j] = ft_strdup(data[1]);
            env[j + 1] = NULL;
        }
    }
    //FREE sorted
    return (0);
}

// int my_export(char **data, char **env)
// {
//     t_list   *sorted=NULL;
//     t_list   *tmp=NULL;
//     int     i;
//     int     j;

//     sorted = ft_sort(env);
//     if (sizeof_array(data) == 1)
//     {
//         tmp = sorted;
//         while (tmp->next)
//         {
//             env_print(tmp->content);
//             tmp = tmp->next;
//         }
//     }
//     else
//     {
//         i = 0;
//         while (env[i] && ft_strncmp(env[i], data[1], find_char(env[i], '=')))
//             i++;
//         if (env[i])
//         {
//             if (data[1][find_char(data[1], '=') - 1] == '+')
//             {
//                 printf("+=\n");
//                 ft_strjoin(env[i], data[1] + find_char(data[1], '='));
//             }
//             else
//                 env[i] = data[1];
//         }
//         else if (!env[i])
//         {
//             j = 0;
//             while(env[j++]);
//             env[j] = ft_strdup(data[1]);
//             env[j + 1] = NULL;
//         }
//         else
//             return (1);
//     }
//     //FREE sorted
//     return (0);
// }

void    my_env(char **env)
{
    int i;

    i = -1;
    while (env[++i])
        if (find_char(env[i], '=') != -1 && env[find_char(env[i], '=') + 1])
            printf("%s\n", env[i]);
}



// Export x; x->export
// Export a=asdf; x->(env, export)
// Export x+=faf