/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:37:57 by jmilhas           #+#    #+#             */
/*   Updated: 2022/03/02 23:09:34 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

/*for use tracking malloc
 	- for protecte malloc use ft_error_mal(void *mem, track); 
	- for *  use ft_track: ex: str = ft_track(malloc(sizeof(type) * nb), track);
	- for **  use ft_track_tab: exemple = str = ft_track_tab(tab, track);
	- for free all alloc use: ft_track_free_all(track);
	- for free * use : ft_track_free(track, *mem);
	- for free ** use : ft_track_free_tab(track, **mem);
*/
typedef struct s_track
{
	void	**mem;
	int		len;
}			t_track;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;

char		**ft_split(char const *s, char c);
char		**ft_strsplit(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strchr(const char *str, int c);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strdup(const char *s1);
char		*ft_strndup(const char *s, size_t size);
char		*ft_strdupcat(char *dest, const char *src);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strncat(char *dest, const char *src, size_t n);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strrchr(const char *str, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_join(const char *str, ...);
int			*ft_dec_to_bin(int nbr, int size);
int			ft_atoi(const char *str);
int			ft_atoi_base(char *str, char *base);
int			ft_binary_len(int nbr);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_isa_white_space(int c);
int			ft_lstsize(t_list *lst);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_putchar(int c);
int			ft_putnbr(int n);
int			ft_putnbr_base(int nbr, char *base, int res);
int			ft_putnbr_unbase(unsigned int nbr, char *base, int res);
int			ft_putnbr_unsigned(unsigned int n);
int			ft_putstr(char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strichr(const char *str, int c);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_strcmp(const char *s1, const char *s2);
long int	ft_atol(const char *str);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
int			**ft_create_tab_int(int nb_all, int size_all);
size_t		ft_strlen(const char *str);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
void		**ft_add_mal(void **mem);
void		**ft_track_free(t_track **track, void *mem);
void		**ft_track_free_all(t_track **track);
void		**ft_track_free_tab(t_track **track, void **mem);
void		**ft_track_tab(void **src, t_track **track);
void		*ft_calloc(size_t count, size_t size);
void		*ft_error_mal(void *mem, t_track **track);
void		**ft_error_malt(void **mem, t_track **track);
void		*ft_memalloc(size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_track(void *src, t_track **track);
void		ft_bzero(void *s, size_t n);
void		ft_lstadd_back(t_list **alst, t_list *ne);
void		ft_lstadd_front(t_list **alst, t_list *ne);
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char const *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char const *s, int fd);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
#endif
