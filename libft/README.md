
# 📝 Description

**Libft** is a custom library created as part of the **42 cursus**. The goal of this project is to recode a set of standard C library functions, providing a deeper understanding of how these functions work under the hood. Additionally, the library includes some custom utility functions that extend its functionality.


## 📂 Features

- **char**: Functions for character manipulation.

- **gnl**: Functions for the Get Next Line (GNL) utility.

- **lst**: Functions for linked list manipulation.

- **mem**: Functions for memory manipulation.

- **nbr**: Functions for number manipulation.

- **printf**: Functions for formatted output (ft_printf).

- **str**: Functions for string manipulation.

- **strbuilder**: Functions for building strings.

- **write**: Functions for writing output.


## 🚀 Installation
To compile the library, navigate to the root directory of the project and run the following command:

```bash
make
```
This will generate a static library file named `libft.a`.


## 🎯 Usage/Examples

To use the library in your project, include the `libft.h` header file and link the library during compilation. For example:

```c
#include "libft.h"

int	main()
{
	char	*str = ft_strdup("Hello World !");
	if (str)
	{
		ft_printf("%s\n", str);
		free(str);
	}
	return (0);
}
```
Compile your program with the following command:
```bash
gcc main.c libft.a
```
