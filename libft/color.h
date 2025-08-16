/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 21:13:23 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/02/25 11:15:47 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# define RESET "\e[0m"

# define BLACK "\e[0;30m"
# define RED "\e[0;31m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[0;33m"
# define BLUE "\e[0;34m"
# define PURPLE "\e[0;35m"
# define CYAN "\e[0;36m"
# define WHITE "\e[0;37m"
# define GREY "\e[0;39m"

# define BLACK_B "\e[1;30m"
# define RED_B "\e[1;31m"
# define GREEN_B "\e[1;32m"
# define YELLOW_B "\e[1;33m"
# define BLUE_B "\e[1;34m"
# define PURPLE_B "\e[1;35m"
# define CYAN_B "\e[1;36m"
# define WHITE_B "\e[1;37m"
# define GREY_B "\e[1;39m"

# define BLACK_U "\e[4;30m"
# define RED_U "\e[4;31m"
# define GREEN_U "\e[4;32m"
# define YELLOW_U "\e[4;33m"
# define BLUE_U "\e[4;34m"
# define PURPLE_U "\e[4;35m"
# define CYAN_U "\e[4;36m"
# define WHITE_U "\e[4;37m"
# define GREY_U "\e[4;39m"

# define BLACK_BG "\e[40m"
# define RED_BG "\e[41m"
# define GREEN_BG "\e[42m"
# define YELLOW_BG "\e[43m"
# define BLUE_BG "\e[44m"
# define PURPLE_BG "\e[45m"
# define CYAN_BG "\e[46m"
# define WHITE_BG "\e[47m"

# define BLACK_HI "\e[90m"
# define RED_HI "\e[91m"
# define GREEN_HI "\e[92m"
# define YELLOW_HI "\e[93m"
# define BLUE_HI "\e[94m"
# define PURPLE_HI "\e[95m"
# define CYAN_HI "\e[96m"
# define WHITE_HI "\e[97m"

# define BLACK_B_HI "\e[1;90m"
# define RED_B_HI "\e[1;91m"
# define GREEN_B_HI "\e[1;92m"
# define YELLOW_B_HI "\e[1;93m"
# define BLUE_B_HI "\e[1;94m"
# define PURPLE_B_HI "\e[1;95m"
# define CYAN_B_HI "\e[1;96m"
# define WHITE_B_HI "\e[1;97m"

# define BLACK_BG_HI "\e[0;100m"
# define RED_BG_HI "\e[0;101m"
# define GREEN_BG_HI "\e[0;102m"
# define YELLOW_BG_HI "\e[0;103m"
# define BLUE_BG_HI "\e[0;104m"
# define PURPLE_BG_HI "\e[0;105m"
# define CYAN_BG_HI "\e[0;106m"
# define WHITE_BG_HI "\e[0;107m"

void	write_color(char *str, char *color);

#endif