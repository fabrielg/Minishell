#include "minishell.h"
#include "parser.h"
#include "exec.h"
#include <readline/history.h>

pid_t g_sig_pid = 0;

int	is_EOF(char *input_line)
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

	add_history(ms->input_line);
	ms->tokens = parser(ms);
	if (!ms->tokens)
		return (1);
	tokens_display(ms->tokens); //DEBUG
	tok = (t_token *) ms->tokens->content;
	cmd = get_command(tok->data);
	exec(cmd, ms);
	ft_lstclear2(&ms->tokens, token_destroy);
}

void	handle_prompt_signal(t_uint8 *exit_code)
{
	if (g_sig_pid != -1)
		return ;
	g_sig_pid = 0;
	*exit_code = 130;
}
