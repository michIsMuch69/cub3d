/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 05:12:08 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/20 13:18:26 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void draw_player(t_img_data *img, int start_x, int start_y, int color)
{
    int x;
    int y;

    y = 0;
    while (y < PLAYER_SIZE)
    {
        x = 0;
        while (x < PLAYER_SIZE)
        {
            my_mlx_pixel_put(img, start_x + x, start_y + y, color);
            x++;
        }
        y++;
    }
}

int draw_tile(t_img_data *img, int start_x, int start_y, int color)
{
    int x;
    int y;

    y = 0;
    while(y < TILE_SIZE)
    {
        x = 0;
        while (x < TILE_SIZE)
        {
            if (x < BORDER_SIZE || x >= TILE_SIZE - BORDER_SIZE || y < BORDER_SIZE || y >= TILE_SIZE - BORDER_SIZE)
                my_mlx_pixel_put(img, start_x + x, start_y + y, BLACK);
            else 
                my_mlx_pixel_put(img, start_x + x, start_y + y, color);
            x++;
        }
        y++;
    }
    return (0);
}

void fill_tile_with_player(t_img_data *img, int tile_x, int tile_y, int floor_color, int player_color)
{
    int tile_start_x;
    int tile_start_y;
    int player_start_x;
    int player_start_y;
    
    tile_start_x = tile_x * TILE_SIZE;
    tile_start_y = tile_y * TILE_SIZE;

    draw_tile(img, tile_start_x, tile_start_y, floor_color);

    player_start_x = tile_start_x + (TILE_SIZE - PLAYER_SIZE) * 0.5;
    player_start_y = tile_start_y + (TILE_SIZE - PLAYER_SIZE) * 0.5;

    draw_player(img, player_start_x, player_start_y, player_color);
}

void draw_map_rays(t_game *game, t_player *player, t_raycaster *raycaster)
{
    raycaster->ray_index = 0;
    while (raycaster->ray_index < GAME_WIDTH)
    {
        raycaster->ray_angle = player->angle + (FOV_ANGLE * 2) - (raycaster->ray_index * (FOV_ANGLE / (GAME_WIDTH - 1)));
        // printf("player angle : %f\n", raycaster->ray_angle);
        raycaster->ray_x = player->player_px_pos_x;
        raycaster->ray_y = player->player_px_pos_y;
        while (game->map->map[(int)(raycaster->ray_y / TILE_SIZE)][(int)(raycaster->ray_x / TILE_SIZE)] != '1')
        {
            if (raycaster->ray_index == (GAME_WIDTH * 0.5))
                my_mlx_pixel_put(game->map_img, (int)raycaster->ray_x, (int)raycaster->ray_y, GREEN);
            else
                my_mlx_pixel_put(game->map_img, (int)raycaster->ray_x, (int)raycaster->ray_y, PINK);
            raycaster->ray_x += sin(raycaster->ray_angle) ;
            raycaster->ray_y -= cos(raycaster->ray_angle) ;
        }
        raycaster->ray_index++;
    }
}

void draw_mini_map(t_game *game)
{
    int x;
    int y;

    y = 0;
    while (game->map->map[y])
	{
		x = 0; 
        while (game->map->map[y][x])
		{
            if (game->map->map[y][x] == '1')
                draw_tile(game->map_img, x * TILE_SIZE, y * TILE_SIZE, BLUE);
			if (game->map->map[y][x] == '0'|| game->map->map[y][x] == 'N' )
                draw_tile(game->map_img, x * TILE_SIZE, y * TILE_SIZE, BLACK);
            x++;
        }
        y++;
    }
}

void all_draws(t_game *game)
{
    draw_mini_map(game);
    fill_tile_with_player(game->map_img, game->player->player_pos_x, game->player->player_pos_y, BLACK, GREEN);
    draw_map_rays(game, game->player, game->raycaster);
    render_3d_map(game, game->player, game->raycaster, game->projection);
}

void draw_and_display_map(t_game *game) 
{
    all_draws(game);
    mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->game_win_ptr, game->map_img->img_ptr, GAME_WIDTH / 4, GAME_HEIGHT);
    mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->game_win_ptr, game->game_img->img_ptr, 0, 0);
   // mlx_hook(game->mlx_data->map_win_ptr, 2, 1L<<0, handle_keypress, game); 
    mlx_hook(game->mlx_data->game_win_ptr, 2, 1L<<0, handle_keypress, game); 
}