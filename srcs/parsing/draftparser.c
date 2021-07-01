static int	char_nb_with_var(char *str, t_shell *shell)
{
	int			i;
	int			variables_len;
	
	i = 0;
	variables_len = 0; //can be negative if var name is longer than its value
	while (str[i])
	{
		if (str[i] == '"')
		{
			while (str[i] != '"' && str[i])
			{
				if (str[i] == '$')
					variables_len += give_values_len(str, i, shell);				
				i++;
			}
		}
		else if (str[i] == '\'')
			while (str[i] != '\'')
				i++;
		else if (str[i] == '$')
		{
			variables_len += give_values_len(str, i, shell);
			while (str[i] != ' ' && str[i])
			i++;
		}
		i++;
	}
	return (ft_strlen(str) + variables_len);
}

//!! strlen de null fait segfault
static char	*process_variables(char *str, t_shell *shell)
{
	int			i;
	int			j;
	char		*str_with_var;
	
	i = 0;
	j = 0;
	str_with_var = (char *)calloc_sh(shell, char_nb_with_var(str, shell));
	//write_new_str(str_with_var);
	while (str[i])
	{
		if (str[i] == '"')
		{
			while (str[i] != '"' && str[i])
			{
				if (str[i] == '$')
					//insert_var();
				i++;
			}
		}
		else if (str[i] == '\'')
			while (str[i] != '\'' && str[i])
				i++;
		if (str[i] == '$')
			//insert_var() str_with_var[i + j] = str[i]; // j = longueur des var values
		i++;
	}
	free_set_null(&str);
	return (str_with_var);
}