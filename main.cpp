#include <iostream>
#include <stdlib.h>
#include <limits>

#ifdef __linux__                                            // include this only on Linux

#include <getopt.h>

#endif                                                      // End

#include <GL/glut.h>

#include "defines.h"

int grid_size{-1};
int snake_num{-1};
// TODO Double check what *snake_size does and if snakeSize is not needed!
int snakeSize{-1};
int *snake_size;
int **snake_position;
int ***grid;
int timer = 500;
//int ***grid_table;

snake *snake_array;
sphere hugeSphere;

using namespace std;

int main(int argc, char** argv)
{
	coord *coordinates;
	int x{-1}, y{-1}, z{-1}, option{0};

	// Decide which code you will compile because Win don't support getopt
#ifdef __linux__

        // Use abs() just in case a negative num is given. I chose not to
        // use unsigned for initialization purposes.

        char *sGrid, *nSnake, *snkSize;
	while ((option = getopt(argc, argv, "g:n:s:ch")) != -1)
         {
                 switch (option)
                 {
                     case 'g' :
                         grid_size = abs(strtol(optarg, &sGrid, 10));
                         break;

                     case 'n' :
                         snake_num = abs(strtol(optarg, &nSnake, 10));
                         break;

                     case 's' :
                         snakeSize = abs(strtol(optarg, &snkSize, 10));
                         break;

                     case 'c' :
                         x = y = z = 0;
                         break;

                     case 'h' :
                         print_usage();
                         exit(EXIT_SUCCESS);

                     default :
                         break;
                }
        }

        // If optopt is non-zero then the user gave an unknown option
        if (optopt)
        {
            exit(EXIT_FAILURE);
        }

        // Either the user didn't provide a valid number or
        // the user provided stupid numbers
        if (grid_size <= 0 || snake_num <= 0 || snakeSize <= 0)
        {
            print_usage();
            cerr << "\nMake sure you didn't give a zero value";
            exit(EXIT_FAILURE);
        }

# elif __WIN32

        while((cout << "Grid size: ") &&
               !(cin >> grid_size))
               {
                   cerr << "Not a numeric value. ";
                   cin.clear();
                   cin.ignore(numeric_limits<streamsize>::max(), '\n');
               }

        while ((cout << "Snake number: ") &&
              !(cin >> snake_num))
              {
                  cerr << "Not a numeric value. ";
                  cin.clear();
                  cin.ignore(numeric_limits<streamsize>::max(), '\n');
              }
#endif

	snake_array = new snake [snake_num];

	//grid_table = new int ** [grid_size];

//setting the grid_table
/*	for(int i = 0; i < grid_size; i++)
	{
		grid_table[i] = new int * [grid_size];

		for(int j = 0; j < grid_size; j++)
		{
			grid_table[i][j] = new int [grid_size];

			for(int k = 0; k < grid_size; k++)
			{
				grid_table[i][j][k] = 0;
			}
		}

	}*/

	for(int i = 0; i < snake_num; i++)
	{
                 if (!(snakeSize))
                 {
                     cout << "Snake's #" << i + 1 << " size: ";
                     cin >> snake_array[i].size;
                 }
                 else
                 {
                     // Append the command line argument
                     snake_array[i].size = snakeSize;
                 }

	}

	for(int i = 0; i < snake_num; i++)
	{
		coordinates = new coord [2 * snake_array[i].size - 1];
		if ((x < 0) || (y < 0) || (z < 0)){
                      cout << "Position for snake #" << i + 1 << "(x,y,z): ";
                      cin >> x >> y >> z;
                }
		snake_array[i].set_coordinates(x, y, z);
	}

    	glutInit(&argc, argv);
    	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    	glutInitWindowSize (WIN_X_SIZE, WIN_Y_SIZE);
    	glutCreateWindow("Open Snake");

    	init ();

    	glutReshapeFunc(reshape);
    	glutDisplayFunc(display);
    	glutKeyboardFunc(keyboard);
	//glutKeyboardUpFunc(keyboard);
	//glutIgnoreKeyRepeat(1);
    	glutSpecialFunc(specialKey);

	glutTimerFunc(timer, update, 0);

    	glutMainLoop();

    	return 0;
}

