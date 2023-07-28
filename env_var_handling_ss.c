#include "shell.h"

/**
 * get_env_func - returns an array of variables from the env
 * @info: environment variables.
 *		  make function prototype.
 * Return: array off strings
 */

char **get_env_func(info_y *info)
{
	/* If the environment variables have not been set or have been changed, update them. */
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_vector(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * _setenvfunc - Adds or updates an environment variable.
 * @info: Structure containing the environment variables.
 *		  
 * @var: The name of the environment variable.
 * @value: The value of the environment variable.
 * Return: 0 variable was successfully added 
 */

int _setenvfunc(info_y *info, char *var, char *value)
{
	char *buf = NULL;
	list_s *node;
	char *p;

	
	if (!var || !value)
		return (1);

	
	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);

	
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);

	
	node = info->env;
	while (node)
	{
		
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}

		
		node = node->next;
	}

	
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

/**
 * _unsetenvfunc - Removes an environment variable.
 * @info: Structure containing the environment variables.
 *		  
 * @var: The name of the environment variable to remove.
 * Return: env variable wwhen successfully 
 */
int _unsetenvfunc(info_y *info, char *var)
{
	list_s *node = info->env;
	size_t index = 0;
	char *p;


	if (!node || !var)
		return (0);

	
	while (node)
	{
		
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			
			info->env_changed = delete_node_at_index(&(info->env), index);

		
			index = 0;
			node = info->env;
			continue;
		}

		
		node = node->next;
		index++;
	}

	return (info->env_changed);
}

