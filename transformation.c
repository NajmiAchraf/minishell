/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 20:49:19 by anajmi            #+#    #+#             */
/*   Updated: 2022/08/15 20:49:21 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmdalloc(t_cmd *cmd, int type)
{
	cmd = (t_cmd*)malloc(sizeof(t_cmd));
	ft_bzero(cmd, sizeof(*t_cmd));
	cmd->type = type;
}

void	transformation(t_cmd *cmd, t_vars *var, t_cmd *predict??)
{

	/* ********************************************************************** */
	/*	the variable "predict" you must replace it by you parsing list		  */
	/*	create new variable in t_vars to count your advance					  */
	/*	??			=>	fill by the right thing from the list bellow :		  */
	/*	->cmd 		=>	lines : {42, 77, 97, 103}							  */
	/*	->cmd type	=>	lines : {42, 77, 97, 103}							  */
	/*	->cmd name	=>	lines : {58}										  */
	/*	->args		=>	lines : {61, 62}									  */
	/*	->file		=>	lines : {80}										  */
	/*	->efile		=>	lines : {81}										  */
	/*	->mode		=>	lines : {82}										  */
	/*	->fd		=>	lines : {83}										  */
	/* ********************************************************************** */

	// var->cmd[var->cod] = (t_cmd*)malloc(sizeof(t_cmd));
	// ft_bzero(var->cmd[var->cod], sizeof(*t_cmd));
	// var->cmd[var->cod]->type = ??;
	cmdalloc(var->cmd[var->cod], ??); // this function is replace the three up commands
	set_parser(var->cmd[var->cod], var, ??);
}

void	set_parser(t_cmd *cmd, t_vars *var, t_cmd *predict??)
{
	t_allways	aws;

	if (cmd->type == EXEC):
	{
		// cmd->type = EXEC; // disabled because of it's allready defined in [cmd type {29}]
		cmd->exe = (t_execcmd*)malloc(sizeof(t_execcmd));
		ft_bzero(cmd->exe, sizeof(*t_execcmd));

		cmd->exe->type = EXEC;

		ft_strlcpy(cmd->exe->name, "ls"??, ft_strlen("ls"??) + 1);

		aws.i = -1;
		while (++aws.i <= ft_lstlen(args??))
			cmd->exe->args[aws.i] = ft_strdup("-l"args[aws.i]??);
		cmd->exe->args[aws.i] = NULL;
	}

	else if (cmd->type == REDIR):
	{
		// cmd->type = REDIR; // disabled because of it's allready defined in [cmd type {29}]
		cmd->red = (t_redircmd*)malloc(sizeof(t_redircmd));
		ft_bzero(cmd->red, sizeof(*t_redircmd));

		cmd->red->type = REDIR;

		// cmd->red->cmd = (t_cmd*)malloc(sizeof(t_cmd));
		// ft_bzero(cmd->red->cmd, sizeof(*t_cmd));
		// cmd->red->cmd->type = ??;
		cmdalloc(cmd->red->cmd, ??); // this function is replace the three up commands
		set_parser(cmd->red->cmd, var, ??);

		ft_strlcpy(cmd->red->file, "ls"??, ft_strlen("ls"??) + 1);
		ft_strlcpy(cmd->red->efile, "ls"??, ft_strlen("ls"??) + 1);
		cmd->red->mode = ??;
		cmd->red->fd = ??;
	}

	else if (cmd->type == PIPE):
	{
		// cmd->type = PIPE; // disabled because of it's allready defined in [cmd type {29}]
		cmd->pip = (t_pipecmd*)malloc(sizeof(t_pipecmd));
		ft_bzero(cmd->pip, sizeof(*t_pipecmd));

		cmd->pip->type = PIPE;
		
		// cmd->pip->left = (t_cmd*)malloc(sizeof(t_cmd));
		// ft_bzero(cmd->pip->left, sizeof(*t_cmd));
		// cmd->pip->left->type = ??;
		cmdalloc(cmd->pip->left, ??); // this function is replace the three up commands
		set_parser(cmd->pip->left, var, ??);

		// cmd->pip->right = (t_cmd*)malloc(sizeof(t_cmd));
		// ft_bzero(cmd->pip->right, sizeof(*t_cmd));
		// cmd->pip->right->type = ??;
		cmdalloc(cmd->pip->right, ??); // this function is replace the three up commands
		set_parser(cmd->pip->right, var, ??);
	}
	else:
		panic("set_parser");
}