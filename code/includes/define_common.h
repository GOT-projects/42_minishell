/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_common.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:14:55 by aartiges &        #+#    #+#             */
/*   Updated: 2022/02/21 20:27:42 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_COMMON_H

# define DEFINE_COMMON_H

# if defined(__linux__) || defined(linux) || defined(__linux)
#  define MY_SIZE_T_MAX	SIZE_MAX
#  define PATH_MAX		4096
# else
#  define MY_SIZE_T_MAX SIZE_T_MAX
# endif
# define TRUE 1
# define FALSE 0
# define ERR_404_EXEC	127
# define ERR_403_EXEC	126

# define ENV_PWD		"PWD"
# define ENV_PWD_OLD	"OLDPWD"

# define SPACES			" \t\n\r\v\f"

# define CHECK_OK			0

# define EMPTY				0b1
# define CHECK_TEXT			0b10
# define CHECK_PIPE			0b100
# define CHECK_RED_APPEND	0b1000
# define CHECK_RED_CREATE	0b10000
# define CHECK_RED_HR_DOC	0b100000
# define CHECK_RED_INPUT	0b1000000
# define CHECK_QUOTE		0b10000000

# define DOUBLE_QUOTE	34
# define SIMPLE_QUOTE   39

# define READ 0
# define WRITE 1

// Bonus

# define CHECK_AND			0b100000000
# define CHECK_OR			0b1000000000
# define CHECK_SUB_OPEN		0b10000000000
# define CHECK_SUB_CLOSE	0b100000000000

# define CHECK_REDIRECTION	0b1111000
# define CHECK_SEPARATOR	0b011101111101
# define CHECK_SEPARATOR2	0b100011111010

#endif
