/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtrx4_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 20:43:08 by mparigi           #+#    #+#             */
/*   Updated: 2017/09/03 20:44:36 by mparigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

/*
**	{1, 0, 0, x,
**	 0, 1, 0, y,
**	 0, 0, 1, z,
**	 0, 0, 0, 1};
*/

t_mtrx4		transl_matrx4(float x, float y, float z)
{
	t_mtrx4		matrix;

	matrix = new_matrx4();
	matrix.mtrx[0] = 1;
	matrix.mtrx[3] = x;
	matrix.mtrx[5] = 1;
	matrix.mtrx[7] = y;
	matrix.mtrx[10] = 1;
	matrix.mtrx[11] = z;
	return (matrix);
}

/*
**	{1, 0,          0,           0,
**	 0, cos(theta), -sin(theta), 0,
**	 0, sin(theta), cos(theta),  0,
**	 0, 0,          0,           1};
*/

t_mtrx4		rotx_matrx4(float theta)
{
	t_mtrx4		matrix;

	matrix = new_matrx4();
	matrix.mtrx[0] = 1;
	matrix.mtrx[5] = cos(theta * PI);
	matrix.mtrx[6] = -sin(theta * PI);
	matrix.mtrx[9] = sin(theta * PI);
	matrix.mtrx[10] = cos(theta * PI);
	round_matrx4(&matrix);
	return (matrix);
}

/*
**	{cos(theta),  0, sin(theta), 0,
**	 0,           1,          0, 0,
**	 -sin(theta), 0, cos(theta), 0,
**	 0,           0,          0, 1};
*/

t_mtrx4		roty_matrx4(float theta)
{
	t_mtrx4		matrix;

	matrix = new_matrx4();
	matrix.mtrx[0] = cos(theta * PI);
	matrix.mtrx[2] = sin(theta * PI);
	matrix.mtrx[5] = 1;
	matrix.mtrx[8] = -sin(theta * PI);
	matrix.mtrx[10] = cos(theta * PI);
	round_matrx4(&matrix);
	return (matrix);
}

/*
**	{cos(theta), -sin(theta),  0, 0,
**	 sin(theta), cos(theta),   0, 0,
**	 0,           0,           1, 0,
**	 0,           0,           0, 1};
*/

t_mtrx4		rotz_matrx4(float theta)
{
	t_mtrx4		matrix;

	matrix = new_matrx4();
	matrix.mtrx[0] = cos(theta * PI);
	matrix.mtrx[1] = -sin(theta * PI);
	matrix.mtrx[4] = sin(theta * PI);
	matrix.mtrx[5] = cos(theta * PI);
	matrix.mtrx[10] = 1;
	round_matrx4(&matrix);
	return (matrix);
}
