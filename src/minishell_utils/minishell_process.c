#include "minishell.h"
#include "parser.h"
#include "exec.h"
#include <readline/history.h>

pid_t	g_sig_pid = 0;

int	is_end_of_file(char *input_line)
{
	if (input_line)
		return (0);
	write(STDOUT_FILENO, "exit\n", 5);
	return (1);
}

int	process_line(t_minishell *ms)
{
	t_token		*tok;
	t_command	*cmd;

	if (!*ms->input_line)
		return (set_err(&ms->last_exit_code, NOT_FOUND_ERR));
	add_history(ms->input_line);
	ms->tokens = parser(ms);
	if (!ms->tokens)
		return (set_err(&ms->last_exit_code, 1));
	if (DEBUG_MODE)
		tokens_display(ms->tokens);
	tok = (t_token *) ms->tokens->content;
	cmd = get_command(tok->data);
	ms->ast_root = ast_build(ms->tokens);
	if (DEBUG_MODE)
		ast_display(ms->ast_root);
	exec(cmd, ms);
	ast_clear(&ms->ast_root);
	ft_lstclear2(&ms->tokens, token_destroy);
	return (0);
}

void	handle_prompt_signal(t_uint8 *exit_code)
{
	if (g_sig_pid != -1)
		return ;
	g_sig_pid = 0;
	*exit_code = 130;
}
