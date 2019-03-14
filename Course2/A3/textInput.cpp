#include "rsdl.hpp"
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define MAX_STRING_LENGTH 15
#define WINDOW_TITLE "RSDL Tutorial"
#define BACK_SPACE 8
#define RETURN 'q'

#define TICK_DURATION 10
#define CURSOR_AGE 50

#define IMG_SQUARE "square.png"
#define IMG_BACKGROUND "background.jpg"
#define FONT_FREESANS "FreeSans.ttf"

//One self defined struct which represents the square on screen.
struct Square
{
  int x,y;
  int v_x,v_y;
  int width,height;
};

//Initializing the square.
Square create_square(int x, int y, int v_x, int v_y, int width, int height) {
  Square square;
  square.x = x;
  square.y = y;
  square.v_x = v_x;
  square.v_y = v_y;
  square.width = width;
  square.height = height;
  return square;
}

//This segment reflects the square when it reaches the borders.
void collide_with_horizontal_border(Square& square)
{
  if (square.y<= 0 || square.y > (WINDOW_HEIGHT - square.height) )
    square.v_y = -square.v_y;
}

void collide_with_vertical_border(Square& square)
{
  if (square.x <= 0 || square.x > (WINDOW_WIDTH - square.width) )
    square.v_x = -square.v_x;
}

//Move the square for one frame.
void move_square(Square& square)
{
  square.x += square.v_x;
  square.y += square.v_y;

  collide_with_horizontal_border(square);
  collide_with_vertical_border(square);
}

//One simple function to draw a string on screen.
void draw_string(window& win, string text)
{
  win.show_text(text, 100, 100, WHITE, FONT_FREESANS, 30);
}

//An example of use cases of RSDL functions.
void draw_dynamic_background(window& win, Square square)
{
  win.draw_bg(IMG_BACKGROUND, 0, 0);
  win.fill_rect(100, 100, (500 - 1), (50 - 1), RED);
  win.draw_png(IMG_SQUARE, square.x, square.y, square.width, square.height, 45);
}

string prepare_output_text(string input_string)
{
  return "  Your name: " + input_string;
}

void erase_last_char(string& input_string)
{
  if(input_string.size() > 0)
      input_string.erase(input_string.size() - 1);
}

void add_char(string& input_string, char c)
{
  if(input_string.size() < MAX_STRING_LENGTH)
    input_string += c;
}

void process_rsdl_input(window& win, bool& quit_flag, string& input_string) {
  //When working with RSDL you first poll for the latest event.
  //Then you can work with the event.
  Event event = win.pollForEvent();

  //List of these events are availabe in rsdl.hpp .
  if(event.type() == KEY_PRESS) {
    if(event.pressedKey() == BACK_SPACE)
      erase_last_char(input_string);
    else {
      if(event.pressedKey() == RETURN)
      	quit_flag = true;
      else
        add_char(input_string, event.pressedKey());
    }
  }
}

void run_input_capture_window(window& win, string& input_string)
{
  Square square = create_square(50, 60, 1, -1, 40, 40);
  bool quit_flag = false;

  while(!quit_flag) {
    //Input Section
    process_rsdl_input(win, quit_flag, input_string);

    //Simple Logic
    move_square(square);

    //Draw Section
    win.clear();
    draw_dynamic_background(win, square);
    draw_string(win, prepare_output_text(input_string));
    //Update the current window.
    win.update_screen();

    //Delay your program for specific amount time.
    Delay(TICK_DURATION);
  }
}
int main()
{
  //  Whenever you're using RSDL, you must first create a new window
  //to draw your shapes in.
  window win(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

  string input_string;
  run_input_capture_window(win, input_string);

	cout<<input_string<<endl;
}
