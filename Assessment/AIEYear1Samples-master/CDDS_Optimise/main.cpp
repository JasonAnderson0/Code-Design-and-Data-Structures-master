#include "raylib.h"
#include "raymath.h"
#include <random>
#include <time.h>
#include "Critter.h"
#include "ResourceManager.h"
#include "ObjectPool.h"

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 550;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");




    //SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    srand(time(NULL));

    const int CRITTER_COUNT = 50;
    ObjectPool critterpool(CRITTER_COUNT);


    const int MAX_VELOCITY = 80;

    for (int i = 0; i < CRITTER_COUNT; i++)
    {
        critterpool.spawn();
    }

    for (int i = 0; i < critterpool.GetInactive().size(); i++) 
    {
        // create a random direction vector for the velocity
        Vector2 velocity = { -100 + (rand() % 200), -100 + (rand() % 200) };
        // normalize and scale by a random speed
        velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);
        critterpool.GetActive()[i].Init(
            { (float)(5 + rand() % (screenWidth - 10)), (float)(5 + (rand() % screenHeight - 10)) },
            velocity,
            12, "res/9.png");
    }



    Critter destroyer;
    Vector2 velocity = { -100 + (rand() % 200), -100 + (rand() % 200) };
    velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);
    destroyer.Init(Vector2{ (float)(screenWidth >> 1), (float)(screenHeight >> 1) }
    ,velocity, 20, "res/10.png");


    float timer = 1;
    Vector2 nextSpawnPos = destroyer.GetPosition();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        float delta = GetFrameTime();

        // update the critters
        for (int i = 0; i < critterpool.GetActive().size(); i++)
        {
            critterpool.GetActive()[i].Update(delta);

            // check each critter against screen bounds
            if (critterpool.GetActive()[i].GetX() < 0) {
                critterpool.GetActive()[i].SetX(0);
                critterpool.GetActive()[i].SetVelocity(Vector2{ -critterpool.GetActive()[i].GetVelocity().x, critterpool.GetActive()[i].GetVelocity().y });
            }
            if (critterpool.GetActive()[i].GetX() > screenWidth) {
                critterpool.GetActive()[i].SetX(screenWidth);
                critterpool.GetActive()[i].SetVelocity(Vector2{ -critterpool.GetActive()[i].GetVelocity().x, critterpool.GetActive()[i].GetVelocity().y });
            }
            if (critterpool.GetActive()[i].GetY() < 0) {
                critterpool.GetActive()[i].SetY(0);
                critterpool.GetActive()[i].SetVelocity(Vector2{ critterpool.GetActive()[i].GetVelocity().x, -critterpool.GetActive()[i].GetVelocity().y });
            }
            if (critterpool.GetActive()[i].GetY() > screenHeight) {
                critterpool.GetActive()[i].SetY(screenHeight);
                critterpool.GetActive()[i].SetVelocity(Vector2{ critterpool.GetActive()[i].GetVelocity().x, -critterpool.GetActive()[i].GetVelocity().y });
            }


            float dist = Vector2Distance(critterpool.GetActive()[i].GetPosition(), destroyer.GetPosition());
            if (dist < critterpool.GetActive()[i].GetRadius() + destroyer.GetRadius())
            {
                //critters.Destroy();
            }
        }

         for(int i = 0; i < critterpool.GetActive().size(); i++)
         {
            for (int j = 0; j < critterpool.GetActive().size(); j++) 
            {
                if (&critterpool.GetActive()[i] != &critterpool.GetActive()[j] || critterpool.GetActive()[i].IsDirty()) // note: the other critter (j) could be dirty - that's OK
                    continue;

                // check every critter against every other critter
                float dist = Vector2Distance(critterpool.GetActive()[i].GetPosition(), critterpool.GetActive()[j].GetPosition());
                if (dist < critterpool.GetActive()[i].GetRadius() + critterpool.GetActive()[j].GetRadius())
                {
                    // collision!
                    // do math to get critters bouncing
                    Vector2 normal = Vector2Normalize(Vector2Subtract(critterpool.GetActive()[j].GetPosition(), critterpool.GetActive()[i].GetPosition()));

                    // not even close to real physics, but fine for our needs
                    critterpool.GetActive()[i].SetVelocity(Vector2Scale(normal, -MAX_VELOCITY));
                    // set the critter to *dirty* so we know not to process any more collisions on it
                    critterpool.GetActive()[i].SetDirty();

                    // we still want to check for collisions in the case where 1 critter is dirty - so we need a check 
                    // to make sure the other critter is clean before we do the collision response
                    if (!critterpool.GetActive()[i].IsDirty()) {
                        critterpool.GetActive()[i].SetVelocity(Vector2Scale(normal, MAX_VELOCITY));
                        critterpool.GetActive()[i].SetDirty();
                    }
                    break;
                }
            }
         }

        timer -= delta;
        if (timer <= 0)
        {
            timer = 1;

            // find any dead critters and spit them out (respawn)
            for (Critter critters : critterpool.GetInactive()) {
                Vector2 normal = Vector2Normalize(destroyer.GetVelocity());

                // get a position behind the destroyer, and far enough away that the critter won't bump into it again
                Vector2 pos = destroyer.GetPosition();
                pos = Vector2Add(pos, Vector2Scale(normal, -50));
                // its pretty ineficient to keep reloading textures. ...if only there was something else we could do
                critterpool.spawn();
                //critters.Init(pos, Vector2Scale(normal, -MAX_VELOCITY), 12, "res/10.png");
                break;
            }
        }
        nextSpawnPos = destroyer.GetPosition();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // draw the critters
        for (Critter critters : critterpool.GetActive())
        {
            for (int i = 0; i < critterpool.GetActive().size(); i++) {
                critterpool.GetActive()[i].Draw();
            }
        }

        
        // draw the destroyer
        // (if you're wondering why it looks a little odd when sometimes critters are destroyed when they're not quite touching the 
        // destroyer, it's because the origin is at the top-left. ...you could fix that!)
        destroyer.Draw();

        DrawFPS(10, 10);
        //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    for (Critter critters : critterpool.GetActive())
    {
        //critters.Destroy();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}