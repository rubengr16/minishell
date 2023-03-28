/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 13:02:59 by rgallego          #+#    #+#             */
/*   Updated: 2022/09/21 22:06:42 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define LLONG_MAX 9223372036854775807

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

/**************************** ERROR MANAGEMENT ****************************** */
# define ERR_SYS 0
# define ERR_USR 1

/**************************************************************************** */
/******************************* PART 1 ************************************* */
/**************************************************************************** */

/******************************* PART 1.1 *********************************** */
int		ft_atoi(const char *s);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/******************************* PART 1.2 *********************************** */
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);

/**************************************************************************** */
/******************************* PART 2 ************************************* */
/**************************************************************************** */
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s1, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/**************************************************************************** */
/******************************* BONUS ************************************** */
/**************************************************************************** */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/**************************************************************************** */
/******************************* EXTRA ************************************** */
/**************************************************************************** */
int		ft_atoi_base(const char *s, const char *base, int base_len);
int		ft_strisbase(char *str, char *base);
int		ft_atoi_check(int nb, char *str);
int		ft_strisnumber(char *str);
void	ft_free_split(char **set);
int		ft_max(int nb1, int nb2);
int		ft_min(int nb1, int nb2);
char	*ft_strtoupper(char *str);
char	*ft_strtolower(char *str);
void	ft_error(char *msg, int fd, int code);
int		ft_atoi_err(const char *s);
char	*ft_strjoinsep(char const *s1, char const *s2, char *c);

#endif
