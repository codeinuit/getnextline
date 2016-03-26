/*
** get_next_line.c for  in /home/debout_l/rendu/CPE_2015_getnextline
** 
** Made by Lucas DEBOUTE
** Login   <debout_l@epitech.net>
** 
** Started on  Thu Jan 14 20:56:51 2016 Lucas DEBOUTE
** Last update Thu Jan 14 21:50:37 2016 Lucas DEBOUTE
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*my_realloc(t_gnl *gnl, int i)
{
  char	*tmp;

  gnl->size += READ_SIZE;
  gnl->str[i] = '\0';
  tmp = malloc(sizeof(char) * gnl->size + 1);
  if (tmp == NULL)
    return (NULL);
  i = 0;
  while (gnl->str[i] != '\0')
    {
      tmp[i] = gnl->str[i];
      i += 1;
    }
  tmp[i] = '\0';
  free(gnl->str);
  return (tmp);
}

int	has_reached_eof(int *eof, int *cursor, char *buffer, t_gnl *gnl)
{
  *cursor = 0;
  *eof = read(gnl->fd, buffer, READ_SIZE);
  if (*eof < 0 || (*eof == 0 && gnl->i == 0))
    {
      free(gnl->str);
      return (0);
    }
  else if (*eof == 0)
    {
      gnl->str[gnl->i] = '\0';
      return (1);
    }
  if ((gnl->str = my_realloc(gnl, gnl->i)) == NULL)
    return (0);
  return (3);
}

char	*init(t_gnl *gnl, int *eof, int *cursor, char *buffer)
{
  gnl->i = 0;
  gnl->size = READ_SIZE;
  if (*eof <= *cursor && READ_SIZE > 0)
    {
      *cursor = 0;
      if ((*eof = read(gnl->fd, buffer, READ_SIZE)) <= 0)
	return (NULL);
    }
  if ((gnl->str = malloc(READ_SIZE + 1)) == NULL)
    return (NULL);
  return ("\0");
}

char		*get_next_line(const int fd)
{
  static char	buffer[READ_SIZE];
  static int	eof;
  static int	cursor;
  t_gnl		gnl;

  gnl.fd = fd;
  if (init(&gnl, &eof, &cursor, buffer) == NULL)
    return (NULL);
  while (buffer[cursor] != '\n')
    if (cursor == eof)
      {
	if ((gnl.bool = has_reached_eof(&eof, &cursor, buffer, &gnl)) == 0)
	  return (NULL);
	else if (gnl.bool == 1)
	  return (gnl.str);
      }
    else
      {
	gnl.str[gnl.i] = buffer[cursor];
	cursor += 1;
	gnl.i+= 1;
      }
  gnl.str[gnl.i] = '\0';
  cursor += 1;
  return (gnl.str);
}
