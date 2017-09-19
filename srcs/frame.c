/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 05:21:15 by mhalit            #+#    #+#             */
/*   Updated: 2017/08/17 21:21:50 by rlecart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void    pixel_to_image(int x, int y, t_rt *e, int color)
{
    int max_x;
    int max_y;
    int start_y;

    x = x * RES;
    y = y * RES;
    start_y = y;
    max_x = x + RES;
    max_y = y + RES;
    while (x <= max_x)
    {
        while (y <= max_y)
        {
            if ((x >= 0 && y >= 0 ) || (x < RES_W && y < RES_H ))
            {
                // if (RES > 10 && (x + 1 == max_x || y + 1 == max_y))
                //     ft_anti_aliasing(x, y, e, 0x333333);
                // else
                    mlx_pixel(x, y, e, color);
            }
            y++;
        }
        y = start_y;
        x++;
    }
    if (color)
    {}
}

void	mlx_pixel(int x, int y, t_rt *e, int color)
{
	int		pos;

	if (x < LARGEUR && y < HAUTEUR)
	{
		pos = x * 4 + y * e->mlx.size_l;
		e->mlx.data[pos] = color;
		e->mlx.data[pos + 1] = color >> 8;
		e->mlx.data[pos + 2] = color >> 16;
	}
}

void	filters(t_rt *e)
{
	if (e->scene.filters == 1)
		fl_sepia_apply(e);
	if (e->scene.filters == 2)
		fl_black_and_white(e);
	if (e->scene.filters == 3)
		fl_revers(e);
}

void	frame(t_rt *e)
{
	t_rt		**th_e;
	int			i;
	int			i2;
	int			x;
	int			y;

	th_e = launch_thread(e);
	i = 0;
	i2 = 0;

	while (i < NB_THREADS)
	{
		y = th_e[i]->thread.y / ALIASING;
		// printf("%f\n", th_e[i]->thread.y/ ALIASING);
		// printf("%f \n\n", th_e[i]->thread.max_y/ ALIASING);
		while (y < th_e[i]->thread.max_y / ALIASING)
		{
			x = 0;
			while (x < th_e[i]->thread.w / ALIASING)
			{
				pixel_to_image(x, y, e, ret_colors(th_e[i]->thread.colors[i2]));
				++x;
				++i2;
			}
			++y;
		}
		i2 = 0;
		++i;
	}
	filters(e);
	// free(th_e);
	mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
}

// void	        *drawline(void *arg)
// {
// 	t_thread		*th;
// 	th = (t_thread *)arg;
// 	int x;
// 	int y;

// 	y = th.thread.y;

// 	printf("min = %d\n", th.thread.y);
// 	printf("max = %d\n\n", th.thread.max_y);
// 	while (y < e->thread.max_y)
// 	{
// 		x = 0;
// 		while (x < LARGEUR)
// 		{
// 			// printf("y = %d\n", y);
// 			// printf("x = %d\n\n", x);
// 			mlx_pixel(x, y, e, ret_colors(raytrace(x, y, e)));
// 			++x;
// 		}
// 		++y;
// 	}
// 	return (NULL);
// }

// void	frame(t_rt *e)
// {
//     int			i;
// 	pthread_t	th[NB_THREADS];
//     t_thread	th_e[NB_THREADS];

//     // if (!(th_e = (t_rt **)malloc(NB_THREADS * sizeof(t_rt *))))
//     //     exit(-42);
	
// 	i = 0;
// 	while (i < 1)
// 	{
// 		th_e[i] = copy_rt(e);
// 		th_e[i].y = (HAUTEUR / NB_THREADS) * i;
// 		th_e[i].max_y = th_e[i].y + (HAUTEUR / NB_THREADS);
// 		printf("min = %d\n", th_e[i].y);
// 		printf("max = %d\n\n", th_e[i].max_y);
// 		// drawline((void *)th_e[i]);

// 		pthread_create(&th[i], NULL, drawline, (void *)th_e[i]);
// 		++i;
// 		// printf("\n");
// 	}
	
// 	i = 0;
// 	while (i < 1)
// 	{
// 		pthread_join(th[i], NULL);
// 		++i;
// 	}
// 	mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
// 	return (th_e);
// }


// void	frame(t_rt *e)
// {
// 	int x;
// 	int y;

// 	y = 0;
// 	while (y < HSS)
// 	{
// 		x = 0;
// 		while (x < WSS)
// 		{
// 			mlx_pixel(x, y, e, ret_colors(raytrace(x, y, e)));
// 			x += 1;
// 		}
// 		y += 1;
// 	}
// 	mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
// }


// void	frame(t_rt *e)
// {
// 	// IMG = mlx_new_image(INIT, LARGEUR, HAUTEUR);
// 	// e->mlx.data = mlx_get_data_addr(IMG, &e->mlx.bpp, &e->mlx.size_l,
// 	// 	&e->mlx.endian);
// 	if (SS == 1)
// 		anti_aliasing_off(e);
// 	else
// 		anti_aliasing_on(e, NULL);
// 	filters(e);
// 	mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
// }




// void *calcul_pixels(void *arg)
// {

// 	t_rt		*e;

// 	e = (t_rt *)arg;

// 	int			x;
// 	int			max_x;
// 	int			y;

// 	x = e->thread.start_x;
// 	max_x = e->thread.start_x + (LARGEUR / NB_THREADS);
// 	printf("x     = %d\n", x);
// 	printf("max_x = %d\n", max_x);
// 	x = 0;
// 	y = 0;
// 	while (x < 100)
// 	{
// 		while (y < 100)
// 		{
// 			printf("print(%d,%d)\n", x, y);
// 		   	mlx_pixel(x, y, e, 0x0ff0000);
// 			// pixel_to_image(x, y, e,
// 			// ret_colors(th_e[i]->thread.colors[x + ((y / NB_THREADS) * RES_W)]));
// 			y++;
// 		}
// 		printf("\n");
// 		y = 0;
// 		x++;
// 	}
	
// 	// filters(e);
// 	// // free(th_e);
// 	// mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
// 	return (NULL);
// }

// void	frame(t_rt *e)
// {
// 	// t_rt		**th_e;
// 	// th_e = launch_thread(e);
// 	calcul_pixels(e);
// }

// t_rt            **launch_thread(t_rt *e)
// {
//     int			i;
// 	pthread_t	th[NB_THREADS];
//     t_rt		**th_e;

//     if (!(th_e = (t_rt **)malloc(NB_THREADS * sizeof(t_rt *))))
//         return (NULL);
	
// 	i = 0;
// 	while (i < 1)
// 	{
// 		printf("\n\nstart\n\n");
// 		th_e[i] = copy_rt(e);
// 		th_e[i]->thread.start_x = (LARGEUR / NB_THREADS) * i;
// 		pthread_create(&th[i], NULL, calcul_pixels, (void *)th_e[i]);
// 		++i;
// 	}
	
// 	i = 0;
// 	while (i < 1)
// 	{
// 		pthread_join(th[i], NULL);
// 		++i;
// 	}
    
// 	return (th_e);
// }




// void	frame(t_rt *e)
// {

// 	t_rt		**th_e;
// 	int			i;
// 	int			x;
// 	int			y;

// 	th_e = launch_thread(e);
// 	i = 0;

// 	while (i < 6)
// 	{
// 		y = i;
// 		while (y < HAUTEUR / RES)
// 		{
// 			x = 0;
// 			while (x < LARGEUR / RES)
// 			{
// 				pixel_to_image(x, y, e,
// 				ret_colors(th_e[i]->thread.colors[x + ((y / NB_THREADS) * RES_W)]));
// 				++x;
// 			}
// 			y += NB_THREADS;
// 		}

// 		++i;
// 	}
// 	// a_aliasing(e);
// 	filters(e);
// 	// free(th_e);
// 	mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
// }


