#include "rsdl.hpp"
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <fstream>

//#include "default_names.hpp"
#include "superman_names.hpp"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

#define DIAMOND_MAKING_MARGIN 150

#define PARTICLE_ABSORBATION_DISTANCE 100
#define PARTICLE_LIFE_TIME (5 * ONE_SECOND)

#define LASER 100
#define BULLET 200

#define DRONE_REAL_SPEED 1000 //pixells per second
#define DRONE_SPEED (DRONE_REAL_SPEED * (float)TICK_DURATION / ONE_SECOND)
#define BULLET_REAL_SPEED 3000
#define BULLET_SPEED (BULLET_REAL_SPEED * (float)TICK_DURATION / ONE_SECOND)
#define LASER_REAL_SPEED 2000
#define LASER_SPEED (LASER_REAL_SPEED * (float)TICK_DURATION / ONE_SECOND)
#define DIAMOND_REAL_SPEED 100
#define DIAMOND_SPEED (DIAMOND_REAL_SPEED * (float)TICK_DURATION / ONE_SECOND)
#define PARTICLE_REAL_SPEED 200
#define PARTICLE_SPEED (PARTICLE_REAL_SPEED * (float)TICK_DURATION / ONE_SECOND)

#define ONE_SECOND 1000
#define TICK_DURATION 2
#define MENU_TICK_DURATION 20

#define EASY 10
#define NORMAL 20
#define HARD 30

#define PI 3.14159265

#define PAUSE_BUTTON 'p'

#define POSSIBILITY_OF_CREATING_DIAMOND_EASY 1
#define POSSIBILITY_OF_CREATING_DIAMOND_NORMAL 3
#define POSSIBILITY_OF_CREATING_DIAMOND_HARD 9
#define REAL_PRODUCING_POSSIBILITY 500

#define MAX_NUM_OF_DIAMONDS_EASY 10
#define MAX_NUM_OF_DIAMONDS_NORMAL 20
#define MAX_NUM_OF_DIAMONDS_HARD 40

#define SCORE_FOR_MORE_DIAMONDS_EASY 1250
#define SCORE_FOR_MORE_DIAMONDS_NORMAL 750
#define SCORE_FOR_MORE_DIAMONDS_HARD 500

#define SCORE_EARNED_BY_EATING_PARTICLE_EASY 5
#define SCORE_EARNED_BY_EATING_PARTICLE_NORMAL 10
#define SCORE_EARNED_BY_EATING_PARTICLE_HARD 15
#define ENERGY_EARNED_BY_EATING_PARTICLE 1

#define SCORE_EARNED_BY_DESTROYING_DIAMOND_EASY 20
#define SCORE_EARNED_BY_DESTROYING_DIAMOND_NORMAL 40
#define SCORE_EARNED_BY_DESTROYING_DIAMOND_HARD 80
#define ENERGY_EARNED_BY_DESTROYING_DIAMOND 1

#define ENERGY_NEEDED_FOR_SHOOTING_LASER 5
#define ENERGY_NEEDED_FOR_BOMB 200

#define LIVES_STARTING_X 5
#define LIVES_STARTING_Y 5
#define LIVES_BOX_STARTING_X 0
#define LIVES_BOX_STARTING_Y 0

#define SCORE_STARTING_X 305
#define SCORE_STARTING_Y 5
#define SCORE_BOX_STARTING_X 300
#define SCORE_BOX_STARTING_Y 0

#define ENERGY_STARTING_X 605
#define ENERGY_STARTING_Y 5
#define ENERGY_BOX_STARTING_X 600
#define ENERGY_BOX_STARTING_Y 0

#define TEXT_DURING_GAME_SIZE 15
#define TEXT_DURING_GAME_COLOR WHITE
#define BOX_DURING_GAME_COLOR STRANGE
#define BOX_DURING_GAME_WIDTH 85
#define BOX_DURING_GAME_HEIGHT 30

#define READY_X 250
#define READY_Y 200
#define READY_SIZE 300
#define READY_COLOR WHITE

#define BOX_WIDTH 300
#define BOX_HEIGHT 70
#define BOX_X 600

#define NEW_GAME 1
#define NEW_GAME_Y 300

#define LEADERBOARD 2
#define LEADERBOARD_Y 400

#define EXIT 3
#define EXIT_Y 500

#define EASY_BUTTON 4
#define EASY_BUTTON_Y 250

#define NORMAL_BUTTON 5
#define NORMAL_BUTTON_Y 350

#define HARD_BUTTON 6
#define HARD_BUTTON_Y 450

#define BACK_BUTTON 7
#define BACK_BUTTON_Y 750

#define MAIN_PAGE 10
#define CHOOSE_DIFFICULTY_PAGE 20
#define LEADERBOARD_PAGE 30

#define FIRST_WORD_Y 200
#define MARGIN_WORDS_X 50
#define MARGIN_WORDS_Y 10
#define STARTING_NAMES_LEADERBOARD_X (HORIZONTAL_LINE_X + MARGIN_WORDS_X)
#define STARTING_SCORE_LEADERBOARD_X (VERTICAL_LINE_X + MARGIN_WORDS_X)
#define HORIZONTAL_LINE_X 500
#define HORIZONTAL_LINE_WIDTH 400
#define VERTICAL_LINE_X 700
#define VERTICAL_LINE_HEIGHT 50
#define LINES_COLOR WHITE
#define TEXT_LEADERBOARD_COLOR WHITE
#define TEXT_LEADERBOARD_SIZE 24

#define MAX_STRING_LENGTH 15
#define BACK_SPACE 8
#define ENTER 13
#define SAVE_BOX_X 400
#define SAVE_BOX_Y 400
#define SAVE_BOX_WIDTH 500
#define SAVE_BOX_HEIGHT 70
#define SAVE_BOX_COLOR RED
#define SAVE_TEXT_COLOR WHITE
#define SAVE_TEXT_SIZE 30
#define MAX_NUM_OF_SAVING 5

using namespace std;

struct Drone
{
  bool super;
  string picture_name;
  float x, y;
  int width, height;
  int angle;
  float v;
  float v_x, v_y;
};
struct Shot
{
  int object;
  string picture_name;
  float x, y;
  int width, height;
  int angle;
  float v;
  float v_x, v_y;
};
struct Diamond
{
  string picture_name;
  float x, y;
  int width, height;
  int angle;
  float v;
  float v_x, v_y;
};
struct Particle
{
  string picture_name;
  float x, y;
  int width, height;
  int angle;
  float v;
  float v_x, v_y;
  bool around_drone;
  int left_time;
};
struct Person
{
  string name;
  int score;
};
struct Box
{
  int id;//defined at the top
  int x, y;
  int x_string, y_string;
  string name;
  int page;
};
struct Page
{
  int id;
  vector<Box> boxes;
};

Drone create_drone();
void calculate_drone_angle(Drone&, int, int);
void calculate_drone_speed(Drone&, int, int);
void move_drone(Drone&, int, int);
void change_drone_to_super(Drone&);
void change_drone_to_normal(Drone&);
void show_drone(window&, Drone);

void shoot(Drone , vector<Shot>&, int&);
void create_bullet(Drone, Shot&);
void create_laser(Drone, Shot&, int&);
void move_shots(vector<Shot>&);
void move_shot(Shot&);
void check_shots_out_of_range(vector<Shot>&);
void show_shots(window&, vector<Shot>);
void remove_shot(vector<Shot>&, int);
void remove_all_shots(vector<Shot>&);

void create_diamond(vector<Diamond>&, Drone);
void move_diamonds(vector<Diamond>&, Drone);
void calculate_diamond_speed(Diamond&, Drone);
void calculate_diamond_angle(Diamond&, Drone);
void show_diamonds(window&, vector<Diamond>);
void anti_diamond_bomb(vector<Diamond>&, int&, int&, int);
void remove_diamond(vector<Diamond>&, int);
void remove_all_diamonds(vector<Diamond>&);
int find_max_num_of_diamonds(int, int, int);
void creating_diamond_function(vector<Diamond>&, Drone, int, int);

Particle create_particle(int, int);
void create_some_particle(vector<Particle>&, int, int);
void move_particles(vector<Particle>&, Drone);
void move_particle(Particle&, Drone);
void calculate_particle_speed(Particle&, Drone);
void calculate_particle_angle(Particle&, Drone);
void check_particles_around_drone(vector<Particle>&, Drone);
void check_particles_left_time(vector<Particle>&);
void show_particles(window&, vector<Particle>);
void remove_particle(vector<Particle>&, int);
void remove_all_particles(vector<Particle>&);

void impact_shots_and_diamonds(vector<Shot>&, vector<Diamond>&, vector<Particle>&, int&, int&, int);
bool check_collision(Shot, Diamond);
void eating_particles(vector<Particle>&, Drone,int&, int&, int);
bool check_close_particle(Particle, Drone);
int calculate_distance(float , float, float, float);
int standarding_angle(int);
bool eating_drone(vector<Diamond>, Drone);
bool check_eated_by_diamond(Diamond, Drone);
bool check_finish_game(vector<Particle>&, vector<Shot>&, vector<Diamond>&, Drone, int&, int&, window&, int, bool&);
string int_to_string(int);
void show_score(window&, int);
void show_energy(window&, int);
void show_lives(window& ,int);
void show_on_screen_during_game(window&, Drone, vector<Diamond>, vector<Particle>, vector<Shot>, int, int, int);
void move_things(Drone&, vector<Diamond>&, vector<Shot>&, vector<Particle>&, int, int);
bool check_things(Drone&, vector<Diamond>&, vector<Shot>&, vector<Particle>&, int&, int&, int&, int&, window&, bool&);
void process_rsdl_keyboard(char, bool&, Drone&, vector<Shot>&, vector<Diamond>&, int&, int&, int);
void do_rsdl(Event, bool&, Drone&, vector<Shot>&, vector<Diamond>&, int&, int&, int, int&, int&);
void show_ready_before_starting(window&, bool&, int, int, int);
int power(int, int);
int string_to_int(string);

int game(window&, int&, bool&);

Box create_box(int, int, int, string, int);
Page create_page(int, vector<Box>);
vector<Page> create_pages();
void show_boxes(window&, Page, Box);
bool process_boxes_on_menu(vector<Box>&, char, Box&);
void show_leaderboard(window&, vector<Person>);
vector<Person> load();
string prepare_output_text(string);
void erase_last_char(string&);
void add_char(string&, char);
void process_rsdl_input(window&, bool&, string&, bool&);
bool save(window&, int, vector<Person>&, bool&);
void pause(window&, bool&, int, int, int);

int main()
{
  window w(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME);
  int level_game = EASY;
  vector<Page> pages = create_pages();
  Page current_page = pages[0];
  Box selected_box = pages[0].boxes[0];
  bool quit_flag = false;
  vector<Person> persons = load();
  Event event = w.pollForEvent();
  while(!quit_flag)
  {
    event = w.pollForEvent();
    if (event.type() == QUIT)
      quit_flag = true;
    w.draw_bg(MENU_BACKGROUND_PICTURE_NAME, 0, 0);
    if (current_page.id == MAIN_PAGE)
    {
      show_boxes(w, current_page, selected_box);
      if (event.type() == KEY_PRESS)
      {
        if(process_boxes_on_menu(current_page.boxes, event.pressedKey(), selected_box))
        {
          if (selected_box.id == EXIT)
            quit_flag = true;
          else if (selected_box.id == LEADERBOARD)
          {
            current_page = pages[2];
            selected_box = pages[2].boxes[0];
          }
          else
          {
            current_page = pages[1];
            selected_box = pages[1].boxes[0];
          }
        }
      }
    }
    else if (current_page.id == LEADERBOARD_PAGE)
    {
      show_leaderboard(w, persons);
      show_boxes(w, current_page, selected_box);
      if (event.type() == KEY_PRESS)
      {
        if (event.pressedKey() == ENTER)
        {
          current_page = pages[0];
          selected_box = pages[0].boxes[0];
        }
      }
    }
    else if (current_page.id == CHOOSE_DIFFICULTY_PAGE)
    {
      show_boxes(w, current_page, selected_box);
      if (event.type() == KEY_PRESS)
      {
        if (process_boxes_on_menu(current_page.boxes, event.pressedKey(), selected_box))
        {
          if (selected_box.id == BACK_BUTTON)
          {
            current_page = pages[0];
            selected_box = pages[0].boxes[0];
            continue;
          }
          else if (selected_box.id == EASY_BUTTON)
            level_game = EASY;
          else if (selected_box.id == NORMAL_BUTTON)
            level_game = NORMAL;
          else if (selected_box.id == HARD_BUTTON)
            level_game = HARD;
          save(w, game(w, level_game, quit_flag), persons, quit_flag);
          current_page = pages[0];
          selected_box = pages[0].boxes[0];
        }
      }
    }
    w.update_screen();
    Delay(MENU_TICK_DURATION);
  }
  return 0;
}

int game(window& w, int& level_game, bool& quit_flag)
{
  srand(time(0));
  int energy = 250, score = 0, lives = 3;
  int x_mouse_location = 0;
  int y_mouse_location = 0;
  Drone drone = create_drone();
  vector<Shot> shots;
  vector<Diamond> diamonds;
  vector<Particle> particles;
  show_ready_before_starting(w, quit_flag, score, energy, lives);
  Event event = w.pollForEvent();
  while(!quit_flag)
  {
    event = w.pollForEvent();
    do_rsdl(event, quit_flag, drone, shots, diamonds, energy, score, level_game, x_mouse_location, y_mouse_location);
    move_things(drone, diamonds, shots, particles, x_mouse_location, y_mouse_location);
    show_on_screen_during_game(w, drone, diamonds, particles, shots, score, energy, lives);
    if (check_things(drone, diamonds, shots, particles, score, energy, lives, level_game, w, quit_flag))
      return score;
    w.update_screen();
    Delay(TICK_DURATION);
  }
  return 0;
}

Drone create_drone()
{
  Drone drone;
  drone.x = WINDOW_WIDTH / 2;
  drone.y = WINDOW_HEIGHT / 2;
  drone.super = false;
  drone.width = DRONE_WIDTH;
  drone.height = DRONE_HEIGHT;
  drone.angle = -90;
  drone.v = DRONE_SPEED;
  drone.picture_name = NORMAL_DRONE_PICTURE_NAME;
  return drone;
}
void calculate_drone_angle(Drone& drone, int x_mouse_location, int y_mouse_location)
{
  if (drone.v != 0 || (drone.v == 0 && drone.super))
  {
    float delta_y = (float)(y_mouse_location) - (float)(drone.y);
    float delta_x = ((float)(x_mouse_location) - (float)(drone.x));
    if (delta_x > 0 && abs(delta_y) <= DRONE_SPEED / 2)
      drone.angle = 0;
    else if(delta_x < 0 && abs(delta_y) <= DRONE_SPEED / 2)
     drone.angle = 180;
    else if (abs(delta_x) <= DRONE_SPEED / 2 && delta_y > 0)
      drone.angle = 90;
    else if (abs(delta_x) <= DRONE_SPEED / 2 && delta_y < 0)
      drone.angle = -90;
    else
    {
      int a = (int)(180 * (float)atan(delta_y / delta_x) / PI);
      if (delta_x < 0 && delta_y > 0)
        a = a + 180;
      if (delta_x < 0 && delta_y < 0)
        a = a - 180;
      drone.angle = a;
    }
  }
}
void calculate_drone_speed(Drone& drone, int x_mouse_location, int y_mouse_location)
{
  if (calculate_distance(x_mouse_location, y_mouse_location, drone.x, drone.y) < 10 || (drone.super))
    drone.v = 0;
  else
    drone.v = DRONE_SPEED;
  calculate_drone_angle(drone, x_mouse_location, y_mouse_location);
  drone.v_x = (float)drone.v * cos(drone.angle * PI / 180);
  drone.v_y = (float)drone.v * sin(drone.angle * PI / 180);
}
void move_drone(Drone& drone, int x_mouse_location, int y_mouse_location)
{
  calculate_drone_speed(drone, x_mouse_location, y_mouse_location);
  drone.x += drone.v_x;
  drone.y += drone.v_y;
}
void show_drone(window& w, Drone drone)
{
  w.draw_png(drone.picture_name, (int)drone.x, (int)drone.y, drone.width, drone.height, standarding_angle(drone.angle));
}
void change_drone_to_super(Drone& drone)
{
  drone.super = true;
  drone.picture_name = LASER_DRONE_PICTURE_NAME;
}
void change_drone_to_normal(Drone& drone)
{
  drone.super = false;
  drone.picture_name = NORMAL_DRONE_PICTURE_NAME;
}

void create_laser(Drone drone, Shot& temp, int& energy)
{
  temp.v = LASER_SPEED;
  temp.object = LASER;
  temp.picture_name = LASER_PICTURE_NAME;
  temp.width = LASER_WIDTH;
  temp.height = LASER_HEIGHT;
  energy -= ENERGY_NEEDED_FOR_SHOOTING_LASER;
}
void create_bullet(Drone drone, Shot& temp)
{
  temp.v = BULLET_SPEED;
  temp.object = BULLET;
  temp.picture_name = BULLET_PICTURE_NAME;
  temp.width = BULLET_WIDTH;
  temp.height = BULLET_HEIGHT;
}
void shoot(Drone drone, vector<Shot>& shots, int& energy)
{
  Shot temp;
  temp.x = drone.x;
  temp.y = drone.y;
  temp.angle = drone.angle;
  if (drone.super && energy >= ENERGY_NEEDED_FOR_SHOOTING_LASER)
    create_laser(drone, temp, energy);
  else if(!drone.super)
    create_bullet(drone, temp);
  temp.v_x = (float)temp.v * cos(temp.angle * PI / 180);
  temp.v_y = (float)temp.v * sin(temp.angle * PI / 180);
  shots.push_back(temp);
}
void show_shots(window& w, vector<Shot> shots)
{
  for (unsigned int i = 0; i < shots.size(); i++)
    w.draw_png(shots[i].picture_name, shots[i].x, shots[i].y, shots[i].width, shots[i].height, standarding_angle(shots[i].angle) - 90);
}
void move_shot(Shot& shot)
{
  shot.x += shot.v_x;
  shot.y += shot.v_y;
}
void move_shots(vector<Shot>& shots)
{
  for (unsigned int i = 0; i < shots.size(); i++)
  {
    move_shot(shots[i]);
  }
}
void check_shots_out_of_range(vector<Shot>& shots)
{
  for (unsigned int i = 0; i < shots.size(); i++)
    if (shots[i].x < 0 || shots[i].y < 0 || shots[i].x - shots[i].width > WINDOW_WIDTH || shots[i].y - shots[i].height > WINDOW_HEIGHT)
      remove_shot(shots, i);
}
void remove_shot(vector<Shot>& shots, int num)
{
  shots.erase(shots.begin() + num);
}
void remove_all_shots(vector<Shot>& shots)
{
  int num_of_shots = shots.size();
  for (int i = 0; i < num_of_shots; i++)
    remove_shot(shots, 0);
}

void calculate_diamond_angle(Diamond& diamond, Drone drone)
{
  float delta_x = drone.x - diamond.x;
  float delta_y = drone.y - diamond.y;
  if (abs(delta_x) <= DIAMOND_SPEED / 2 && abs(delta_y) <= DIAMOND_SPEED / 2)
    diamond.angle = 0;
  else if (delta_x > 0 && abs(delta_y) <= DIAMOND_SPEED / 2)
    diamond.angle = 0;
  else if(delta_x < 0 && abs(delta_y) <= DIAMOND_SPEED / 2)
   diamond.angle = 180;
  else if (abs(delta_x) <= DIAMOND_SPEED / 2 && delta_y > 0)
    diamond.angle = 90;
  else if (abs(delta_x) <= DIAMOND_SPEED / 2 && delta_y < 0)
    diamond.angle = -90;
  else
  {
    int a = (int)(180 * (float)atan(delta_y / delta_x) / PI);
    if (delta_x < 0 && delta_y > 0)
      a = a + 180;
    if (delta_x < 0 && delta_y < 0)
      a = a - 180;
    diamond.angle = a;
  }
}
void calculate_diamond_speed(Diamond& diamond, Drone drone)
{
  calculate_diamond_angle(diamond, drone);
  diamond.v_x = (float)diamond.v * cos(diamond.angle * PI / 180);
  diamond.v_y = (float)diamond.v * sin(diamond.angle * PI / 180);
}
void create_diamond(vector<Diamond>& diamonds, Drone drone)
{
  Diamond temp;
  temp.picture_name = DIAMOND_PICTURE_NAME;
  temp.x = rand() % WINDOW_WIDTH;
  while(temp.x < DIAMOND_MAKING_MARGIN || temp.x > WINDOW_WIDTH - DIAMOND_MAKING_MARGIN || (temp.x > drone.x - DIAMOND_MAKING_MARGIN && temp.x < drone.x + DIAMOND_MAKING_MARGIN))
    temp.x = rand() % WINDOW_WIDTH;
  temp.y = rand() % WINDOW_HEIGHT;
  while(temp.y < DIAMOND_MAKING_MARGIN || temp.y > WINDOW_HEIGHT - DIAMOND_MAKING_MARGIN || (temp.y > drone.y - DIAMOND_MAKING_MARGIN && temp.y < drone.y + DIAMOND_MAKING_MARGIN))
    temp.y = rand() % WINDOW_HEIGHT;
  temp.width = DIAMOND_HEIGHT;
  temp.height = DIAMOND_WIDTH;
  temp.v = (float)DIAMOND_SPEED;
  calculate_diamond_angle(temp, drone);
  calculate_diamond_speed(temp, drone);
  diamonds.push_back(temp);
}
void show_diamonds(window& w, vector<Diamond> diamonds)
{
  for (unsigned int i = 0; i < diamonds.size(); i++)
    w.draw_png(diamonds[i].picture_name, diamonds[i].x, diamonds[i].y, diamonds[i].width, diamonds[i].height, standarding_angle(diamonds[i].angle));
}
void move_diamonds(vector<Diamond>& diamonds, Drone drone)
{
  for (unsigned int i = 0; i < diamonds.size(); i++)
  {
    calculate_diamond_speed(diamonds[i], drone);
    diamonds[i].x += diamonds[i].v_x;
    diamonds[i].y += diamonds[i].v_y;
  }
}
void anti_diamond_bomb(vector<Diamond>& diamonds, int& energy, int& score, int level)
{
  if (energy >= ENERGY_NEEDED_FOR_BOMB)
  {
    energy -= ENERGY_NEEDED_FOR_BOMB;
    energy += ENERGY_EARNED_BY_DESTROYING_DIAMOND * diamonds.size();
    switch (level)
    {
      case EASY :
      score += SCORE_EARNED_BY_DESTROYING_DIAMOND_EASY * diamonds.size();
      break;
      case NORMAL :
      score += SCORE_EARNED_BY_DESTROYING_DIAMOND_NORMAL * diamonds.size();
      break;
      case HARD :
      score += SCORE_EARNED_BY_DESTROYING_DIAMOND_HARD * diamonds.size();
      break;
    }
    remove_all_diamonds(diamonds);
  }
}
void remove_diamond(vector<Diamond>& diamonds, int num)
{
  diamonds.erase(diamonds.begin() + num);
}
void remove_all_diamonds(vector<Diamond>& diamonds)
{
  int num_of_diamonds = diamonds.size();
  for (int i = 0; i < num_of_diamonds; i++)
    remove_diamond(diamonds, 0);
}
int find_max_num_of_diamonds(int score, int score_needed_for_more, int max_of_diamonds)
{
  return max_of_diamonds + (score / score_needed_for_more);
}
void creating_diamond_function(vector<Diamond>& diamonds, Drone drone, int level, int score)
{
  int max_of_diamonds = MAX_NUM_OF_DIAMONDS_EASY;
  int producing_diamonds_possibility = POSSIBILITY_OF_CREATING_DIAMOND_EASY;
  int more_diamonds_score = SCORE_FOR_MORE_DIAMONDS_EASY;
  switch (level)
  {
    case NORMAL :
    max_of_diamonds = MAX_NUM_OF_DIAMONDS_NORMAL;
    producing_diamonds_possibility = POSSIBILITY_OF_CREATING_DIAMOND_NORMAL;
    more_diamonds_score = SCORE_FOR_MORE_DIAMONDS_NORMAL;
    break;
    case HARD :
    max_of_diamonds = MAX_NUM_OF_DIAMONDS_HARD;
    producing_diamonds_possibility = POSSIBILITY_OF_CREATING_DIAMOND_HARD;
    more_diamonds_score = SCORE_FOR_MORE_DIAMONDS_HARD;
    break;
  }
  max_of_diamonds = find_max_num_of_diamonds(score, more_diamonds_score, max_of_diamonds);
  int a = rand() % REAL_PRODUCING_POSSIBILITY;
  if (a < producing_diamonds_possibility && diamonds.size() < (unsigned int)max_of_diamonds)
    create_diamond(diamonds, drone);
}

Particle create_particle(int x, int y)
{
  Particle temp;
  temp.picture_name = PARTICLE_PICTURE_NAME;
  temp.x = x;
  temp.y = y;
  temp.width = PARTICLE_WIDTH;
  temp.height = PARTICLE_HEIGHT;
  temp.v = PARTICLE_SPEED;
  temp.angle = (rand() % 360) - 180;
  if (temp.angle == -180)
    temp.angle = 180;
  temp.around_drone = false;
  temp.v_x = temp.v * cos(temp.angle * PI / 180);
  temp.v_y = temp.v * sin(temp.angle * PI / 180);
  temp.left_time = PARTICLE_LIFE_TIME;
  return temp;
}
void create_some_particle(vector<Particle>& particles, int x, int y)
{
  int num_of_particles = (rand() % 5) + 1;
  for (int i = 0; i < num_of_particles; i++)
  {
    Particle temp = create_particle(x, y);
    particles.push_back(temp);
  }
}
void move_particle(Particle& particle, Drone drone)
{
  calculate_particle_speed(particle, drone);
  particle.x += particle.v_x;
  particle.y += particle.v_y;
}
void calculate_particle_angle(Particle& particle, Drone drone)
{
  float delta_y = drone.y - particle.y;
  float delta_x = drone.x - particle.x;
  int a = (int)(180 * (float)atan(delta_y / delta_x) / PI);
  if (delta_x < 0 && delta_y > 0)
    a = a + 180;
  if (delta_x < 0 && delta_y < 0)
    a = a - 180;
  particle.angle = a;
}
void calculate_particle_speed(Particle& particle, Drone drone)
{
  if (particle.around_drone)
  {
    calculate_particle_angle(particle, drone);
    particle.v_x = (float)particle.v * cos(particle.angle * PI / 180);
    particle.v_y = (float)particle.v * sin(particle.angle * PI / 180);
  }
  else
  {
    particle.v_x = (float)particle.v * cos(particle.angle * PI / 180);
    particle.v_y = (float)particle.v * sin(particle.angle * PI / 180);
    if (particle.x < 0 || particle.x + particle.width > WINDOW_WIDTH)
      particle.v_x = -particle.v_x;
    if(particle.y < 0  || particle.y + particle.height > WINDOW_HEIGHT)
      particle.v_y = -particle.v_y;
    /*we need to know what is the angle will be again. cause it will change after we change the speeds*/
    particle.angle = (atan(particle.v_y / particle.v_x) * 180 / PI);
    if (particle.v_x < 0 && particle.v_y > 0)
      particle.angle = particle.angle + 180;
    if (particle.v_x < 0 && particle.v_y < 0)
      particle.angle = particle.angle - 180;
  }
}
void move_particles(vector<Particle>& particles, Drone drone)
{
  for (unsigned int i = 0; i < particles.size(); i++)
    move_particle(particles[i], drone);
}
void check_particles_around_drone(vector<Particle>& particles, Drone drone)
{
  for (unsigned int i = 0; i < particles.size(); i++)
  {
    if (calculate_distance(drone.x, drone.y, particles[i].x, particles[i].y) < PARTICLE_ABSORBATION_DISTANCE)
      particles[i].around_drone = true;
    else
      particles[i].around_drone = false;
  }
}
void check_particles_left_time(vector<Particle>& particles)
{
  for (unsigned int i = 0; i < particles.size(); i++)
  {
    if(particles[i].left_time < 0)
      remove_particle(particles, i);
    particles[i].left_time -= TICK_DURATION;
  }
}
void show_particles(window& w,vector<Particle> particles)
{
  for (unsigned int i = 0; i < particles.size(); i++)
  w.draw_png(particles[i].picture_name, particles[i].x, particles[i].y, particles[i].width, particles[i].height, standarding_angle(particles[i].angle));
}
void remove_particle(vector<Particle>& particles, int num)
{
  particles.erase(particles.begin() + num);
}
void remove_all_particles(vector<Particle>& particles)
{
  int num_of_particles = particles.size();
  for (int i = 0; i < num_of_particles; i++)
    remove_particle(particles, 0);
}

bool check_collision(Shot shot, Diamond diamond)
{
  if (shot.x > diamond.x && shot.x < diamond.x + diamond.width && shot.y > diamond.y && shot.y < diamond.y + diamond.height)
    return true;
  return false;
}
void impact_shots_and_diamonds(vector<Shot>& shots, vector<Diamond>& diamonds, vector<Particle>& particles, int& energy, int& score, int level)
{
  for (unsigned int i = 0; i < diamonds.size(); i++)
  {
    for (unsigned int j = 0; j < shots.size(); j++)
    {
      if (check_collision(shots[j], diamonds[i]))
      {
        if (shots[j].object == BULLET)
          remove_shot(shots, j);
        create_some_particle(particles, diamonds[i].x, diamonds[i].y);
        remove_diamond(diamonds, i);
        energy += ENERGY_EARNED_BY_DESTROYING_DIAMOND;
        switch (level)
        {
          case EASY :
          score += SCORE_EARNED_BY_DESTROYING_DIAMOND_EASY;
          break;
          case NORMAL :
          score += SCORE_EARNED_BY_DESTROYING_DIAMOND_NORMAL;
          break;
          case HARD :
          score += SCORE_EARNED_BY_DESTROYING_DIAMOND_HARD;
          break;
        }
      }
    }
  }
}
bool check_close_particle(Particle particle, Drone drone)
{
  if (particle.x > drone.x && particle.x < drone.x + drone.width && particle.y > drone.y && particle.y < drone.y + drone.height)
    return true;
  return false;
}
void eating_particles(vector<Particle>& particles, Drone drone,int& score, int& energy, int level)
{
  for (unsigned int i = 0; i < particles.size(); i++)
  {
    if(check_close_particle(particles[i], drone))
    {
      remove_particle(particles, i);
      energy += ENERGY_EARNED_BY_EATING_PARTICLE;
      switch (level)
      {
        case EASY :
        score += SCORE_EARNED_BY_EATING_PARTICLE_EASY;
        break;
        case NORMAL :
        score += SCORE_EARNED_BY_EATING_PARTICLE_NORMAL;
        break;
        case HARD :
        score += SCORE_EARNED_BY_EATING_PARTICLE_HARD;
        break;
      }
    }
  }
}
int calculate_distance(float x1, float y1, float x2, float y2)
{
  return sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
}
int standarding_angle(int angle)
{
  return angle + 90;
}
bool eating_drone(vector<Diamond> diamonds, Drone drone)
{
  for (unsigned int i = 0; i < diamonds.size(); i++)
    if(check_eated_by_diamond(diamonds[i], drone))
      return true;
  return false;
}
bool check_eated_by_diamond(Diamond diamond, Drone drone)
{
  if (diamond.x > drone.x && diamond.x < drone.x + drone.width && diamond.y > drone.y && diamond.y < drone.y + drone.height)
    return true;
  return false;
}
bool check_finish_game(vector<Particle>& particles, vector<Shot>& shots, vector<Diamond>& diamonds, Drone drone, int& lives, int& energy, window& w, int score, bool& quit_flag)
{
  if (eating_drone(diamonds, drone))
  {
    lives--;
    remove_all_particles(particles);
    remove_all_shots(shots);
    remove_all_diamonds(diamonds);
    energy = 0;
    if (lives != 0)
      show_ready_before_starting(w, quit_flag, score, energy, lives);
  }
  if(lives == 0)
    return true;
  return false;
}
string int_to_string(int input)
{
  if (input == 0)
    return string("0");
  char temp[10];
  int i;
  for (i = 0; input != 0; i++)
  {
    temp[i] = input % 10 + 48;
    input = input / 10;
  }
  char inverted[10];
  for(int j = i - 1;j >= 0; j--)
  {
    inverted[j] = temp[i - 1 - j];
  }
  inverted[i] = '\0';
  return string(inverted);
}
void show_score(window& w, int score)
{
  w.fill_rect(SCORE_BOX_STARTING_X, SCORE_BOX_STARTING_Y, BOX_DURING_GAME_WIDTH, BOX_DURING_GAME_HEIGHT, BOX_DURING_GAME_COLOR);
  w.show_text("score: " + int_to_string(score), SCORE_STARTING_X, SCORE_STARTING_Y, TEXT_DURING_GAME_COLOR, FONT_NAME, TEXT_DURING_GAME_SIZE);
}
void show_energy(window& w, int energy)
{
  if (energy < 200)
    w.fill_rect(ENERGY_BOX_STARTING_X, ENERGY_BOX_STARTING_Y, BOX_DURING_GAME_WIDTH, BOX_DURING_GAME_HEIGHT, BOX_DURING_GAME_COLOR);
  else
    w.fill_rect(ENERGY_BOX_STARTING_X, ENERGY_BOX_STARTING_Y, BOX_DURING_GAME_WIDTH, BOX_DURING_GAME_HEIGHT, RED);
  w.show_text("energy: " + int_to_string(energy), ENERGY_STARTING_X, ENERGY_STARTING_Y, TEXT_DURING_GAME_COLOR, FONT_NAME, TEXT_DURING_GAME_SIZE);
}
void show_lives(window& w, int lives)
{
  w.fill_rect(LIVES_BOX_STARTING_X, LIVES_BOX_STARTING_Y, BOX_DURING_GAME_WIDTH, BOX_DURING_GAME_HEIGHT, BOX_DURING_GAME_COLOR);
  w.show_text("lives: " + int_to_string(lives), LIVES_STARTING_X, LIVES_STARTING_Y, TEXT_DURING_GAME_COLOR, FONT_NAME, TEXT_DURING_GAME_SIZE);
}
void show_on_screen_during_game(window& w, Drone drone, vector<Diamond> diamonds, vector<Particle> particles, vector<Shot> shots, int score, int energy, int lives)
{
  w.draw_bg(BACKGROUND_PICTURE_NAME);
  show_drone(w, drone);
  show_shots(w, shots);
  show_diamonds(w, diamonds);
  show_particles(w, particles);
  show_lives(w, lives);
  show_score(w, score);
  show_energy(w, energy);
}
void move_things(Drone& drone, vector<Diamond>& diamonds, vector<Shot>& shots , vector<Particle>& particles, int x_mouse_location, int y_mouse_location)
{
  move_drone(drone, x_mouse_location, y_mouse_location);
  move_shots(shots);
  move_particles(particles, drone);
  move_diamonds(diamonds, drone);
}
bool check_things(Drone& drone,vector<Diamond>& diamonds,vector<Shot>& shots,vector<Particle>& particles, int& score, int& energy, int& lives, int& level, window& w,bool& quit_flag)
{
  check_particles_around_drone(particles, drone);
  check_shots_out_of_range(shots);
  check_particles_left_time(particles);
  eating_particles(particles, drone, score, energy, level);
  impact_shots_and_diamonds(shots, diamonds, particles, energy, score, level);
  creating_diamond_function(diamonds, drone, level, score);
  if (check_finish_game(particles, shots, diamonds, drone, lives, energy, w, score, quit_flag))
    return true;
  pause(w, quit_flag, score, energy, lives);
  return false;
}
void process_rsdl_keyboard(char input, bool& quit_flag, Drone& drone, vector<Shot>& shots, vector<Diamond>& diamonds, int& energy, int& score, int level)
{
  switch(input)
  {
    case 's' :
    change_drone_to_super(drone);
    break;
    case 'n' :
    change_drone_to_normal(drone);
    break;
    case 'b' :
    anti_diamond_bomb(diamonds, energy, score, level);
  }
}
void do_rsdl(Event event,bool& quit_flag,Drone& drone,vector<Shot>& shots,vector<Diamond>& diamonds, int& energy, int& score, int level, int& x_mouse_location,int& y_mouse_location)
{
  if(event.type() == KEY_PRESS)
    process_rsdl_keyboard(event.pressedKey(), quit_flag, drone, shots, diamonds, energy, score, level);
  else if(event.type() == LCLICK)
    shoot(drone, shots, energy);
  else if(event.type() == QUIT)
    quit_flag = true;
  if (event.mouseX() != -1)
    x_mouse_location = event.mouseX();
  if (event.mouseY() != -1)
    y_mouse_location = event.mouseY();
}
void show_ready_before_starting(window& w, bool& quit_flag, int score, int energy, int lives)
{
  Event event = w.pollForEvent();
  while (event.type() != KEY_PRESS)
  {
    if (event.type() == QUIT)
    {
      quit_flag = true;
      break;
    }
    if (event.type() == LCLICK)
      break;
    event = w.pollForEvent();
    w.draw_bg(MENU_BACKGROUND_PICTURE_NAME);
    w.show_text("READY?", READY_X, READY_Y, READY_COLOR, FONT_NAME, READY_SIZE);
    show_score(w, score);
    show_energy(w, energy);
    show_lives(w, lives);
    w.update_screen();
    Delay(20);
  }
}
int power(int a, int b)
{
  int result = 1;
  for (int i = 0; i < b; i++)
    result *= a;
  return result;
}
int string_to_int(string input)
{
  char c;
  int result = 0;
  for (unsigned int i = 0; i < input.size(); i++)
  {
    c = input[i];
    result += ((int)c - 48) * power(10, input.size() - 1 - i);
  }
  return result;
}

Box create_box(int id, int x, int y, string name, int page)
{
  Box temp;
  temp.id = id;
  temp.x = x;
  temp.x_string = x + 50;
  temp.y = y;
  temp.y_string = y + 12;
  temp.name = name;
  temp.page = page;
  return temp;
}
Page create_page(int id, vector<Box> boxes)
{
  Page temp;
  temp.id = id;
  temp.boxes = boxes;
  return temp;
}
vector<Page> create_pages()
{
  vector<Page> temp;
  vector<Box> result;
  result.push_back(create_box(NEW_GAME, BOX_X, NEW_GAME_Y, "NEW GAME", MAIN_PAGE));
  result.push_back(create_box(LEADERBOARD, BOX_X, LEADERBOARD_Y, "LEADERBOARD", MAIN_PAGE));
  result.push_back(create_box(EXIT, BOX_X, EXIT_Y, "EXIT", MAIN_PAGE));
  vector<Box> result2;
  result2.push_back(create_box(EASY_BUTTON, BOX_X, EASY_BUTTON_Y, "EASY", CHOOSE_DIFFICULTY_PAGE));
  result2.push_back(create_box(NORMAL_BUTTON, BOX_X, NORMAL_BUTTON_Y, "NORMAL", CHOOSE_DIFFICULTY_PAGE));
  result2.push_back(create_box(HARD_BUTTON, BOX_X, HARD_BUTTON_Y, "HARD", CHOOSE_DIFFICULTY_PAGE));
  result2.push_back(create_box(BACK_BUTTON, BOX_X, BACK_BUTTON_Y, "BACK", CHOOSE_DIFFICULTY_PAGE));
  vector<Box> result3;
  result3.push_back(create_box(BACK_BUTTON, BOX_X, BACK_BUTTON_Y, "BACK", LEADERBOARD_PAGE));
  temp.push_back(create_page(MAIN_PAGE, result));
  temp.push_back(create_page(CHOOSE_DIFFICULTY_PAGE, result2));
  temp.push_back(create_page(LEADERBOARD_PAGE, result3));
  return temp;
}
void show_boxes(window& w, Page current_page, Box selected_box)
{
  for (unsigned int i = 0; i < current_page.boxes.size(); i++)
  {
    if (current_page.boxes[i].id != selected_box.id)
    {
      w.fill_rect(current_page.boxes[i].x, current_page.boxes[i].y, BOX_WIDTH, BOX_HEIGHT, DEFAULT_BOX_COLOR_MENU);
      w.show_text(current_page.boxes[i].name, current_page.boxes[i].x_string, current_page.boxes[i].y_string, WHITE, FONT_NAME, 30);
    }
    else
    {
      w.fill_rect(current_page.boxes[i].x, current_page.boxes[i].y, BOX_WIDTH, BOX_HEIGHT, SELECTED_BOX_COLOR_MENU);
      w.show_text(current_page.boxes[i].name, current_page.boxes[i].x_string, current_page.boxes[i].y_string, WHITE, FONT_NAME, 30);
    }
  }
}
bool process_boxes_on_menu(vector<Box>& boxes, char input, Box& selected_box)
{
  if (input == ENTER)
    return true;
  unsigned int i = 0;
  for (i = 0; i < boxes.size(); i++)
  {
    if (boxes[i].id == selected_box.id)
      break;
  }
  if (input == 's')
  {
    if (i == boxes.size() - 1)
      return false;
    selected_box = boxes[i + 1];
  }
  if (input == 'w')
  {
    if (i == 0)
      return false;
    selected_box = boxes[i - 1];
  }
  return false;
}
void show_leaderboard(window& w, vector<Person> persons)
{
  w.draw_line(HORIZONTAL_LINE_X, FIRST_WORD_Y, HORIZONTAL_LINE_X + HORIZONTAL_LINE_WIDTH, FIRST_WORD_Y, LINES_COLOR);

  w.draw_line(HORIZONTAL_LINE_X, FIRST_WORD_Y, HORIZONTAL_LINE_X, FIRST_WORD_Y + VERTICAL_LINE_HEIGHT, LINES_COLOR);
  w.show_text("NAME", STARTING_NAMES_LEADERBOARD_X, FIRST_WORD_Y + MARGIN_WORDS_Y, TEXT_LEADERBOARD_COLOR, FONT_NAME, TEXT_LEADERBOARD_SIZE);
  w.draw_line(VERTICAL_LINE_X, FIRST_WORD_Y, VERTICAL_LINE_X, FIRST_WORD_Y + VERTICAL_LINE_HEIGHT, LINES_COLOR);
  w.show_text("SCORE", STARTING_SCORE_LEADERBOARD_X, FIRST_WORD_Y + MARGIN_WORDS_Y, TEXT_LEADERBOARD_COLOR, FONT_NAME, TEXT_LEADERBOARD_SIZE);
  w.draw_line(HORIZONTAL_LINE_X + HORIZONTAL_LINE_WIDTH, FIRST_WORD_Y, HORIZONTAL_LINE_X + HORIZONTAL_LINE_WIDTH, FIRST_WORD_Y + VERTICAL_LINE_HEIGHT, LINES_COLOR);
  w.draw_line(HORIZONTAL_LINE_X, FIRST_WORD_Y + VERTICAL_LINE_HEIGHT, HORIZONTAL_LINE_X + HORIZONTAL_LINE_WIDTH, FIRST_WORD_Y + VERTICAL_LINE_HEIGHT, LINES_COLOR);
  for (unsigned int i = 0; i < persons.size(); i++)
  {
    w.draw_line(HORIZONTAL_LINE_X, (i + 1) * VERTICAL_LINE_HEIGHT + FIRST_WORD_Y, HORIZONTAL_LINE_X, (i + 2) * VERTICAL_LINE_HEIGHT + FIRST_WORD_Y, LINES_COLOR);
    w.show_text(persons[i].name, STARTING_NAMES_LEADERBOARD_X,(i + 1) * VERTICAL_LINE_HEIGHT + FIRST_WORD_Y + MARGIN_WORDS_Y, TEXT_LEADERBOARD_COLOR, FONT_NAME, TEXT_LEADERBOARD_SIZE);
    w.draw_line(VERTICAL_LINE_X, (i + 1) * VERTICAL_LINE_HEIGHT + FIRST_WORD_Y, VERTICAL_LINE_X, (i + 2) * VERTICAL_LINE_HEIGHT + FIRST_WORD_Y, LINES_COLOR);
    w.show_text(int_to_string(persons[i].score), STARTING_SCORE_LEADERBOARD_X, (i + 1) * VERTICAL_LINE_HEIGHT + FIRST_WORD_Y + MARGIN_WORDS_Y, TEXT_LEADERBOARD_COLOR, FONT_NAME, TEXT_LEADERBOARD_SIZE);
    w.draw_line(HORIZONTAL_LINE_X + HORIZONTAL_LINE_WIDTH, (i + 1) * VERTICAL_LINE_HEIGHT + FIRST_WORD_Y, HORIZONTAL_LINE_X + HORIZONTAL_LINE_WIDTH, (i + 2) * VERTICAL_LINE_HEIGHT + FIRST_WORD_Y, LINES_COLOR);
    w.draw_line(HORIZONTAL_LINE_X, (i + 2) * VERTICAL_LINE_HEIGHT + FIRST_WORD_Y, HORIZONTAL_LINE_X + HORIZONTAL_LINE_WIDTH, (i + 2) * VERTICAL_LINE_HEIGHT + FIRST_WORD_Y, LINES_COLOR);
  }
}
vector<Person> load()
{
  ifstream myfile;
  myfile.open(SAVED_NAMES);
  string s;
  Person temp;
  vector<Person> result;
  string change;
  while(getline(myfile, s))
  {
    istringstream iss(s);
    iss >> temp.name;
    iss >> change;
    temp.score = string_to_int(change);
    result.push_back(temp);
  }
  while (result.size() > MAX_NUM_OF_SAVING)
    result.pop_back();
  myfile.close();
  return result;
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
void process_rsdl_input(window& win, bool& done, string& input_string, bool& quit_flag)
{
  Event event = win.pollForEvent();
  if (event.type() == QUIT)
    quit_flag = true;
  else if(event.type() == KEY_PRESS)
  {
    if(event.pressedKey() == BACK_SPACE)
      erase_last_char(input_string);
    else
    {
      if(event.pressedKey() == ENTER)
      	done = true;
      else
        add_char(input_string, event.pressedKey());
    }
  }
}
bool save(window& w, int score, vector<Person>& persons, bool& quit_flag)
{
  if (persons[persons.size() - 1].score > score && persons.size() == MAX_NUM_OF_SAVING)
    return false;
  bool done = false;
  string input_string = "";
  while (!quit_flag)
  {
    w.draw_bg(BACKGROUND_PICTURE_NAME);
    process_rsdl_input(w, done, input_string, quit_flag);
    w.fill_rect(SAVE_BOX_X, SAVE_BOX_Y, SAVE_BOX_WIDTH, SAVE_BOX_HEIGHT, SAVE_BOX_COLOR);
    w.show_text(prepare_output_text(input_string), SAVE_BOX_X + MARGIN_WORDS_X, SAVE_BOX_Y + MARGIN_WORDS_Y, SAVE_TEXT_COLOR, FONT_NAME, SAVE_TEXT_SIZE);
    if (done)
      break;
    w.update_screen();
    Delay(MENU_TICK_DURATION);
  }
  unsigned int i = 0;
  for (i = 0; i < persons.size(); i++)
    if (persons[i].score < score)
      break;
  Person temp;
  temp.name = input_string;
  temp.score = score;
  persons.insert(persons.begin() + i, temp);
  if (persons.size() > 5)
  persons.pop_back();
  ofstream myfile;
  myfile.open(SAVED_NAMES);
  for (unsigned int i = 0; i < persons.size(); i++)
  {
    myfile << persons[i].name << " " << persons[i].score << endl;
  }
  myfile.close();
  return true;
}
void pause(window& w, bool& quit_flag, int score, int energy, int lives)
{
  Event event = w.pollForEvent();
  if (event.type() == KEY_PRESS)
    if (event.pressedKey() == PAUSE_BUTTON)
      show_ready_before_starting(w, quit_flag, score, energy, lives);
}
