/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_shot.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 16:08:23 by htagrour          #+#    #+#             */
/*   Updated: 2020/02/26 17:04:32 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCREEN_SHOT_H
# define SCREEN_SHOT_H
# include <stdint.h>

# pragma pack(push, 1)

typedef	struct	s_filehdr
{
	uint16_t	bf_type;
	uint32_t	bf_size;
	uint16_t	bf_reserved1;
	uint16_t	bf_reserved2;
	uint32_t	bf_off_bits;
}				t_filehdr;

typedef	struct	s_infohdr
{
	uint32_t	bi_size;
	int32_t		bi_width;
	int32_t		bi_height;
	uint16_t	bi_planes;
	uint16_t	bi_bit_count;
	uint32_t	bi_compression;
	uint32_t	bi_size_image;
	int32_t		bix_pels_per_meter;
	int32_t		biy_els_per_meter;
	uint32_t	bi_clr_used;
	uint32_t	bi_clr_important;
}				t_infohdr;
# pragma pack(pop)
#endif
