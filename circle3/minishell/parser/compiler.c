/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:51:48 by jaju              #+#    #+#             */
/*   Updated: 2023/08/08 14:43:03 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compiler.h"
#include <libft/libft.h>
#include <parser/tokenizer.h>
#include <unistd.h>

#define FALSE 0
#define TRUE 1

void	process_init(t_process *process);
void	set_name(t_process *process, char const *name);
void	add_arg(t_process *process, char const *arg);
int		set_output(t_process *process, char *filename, int append);
int		set_input(t_process *process, char *filename);

//토큰 리스트로부터 프로세스의 정보를 채워넣음
static void	parse_process(t_process *process, t_list const *tokens, int *i)
{
	t_token			*token;
	int				success;

	success = 1;
	while (*i < tokens->length)
	{
		token = list_get(tokens, (*i)++);
		if (!(token->type != TK_PIPE))
			return ((*i)--, (void)0);
		if (!success)
			continue ;
		if (token->type == TK_STR && process->name == (void *)0)
			set_name(process, token->content);
		else if (token->type == TK_STR)
			add_arg(process, token->content);
		else if (token->type == TK_ORD)
			success = set_output(process,
					((t_token *)list_get(tokens, (*i)++))->content, FALSE);
		else if (token->type == TK_ARD)
			success = set_output(process,
					((t_token *)list_get(tokens, (*i)++))->content, TRUE);
		else if (token->type == TK_IRD)
			success = set_input(process,
					((t_token *)list_get(tokens, (*i)++))->content);
	}
}

//파이프라인 (|) 단위로 프로세스를 만들어 리스트에 넣고 리턴
t_list	compile(t_list const *tokens)
{
	int			i;
	t_process	*process;
	t_list		process_list;

	list_init(&process_list);
	i = 0;
	while (i < tokens->length)
	{
		process = allocate(sizeof(t_process));
		process_init(process);
		parse_process(process, tokens, &i);
		list_add(&process_list, process);
		i++;
	}
	return (process_list);
}
