/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:48:12 by gsaile            #+#    #+#             */
/*   Updated: 2022/11/26 11:29:30 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_line	*list[4096];
	char			*line;
	int				readed;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	readed = 1;
	while (!has_nl(list[fd]) && readed > 0)
	{
		readed = read_to_list(fd, &(list[fd]));
		if (readed == -1)
			return (clear_list(&(list[fd]), 1));
	}
	line = get_lline(list[fd]);
	clear_list(&(list[fd]), 0);
	if (!line || line[0] == 0)
	{
		if (line)
			free(line);
		return (NULL);
	}
	return (line);
}

int	read_to_list(int fd, t_line **list)
{
	char	buffer[BUFFER_SIZE + 1];
	t_line	*new_elem;
	int		i;

	i = 0;
	while (i <= BUFFER_SIZE)
		buffer[i++] = 0;
	new_elem = malloc(sizeof(t_line));
	if (new_elem == NULL)
		return (-1);
	i = read(fd, buffer, BUFFER_SIZE);
	if (i > 0)
	{
		new_elem->content = ft_strdup(buffer);
		if (new_elem->content == NULL)
			return (ft_strlen_and_free(NULL, &new_elem, 1));
		new_elem->next = NULL;
		if (*list == NULL)
			*list = new_elem;
		else
			lst_getlast(*list)->next = new_elem;
	}
	else
		free(new_elem);
	return (i);
}

int	get_len(t_line *list)
{
	int	len;
	int	i;

	len = 0;
	if (list == NULL)
		return (0);
	while (list->next)
	{
		len += ft_strlen_and_free(list->content, NULL, 0);
		list = list->next;
	}
	i = 0;
	while (list->content[i] && list->content[i] != '\n')
		i++;
	if (list->content[i])
		i++;
	len += i;
	return (len);
}

char	*get_lline(t_line *list)
{
	char	*line;
	int		i;
	int		j;

	if (list == NULL)
		return (NULL);
	line = malloc(sizeof(char) * (get_len(list) + 1));
	if (line == NULL)
		return (NULL);
	j = 0;
	while (list->next)
	{
		i = 0;
		while (list->content[i])
			line[j++] = list->content[i++];
		list = list->next;
	}
	i = 0;
	while (list->content[i] && list->content[i] != '\n')
		line[j++] = list->content[i++];
	if (list->content[i])
		line[j++] = '\n';
	line[j] = 0;
	return (line);
}

int	has_nl(t_line *list)
{
	t_line	*last;
	int		i;

	if (list == NULL)
		return (0);
	last = lst_getlast(list);
	i = 0;
	while (last->content[i])
	{
		if (last->content[i++] == '\n')
			return (1);
	}
	return (0);
}
