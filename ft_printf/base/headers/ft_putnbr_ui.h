/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ui.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgroot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:17:36 by mgroot            #+#    #+#             */
/*   Updated: 2020/11/15 09:00:52 by mgroot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUTNBR_UI_H
# define FT_PUTNBR_UI_H

# include "ft_printdata.h"

int		write_aligned_ui(t_printdata *data, unsigned long long nbr);

int		count_digits_ui(unsigned long long nbr);
int		ft_putnbr_ui(unsigned long long nbr, int precision);

#endif
