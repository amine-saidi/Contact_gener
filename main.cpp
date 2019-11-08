#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include "Myfonction.h"
#include <map>
#include <algorithm>
#include <sstream>
#include <fstream>


using namespace std;
map<string,int>  mapT;

int main (int argc, char ** argv)
{

string line;
int d;
int tx=10;
int ty=15;

fstream fichier("logfile");
getline(fichier, line); 
getline(fichier, line);
getline(fichier, line);
getline(fichier, line);
getline(fichier, line);
while(getline(fichier, line,'*')){
getline(fichier, line,'*');
istringstream iss(line);
iss>>d;
getline(fichier, line,'*');
line=removeSpaces(line);
mapT[line]=d;
getline(fichier, line);
}

GtkWidget *pWindow;
pWindow=CreateWin(tx,ty,argc,argv);
gtk_widget_show_all(pWindow);
gtk_main();


return EXIT_SUCCESS;
}

