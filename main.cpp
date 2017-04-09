#include <iostream>
#include <stdlib.h>
#include <limits>

#ifdef __linux__                                            // include this only on Linux

#include <getopt.h>

#endif                                                      // End

#include <GL/glut.h>

#include "defines.h"

// TODO Shouldn't these be unsigned ints?

int grid_size{0};
int snake_num{0};
// TODO Double check what *snake_size does and if snakeSize is not needed!
int snakeSize{0};
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
	int x, y, z, option{0};

	// Decide which code you will compile because Win don't support getopt
#ifdef __linux__

        char *sGrid, *nSnake, *snkSize;
	while ((option = getopt(argc, argv, "g:n:s:")) != -1)
         {
                 switch (option)
                 {
                     case 'g' :
                         grid_size = strtol(optarg, &sGrid, 10);
                         cout << "Grid's size = " << grid_size << '\n';
                         break;

                     case 'n' :
                         snake_num = strtol(optarg, &nSnake, 10);
                         cout << "Number of snakes = " << snake_num << '\n';
                         break;

                     case 's' :
                         snakeSize = strtol(optarg, &snkSize, 10);
                         // I know this will annoy you Nikos :D
                         cout << "Size of "
                           << ((snakeSize == 1)  ? "snake = " : "snakes = ")
                           << snakeSize << '\n';

                     default :
                         break;
                }
        }

        // Either the user didn't provide a valid number or
        // the user provided stupid numbers
        if (grid_size <= 0 || snake_num <= 0 || snakeSize <= 0)
        {
            cerr << "Usage: openSnake -g value_Foo -n value_Bar -s size_of_snake\n";
            cerr << "Make sure you didn't enter a negative value\n";
            exit(EXIT_FAILURE);
        }

        // If optopt is non-zero then the user gave an unknown option
        if (optopt)
        {
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
                 if (!snakeSize)
                 {
                     cout << "Snake's #" << i + 1 << " size: ";
                     cin >> snake_array[i].size;
                 }

	}

	for(int i = 0; i < snake_num; i++)
	{
		coordinates = new coord [2 * snake_array[i].size - 1];
		cout << "Position for snake #" << i + 1 << "(x,y,z): ";
		cin >> x >> y >> z;
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

