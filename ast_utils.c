/*
	An example of an AST:
 
	         (>>)
	        /  \
	      (|)  (file)
	     /   \
	   (|)   (sed)
	  /   \
       (grep)(awk)
*/

#include "minishell.h"

void	init_ast()

void	exe_ast_node(t_ast *node)
{
	// Node should always be an operator first
	// & have no content
	if (node->operator == PIPE)
		content = pipe(left->content, right->content);
	else if (node->operator == REPLACE)
		content = replace(left->content, right->content);
	else if (node->opreator == NONE)
		return;
}

void	exe_ast(t_ast *node)
{
	while (node)
	{
		exe_ast_node(node);
		node = node->next;
	}
}
