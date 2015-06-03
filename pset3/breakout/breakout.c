//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

//height and width of bricks
#define BHEIGHT 15
#define BWIDTH 35

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// height and width of game's paddle in pixels
#define PHEIGHT 10
#define PWIDTH 50
#define PBUFFER 30

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

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

    // ball velocity
    double xvelocity = drand48() + 2.0;
    double yvelocity = drand48() + 2.0;

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

    // starting location for paddle
    setLocation(paddle, WIDTH / 2 - PWIDTH / 2, HEIGHT - PBUFFER);

    // wait for click to start
    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // ball movement
        move(ball, xvelocity, yvelocity);

        // linger before moving again
        pause(10);

        // check for collision
        GObject collider = detectCollision(window, ball);

        //bounce ball on top and paddle
        if (getY(ball) <= 0 || (collider == paddle))
        {
            yvelocity = -yvelocity;
        }
        
        // bounce ball on sides
        if ((getX(ball) <= 0) || ((getX(ball) + getWidth(ball)) >= WIDTH))
        {
            xvelocity = -xvelocity;
        }
 
        // bounce and remove bricks
        if ((collider != NULL) && (collider != paddle))
        {
            if (strcmp(getType(collider), "GRect") == 0)
            {
                // remove bricks
                removeGWindow(window, collider);
                bricks--;

                // change ball direction
                yvelocity = -yvelocity;   

                // update points
                points++;
                
            }
        }    

        updateScoreboard(window, label, points);

        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard a mouse event
        if (event != NULL)
        {            
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure paddle follows middle cursor and only moves horizontally within bounds
                double x = getX(event) - PWIDTH / 2;
                
                if (x < 0)
                    setLocation(paddle, 0, HEIGHT - PBUFFER);

                else if ((x + PWIDTH) > WIDTH)
                    setLocation(paddle, WIDTH - PWIDTH, HEIGHT - PBUFFER);
                
                else
                    setLocation(paddle, x, HEIGHT - PBUFFER);
            }
        }

        // end session for temporary game over if ball hits window bottom
        if (getY(ball) + getWidth(ball) >= HEIGHT)
        {
            xvelocity = 0;
            yvelocity = 0;
            lives--;
            removeGWindow(window, ball);

            // instantiate ball, centered in middle of window
            ball = initBall(window);

            // starting location for paddle
            setLocation(paddle, WIDTH / 2 - PWIDTH / 2, HEIGHT - PBUFFER);

            // wait for click to start
            waitForClick();

            xvelocity = drand48() + 2.0;
            yvelocity = drand48() + 2.0;
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    double x = 2.5;
    double y = 20.0;

    string color[ROWS] = {"RED", "ORANGE", "YELLOW", "GREEN", "BLUE"};

    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            GRect brick = newGRect(x, y, BWIDTH, BHEIGHT);
            setFilled(brick, true);
            setColor(brick, color[r % ROWS]);
            add(window, brick);

            // column spacing
            x += (BWIDTH + 5);
        }
        // reset row
        x = 2.5;

        // row spacing
        y += (BHEIGHT + 3);
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH / 2 - RADIUS / 2, HEIGHT / 2 - RADIUS / 2, RADIUS * 2, RADIUS * 2);

    setFilled(ball, true);
    setColor(ball, "BLACK");
    add(window, ball);

    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect rect = newGRect(WIDTH / 2 - PWIDTH / 2, HEIGHT - PBUFFER, PWIDTH, PHEIGHT);
        
    setFilled(rect, true);
    setColor(rect, "BLACK");
    add(window, rect);

    return rect;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("Click to Start");

    setFont(label, "SansSerif-36");
    setColor(label, "LIGHT_GRAY");
    add(window, label);

    // center label in window
    double x = (WIDTH - getWidth(label)) / 2;
    double y = (WIDTH - getHeight(label)) / 2;
    setLocation(label, x, y);
    
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
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
