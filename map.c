// Custom parser for
// parsing map from index 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#define AUTHOR "Kushal"

#define ASCII_ROWS 0
#define ASCII_COLS 0
#define ASCII_MAP NULL


#define errExit(msg) do {   \
  fprintf(stderr, msg);     \
  exit(EXIT_FAILURE);       \
} while (0)

typedef struct {
  char *map_array;      // map array

  size_t cols;          // number of columns in map
  size_t rows;          // number of rows in map
} map_t;


/*
 * generates map
 * from character array
 * with supplied rows
 * and columns
 */
map_t *generate_map(map_t *gMap)
{
  unsigned color_robin = 0;
  map_t *copyMap;
  
  copyMap = malloc(sizeof(map_t));
  assert(copyMap != NULL);

  /* create a copy of the array */
  copyMap->map_array = calloc(gMap->rows * gMap->cols, sizeof(int));
  assert(copyMap->map_array != NULL);

  copyMap->rows = gMap->rows;
  copyMap->cols = gMap->cols;

  for (size_t y = 1; y < gMap->rows-1; y++)
  {
    for (size_t x = 1; x < gMap->cols-1; x++)
    {
      char bottom, front;
      char top, back;

      bottom = (char)gMap->map_array[(y+1) * gMap->cols + x];
      front = (char)gMap->map_array[y * gMap->cols + (x+1)];
      top = (char)gMap->map_array[(y-1) * gMap->cols + x];
      back = (char) gMap->map_array[y * gMap->cols + (x-1)];

      if (gMap->map_array[y * gMap->cols + x] == ' ')
      {

        /*
         *
         * Image index 
         *    |
         *    |&>
         *    |
         *
         */
        if (bottom == ' ' && front == ' ' && back == '|' && top == ' ')
        {
          copyMap->map_array[y * copyMap->cols + x] = 10;
        }
        /*
         *  Image index 6 
         *        |
         *      &>|
         *        |
         */
        else if (bottom == ' ' && front == '|' && back == ' ' && top == ' ')
        {
          copyMap->map_array[y * copyMap->cols + x] = 6;
        }
        /*
         *  Image index 8
         *
         *      &>
         *  --------------
         */
        else if (bottom == '-' && front == ' ' && back == ' ' && top == ' ')
        {
          copyMap->map_array[y * copyMap->cols + x] = 8;
        }
        /*
         * Image index 4
         *
         *  ------------------
         *          &>
         */
        else if (bottom == ' ' && front == ' ' && back == ' ' && top == '-')
        {
          copyMap->map_array[y * copyMap->cols + x] = 4;
        }
        /*
         *  Image index 5
         *         ------------|
         *                   &>|
         */
        else if (bottom == ' ' && front == '|' && back == ' ' && top == '-')
        {
          copyMap->map_array[y * copyMap->cols + x] = 5;
        }
        /*
         * Image index 11 
         *
         *  |------------------
         *  |&>
         */
        else if (bottom == ' ' && front == ' ' && back == '|' && top == '-')
        {
          copyMap->map_array[y * copyMap->cols + x] = 11;
        }
        /*
         * Image index
         *                      &>|
         *------------------------|
         */
        else if (bottom == '-' && front == '|' && back == ' ' && top == ' ')
        {
          copyMap->map_array[y * copyMap->cols + x] = 7;
        }
        /*
         * Image index
         *
         *    |&>
         *    |--------------
         *
         */
        else if (bottom == '-' && front == ' ' && back == '|' && top == ' ')
        {
          copyMap->map_array[y * copyMap->cols + x] = 9;
        }
        /*
         * Image index 3
         *                  
         *     &>
         *
         */
        else if (bottom == ' ' && front == ' ' && back == ' ' && top == ' ')
        {
          copyMap->map_array[y * copyMap->cols + x] = 3;
        }
      }
      else
      {
          copyMap->map_array[y * copyMap->cols + x] = color_robin++;
      }
      color_robin++;
      color_robin %= 3;
    }
  }
  return copyMap;
}

/*
 * read from file by removing
 * endofline from the file
 */
void inputFromFile(char *filename, map_t *cmap_array)
{
  char buffer[1024];
  char check_byte;
  size_t count = 0;
  ssize_t nbytes;
  size_t filesize;
  int fild;

  /*
   * open the file with
   * safety check
   */
  fild = open(filename, O_RDONLY);
  assert(fild > 0);

  /*
   * find index of first occurence of
   * eol character and also find the size
   * of file
   */
  while ((nbytes = read(fild, buffer, 1024)) > 0)
  {
    for (unsigned i = 0; i < nbytes; i++)
    {
      if (buffer[i] == '\n')
      {
        filesize = lseek(fild, 0, SEEK_END);
        lseek(fild, 0, SEEK_SET);
        goto out;
      }
      count++;
    }
  }
out:
  cmap_array->cols = count;
  cmap_array->rows = filesize/++count;

  cmap_array->map_array = malloc(sizeof(char) * cmap_array->cols * cmap_array->rows);
  assert(cmap_array->map_array != NULL);

  count = 0;

  while ((nbytes = read(fild, buffer, cmap_array->cols)) > 0)
  {
    for (unsigned i = 0; i < nbytes; i++)
      if (buffer[i] != '\n')
        cmap_array->map_array[count++] = buffer[i];
  }

  close(fild);

}


int main(int argc, char* argv[])
{
  map_t cmap_array, *generated_map;
  ssize_t nbytes = 0;
  bool file_flag = false;

  if (argc == 2)
  {
    // Read input from file from argument
    inputFromFile(argv[1], &cmap_array);
    file_flag = true;
  }
  else
  {
    // Read input from character array
    cmap_array.map_array = ASCII_MAP;
    cmap_array.rows = ASCII_ROWS;
    cmap_array.cols = ASCII_COLS;

    assert(cmap_array.map_array != NULL);
  }


  // Generate byte map from ascii map
  generated_map = generate_map(&cmap_array);


  for (size_t y = 0; y < generated_map->rows; y++)
  {
    for (size_t x = 0; x < generated_map->cols; x++)
      printf("%02d ", (int)generated_map->map_array[y * generated_map->cols + x]);

    putchar('\n');
  }

  if (file_flag == true)
    free(cmap_array.map_array);

  free(generated_map->map_array);
  free(generated_map);

  return 0;
}
