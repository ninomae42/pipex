#include "pipex.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*p_ret;
	size_t	alloc_size;

	if (s1 == NULL && s2 == NULL)
		return (ft_strdup(""));
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	alloc_size = sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1);
	p_ret = (char *)malloc(alloc_size);
	ft_stpcpy(ft_stpcpy(p_ret, s1), s2);
	return (p_ret);
}
