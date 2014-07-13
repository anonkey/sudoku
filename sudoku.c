#include <unistd.h>
#include <stdio.h>
#include <string.h>

char	*ft_strncpy(char *s1, const char *s2, size_t n)
{
	if (!s1 || !s2)
		return (NULL);
	while (n > 0)
	{
		--n;
		*(s1 + n) = *(s2 + n);
	}
	return (s1);
}

void	ft_bzero(void *s, size_t n)
{
	if (!s)
		return ;
	while (n > 0)
	{
		--n;
		*((char *)s + n) = '\0';
	}
}

void	ft_strtabcpy(char (*newtab)[9][9], char **strtab)
{
	int		i;

	i = 0;
	while (i < 9)
	{
	    ft_strncpy((*newtab)[i], strtab[i], 9);
	    ++i;
	}
}

int	ft_checklines(char **lines)
{
    char    is_used[9];
    int	    i;
    int	    j;

    i = 0;
    while (i < 9)
    {
	ft_bzero(is_used, sizeof(char) * 9);
	j = 0;
	while (j < 9)
	{
	    if (lines[i][j] <= '9' && lines[i][j] > '0')
	    {
		if (!is_used[(int)(lines[i][j] - '1')])
		    is_used[(int)(lines[i][j] - '1')] = '1';
		else
		    return (-1);
	    }
	    else if (lines[i][j] != '.')
		return (-2);
	    ++j;
	}
	++i;
    }
    return (0);
}


int	ft_checknb(char **grid, int pos, char digit)
{
    int	    i;
    int	    xstart;
    int	    ystart;


    xstart = ((pos % 9) / 3) * 3;
    ystart = ((pos / 9) / 3) * 3;
    i = 0;
    while (i < 9)
    {
	if (grid[i][pos % 9] == digit
	    || grid[pos / 9][i] == digit
	    || grid[ystart + i / 3][xstart + i % 3] == digit)
		return (1);
	++i;
    }
    return (0);
}

void	ft_putgrid(char grid[9][9])
{
    int	    i;

    i = 0;
    while (i < 9)
    {
	write(1, grid[i], 9);
	write(1, "\n", 1);
	++i;
    }
}

int	ft_solve(char **grid, int pos, int *solved, char (*res_p)[9][9])
{
    char    c;

    c = '0';
    if (pos == 81)
    {
	++(*solved);
	ft_strtabcpy(res_p, grid);
	return (1);
    }
    if (grid[pos / 9][pos % 9] != '.')
	return (ft_solve(grid, pos + 1, solved, res_p));
    while (++c <= '9')
    {
	if (!ft_checknb(grid, pos, c))
	{
	    grid[pos / 9][pos % 9] = c;
	    if (ft_solve(grid, pos + 1, solved, res_p))
	    {
		if (*solved > 1)
		    return (*solved);
	    }
	    grid[pos / 9][pos % 9] = '.';
	}
    }
    return (*solved);
}

int	main(int argc, char **argv)
{
    char    result[9][9];
    int	    i;

    i = 0;
    if (argc != 10 || ft_checklines(argv + 1)
	|| 1 != ft_solve(argv + 1, 0, &i, &result))
	write(1, "Erreur\n", 7);
    else
	ft_putgrid(result);
    return (0);
}