

# ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
# endif

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char	*ft_strdup(const char *string);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strcat(char *buff, char *prev);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif