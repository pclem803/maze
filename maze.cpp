//
//  main.cpp
//  Maze Game
//
//  Created by Philip Clement on 7/29/19.
//  Copyright © 2019 Philip Clement. All rights reserved.
//


#include <fstream>
#include <string>
#include <random>
#include <iostream>
#include <iomanip>


using namespace std;

#include "definitions.h"
#include "block.h"



int mazemaker(block** maze, int dimension)
{
    srand(time(NULL));
    stack* mystack;
    mystack=new stack();
    
    int x_value=dimension;
    int y_value=dimension;
    
    //DECLARING ARRAY OF ARRAYS OF BLOCK ELEMENTS
    
    
    //initialize the maze
    for (int i=0; i<y_value;i++){
        for (int j=0; j<x_value;j++){
            maze[i][j].new_point=true;
            maze[i][j].image='+';
            maze[i][j].right_wall=true;
            maze[i][j].left_wall=true;
            maze[i][j].ceiling=true;
            maze[i][j].floor=true;
            maze[i][j].x_position=j;
            maze[i][j].y_position=i;
        }
    }
    
    //MAKE EDGE CONDITIONS
    //left wall of maze
    for (int i=0; i<y_value;i++){
        maze[i][0].left_wall=false;
    }
    
    //right wall of maze
    for (int i=0; i<y_value; i++){
        maze[i][x_value-1].right_wall=false;
    }
    
    //top of maze
    for (int i=0; i<x_value; i++){
        maze[0][i].ceiling=false;
    }
    
    //bottom of maze
    for (int i=0; i<x_value; i++){
        maze[y_value-1][i].floor=false;
    }

    
    //Create curX and curY variables and set them to a random position in the maze.
    int x_posn=2;
    int y_posn=2;
    int max=dimension-1;
    int min=1;
    while ((x_posn%2)==0){
        x_posn = min + (rand() % (int)(max - min + 1));
    }
    while ((y_posn%2)==0){
        y_posn = min + (rand() % (int)(max - min + 1));
    }
    
    //Grab the Cell at the curX, curY position and push it on the trail stack.

    mystack->push(maze[y_posn][x_posn]);
    maze[y_posn][x_posn].image='S'; //INDICATE THE STARTING POINT and surrounding points walls
    maze[y_posn+1][x_posn].ceiling=false;
    maze[y_posn-1][x_posn].floor=false;
    maze[y_posn][x_posn+1].left_wall=false;
    maze[y_posn][x_posn-1].right_wall=false;
 
    
    int randomizer;
    int directions[4];
    int end_counter=0;
    
    //While the trail stack is not empty do the following:
    while (mystack->isEmpty()==false){
        cout<<"Current point is "<<mystack->peek().y_position<<mystack->peek().x_position<<endl;
        //PRINT THE MAZE
        cout<<endl;
        for(int i=0; i<y_value;i++){
            for(int j=0;j<x_value;j++){
                cout<<setw(3)<<maze[i][j].image;
            }
            cout<<endl;
        }
        //SET DIRECTION VECTOR EQUAL TO -1 (NULL DIRECTION)
        for (int i=0; i<4; i++){
            directions[i]=-1;
        }
        //checking up block to see if is viable
        if (maze[y_posn-1][x_posn].new_point == true && maze[y_posn-1][x_posn].right_wall==true && maze[y_posn-1][x_posn].left_wall==true && maze[y_posn-1][x_posn].ceiling==true){
            directions[3]=0;
        }
        //checking right block to see if is viable
        if (maze[y_posn][x_posn+1].new_point == true && maze[y_posn][x_posn+1].right_wall==true && maze[y_posn][x_posn+1].floor==true && maze[y_posn][x_posn+1].ceiling==true){
            directions[1]=1;
        }
        //checking left block to see if is viable
        if (maze[y_posn][x_posn-1].new_point == true && maze[y_posn][x_posn-1].left_wall==true && maze[y_posn][x_posn-1].floor==true && maze[y_posn][x_posn-1].ceiling==true){
            directions[2]=2;
        }
        //checking down block to see if is viable
        if (maze[y_posn+1][x_posn].new_point == true && maze[y_posn+1][x_posn].right_wall==true && maze[y_posn+1][x_posn].left_wall==true && maze[y_posn+1][x_posn].floor==true){
            directions[3]=3;
        }
        
        //CHECK TO SEE IF ANY DIRECTION IS VIABLE
        if (directions[0]!=-1 || directions[1]!=-1 || directions[2]!=-1 || directions[3]!=-1){ //TO SEE IF ALL DIRECTIONS ARE INVALID
            do{
                randomizer= rand()%(3-0+1)+0;//select random direction in array
            }while(directions[randomizer]==-1);
            maze[y_posn][x_posn].new_point=false;
            if (directions[randomizer]==UP){
                maze[y_posn][x_posn].ceiling=false;
                y_posn--;
                maze[y_posn][x_posn].new_point=false;
                maze[y_posn][x_posn].floor=false;
                maze[y_posn-1][x_posn].floor=false;
                maze[y_posn][x_posn-1].right_wall=false;
                maze[y_posn][x_posn+1].left_wall=false;
                if (maze[y_posn][x_posn].image!='S')
                    maze[y_posn][x_posn].image=' ';
                mystack->push(maze[y_posn][x_posn]);
            }
            else if (directions[randomizer]==DOWN){
                if (maze[y_posn][x_posn].image!='S')
                    maze[y_posn][x_posn].image=' ';
                maze[y_posn][x_posn].floor=false;
                y_posn++;
                maze[y_posn][x_posn].new_point=false;
                maze[y_posn][x_posn].ceiling=false;
                maze[y_posn+1][x_posn].ceiling=false;
                maze[y_posn][x_posn-1].right_wall=false;
                maze[y_posn][x_posn+1].left_wall=false;
                if (maze[y_posn][x_posn].image!='S')
                    maze[y_posn][x_posn].image=' ';
                mystack->push(maze[y_posn][x_posn]);
            }
            else if (directions[randomizer]==RIGHT){
                if (maze[y_posn][x_posn].image!='S')
                    maze[y_posn][x_posn].image=' ';
                maze[y_posn][x_posn].right_wall=false;
                x_posn++;
                maze[y_posn][x_posn].new_point=false;
                maze[y_posn][x_posn].left_wall=false;
                maze[y_posn+1][x_posn].ceiling=false;
                maze[y_posn-1][x_posn].floor=false;
                maze[y_posn][x_posn+1].left_wall=false;
                if (maze[y_posn][x_posn].image!='S')
                    maze[y_posn][x_posn].image=' ';
                mystack->push(maze[y_posn][x_posn]);
            }
            else if (directions[randomizer]==LEFT){
                if (maze[y_posn][x_posn].image!='S')
                    maze[y_posn][x_posn].image=' ';
                maze[y_posn][x_posn].left_wall=false;
                x_posn--;
                maze[y_posn][x_posn].new_point=false;
                maze[y_posn][x_posn].right_wall=false;
                maze[y_posn+1][x_posn].ceiling=false;
                maze[y_posn-1][x_posn].floor=false;
                maze[y_posn][x_posn-1].right_wall=false;
                if (maze[y_posn][x_posn].image!='S')
                    maze[y_posn][x_posn].image=' ';
                mystack->push(maze[y_posn][x_posn]);
            }
        }
        //TO SEE IF ALL DIRECTIONS ARE INVALID
        else if (directions[0]==-1 && directions[1]==-1 && directions[2]==-1 && directions[3]==-1) {
            maze[y_posn][x_posn].new_point=false;
            mystack->pop();
            if (end_counter==0){
                maze[y_posn][x_posn].image='F';
                end_counter++;
            }
            if (mystack->isEmpty()==false){
                x_posn=(mystack->peek()).x_position;
                y_posn=(mystack->peek()).y_position;
            }
        }

    
    }
    
    
    mystack->~stack();
    return 0;
}

