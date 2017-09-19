/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtrx4_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparigi <mparigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 23:27:08 by mparigi           #+#    #+#             */
/*   Updated: 2017/09/03 21:46:55 by mparigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

/*
**	The matrix will be :
**	[a0  a1  a2  a3 ]
**	[a4  a5  a6  a7 ]
**	[a8  a9  a10 a11]
**	[a12 a12 a14 a15]
**
**	A vector to mtr4 will be :
**	[vec.x]
**	[vec.y]
**	[vec.z]
**	[  1  ]
**
**	{0, 0, 0, 0,
**	 0, 0, 0, 0,
**	 0, 0, 0, 0,
**	 0, 0, 0, 1};
*/

t_mtrx4		new_matrx4(void)
{
	t_mtrx4		matrix;

	matrix.mtrx[0] = 0;
	matrix.mtrx[1] = 0;
	matrix.mtrx[2] = 0;
	matrix.mtrx[3] = 0;
	matrix.mtrx[4] = 0;
	matrix.mtrx[5] = 0;
	matrix.mtrx[6] = 0;
	matrix.mtrx[7] = 0;
	matrix.mtrx[8] = 0;
	matrix.mtrx[9] = 0;
	matrix.mtrx[10] = 0;
	matrix.mtrx[11] = 0;
	matrix.mtrx[12] = 0;
	matrix.mtrx[13] = 0;
	matrix.mtrx[14] = 0;
	matrix.mtrx[15] = 1;
	return (matrix);
}

/*
**	{1, 0, 0, 0,
**	 0, 1, 0, 0,
**	 0, 0, 1, 0,
**	 0, 0, 0, 1};
*/

t_mtrx4		id_matrx4(void)
{
	t_mtrx4		matrix;

	matrix = new_matrx4();
	matrix.mtrx[0] = 1;
	matrix.mtrx[5] = 1;
	matrix.mtrx[10] = 1;
	return (matrix);
}

t_mtrx4		prod_matrx4(t_mtrx4 a, t_mtrx4 b)
{
	t_mtrx4		matrix;

	matrix.mtrx[0]  = a.mtrx[0]  * b.mtrx[0] + a.mtrx[1]  * b.mtrx[4] + a.mtrx[2]  * b.mtrx[8]  + a.mtrx[3]  * b.mtrx[12];
	matrix.mtrx[1]  = a.mtrx[0]  * b.mtrx[1] + a.mtrx[1]  * b.mtrx[5] + a.mtrx[2]  * b.mtrx[9]  + a.mtrx[3]  * b.mtrx[13];
	matrix.mtrx[2]  = a.mtrx[0]  * b.mtrx[2] + a.mtrx[1]  * b.mtrx[6] + a.mtrx[2]  * b.mtrx[10] + a.mtrx[3]  * b.mtrx[14];
	matrix.mtrx[3]  = a.mtrx[0]  * b.mtrx[3] + a.mtrx[1]  * b.mtrx[7] + a.mtrx[2]  * b.mtrx[11] + a.mtrx[3]  * b.mtrx[15];
	matrix.mtrx[4]  = a.mtrx[4]  * b.mtrx[0] + a.mtrx[5]  * b.mtrx[4] + a.mtrx[6]  * b.mtrx[8]  + a.mtrx[7]  * b.mtrx[12];
	matrix.mtrx[5]  = a.mtrx[4]  * b.mtrx[1] + a.mtrx[5]  * b.mtrx[5] + a.mtrx[6]  * b.mtrx[9]  + a.mtrx[7]  * b.mtrx[13];
	matrix.mtrx[6]  = a.mtrx[4]  * b.mtrx[2] + a.mtrx[5]  * b.mtrx[6] + a.mtrx[6]  * b.mtrx[10] + a.mtrx[7]  * b.mtrx[14];
	matrix.mtrx[7]  = a.mtrx[4]  * b.mtrx[3] + a.mtrx[5]  * b.mtrx[7] + a.mtrx[6]  * b.mtrx[11] + a.mtrx[7]  * b.mtrx[15];
	matrix.mtrx[8]  = a.mtrx[8]  * b.mtrx[0] + a.mtrx[9]  * b.mtrx[4] + a.mtrx[10] * b.mtrx[8]  + a.mtrx[11] * b.mtrx[12];
	matrix.mtrx[9]  = a.mtrx[8]  * b.mtrx[1] + a.mtrx[9]  * b.mtrx[5] + a.mtrx[10] * b.mtrx[9]  + a.mtrx[11] * b.mtrx[13];
	matrix.mtrx[10] = a.mtrx[8]  * b.mtrx[2] + a.mtrx[9]  * b.mtrx[6] + a.mtrx[10] * b.mtrx[10] + a.mtrx[11] * b.mtrx[14];
	matrix.mtrx[11] = a.mtrx[8]  * b.mtrx[3] + a.mtrx[9]  * b.mtrx[7] + a.mtrx[10] * b.mtrx[11] + a.mtrx[11] * b.mtrx[15];
	matrix.mtrx[12] = a.mtrx[12] * b.mtrx[0] + a.mtrx[13] * b.mtrx[4] + a.mtrx[14] * b.mtrx[8]  + a.mtrx[15] * b.mtrx[12];
	matrix.mtrx[13] = a.mtrx[12] * b.mtrx[1] + a.mtrx[13] * b.mtrx[5] + a.mtrx[14] * b.mtrx[9]  + a.mtrx[15] * b.mtrx[13];
	matrix.mtrx[14] = a.mtrx[12] * b.mtrx[2] + a.mtrx[13] * b.mtrx[6] + a.mtrx[14] * b.mtrx[10] + a.mtrx[15] * b.mtrx[14];
	matrix.mtrx[15] = a.mtrx[12] * b.mtrx[3] + a.mtrx[13] * b.mtrx[7] + a.mtrx[14] * b.mtrx[11] + a.mtrx[15] * b.mtrx[15];
	return (matrix);
}

t_vec3		prod_vec3_matrx4(t_vec3 vec, t_mtrx4 a)
{
	t_vec3		ret;

	ret.x = vec.x * a.mtrx[0] + vec.y * a.mtrx[1] + vec.z * a.mtrx[2] + a.mtrx[3];
	ret.y = vec.x * a.mtrx[4] + vec.y * a.mtrx[5] + vec.z * a.mtrx[6] + a.mtrx[7];
	ret.z = vec.x * a.mtrx[8] + vec.y * a.mtrx[9] + vec.z * a.mtrx[10] + a.mtrx[11];
	return (ret);
}
