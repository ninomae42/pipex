#include "pipex.h"

// save a copy of a string.
char	*ft_strdup(const char *s)
{
	char	*p_ret;

	p_ret = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (p_ret == NULL)
		return (NULL);
	ft_stpcpy(p_ret, s);
	return (p_ret);
}
