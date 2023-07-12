/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:22:26 by soohlee           #+#    #+#             */
/*   Updated: 2023/03/30 20:57:37 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	heredoc_chk(t_data *data)
{
	if (ft_strncmp("here_doc", data->argv[1], 9))
		data->hdflag = 0;
	else
		data->hdflag = 1;
	return (0);
}

int	heredoc(t_data *data)
{
	char	*buff;
	char	herefd;
	char	*endflag;

	buff = 0;
	herefd = open(".here_doc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	endflag = ft_strjoin(data->argv[2], "\n");
	while (1)
	{
		write(1, "> ", 2);
		buff = get_next_line(0);
		if (ft_strncmp(buff, endflag, ft_strlen(endflag)) == 0)
		{
			free(buff);
			free(endflag);
			close(herefd);
			return (0);
		}
		write(herefd, buff, ft_strlen(buff));
		if (buff)
			free(buff);
		buff = 0;
	}
	return (0);
}
