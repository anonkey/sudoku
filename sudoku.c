#include <unistd.h>
#include <string.h>

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

size_t	ft_strlen(const char *str)
{
	size_t		len;

	len = 0;
	while (*(str + len))
		++len;
	return (len);
}

void	ft_putstr(char const *s)
{
	if (!s)
		write(1, "(NULL)", 6);
	else
		write(1, s, ft_strlen(s));
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

void	ft_putgrid(char **grid)
{
    int	    i;
    int	    j;

    i = 0;
    while (i < 9)
    {
	j = 0;
	while (j < 9)
	{
	    write(1, grid[i] + j, 1);
	    ++j;
	}
	ft_putstr("\n");
	++i;
    }
}

int	ft_solve(char **grid, int pos, int solved)
{
    char    c;

    c = '1';
    if (pos == 81)
    {
	ft_putgrid(grid);
	return (1);
    }
    if (grid[pos / 9][pos % 9] != '.')
	return (ft_solve(grid, pos + 1, solved));
    while (c <= '9')
    {
	if (!ft_checknb(grid, pos, c))
	{
	    grid[pos / 9][pos % 9] = c;
	    if (ft_solve(grid, pos + 1, solved))
	    {
		if (solved)
		    return (0);
		else
		    solved = 1;
	    }
	    grid[pos / 9][pos % 9] = '.';
	}
	++c;
    }
    return (solved);
}

int	main(int argc, char **argv)
{
    if (argc != 10 || ft_checklines(argv + 1)
	|| ft_solve(argv + 1, 0, 0))
    {
	ft_putstr("Erreur\n");
	return (0);
    }
    return (0);
}