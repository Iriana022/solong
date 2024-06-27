/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:13:06 by irazafim          #+#    #+#             */
/*   Updated: 2024/06/27 11:09:36 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int handle_key(int keycode, void *param)
{
	(void)param;
	if(keycode == 65307)
		exit(0);
	return 0;
}

int main()
{
	void 	*mlx;
	void *mlx_win;
	t_data	img;
	int file;
	char buf[1000];
	int i = 0;
	
	mlx = mlx_init();
	if (!mlx)
		return 1;
	mlx_win = mlx_new_window(mlx, 720, 400, "test")	;
	if(!mlx_win)
		return 1;
	mlx_key_hook(mlx_win, handle_key, NULL);
	
	file = open("carte.ber", O_RDONLY);
	int byte_read = 10;
	while (read(file, buf, 10) != 0)
	{
		if(*buf == '\n')
			i++;
	}
	printf("%d >> lignes\n", i);
		
	if(byte_read < 0)
	{
		perror("error reading file");
		close(file);
		return 1;
	}
	
	i = 0;
	while(buf[i])
	{
		printf("%c", buf[i]);
		i++;
	}

	img.img = mlx_new_image(mlx, 720, 400);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	for(int i = 0; i < 61; i++)
	{
		my_mlx_pixel_put(&img, i, 0, 0x00FF0000);
		if(i == 60)
			for(int j = 0; j < 61; j++)
			{
				my_mlx_pixel_put(&img, i, j, 0x00FF0000);
				if (j == 60)
					for(int k = i; k >= 0; k--)
					{
						my_mlx_pixel_put(&img, k, j, 0x00FF0000);
						if(k == 0)
							for(int l = j; l >= 0; l--)
								my_mlx_pixel_put(&img, k, l, 0x00FF0000);
					}
			}
		
	
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 20, 20);
	mlx_loop(mlx);
}
