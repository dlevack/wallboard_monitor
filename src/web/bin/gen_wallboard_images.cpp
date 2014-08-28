#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <Magick++.h> 

using namespace std; 
using namespace Magick; 

string* get_color_list();
int count_colors();

int main(int argc,char **argv)  { 
  int count = count_colors();
  string* colors = new string[count];
  int i;
  
  try { 
    InitializeMagick(*argv);
    Image image;
    string gradient;
    string radgradient;
    string imagefile;
    string imagepath = "/opt/wallboard_monitor/wallboard_web/images/";
    
    colors = get_color_list();
    for (i = 0; i < count; ++i) {
      gradient  = "gradient:";
      gradient += colors[i];
      gradient += "-black";
      
      radgradient  = "radial-gradient:";
      radgradient += colors[i];
      radgradient += "-black";
      
      imagefile  = imagepath;
      imagefile += colors[i];
      imagefile += "-bg.jpg";
      
      image.size("5x200");
      image.read(gradient);
      image.rotate(-90);
      image.write(imagefile);
      
      imagefile  = imagepath;
      imagefile += colors[i];
      imagefile += "-bg2.jpg";

      image.size("5x200");
      image.read(gradient);
      image.rotate(90);
      image.write(imagefile);

      imagefile  = imagepath;
      imagefile += colors[i];
      imagefile += ".png";
      
      image.size("25x25");
      image.read(radgradient);
      image.write(imagefile);
    }
  }
  catch( Exception &error_ ) { 
    cout << "Caught exception: " << error_.what() << endl; 
    return 1; 
  } 
  return 0; 
}
