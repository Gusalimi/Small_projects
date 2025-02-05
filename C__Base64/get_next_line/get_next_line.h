/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:17:09 by gsaile            #+#    #+#             */
/*   Updated: 2022/11/26 11:30:02 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_line
{
	char			*content;
	struct s_line	*next;
}					t_line;

int					read_to_list(int fd, t_line **list);
t_line				*lst_getlast(t_line *list);
char				*get_next_line(int fd);
char				*ft_strdup(const char *s1);
char				*get_lline(t_line *list);
size_t				ft_strlen(const char *s);
int					has_nl(t_line *list);
int					ft_strlen_and_free(const char *s, t_line **elem,
						int behavior);
char				*clear_list(t_line **list, int behavior);
void				clear_list2(t_line **current, t_line **list);

#endif
