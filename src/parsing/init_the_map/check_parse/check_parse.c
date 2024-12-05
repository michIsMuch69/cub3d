/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:36:49 by gsuter            #+#    #+#             */
/*   Updated: 2024/11/13 15:36:49 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3D.h"

bool	is_line_full_spaces(char *line)
{
	ssize_t	i;

	i = -1;
	while (i++, line[i])
	{
		if (line[i] == 32 || (line[i] > 8 && line[i] < 14))
			continue ;
		return (false);
	}
	return (true);
}

void	fill_rgb(char *line, t_map *map, e_rgb type)
{
	char	**temp;

	temp = ft_split(line, ',');
	if (!temp)
		return ;
	printf("%s", temp[0]);
	if (type == CEI)
	{
		map->ceiling->r = ft_atoi(temp[0]);
		map->ceiling->g = ft_atoi(temp[1]);
		map->ceiling->b = ft_atoi(temp[2]);
	}
	if (type == FLO)
	{
		map->floor->r = ft_atoi(temp[0]);
		map->floor->g = ft_atoi(temp[1]);
		map->floor->b = ft_atoi(temp[2]);
	}
	free(line);
	free_tab(temp);
}

void	fill_tex(char *line, t_texture *texture, e_txt type)
{
	if (type == NO)
	{
		texture->no = ft_dup(line);
		if (texture->no == NULL)
			return (printf("texture no is null\n"), free(line));
	}
	if (type == SO)
	{
		texture->so = ft_dup(line);
		if (texture->so == NULL)
			return (printf("texture no is null\n"), free(line));
	}
	if (type == WE)
	{
		texture->we = ft_dup(line);
		if (texture->we == NULL)
			return (printf("texture no is null\n"), free(line));
	}
	if (type == EA)
	{
		texture->ea = ft_dup(line);
		if (texture->ea == NULL)
			return (printf("texture no is null\n"), free(line));
	}
	free(line);
}

/*bool	fill_in_list(char *temp, t_texture *texture)
{
	size_t	i;
	size_t	y;

	i = parse_ws(temp);
	y = i + parse_ws(temp + i + 2) + 2;
	if (temp[i] == 'N' && temp[i + 1] == 'O')
		return (fill_tex(temp + y, texture, NO), false);
	if (temp[i] == 'S' && temp[i + 1] == 'O')
		return (fill_tex(temp + y, texture, SO), false);
	if (temp[i] == 'W' && temp[i + 1] == 'E')
		return (fill_tex(temp + y, texture, WE), false);
	if (temp[i] == 'E' && temp[i + 1] == 'A')
		return (fill_tex(temp + y, texture, EA), false);
	return (true);
}*/

bool	is_line_m_ok(char *line)
{
	size_t	i;

	i = parse_ws(line);
	while (line[i])
	{
		if (line[i] == 32 || (line[i] > 8 && line[i] < 14))
			line[i] = '0';
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S'\
			&& line[i] != 'W' && line[i] != 'E')
		{
			printf("Line is invalid: '%s'\n", line);
			free(line);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	is_line_ok(char	*line)
{
	size_t	i;

	if (ft_comp_str(line, "\n") || is_line_full_spaces(line))
		return (true);
	i = parse_ws(line);
	if (line[i] == 'N' && line[i + 1] == 'O')
		return (true);
	if (line[i] == 'S' && line[i + 1] == 'O')
		return (true);
	if (line[i] == 'W' && line[i + 1] == 'E')
		return (true);
	if (line[i] == 'E' && line[i + 1] == 'A')
		return (true);
	if (line[i] == 'F')
		return (true);
	if (line[i] == 'C')
		return (true);
	printf("Line is invalid: '%s'\n", line);
	free(line);
	return (false);
}