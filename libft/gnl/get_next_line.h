/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 09:59:38 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/23 10:39:02 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 2048

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char			*substr_gnl(char *s, unsigned int start, size_t len);
char			*strjoin_free1(char *s1, char *s2);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
void			*ft_calloc(size_t count, size_t size);
int				get_next_line(int fd, char **line);
void			*ft_calloc(size_t count, size_t size);
void			gnl_free_set_null(char **ptr);

#endif
