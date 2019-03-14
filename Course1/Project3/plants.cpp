#include <vector>
#include "rsdl.hpp"
#include <string>

using namespace std;

#define CARD_LENGTH 85
#define CARD_WIDTH 62
#define X_FIRST_CARD 100
#define Y_FIRST_CARD 5
#define CARD_DISTANCE 5

#define LEFT_YARD 200
#define RIGHT_YARD 760
#define UP_YARD 70
#define DOWN_YARD 540

#define CELL_WIDTH 62
#define CELL_LENGTH 94

#define PEASHOOTER 1
#define SUNFLOWER 2
#define WALLNUT 3
#define CRACKED1_WALLNUT 4
#define CRACKED2_WALLNUT 5

#define SUN_DIAMETER 70
#define SUNCENTER_DIAMETER 20

#define plants_sun_time 10000000
#define SUNFLOWER_SUN_TIME 25000
#define SUN_STAYING_TIME 5000

#define MYDELAY 20

#define PEA_SPEED 200 //it means 200 cordinate pixels per second.
#define ZOMBIE_SPEED 13
#define SUN_SPEED 50

struct peas
{
  int x_cordinate;
  int row;
};
struct plants
{
  int plant;
  int health;
  int row;
  int col;
  int sun_left_time;
  int pea_left_time;
  int cost;
};
struct zombies
{
  int row;
  float x_cordinate;
  int health;
  int bite_time;
};
struct suns
{
  int col;
  int y_final;
  int y_cordinate;
  int time_left;
};

float absolute(float);
int absolute(int);
void showing_main_picture(window& ,int);
void showing_peashooter(window& ,int ,int);
void showing_sunflower(window& ,int ,int);
void showing_wallnut(window& ,int ,int ,int);
void showing_and_moving_pea(window& ,int ,int&);
void creat_peashooter();
int detect_plant(int ,int);
int saving_plants(bool& ,int& ,int& ,int ,vector<vector<int> >& ,vector<plants>& ,int&);
void creating_pea(window& ,vector<plants>& ,vector<peas>& ,vector<zombies>);
void checking_pea_area(vector<peas>&);
void create_one_zombie(int ,vector<zombies>&);
void showing_all_zombies(window& ,vector<zombies>);
void moving_all_zombies(vector<zombies>& ,vector<vector<int> >);
void checking_pea_hit_zombie(vector<peas>& ,vector<zombies>&);
bool checking_end_game(vector<zombies>);
void eating_plants(vector<zombies>& ,vector<plants>& ,vector<vector<int> >&);
void creating_zombie_function(vector<zombies>& ,int&);
int create_normal_sun(vector<suns>& ,int&);
void create_sunflower_sun(vector<plants>& ,vector<suns>&);
void moving_normal_suns(vector<suns>&);
void deleting_long_suns(vector<suns>&);
void collecting_suns(vector<suns>& ,int ,int ,int&);
void showing_all_suns(window& ,vector<suns>);
void erase_plant(int ,int ,vector<vector<int> >& ,vector<plants>& ,bool& ,bool&);
void selected_plant_shovel(window& ,bool ,int ,bool);

int main()
{
  window main_window(800 ,600);
  vector<vector<int> > yard(5 ,vector<int>(9 ,0));
  vector<plants> plant_details(45);
  vector<peas> all_peas;
  vector<zombies> all_zombies;
  vector<suns> all_suns;
  int selected_plant = 0; //zero is for the times that no plants is selected.
  bool any_plant_selected = false;
  bool shovel_select = false;
  int x_mouse = 0 ,y_mouse = 0;
  int row_number = 0 ,col_number = 0;
  int sun_point = 1000;
  int zombie_left_time = 0;
  int sun_left_time = 4000;
  int number_of_peashooter = 0;
  int number_of_sunflower = 0;
  int number_of_wallnut = 0;
  int number_of_cracked1_wallnut = 0;
  int number_of_cracked2_wallnut = 0;
  while(true) //starting page
  {
    main_window.draw_png("Start.png" ,0 ,0 ,800 ,600);
    HANDLE(
      QUIT({return 0;})
      LCLICK({
        x_mouse = mouse_x;
        y_mouse = mouse_y;
      })
    )
    if (x_mouse > 240 && x_mouse < 550 && y_mouse > 530 && y_mouse < 575)
      break;
    main_window.update_screen();
    DELAY(100);
  }
  x_mouse = 0;
  y_mouse = 0;
  while (true)
  {
    showing_main_picture(main_window ,sun_point);
    HANDLE(
      QUIT({return 0;})
      LCLICK(
      {
        x_mouse = mouse_x;
        y_mouse = mouse_y;
      })
      KEY_PRESS(d ,{
        shovel_select = true;
      })
    )
    if (x_mouse < RIGHT_YARD && x_mouse > LEFT_YARD && y_mouse < DOWN_YARD && y_mouse > UP_YARD) // clicked at the yard.
    {
      row_number = (y_mouse - UP_YARD) / CELL_LENGTH + 1;
      col_number = (x_mouse - LEFT_YARD) / CELL_WIDTH + 1;
      // cout << "mouse clicked at row number :" << row_number << " and col number :" << col_number << endl;
    }
    else if (y_mouse > Y_FIRST_CARD && y_mouse < Y_FIRST_CARD + CARD_LENGTH && x_mouse > X_FIRST_CARD && x_mouse < X_FIRST_CARD + 3 * CARD_WIDTH + 2 * CARD_DISTANCE) // clicked at the cards regin
    {
      any_plant_selected = true;
      selected_plant = detect_plant(x_mouse ,y_mouse);
      shovel_select = false;
      row_number = 0;
      col_number = 0;
      // cout << "plant " << selected_plant << " is selected." << endl;
    }
    erase_plant(row_number ,col_number ,yard ,plant_details ,shovel_select ,any_plant_selected);
    saving_plants(any_plant_selected ,row_number ,col_number ,selected_plant ,yard ,plant_details ,sun_point);
    for (int i = 0 ;i < 5 ;i++) //this for will help in having all of the plants showed on the screen.
      for(int j = 0 ;j < 9 ;j++)
      {
        if(yard[i][j] == PEASHOOTER)
          showing_peashooter(main_window ,i + 1 ,j + 1);
        if(yard[i][j] == SUNFLOWER)
          showing_sunflower(main_window ,i + 1 ,j + 1);
        if(yard[i][j] == WALLNUT)
          showing_wallnut(main_window ,i + 1 ,j + 1 ,0);
        if(yard[i][j] == CRACKED1_WALLNUT)
          showing_wallnut(main_window ,i + 1 ,j + 1 ,1);
        if(yard[i][j] == CRACKED2_WALLNUT)
          showing_wallnut(main_window ,i + 1 ,j + 1 ,2);
      }
    creating_pea(main_window ,plant_details ,all_peas ,all_zombies);
    checking_pea_area(all_peas);
    for (int i = 0 ;i < all_peas.size() ;i++)
      showing_and_moving_pea(main_window ,all_peas[i].row ,all_peas[i].x_cordinate);
    moving_all_zombies(all_zombies ,yard);
    showing_all_zombies(main_window ,all_zombies);
    checking_pea_hit_zombie(all_peas ,all_zombies);
    eating_plants(all_zombies ,plant_details ,yard);
    creating_zombie_function(all_zombies ,zombie_left_time);
    create_normal_sun(all_suns ,sun_left_time);
    create_sunflower_sun(plant_details ,all_suns);
    deleting_long_suns(all_suns);
    moving_normal_suns(all_suns);
    showing_all_suns(main_window ,all_suns);
    collecting_suns(all_suns ,x_mouse ,y_mouse ,sun_point);
    selected_plant_shovel(main_window ,any_plant_selected ,selected_plant ,shovel_select);
    main_window.update_screen();
    if(checking_end_game(all_zombies)){break;}
    DELAY(MYDELAY);
  }
    x_mouse = 0;
    y_mouse = 0;
    while(true)
    {
      HANDLE(
        QUIT({return 0;})
      )
      main_window.draw_png("Gameover.png" ,200 ,150 ,400 ,200);
      main_window.update_screen();
    }
  }


float absolute(float x)
{
  if (x < 0)
    return x * (-1);
  return x;
}
int absolute(int x)
{
  if (x < 0)
    return x * (-1);
  return x;
}
void showing_main_picture(window& w ,int points)
{
  w.draw_png("frontyard.png" ,0 ,0 ,800 ,600);
  w.draw_png("Sun1.png" ,20 ,20 ,25 ,25);
  w.draw_png("Sun2.png" ,0 ,0 ,75 ,75);
  w.draw_png("peashooter_card.png" ,X_FIRST_CARD ,Y_FIRST_CARD ,CARD_WIDTH ,CARD_LENGTH);
  w.draw_png("sunflower_card.png" ,X_FIRST_CARD + CARD_WIDTH + 5 ,Y_FIRST_CARD ,CARD_WIDTH ,CARD_LENGTH);
  w.draw_png("wallnut_card.png" ,X_FIRST_CARD + 2 * CARD_WIDTH + 2 * 5 ,Y_FIRST_CARD ,CARD_WIDTH ,CARD_LENGTH);
  w.draw_png("Shovel.png" ,700 ,0 ,CARD_WIDTH ,CARD_LENGTH);
}
void showing_peashooter(window& w ,int row ,int col)
{
  int x_cordinate = LEFT_YARD + (col - 1) * CELL_WIDTH;
  int y_cordinate = UP_YARD + (row - 1) * CELL_LENGTH;
  w.draw_png("peashooter.png" ,x_cordinate ,y_cordinate ,CELL_WIDTH ,84);
}
void showing_sunflower(window& w ,int row ,int col)
{
  int x_cordinate = LEFT_YARD + (col - 1) * CELL_WIDTH;
  int y_cordinate = UP_YARD + (row - 1) * CELL_LENGTH;
  w.draw_png("Sunflower.png" ,x_cordinate ,y_cordinate ,CELL_WIDTH ,84);
}
void showing_wallnut(window& w ,int row ,int col ,int damage)
{
  int x_cordinate = LEFT_YARD + (col - 1) * CELL_WIDTH;
  int y_cordinate = UP_YARD + (row - 1) * CELL_LENGTH;
  if (damage == 0)
  w.draw_png("Wallnut_body.png" ,x_cordinate ,y_cordinate + 5 ,CELL_WIDTH ,74);
  else if(damage == 1)
  w.draw_png("Wallnut_cracked1.png" ,x_cordinate ,y_cordinate + 5 ,CELL_WIDTH ,74);
  else if(damage == 2)
  w.draw_png("Wallnut_cracked2.png" ,x_cordinate ,y_cordinate + 5 ,CELL_WIDTH ,74);
}
int detect_plant(int x ,int y)
{
  if(y > Y_FIRST_CARD && y < Y_FIRST_CARD + CARD_LENGTH)
  {
    if(x > X_FIRST_CARD && x < X_FIRST_CARD + CARD_WIDTH)
      return PEASHOOTER;
    else if(x > X_FIRST_CARD + CARD_WIDTH + CARD_DISTANCE && x < X_FIRST_CARD + 2 * CARD_WIDTH + CARD_DISTANCE)
      return SUNFLOWER;
    else if(x > X_FIRST_CARD + 2 * CARD_WIDTH + 2 * CARD_DISTANCE && x < X_FIRST_CARD + 3 * CARD_WIDTH + 2 * CARD_DISTANCE)
      return WALLNUT;
    else
      return 0;
  }
  else
    return 0;
}
int saving_plants(bool& is_selected ,int& row ,int& col ,int selected_plant ,vector<vector<int> >& yard ,vector<plants>& stuff ,int& points)
{
  switch(selected_plant)
  {
    case PEASHOOTER :
      stuff[(row - 1) * 9 + col - 1].cost = 100;
      break;
    case SUNFLOWER :
      stuff[(row - 1) * 9 + col - 1].cost = 50;
      break;
    case WALLNUT :
      stuff[(row - 1) * 9 + col - 1].cost = 50;
      break;
  }
  if(stuff[(row - 1) * 9 + col - 1].cost > points )
  {
    is_selected = false;
    return 0;
  }
  if(is_selected == true && row != 0 &&  col != 0 && yard[row - 1][col - 1] != 0)
    is_selected = false;
  if(is_selected == true && row != 0 &&  col != 0 && yard[row - 1][col - 1] == 0)
  {
      yard[row - 1][col - 1] = selected_plant;
      // cout << "plant is saved at (" << row << "," << col << ")" << endl;
      is_selected = false;
    stuff[(row - 1) * 9 + col - 1].plant = selected_plant;
    stuff[(row - 1) * 9 + col - 1].row = row;
    stuff[(row - 1) * 9 + col - 1].col = col;
    switch(selected_plant)
    {
      case PEASHOOTER :
        stuff[(row - 1) * 9 + col - 1].health = 5;
        stuff[(row - 1) * 9 + col - 1].cost = 100;
        stuff[(row - 1) * 9 + col - 1].sun_left_time = plants_sun_time;
        stuff[(row - 1) * 9 + col - 1].pea_left_time = 1500;
        break;
      case SUNFLOWER :
        stuff[(row - 1) * 9 + col - 1].health = 5;
        stuff[(row - 1) * 9 + col - 1].cost = 50;
        stuff[(row - 1) * 9 + col - 1].sun_left_time = SUNFLOWER_SUN_TIME;
        break;
      case WALLNUT :
        stuff[(row - 1) * 9 + col - 1].health = 24;
        stuff[(row - 1) * 9 + col - 1].cost = 50;
        stuff[(row - 1) * 9 + col - 1].sun_left_time = plants_sun_time;
        break;
    }
    points -= stuff[(row - 1) * 9 + col - 1].cost;
    row = 0;
    col = 0;
    cout << points << endl;
  }
}
void showing_and_moving_pea(window& w ,int row ,int& x_cordinate)
{
  int y_cordinate = UP_YARD + (row - 1) * CELL_LENGTH + 15;
  x_cordinate += PEA_SPEED / (1000 / MYDELAY);
  w.draw_png("pea.png" ,x_cordinate ,y_cordinate ,20 ,20);
}
void creating_pea(window& w ,vector<plants>& shooter ,vector<peas>& pea ,vector<zombies> zombielist)
{
  bool flag[5];
  for (int i = 0 ;i < 6 ;i++)
    flag[i] = false;
  for (int i = 0 ;i < zombielist.size() ;i++)
  {
    if (zombielist[i].row == 1){flag[1] = true;}
    else if (zombielist[i].row == 2){flag[2] = true;}
    else if (zombielist[i].row == 3){flag[3] = true;}
    else if (zombielist[i].row == 4){flag[4] = true;}
    else if (zombielist[i].row == 5){flag[5] = true;}
  }
  for(int i = 0 ;i < 45 ;i++)
  {
    if(flag[shooter[i].row])
    {
      if (shooter[i].plant == PEASHOOTER)
      {
        if (shooter[i].pea_left_time == 0)
        {
          shooter[i].pea_left_time = 1500;
          peas temp;
          temp.row = shooter[i].row;
          temp.x_cordinate = LEFT_YARD + (shooter[i].col - 1) * CELL_WIDTH + 30;
          int y_cordinate = UP_YARD + (temp.row - 1) * CELL_LENGTH + 15;
          pea.push_back(temp);
        }
        shooter[i].pea_left_time -= MYDELAY;
      }
    }
  }
  bool zombie_infront = false;
  if (pea.size() != 0)
  {
    for (int i = 0 ;i < zombielist.size() ; i++)
    {
      if (pea[pea.size() - 1].row == zombielist[i].row && pea[pea.size() - 1].x_cordinate < zombielist[i].x_cordinate)
      {
        zombie_infront = true;
        break;
      }
    }
  if (zombie_infront == false)
    pea.pop_back();
  }
}
void checking_pea_area(vector<peas>& peas)
{
  for(int i = 0 ;i < peas.size() ;i++)
    if (peas[i].x_cordinate >= 800)
      peas.erase(peas.begin() + i);
}
void create_one_zombie(int row ,vector<zombies>& zombielist)
{
   zombies temp;
   temp.row = row;
   temp.x_cordinate = 780;
   temp.health = 12;
   temp.bite_time = 1000;
   zombielist.push_back(temp);
}
void showing_all_zombies(window& w ,vector<zombies> zombielist)
{
  int y_cordinate;
  for(int i = 0 ;i < zombielist.size() ;i++)
  {
    y_cordinate = UP_YARD + (zombielist[i].row - 1) * CELL_LENGTH - 10;
    w.draw_png("Zombie.png" ,zombielist[i].x_cordinate ,y_cordinate - 10 ,CELL_WIDTH + 10 ,CELL_LENGTH + 15);
  }
}
void moving_all_zombies(vector<zombies>& zombielist ,vector<vector<int> > plantexist)
{
  int col = 0;
  for (int i = 0 ;i < zombielist.size() ;i++)
  {
    col = (zombielist[i].x_cordinate - LEFT_YARD) / CELL_WIDTH + 1;
    if (plantexist[zombielist[i].row - 1][col - 1] == 0)//if there was no plant in the way of the zombie.
      zombielist[i].x_cordinate -= float(ZOMBIE_SPEED) * float(MYDELAY) / 1000;
  }
}
void checking_pea_hit_zombie(vector<peas>& pealist ,vector<zombies>& zombielist)
{
  for (int i = 0 ;i < pealist.size() ;i++)
  {
    for (int j = 0 ;j < zombielist.size() ;j++)
    {
      if ((pealist[i].row == zombielist[j].row) && (absolute(zombielist[j].x_cordinate - pealist[i].x_cordinate) < 5))
      {
        pealist.erase(pealist.begin() + i);
        if (zombielist[j].health > 1)
          zombielist[j].health--;
        else
          zombielist.erase(zombielist.begin() + j);
        break;
      }
    }
  }
}
bool checking_end_game(vector<zombies> zombielist)
{
  for (int i = 0 ;i < zombielist.size() ;i++)
    if (zombielist[i].x_cordinate < LEFT_YARD - 50)
      return true;
  return false;
}
void eating_plants(vector<zombies>& zombielist ,vector<plants>& plantlist ,vector<vector<int> >& plantexist)
{
  int zombie_col = 0;
  for (int i = 0 ;i < zombielist.size() ;i++)//checking all of the zombies.
  {
    zombie_col = ((zombielist[i].x_cordinate - LEFT_YARD) / CELL_WIDTH) + 1;// finding out what col is this zombie in.
    if (plantexist[zombielist[i].row - 1][zombie_col - 1] != 0)// checking if there is any plant in front of that or not.
    {
      if (zombielist[i].bite_time > 0)// checking if the zombie can bite or not(can not bite)
      {
        zombielist[i].bite_time -= MYDELAY;
      }
      else// the zombie can bite.
      {
        zombielist[i].bite_time = 1000;//making it wait for the next bite again.
        if (plantlist[(zombielist[i].row - 1) * 9 + zombie_col - 1].plant == PEASHOOTER || plantlist[(zombielist[i].row - 1) * 9 + zombie_col - 1].plant == SUNFLOWER || plantlist[(zombielist[i].row - 1) * 9 + zombie_col - 1].plant == CRACKED2_WALLNUT)
        //checking if the plant in front of the zombie is peashooter , sunflower or the second cracked wallnut.
        {
          if (plantlist[(zombielist[i].row - 1) * 9 + zombie_col - 1].health == 1) // checking if the plant is supposed to die or not.(supposed to die)
          {
            plantlist[(zombielist[i].row - 1) * 9 + zombie_col - 1].plant = 0;
            plantexist[zombielist[i].row - 1][zombie_col - 1] = 0;
          }
          else// supposed to live.
            plantlist[(zombielist[i].row - 1) * 9 + zombie_col - 1].health --;
        }
        else if (plantlist[(zombielist[i].row - 1) * 9 + zombie_col - 1].plant == WALLNUT)// checking if the plant in front of the zombie is wallnut
        {
          if (plantlist[(zombielist[i].row - 1) * 9 + zombie_col - 1].health == 1) // checking if the wallnut is supposed to change or not.
          {
            plantexist[zombielist[i].row - 1][zombie_col - 1] = CRACKED1_WALLNUT;
            plantlist[(zombielist[i].row - 1) * 9 + zombie_col - 1].plant = CRACKED1_WALLNUT;
            plantlist[(zombielist[i].row - 1) * 9 + zombie_col - 1].health = 24;
          }
          else//supposed to live
            plantlist[(zombielist[i].row - 1) * 9 + zombie_col - 1].health--;
        }
        else if (plantlist[(zombielist[i].row - 1) * 9 + zombie_col - 1].plant == CRACKED1_WALLNUT)// checking if the plant in front of the zombie is first cracked wallnut
        {
          if (plantlist[(zombielist[i].row - 1) * 9 + zombie_col - 1].health == 1) // checking if the plant is supposed to change or not.
          {
            plantexist[zombielist[i].row - 1][zombie_col - 1] = CRACKED2_WALLNUT;
            plantlist[(zombielist[i].row - 1) * 9 + zombie_col - 1].plant = CRACKED2_WALLNUT;
            plantlist[(zombielist[i].row - 1) * 9 + zombie_col - 1].health = 24;
          }
          else//supposed to live
            plantlist[(zombielist[i].row - 1) * 9 + zombie_col - 1].health--;
        }
      }
    }
  }
}
void creating_zombie_function(vector<zombies>& zombielist,int& left_time)
{
  int number_of_entered_zombies = 0;
  if(left_time <= 0)
  {
    left_time = 15000;
    number_of_entered_zombies = rand() % 5 + 1;
    for (int i = 0 ;i < number_of_entered_zombies ;i++)
      create_one_zombie(rand() % 5 + 1 ,zombielist);
  }
  else
    left_time -= MYDELAY;
}
int create_normal_sun(vector<suns>& sunlist ,int& sun_left_time)
{
  bool flag = false;
  if (sun_left_time > 0)
  {
    sun_left_time -= MYDELAY;
    return 0;
  }
  sun_left_time = 4000 + (rand() % 4000);
  suns temp;
  while(true)
  {
    flag = false;
    temp.col = rand() % 9 + 1;
    temp.y_cordinate = 0;
    temp.y_final = UP_YARD + (rand() % (5 * CELL_LENGTH));
    temp.time_left = SUN_STAYING_TIME;
    for (int i = 0 ;i < sunlist.size() ;i++)
    {
      if (temp.col == sunlist[i].col && absolute(temp.y_final - sunlist[i].y_final) < SUN_DIAMETER)
      {
        flag = true;
        break;
      }
    }
    if (flag == false)
      break;
  }
  sunlist.push_back(temp);
}
void moving_normal_suns(vector<suns>& sunlist)
{
  for (int i = 0 ;i < sunlist.size() ;i++)
  {
    if (absolute(sunlist[i].y_cordinate - sunlist[i].y_final) > SUN_DIAMETER / 2)
      sunlist[i].y_cordinate += SUN_SPEED * MYDELAY / 1000;
  }
}
void showing_all_suns(window& w ,vector<suns> sunlist)
{
  int x_cordinate = 0;
  for (int i = 0 ;i < sunlist.size() ; i++)
  {
    x_cordinate = LEFT_YARD + ((sunlist[i].col - 1) * CELL_WIDTH);
    w.draw_png("Sun2.png" ,x_cordinate ,sunlist[i].y_cordinate ,SUN_DIAMETER ,SUN_DIAMETER);
    w.draw_png("Sun1.png" ,x_cordinate + (SUN_DIAMETER - SUNCENTER_DIAMETER) / 2 ,sunlist[i].y_cordinate + (SUN_DIAMETER - SUNCENTER_DIAMETER) / 2 ,SUNCENTER_DIAMETER ,SUNCENTER_DIAMETER);
  }
}
void create_sunflower_sun(vector<plants>& plantlist,vector<suns>& sunlist)
{
  suns temp;
  for (int i = 0 ;i < plantlist.size() ;i++)
  {
    if (plantlist[i].plant == SUNFLOWER)
    {
      if (plantlist[i].sun_left_time > 0)
        plantlist[i].sun_left_time -= MYDELAY;
      else
      {
        plantlist[i].sun_left_time = SUNFLOWER_SUN_TIME;
        temp.col = plantlist[i].col;
        temp.y_final = UP_YARD + ((plantlist[i].row - 1) * CELL_LENGTH);
        temp.y_cordinate = UP_YARD + ((plantlist[i].row - 1) * CELL_LENGTH);
        temp.time_left = SUN_STAYING_TIME;
        sunlist.push_back(temp);
      }
    }
  }
}
void deleting_long_suns(vector<suns>& sunlist)
{
  for (int i = 0 ;i < sunlist.size() ;i++)
  {
    if(absolute(sunlist[i].y_cordinate - sunlist[i].y_final) <= (SUN_DIAMETER / 2))
    {
      if (sunlist[i].time_left > 0)
        sunlist[i].time_left -= MYDELAY;
      else
        sunlist.erase(sunlist.begin() + i);
    }
  }
}
void collecting_suns(vector<suns>& sunlist ,int x_clicked ,int y_clicked ,int& points)
{
  int x_cordinate;
  for (int i = 0 ;i < sunlist.size() ;i++)
  {
    x_cordinate = LEFT_YARD + ((sunlist[i].col) - 1) * CELL_WIDTH;
    if (x_clicked > x_cordinate && x_clicked < x_cordinate + SUN_DIAMETER && y_clicked > sunlist[i].y_cordinate && y_clicked < sunlist[i].y_cordinate + CELL_LENGTH)
    {
      sunlist.erase(sunlist.begin() + i);
      points += 25;
      break;
    }
  }
}
void erase_plant(int row ,int col ,vector<vector<int> >& plantexist,vector<plants>& plantlist ,bool& selected ,bool& any_plant_selected)
{
  if (selected)
  {
    if (row > 0 && col > 0)
    {
      if(plantexist[row - 1][col - 1] != 0)
      {
        plantexist[row -1 ][col - 1] = 0;
        plantlist[9 * (row - 1) + col - 1].plant = 0;
      }
      selected = false;
    }
    any_plant_selected = false;
  }
}
void selected_plant_shovel(window& w ,bool any_plant_selected ,int plant_selected ,bool shovel_selected)
{
  if (any_plant_selected)
  {
    switch (plant_selected)
    {
      case PEASHOOTER:
        w.draw_rect(X_FIRST_CARD ,Y_FIRST_CARD ,CARD_WIDTH ,CARD_LENGTH ,BLUE);
        break;
      case SUNFLOWER:
        w.draw_rect(X_FIRST_CARD + CARD_WIDTH + 5 ,Y_FIRST_CARD ,CARD_WIDTH ,CARD_LENGTH ,BLUE);
        break;
      case WALLNUT:
        w.draw_rect(X_FIRST_CARD + 2 * CARD_WIDTH + 2 * 5 ,Y_FIRST_CARD ,CARD_WIDTH ,CARD_LENGTH ,BLUE);
        break;
    }
  }
  if (shovel_selected)
  {
    w.draw_rect(700 ,0 ,CARD_WIDTH ,CARD_LENGTH ,RED);
  }
}
