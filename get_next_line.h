/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:19:40 by akilk             #+#    #+#             */
/*   Updated: 2022/01/06 14:44:02 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# define BUFF_SIZE 80
# define MAX_FD 4096

int	get_next_line(const int fd, char **line);

#endif
