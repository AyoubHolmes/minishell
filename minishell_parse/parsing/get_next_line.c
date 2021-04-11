#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


int ft_strlen(const char *s)
{
    int i;

    i = 0;
    if (s)
    {
        while(s[i])
            i++;
    }
    return (i);
}

char *ft_ministrdup(const char *s)
{
    int len = 0;
    int i = 0;
    char *tmp;

    while(s[len])
        len++;
    if(!(tmp = (char *)malloc(len + 1)))
        return (NULL);
    while(i < len)
    {
        tmp[i] = s[i];
        i++;
    }
    tmp[i] = '\0';
    return (tmp);
}

char *ft_minisubstr(char const *s, unsigned int start, int len)
{
    char *tmp;
    int i = 0;

    if (s == NULL)
        return (NULL);
    if (!(tmp = malloc(len + 1)))
        return (NULL);
    while (i < len)
    {
        *(tmp + i) = *(s + start);
        s++;
        i++;
    }
    *(tmp + i) = '\0';
    return (tmp);
}

char *ft_ministrjoin(char const *s1, char const *s2)
{
    char *tmp;
    int i = 0;
    int j = 0;

    if (s1 == NULL)
        return ft_ministrdup(s2);
    if (s2 == NULL)
        return ft_ministrdup(s1);
    if (!(tmp = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
        return (NULL);
    while (s1[i])
    {
        tmp[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        tmp[i + j] = s2[j];
        j++;
    }
    tmp[i + j] = '\0';
    return (tmp);
}

char *ft_ministrchr(char *s, int c)
{
    int i = 0;
    char ch = c;

    while (s[i] && s[i] != ch)
        i++;
    if (s[i] == ch)
        return ((char *)&s[i]);
    else 
        return (NULL);
}

int read_line(char **str, char **line)
{
    int i = 0;
    char *tmp;

    if (*str)
    {
        while((*str)[i] && (*str)[i] != '\n')
            i++;
        if ((*str)[i] == '\n')
        {
            *line = ft_minisubstr(*str, 0, i);
            tmp = *str;
            *str = ft_ministrdup(*str + i + 1);
            free(tmp);
        }
        else if((*str)[i] == '\0')
        {
            *line = ft_ministrdup(*str);
            free(*str);
            *str = NULL;
            return (0);
        }
    }
    return (1);
}

int get_next_line(char **line)
{
    int r;
    char *tmp;
    static char *str;
    char buff[1025];

    while((r = read(0, buff, 1024)) > 0)
    {
        buff[r] = '\0';
        tmp = str;
        str = ft_ministrjoin(str, buff);
        free(tmp);
        if (ft_ministrchr(str, '\n'))
            break;
    }
    if(r < 0)
        return (-1);
    if (!r && (str == NULL || str[0] == '\0'))
    {
        *line = ft_ministrdup("");
        return (0);
    }
    return (read_line(&str, line));
}
