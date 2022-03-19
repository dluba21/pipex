/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:29:08 by dluba             #+#    #+#             */
/*   Updated: 2021/10/17 14:29:11 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>

int		ft_toupper(int c);

int		ft_tolower(int c);

int		ft_atoi(const char *str);

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strtrim(char const *s1, char const *set);

char	*ft_strrchr(const char *str, int sym);

char	*ft_strnstr(const char *big, const char *little, size_t len);

int		ft_strncmp(const char *str1, const char *str2, size_t n);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

size_t	ft_strlen(const char *str);

size_t	ft_strlcpy(char *dest, const char *src, size_t n);

size_t	ft_strlcat(char *buf, const char *src, size_t n);

char	*ft_strjoin(char const *s1, char const *s2);

void	ft_striteri(char *s, void (*f)(unsigned int, char*));

char	*ft_strdup(const char *str);

char	*ft_strchr(const char *str, int sym);

char	**ft_split(char const *s, char c);

void	ft_putstr_fd(char *s, int fd);

void	ft_putnbr_fd(int n, int fd);

void	ft_putnbr_fd(int n, int fd);

void	ft_putendl_fd(char *s, int fd);

void	ft_putchar_fd(char c, int fd);

void	*ft_memset(void *dest, int c, size_t n);

void	*ft_memmove(void *dest0, const void *src0, size_t n);

void	*ft_memcpy(void *dest_0, const void *src_0, size_t n);

int		ft_memcmp(const void *str1_0, const void *str2_0, size_t n);

void	*ft_memchr(const void *str_0, int c, size_t n);

char	*ft_itoa(int n);

int		ft_isprint(int c);

int		ft_isdigit(int c);

int		ft_isascii(int c);

int		ft_isalpha(int c);

int		ft_isalnum(int c);

void	*ft_calloc(size_t elem, size_t size);

void	ft_bzero(void *s, size_t n);

#endif
