/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_to_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglier <sanglier@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:52:22 by sanglier          #+#    #+#             */
/*   Updated: 2024/11/21 14:52:22 by sanglier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3D.h"

char	**heap_map(size_t len)
{
	char	**map;
	map = ft_calloc(sizeof(char *), len + 1);
	if (!map)
		return (NULL);
	return (map);
}

void	fill_list_to_map(t_game *game, t_list **list)
{
	t_list	*temp;
	char	*dest;
	size_t	i;

	game->map->map = heap_map(get_list_len(*list));
	game->map->map_height = (int)get_list_len(*list);
	temp = *list;
	if (!temp)
		return (printf("Error malloc\n"), exit_prog(game));
	i = 0;
	game->map->map_width = 0;
	while (temp)
	{
		dest = rm_bs_wp(temp->value);
		game->map->map[i++] = ft_dup(dest);
		if (game->map->map_width < (int) ft_strlen(dest))
			game->map->map_width = (int)ft_strlen(dest);
		temp = temp->next;
		free(dest);
	}
}