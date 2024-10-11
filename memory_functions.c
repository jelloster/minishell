#include "minishell.h"

int	free_cmds(t_cmd *cmds, int cmd_n)
{
	int	i;

	i = 0;
	if (cmds)
	{
		while (i < cmd_n)
		{
			if (cmds[i].pathed_cmd && cmds[i].args[0] != cmds[i].pathed_cmd)
				ft_memdel(&cmds[i].pathed_cmd);
			if (cmds[i].args)
				free_array_of_arrays(cmds[i].args);
			if (cmds[i].file)
				ft_memdel(&cmds[i].file);
			if (cmds[i].infile)
				ft_memdel(&cmds[i].infile);
			if (cmds[i].outfile)
				ft_memdel(&cmds[i].outfile);
			i++;
		}
		free(cmds);
		cmds = NULL;
	}
	return(0);
}
