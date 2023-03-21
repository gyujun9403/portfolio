/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 21:17:55 by gyeon             #+#    #+#             */
/*   Updated: 2022/04/07 19:16:01 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "ray.h"
# include "object.h"
# include "three_value.h"

typedef struct s_ambient
{
	double	ratio;
	t_rgb	color;
}	t_ambient;

typedef struct s_diffuse
{
	double	kd;
}	t_diffuse;

typedef struct s_light
{
	t_point			point;
	t_rgb			rgb;
	t_ambient		ambient;
	t_diffuse		diffuse;
	struct s_light	*next;
}	t_light;

void	cal_diffuse(t_hit hit, t_light *light);
void	cal_pixel_color(t_hit hit,
			t_hit hit_shadow, t_light *light, t_rgb *color);
int		get_argb(t_hit hit, t_light *light, t_object *obj);

#endif