/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglier <sanglier@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:18:12 by sanglier          #+#    #+#             */
/*   Updated: 2024/11/13 13:52:22 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/*################ STRUCTURES #####################*/


typedef struct	s_img_data t_img_data;
typedef struct	s_mlx_data t_mlx_data;
typedef	struct	s_map t_map;
typedef struct	s_player t_player;
typedef struct	s_raycaster t_raycaster;
typedef struct	s_proj t_proj;
typedef struct	s_game t_game;
typedef struct	s_list t_list;

struct	s_img_data
{
    void	*img_ptr;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
};

struct	s_mlx_data
{
    void	*mlx_ptr;
    void	*map_win_ptr;
    void	*game_win_ptr;
};

struct s_player
{
    int	player_pos_x;
    int	player_pos_y;
    int	player_px_pos_x;
    int	player_px_pos_y;
    double	angle;
    double distance;
    char *direction;
};

struct s_raycaster
{
	double ray_angle;
	double ray_x;
	double ray_y;
	int ray_index;
};

struct s_proj
{
	long distance_to_wall;
	int wall_height;
	int wall_start;
	int wall_end;
};

/*####PARSE####*/
struct	s_map
{
	int						count;
	char					**map;
	int					map_height;
	int					map_length;
};

struct	s_list
{
	char			*value;
	struct s_list	*next;
	struct s_list	*prev;
};

struct s_game
{
	t_map			*map;
	t_list			*list;
	t_mlx_data		*mlx_data;
	t_player		*player;
	t_img_data		*map_img;
	t_img_data		*game_img;
	t_raycaster		*raycaster;
	t_proj			*projection;
};

# endif