# ft\_printf
## Recode printf in order to learn about variadic arguments
The following project consists of the creation of ft\_printf function.
It is a function which reproduces the original printf found in the
<stdio.h> library.

### Mandatory Part


* ```int	ft_atoi(const char *s)```: function which receives a string with
a number writen in ASCII and returns the integer representation of it -[ft_atoi](https://github.com/rubengr16/42/blob/main/42cursus/libft/src/ft_atoi.c)-.

* **%c** - char : prints a single character -which I managed in 
[ft\_printf\_chr.c](https://github.com/rubengr16/42/blob/main/42cursus/ft_printf/ft_printf_chr.c)-.

* **%s** - string : prints a string of characters
-[ft\_printf\_str.c](https://github.com/rubengr16/42/blob/main/42cursus/ft_printf/ft_printf_str.c)-.

* **%p** - pointer : prints a _void \*_ in hexadecimal followed by "0x"
-[ft\_printf\_ptr.c](https://github.com/rubengr16/42/blob/main/42cursus/ft_printf/ft_printf_ptr.c)-.

* **%d** and **%i** - decimal : prints a decimal or integer number in base 10
-[ft\_printf\_int.c](https://github.com/rubengr16/42/blob/main/42cursus/ft_printf/ft_printf_int.c)-.

* **%u** - unsigned : prints an unsigned decimal number in base 10.
-[ft\_printf\_uns.c](https://github.com/rubengr16/42/blob/main/42cursus/ft_printf/ft_printf_uns.c)-.

* **%x** and **%X** - hexadecimal : prints a number in hexadecimal in base 16,
with the first conversion it will we displayed in lowercase and with the other
in uppercase -[ft\_printf\_hex.c](https://github.com/rubengr16/42/blob/main/42cursus/ft_printf/ft_printf_hex.c) and
[ft\_printf\_hexup.c](https://github.com/rubengr16/42/blob/main/42cursus/ft_printf/ft_printf_hexup.c)-

* **%%** - percent : prints a percent sign.

* **%<else>** - other incorrect conversions : prints just the char in the else.
It is undefined behaviour according to the original *printf*.

In order to know which function was needed for each conversion I used different *else if*'s located
in the main file of my project which is
[ft\_printf.c](https://github.com/rubengr16/42/blob/main/42cursus/ft_printf/ft_printf.c).

Finally, we need to keep in mind that I used a recursive
-[ft\_putnbr\_base](https://github.com/rubengr16/42/blob/main/42cursus/ft_printf/ft_putnbr_base.c)-
for the conversions which implies a number conversion such as **p**, **d** and
**i**, **u**, **x** and **X**.

### Bonus Part

### Bibliography
* [Variadic Functions](https://www.thegeekstuff.com/2017/c-variadic-functions/)

* [man 3 stdarg](https://man7.org/linux/man-pages/man0/stdarg.h.0p.html)
