/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:30:49 by sanglier          #+#    #+#             */
/*   Updated: 2024/12/20 15:47:50 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3D.h"

static bool	wall_follow(const char *line, size_t i)
{
	while (line[i++])
	{
		if (!line[i + 1])
			return (true);
		if (line[i] != '1')
			break ;
	}
	return (false);
}

void	wall_is_good(t_game *game, char *line, bool flag, char *prev)
{
	size_t	i;
	size_t	len;
	char	*temp;

	i = parse_ws(line);
	len = ft_strlen(line);
	if (flag)
	{
		temp = copy_map_line(prev, game->map->width);
		if (!temp)
			force_exit(line, game);
		while (len--, line[len])
		{
			if (line[len] != '1' || line[0] != '1' || \
				(line[len] == '1' && temp[len] == '0' && temp[len + 1] != '1'))
				break ;
			return (free(temp));
		}
		free(temp);
	}
	if (!flag && wall_follow(line, i))
		return ;
	force_exit(line, game);
}

bool	rgb_is_good(char *line)
{
	char	**temp;
	int		i;

	i = -1;
	temp = ft_split(line, ',');
	if (!temp)
		return (false);
	while (++i, temp[i])
	{
		if (ft_atoi(temp[i]) > 255 || ft_atoi(temp[i]) < 0)
			return (free_tab(temp), printf("Error rgb\n"), false);
	}
	free_tab(temp);
	return (true);
}

bool	check_rgb(char *line)
{
	size_t	i;

	i = parse_ws(line);
	if (!parse_comma(line + parse_ws(line)))
		return (false);
	if (ft_strlen(line + i) > 11)
		return (false);
	if (!rgb_is_good(line + i))
		return (false);
	return (true);
}

bool	check_texture(char	*line)
{
	int	fd;

	if (!line)
		return (false);
	if (!ft_comp_str(".xpm", line + ft_strlen(line) - 4))
	{
		printf("Error, it's texture is not an xpm...\n");
		return (false);
	}
	fd = open(line, O_RDONLY);
	if (fd == -1)
	{
		printf("Error, no textures...\n");
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}
