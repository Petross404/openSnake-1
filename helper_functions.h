#include "openSnakeConfig.h"
#include <string>
#include <iostream>

#ifdef _WIN32                                               // If Win, then use "/opt" instead of --opt
# define TCLAP_NAMESTARTSTRING "~~"
# define TCLAP_FLAGSTARTSTRING "/"
#endif
#include <tclap/CmdLine.h>

static int window;
static int menu_id;
static int submenu_id;
static int value {0};


typedef struct XYZ{
    int x = -1;
    int y = -1;
    int z = -1;
    bool is_set = false;
  } XYZ;

typedef struct SizeOptions{
    int grid_size = 0;
    int snake_num = 0;
    int snakeSize = 0;
  } SizeOptions;

class Program{

private:
    std::string m_name;
    std::string m_version;
    std::string m_author;
    int m_argc;
    char** m_argv;

public:
    Program(int argc, char** argv);
    std::string getName();
    std::string getVersionStr();
    std::string authorInfo();
    std::string getVersionMsg();
    void handleArguments (XYZ& PointOnAxis, SizeOptions& NumericArgs);
};

void menu ( int num );
void createMenu ();
bool check_cin();