/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:56:09 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/07 18:54:39 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NBR_H
# define NBR_H

int		ft_atoi_base(char *str, char *base);
int		ft_atoi(const char *nptr);
int		ft_atoi_strict(const char *nptr, int *dest);
char	*ft_itoa(int n);
int		ft_max(int a, int b);
int		ft_min(int a, int b);
int		ft_nb_digits(int n);
long	ft_abs(int x);

#endif