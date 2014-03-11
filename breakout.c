//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//
 
// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
 
// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"
 
// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400
 
// number of rows of bricks
#define ROWS 5
 
// number of columns of bricks
#define COLS 10
 
// radius of ball in pixels
#define RADIUS 10
 
// lives
#define LIVES 3
 
 
// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points, int lives);
GObject detectCollision(GWindow window, GOval ball);
void removeGWindow(GWindow window, GObject bricks);
//bool won(void);
 
int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));
 
    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);
 
    // instantiate bricks
    initBricks(window);
 
    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);
 
    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);
 
    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);
 
    // number of bricks initially
    int bricks = COLS * ROWS;
 
    // number of lives initially
    int lives = LIVES;
 
    // number of points initially
    int points = 0;
 
    // keep playing until game over
    double velocity_x = drand48() * 3;
    double velocity_y = 2.5;
     
    double x = getX(ball);
    double y = getY(ball);
    waitForClick();
    
    while (lives > 0 && bricks > 0)
    {
        GEvent event = getNextEvent(MOUSE_EVENT);
        if (event != NULL)
        
        if(getEventType(event) == MOUSE_MOVED)
        {
        double x = getX(event) - getWidth(paddle) / 2;
        double y = 500;
        setLocation(paddle, x, y);
        }
             
             
        move(ball, velocity_x, velocity_y);
        if (getY(ball) + getHeight(ball) > getHeight(window))
        {
            velocity_y = -velocity_y;
        }
        else if (getY(ball) <= 0)
        {
            velocity_y = -velocity_y;
        }
        else if (getX(ball) + getWidth(ball) > getWidth(window))
        {
            velocity_x = -velocity_x;
        }
        else if (getX(ball) <= 0)
        {
            velocity_x = -velocity_x;
        }
        
        GObject object = detectCollision(window, ball);
        if (object == paddle)
        {
          velocity_y = -velocity_y;  
        }
        
        if ((strcmp(getType(object), "GRect") == 0) && (object != paddle))    
        {
            points = points + 1;
            removeGWindow(window, object);
            velocity_y = -velocity_y;
            char s[12];
            sprintf(s, "Score: %i", points);
            setLabel(label, s);
        }
            if (points == 50)
            {
                char s[12];
                sprintf(s, "Well Done!");               
                setLabel(label, s);
                pause(10);    
                break;
            }
        
        if (getY(ball) + 95 >= getHeight(window))
        {
            lives = lives -1;
            removeGWindow(window, ball);
            waitForClick(); 
            ball = initBall(window);
            char t[12];
            sprintf(t, "Lives: %i", lives);
            setLabel(label, t); 
        }
            if (lives == 0)
            {
                char s[12];
                sprintf(s, "Score: %i", points);
                sprintf(s,"Nice try!");
                setLabel(label, s);
                pause(20);
                break;
            }   
        
        pause(10);
        
    
    }
 
           
        waitForClick();
        pause(10);
    // game over
       
   
    closeGWindow(window);
    return 0;
    }
 
/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
   int i, j;
   int x = 0, y = 50;
   int bricks = ROWS * COLS;
   //int br_width = 33;
   //int br_height = 8;
   //int br_space = 2;
    
   for(i = 0; i < ROWS; i++)
   {
       for(j = 0; j < COLS; j++)
       {
            GRect bricks = newGRect (x + 7, y + 7, 35, 10);
            x += (35 + 3);
            
             
            if(i == 0 && j <= 10) 
            {
                setColor(bricks, "RED");
            }
            if(i == 1 && j <= 10) 
            {
                setColor(bricks, "ORANGE");
            }
            if(i == 2 && j <= 10) 
            {
                setColor(bricks, "YELLOW");
            }
            if(i == 3 && j <= 10) 
            {
                setColor(bricks, "GREEN");
            }
            if(i == 4 && j <= 10) 
            {
                setColor(bricks, "BLUE");
            }
            setFilled(bricks, true);
            add(window, bricks);    
    }
        x = 0;
        y += (10 + 3);
  }        
}
 
/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    int ballx = 20;
    int bally = 20;
    GOval ball = newGOval(180, 150, 20, 20);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}
 
/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(175, 500, 50, 10);
    setColor (paddle, "MAGENTA");
    setFilled (paddle, true);
    add (window, paddle);
    return paddle;
}
     
 
/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    
    GLabel score = newGLabel("Score: 0");
    setFont(score, "SansSerif-24");
    //GLabel livelab = newGLabel ("Lives: 3");
    //setFont(livelab, "SansSerif-24");
    double x = (getWidth(window) - getWidth(score)) / 2;
    double y = (getHeight(window) - getHeight(score)) / 2;
    setLocation(score, x, y + 15);
    add(window, score);
    //setLocation(livelab, x, y - 250);
    //add(window, livelab);
    return score;
    //return livelab;
}
 
/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label,int points, int lives)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);
    char t[12];
    sprintf(t, "%i", lives);
    setLabel(label, t); 
 
    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    setLocation(label, x, y - 250);
}
 
/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);
 
    // for checking for collisions
    GObject object;
 
    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }
 
    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }
 
    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }
 
    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }
    
     
    // no collision
    return NULL;
}

