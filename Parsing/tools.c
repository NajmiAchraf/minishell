/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:52:39 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/13 02:57:04 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void ft_output(t_final *s)
{
	t_final *final;
	t_file *file;
	char **cmd;
	int id = 1;
	int		i;
	final = s;
    while (final)
	{
		i = 0;
		printf("output cmd number %d\n",id);
		cmd = final->cmd;
		while (cmd[i])
		{
			printf("name cmd is = %s and id is %d\n", cmd[i], id);
			i++;
		}
		file = final->file;
		while (file != NULL)
		{
			printf("name file is = %s and id is = %d\n", file->str, file->id);
			file = file->next;
		}
		final= final->next;
		printf("end node number %d\n", id);
		id++;
	}
}



// void	free_cmdfinal(t_cmdfinal *cmd)
// {
// 	t_files		*tmp;
// 	t_cmdfinal	*pointer;
// 	t_cmdfinal	*fr;

// 	if (cmd->env)
// 		free(cmd->env);
// 	while (cmd != NULL)
// 	{
// 		pointer = cmd;
// 		fr = cmd;
// 		free_lines(cmd->tab);
// 		while (cmd->file)
// 		{
// 			tmp = cmd->file->next;
// 			free(cmd->file->name);
// 			free(cmd->file);
// 			cmd->file = tmp;
// 		}
// 		cmd = pointer->next;
// 		free(fr);
// 	}
// }


void	free_parser(t_final *cmd)
{
	t_file	*tmp;
	t_final	*pointer;
	t_final	*fr;
    t_cmd *name;

	while (cmd != NULL)
	{
		pointer = cmd;
		fr = cmd;
        while (cmd->name)
		{
			name = cmd->name->next;
			free(cmd->name->str);
			free(cmd->name);
			cmd->name = name;
		}
		while (cmd->file)
		{
			tmp = cmd->file->next;
			free(cmd->file->str);
			free(cmd->file);
			cmd->file = tmp;
		}
		cmd = pointer->next;
		free(fr);
	}
}


// void free_tokens(t_token *data)
// {
// 	t_token *tmp;
// 	t_token *node;

// 	while (data->next != NULL)
// 	{
// 		printf("|%s|\n", data->str);
// 		tmp = data->next;
// 		printf("%s\n", tmp->str); // **** sefault hna
// 		free(data->str);
// 		free(data);
// 		data = tmp;
// 	}
// 	printf("end free \n");
// }

void free_tokens(t_token *data)
{
	t_token *tmp;
	t_token *node;
	t_token *new;

	new = data;

	while (new != NULL)
	{
		// printf("FREED ?\n");
		//printf("|%s|\n", data->str);
		tmp = new->next;
		// printf("%s\n", new->str);
		// printf("%p\n", new->str);
		//printf("%s\n",new->next->str);
		//printf("%p\n",new->next->str);
		free(new->str);
		free(new);
		new = tmp;
	}
	
	// printf("end free \n");
}



// void    creat_node(t_node *head, char *data)
// {
//     t_node    *new;
//     t_node    last_node;

//     new = (t_node)malloc(sizeof(t_node));
//     if (!new)
//         return ;
//     new->data = my_strdup(data);
//     new->next = NULL;
//     if (*head == NULL)
//         head = new;
//     else
//     {
//         last_node =head;
//         while (last_node->next != NULL)
//         {
//             last_node = last_node->next;
//         }
//                 last_node->next = new;
//     }
// }