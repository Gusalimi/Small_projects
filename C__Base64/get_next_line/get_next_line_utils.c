/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:18:37 by gsaile            #+#    #+#             */
/*   Updated: 2022/11/26 11:29:53 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	s2 = malloc((ft_strlen_and_free(s1, NULL, 0) + 1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = 0;
	return (s2);
}

t_line	*lst_getlast(t_line *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	ft_strlen_and_free(const char *s, t_line **elem, int behavior)
{
	int	i;

	if (behavior == 0)
	{
		i = 0;
		while (s[i])
			i++;
		return (i);
	}
	else
	{
		free(*elem);
		*elem = NULL;
		return (-1);
	}
}

char	*clear_list(t_line **list, int behavior)
{
	t_line	*current;
	t_line	*next;

	if (*list == NULL)
		return (NULL);
	current = *list;
	while (current->next)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
	if (behavior == 0)
		clear_list2(&current, list);
	else
	{
		free(current->content);
		free(current);
		*list = NULL;
	}
	return (NULL);
}

void	clear_list2(t_line **current, t_line **list)
{
	char	*tmp;
	int		i;

	i = 0;
	while (((*current)->content)[i] && ((*current)->content)[i] != '\n')
		i++;
	if (((*current)->content)[i] == '\n')
		i++;
	if (!(((*current)->content)[i]))
	{
		free((*current)->content);
		free(*current);
		*list = NULL;
		return ;
	}
	tmp = ft_strdup((*current)->content + i);
	free((*current)->content);
	if (!tmp)
	{
		free(*current);
		*list = NULL;
		return ;
	}
	(*current)->content = tmp;
	*list = *current;
}
