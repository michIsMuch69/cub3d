/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 05:22:20 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/22 15:44:35 by sanglier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


void clean_up(t_game *game)
{
    if (game->map)
    {
        free_tab(game->map->map);
        free(game->map);
    }
    if (game->map_img && game->mlx_data)
    {
        mlx_destroy_image(game->mlx_data->mlx_ptr, game->map_img->img_ptr);
        mlx_destroy_image(game->mlx_data->mlx_ptr, game->game_img->img_ptr);

    }
    if (game->mlx_data)
    {
        mlx_destroy_window(game->mlx_data->mlx_ptr, game->mlx_data->map_win_ptr);
        mlx_destroy_window(game->mlx_data->mlx_ptr, game->mlx_data->game_win_ptr);
        free(game->mlx_data);
    }
    if (game->player)
        free(game->player);
    if (game->map_img)
    {
        free(game->map_img);
        free(game->game_img);

    }
}

int main(int arc, char **argv)
{
	t_game		*game;

    if (arc < 2)
        return (printf("Please insert a map..."));
    init_struct(&game);
	get_map(game, argv[1]);
    /*int i = 0;
    while (game->map->map[i])
        printf("%s$", game->map->map[i++]);*/
    printf("%s\n", game->map->texture->no);
    printf("%s\n", game->map->texture->so);
    printf("%s\n", game->map->texture->ea);
    printf("%s\n", game->map->texture->we);
    /*printf("floor r = %d \n", game->map->floor->r);
    printf("floor g = %d \n", game->map->floor->g);
    printf("floor b = %d \n", game->map->floor->b);
    printf("ceiling r = %d \n", game->map->ceiling->r);
    printf("ceiling g = %d \n", game->map->ceiling->g);
    printf("ceiling b = %d \n", game->map->ceiling->b);*/

	exit_prog(game);
	printf("\nend\n");
	return (0);
}



