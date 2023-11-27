/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:35:20 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/11/13 18:35:21 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>

typedef enum s_flag
{
	WORD = 0,
	DQ = 1,
	SQ = 2,
	PIPE = 3,
	RIN = 4,
	ROUT = 5,
	OPAR = 6,
	CPAR = 7,
	SPAC = 8,
	AND = 9,
	OR = 10,
	HEREDOC = 11,
	APPEND = 12,
	SUBSHELL,
	REDIR,
	SIGHER,
	END,
}					t_flag;

typedef struct s_token
{
	t_flag			type;
	bool			hdoc;
	bool			expand;
	char			*token;
	struct s_token	*next;
	struct s_token	*down;
	struct s_token	*prev;
}					t_token;

typedef struct s_norm
{
	int				i;
	t_token			*token;
	t_token			*down;
	bool			dq;
	bool			sq;
	bool			space;
	int				x;
	int				op;
	int				cp;
}					t_norm;

t_token				*ft_newtoken(t_flag type, char *word, int flag, int hdoc);
t_token				*lasttok(t_token *lst);
void				addtok(t_token **lst, t_token *new);
t_token				*tokenizer(char *c);
t_token				*lasttok_down(t_token *lst);
int					size_token(t_token *lst);
char				*getword(char *str, int *index);
char				*getq(char *str, int *index, char c);
int					getflag(char c, int flag);
int					allspace(int i, char *c);

#endif