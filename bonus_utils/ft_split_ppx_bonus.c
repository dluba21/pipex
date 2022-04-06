/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ppx_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:38:02 by dluba             #+#    #+#             */
/*   Updated: 2022/04/03 20:39:09 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	split_init(char *str, char c, t_split *s)
{
	s->i = 0;
	s->j = 0;
	s->str = str;
	s->c = c;
	s->len = ft_strlen(str);
	s->word_counter = 0;
	word_counter_ppx(str, c, s);
	s->i = 0;
	s->j = 0;
	s->k = 0;
}

static void	make_small_str(t_split *s, int start, int end)
{
	char	*small_str;
	int		i;

	i = 0;
	small_str = (char *)malloc(end - start + 1);
	if (!small_str)
	{
		while (i < s->k)
			free(s->big_str[i++]);
		free(s->big_str);
		write(2, "split_error\n", 12);
		exit(0);
	}
	while (start < end)
		small_str[i++] = s->str[start++];
	small_str[i] = 0;
	s->big_str[s->k++] = small_str;
}

static void	quote_condition(t_split *s, int case_flag)
{
	char	temp;

	s->j = s->i;
	temp = s->str[s->i++];
	while (s->str[s->i] != temp && s->i < s->len)
		s->i++;
	if (s->i < s->len && (s->str[s->i + 1] == s->c || !s->str[s->i + 1]))
	{
		if (case_flag == 0)
			s->word_counter++;
		else
			make_small_str(s, s->j + 1, s->i);
		s->i++;
	}
	else
		s->i = s->j;
}

void	word_counter_ppx(char *str, char c, t_split *s)
{
	while (s->i < s->len)
	{
		s->j = s->i;
		while (str[s->i] == c && s->i < s->len)
			s->i++;
		if ((str[s->i] == 34 || str[s->i] == 39) && (s->i > s->j || s->i == 0))
			quote_condition(s, 0);
		s->j = s->i;
		while (str[s->i] != c && s->i < s->len)
			s->i++;
		if (s->i > s->j)
			s->word_counter++;
	}
}

char	**ft_split_ppx(char *str, char c)
{
	t_split	s;

	s.i = 0;
	split_init(str, c, &s);
	if (!str || s.len == 0)
		return (NULL);
	s.big_str = (char **)malloc(sizeof(char *) * s.word_counter + 1);
	if (!s.big_str)
		return (NULL);
	while (s.i < s.len)
	{
		s.j = s.i;
		while (str[s.i] == c && s.i < s.len)
			s.i++;
		if ((str[s.i] == 34 || str[s.i] == 39) && (s.i > s.j || s.i == 0))
			quote_condition(&s, 1);
		s.j = s.i;
		while (str[s.i] != c && s.i < s.len)
			s.i++;
		if (s.i > s.j)
			make_small_str(&s, s.j, s.i);
	}
	s.big_str[s.k] = NULL;
	return (s.big_str);
}
