/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrdeysuvorov <anrdeysuvorov@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 03:48:42 by anrdeysuvor       #+#    #+#             */
/*   Updated: 2022/03/12 03:48:47 by anrdeysuvor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 1

int				ft_strlen_gnl(char *c);

char			*ft_strjoin_gnl(char *s1, char *s2, char c);

int				ft_strchr_gnl(const char *str, int sym);

char			*re_string(char *str, int flag);

char			*ft_strdup_gnl(char *str);

char			*get_next_line(int fd);

#endif
