/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:21:09 by akilk             #+#    #+#             */
/*   Updated: 2021/12/27 10:47:13 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * p_n is a pointer to '\n'. It is first set to NULL. If there is a reminder,
 * we check for the '\n' in remainder. If 'new line' exists, we set theand
 * we set the '\0' instead of it. And copy contents of remainder to the line.
 * We then copy next line, that is after p_n to remainder. The space for
 * remainder is allocated earlier in get_next_line function, so we use strcpy.
 * if no 'new line' found in remainder we duplicate the whole contents to line
 * and remove remainder.
 * If no remainder exists, that is, when we start reading the file, we just
 * allocate space for line with ft_strnew.
 * Function returns NULL if no there is no remainder or pointer to next line
 * if there is a remainder.
 */

static char	*check_remainder(char *remainder, char **line)
{
	char	*p_n;

	p_n = NULL;
	if (remainder)
	{
		p_n = ft_strchr(remainder, '\n');
		if (p_n)
		{
			*p_n = '\0';
			*line = ft_strdup(remainder);
			ft_strcpy(remainder, ++p_n);
		}
		else
		{
			*line = ft_strdup(remainder);
			ft_strclr(remainder);
		}
	}
	else
		*line = ft_strnew(1);
	return (p_n);
}

/*
 * We assign contents of line to tmp pointer and free it afterwards to avoid
 * memory leak, when joining a line with a part of buffer.
 */

static void	join_line(char *buf, char **line)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(*line, buf);
	free(tmp);
}

/*
 * p_n is a pointer to '\n'. It is set to NULL in the check_reminder,
 * unless there is something left in reminder from last call. Remainder is
 * the part of text that left in the buffer after '\n'.
 * As stated before, check_remainder returns NULL if there is no remainder.
 * We then cycle trough return unless there is a remainder with a 'new line'
 * symbol. After each part of buffer read, we join it with the line.
 * We stop the cycle in two ways:
 * 1) If symbol 'new line' is found in check_next_line, we assign
 *  '\0' to p_n and put what's left to remainder.
 * 2) If no data in file is left, we break.
 * Function returns 1 in case there are bytes left unread or line
 * length is not 0;
 */

static void	check_line_end(char *p_n, char **remainder)
{
	if (p_n)
	{
		*p_n = '\0';
		*remainder = ft_strdup(++p_n);
	}
}

int	get_next_line(const int fd, char **line)
{
	int			ret;
	char		buf[BUFF_SIZE + 1];
	char		*p_n;
	static char	*remainder;

	if (fd < 0 || !line)
		return (-1);
	p_n = check_remainder(remainder, line);
	while (!p_n)
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (!ret)
			break ;
		buf[ret] = '\0';
		p_n = ft_strchr(buf, '\n');
		check_line_end(p_n, &remainder);
		join_line(buf, line);
	}
	if (ret || ft_strlen(*line) || ft_strlen(remainder))
		return (1);
	else
		return (0);
}
