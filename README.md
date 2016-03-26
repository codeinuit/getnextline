# GetNextLine

##{Epitech.}
###Tek 1 project for CPE

-> get_next_line.h needs to be included

A function to get the next line of a file descriptor for each call.

#Basic exemple
```
#include get_next_line.h

int     main(void)
{
  char  *s;

  while ((s = get_next_line(0) != NULL)
    {
      printf("%s\n", s);
      free(s);
    }
  return (0);
}
