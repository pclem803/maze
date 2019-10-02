//
//  main.cpp
//  Maze Solver
//
//  Created by Philip Clement on 8/7/19.
//  Copyright © 2019 Philip Clement. All rights reserved.
//


#include <fstream>
#include <string>
#include <random>
#include <iostream>
#include <iomanip>


using namespace std;

#include "definitions.h"
#include "block.hpp"

int mazemaker(block** maze, int dimension, int y_posn, int x_posn, bool watch)
{
    srand(time(NULL));
    stacks* mystack;
    mystack=new stacks();
    
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
    
    //Grab the Cell at the curX, curY position and push it on the trail stack.
    
    mystack->push(maze[y_posn][x_posn]);
    maze[y_posn][x_posn].image='S'; //INDICATE THE STARTING POINT and surrounding points walls
    int start_position_x= x_posn;
    int start_position_y= y_posn;
    maze[y_posn+1][x_posn].ceiling=false;
    maze[y_posn-1][x_posn].floor=false;
    maze[y_posn][x_posn+1].left_wall=false;
    maze[y_posn][x_posn-1].right_wall=false;
    
    
    int randomizer;
    int directions[4];
    int end_counter=0;
    int end_iterator;
    if (dimension>9){
        end_iterator=rand()%(4-2+1)+2;
    }
    else
        end_iterator=1;
    
    //While the trail stack is not empty do the following:
    while (mystack->isEmpty()==false){
        if (watch==true){
            cout<<endl;
            //TO PRINT THE MAZE
            for(int i=0; i<y_value;i++){
                for(int j=0;j<x_value;j++){
                    cout<<setw(3)<<maze[i][j].image;
                }
                cout<<endl;
            }
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
            if (end_counter==end_iterator){
                maze[y_posn][x_posn].image='F';
                end_counter++;
            }
            else
                end_counter++;
            if (mystack->isEmpty()==false){
                x_posn=(mystack->peek()).x_position;
                y_posn=(mystack->peek()).y_position;
            }
        }
        
        
    }
    
    //set status of all blocks to unvisited for solving
    //initialize the maze
    for (int i=0; i<y_value;i++){
        for (int j=0; j<x_value;j++){
            maze[i][j].new_point=true;
        }
    }
    
    mystack->~stacks();
    return 0;
}


int main () {
    cout<<"Please enter odd maze dimensions (must be odd): "<<endl;
    int dimensions;
    cin>>dimensions;
    
    int x_value=dimensions;
    int y_value=dimensions;
    
    //DECLARING ARRAY OF ARRAYS OF BLOCK ELEMENTS
    block** maze = new block*[y_value];
    for(int i = 0; i < y_value; i++){
        maze[i] = new block[x_value];
    }
    
    //MAKING THE START POSITION
    //Create curX and curY variables and set them to a random position in the maze.
    int x_posn=2;
    int y_posn=2;
    int max=dimensions-1;
    int min=1;
    while ((x_posn%2)==0){
        x_posn = min + (rand() % (int)(max - min + 1));
    }
    while ((y_posn%2)==0){
        y_posn = min + (rand() % (int)(max - min + 1));
    }
    
    bool watch_maze=false;
    string question;
    cout<<"Would you like to watch the maze be made? (y/n)"<<endl;
    cin>>question;
    if (question=="y")
        watch_maze=true;
    
    
    mazemaker(maze, dimensions, y_posn, x_posn, watch_maze);
    
    
    
    cout<<"Randomly Generated Maze: "<<endl;
    
    cout<<endl;
    //TO PRINT THE MAZE
    for(int i=0; i<y_value;i++){
        for(int j=0;j<x_value;j++){
            cout<<setw(3)<<maze[i][j].image;
        }
        cout<<endl;
    }
    
    bool maze_solve=false;
    cout<<"Would you like to solve the maze? (y/n)"<<endl;
    cin>>question;
    if (question=="y")
        maze_solve=true;
    
    
    if (maze_solve==true){
        //INITIALIZE QUEUE
        queue* myqueue;
        myqueue=new queue();
        
        //FIND THE STARTING POINT
        for (int i=0; i<y_value;i++){
            for (int j=0; j<x_value;j++){
                if (maze[i][j].image=='S'){
                    x_posn=j;
                    y_posn=i;
                }
            }
        }
        maze[y_posn][x_posn].parent_x=NULL;
        maze[y_posn][x_posn].parent_y=NULL;
        
        //ADD STARTING POINT TO QUEUE
        myqueue->add(maze[y_posn][x_posn]);
        block curr_block;
        block end_block;
        while (myqueue->isEmpty()==false){
            //POP THE FIRST ELEMENT OFF THE QUEUE AND FIND ITS X AND Y
            curr_block=myqueue->remove();
            x_posn=curr_block.x_position;
            y_posn=curr_block.y_position;
            
            //TEST EVERY DIRECTION TO SEE IF IT IS VIABLE, IF IT IS ADD TO QUEUE
            //testing up
            if (maze[y_posn-1][x_posn].image=='F'){
                end_block=maze[y_posn-1][x_posn];
                end_block.parent_x=x_posn;
                end_block.parent_y=y_posn;
                end_block.x_position=x_posn;
                end_block.y_position=y_posn-1;
                break;
            }
            else if (maze[y_posn-1][x_posn].image!='+' && maze[y_posn-1][x_posn].new_point==true){
                maze[y_posn-1][x_posn].parent_x=x_posn;
                maze[y_posn-1][x_posn].parent_y=y_posn;
                maze[y_posn-1][x_posn].new_point=false;
                myqueue->add(maze[y_posn-1][x_posn]);
            }
            //testing down
            if (maze[y_posn+1][x_posn].image=='F'){
                end_block=maze[y_posn+1][x_posn];
                end_block.parent_x=x_posn;
                end_block.parent_y=y_posn;
                end_block.x_position=x_posn;
                end_block.y_position=y_posn+1;
                break;
            }
            else if (maze[y_posn+1][x_posn].image!='+' && maze[y_posn+1][x_posn].new_point==true){
                maze[y_posn+1][x_posn].parent_x=x_posn;
                maze[y_posn+1][x_posn].parent_y=y_posn;
                maze[y_posn+1][x_posn].new_point=false;
                myqueue->add(maze[y_posn+1][x_posn]);
            }
            //testing right
            if (maze[y_posn][x_posn+1].image=='F'){
                end_block=maze[y_posn][x_posn+1];
                end_block.parent_x=x_posn;
                end_block.parent_y=y_posn;
                end_block.x_position=x_posn+1;
                end_block.y_position=y_posn;
                break;
            }
            else if (maze[y_posn][x_posn+1].image!='+' && maze[y_posn][x_posn+1].new_point==true){
                maze[y_posn][x_posn+1].parent_x=x_posn;
                maze[y_posn][x_posn+1].parent_y=y_posn;
                maze[y_posn][x_posn+1].new_point=false;
                myqueue->add(maze[y_posn][x_posn+1]);
            }
            //testing left
            if (maze[y_posn][x_posn-1].image=='F'){
                end_block=maze[y_posn][x_posn-1];
                end_block.parent_x=x_posn;
                end_block.parent_y=y_posn;
                end_block.x_position=x_posn-1;
                end_block.y_position=y_posn;
                break;
            }
            else if (maze[y_posn][x_posn-1].image!='+' && maze[y_posn][x_posn-1].new_point==true){
                maze[y_posn][x_posn-1].parent_x=x_posn;
                maze[y_posn][x_posn-1].parent_y=y_posn;
                maze[y_posn][x_posn-1].new_point=false;
                myqueue->add(maze[y_posn][x_posn-1]);
            }
        }
        
        cout<<"The end poisition is "<<end_block.x_position<<", "<< end_block.y_position<<endl;
        
        myqueue->~queue();
    
        
        
        
        
        //SHOWING THE PATH
        bool completed=true;
        int x_iterator=end_block.x_position;
        int y_iterator=end_block.y_position;
        block block_iterator=end_block;
        while(completed){
            x_iterator=block_iterator.parent_x;
            y_iterator=block_iterator.parent_y;
            if (maze[y_iterator][x_iterator].image!='S'){
                maze[y_iterator][x_iterator].image='.';
                block_iterator= maze[y_iterator][x_iterator];
            }
            else{
                completed=false;
            }
        }
    }
    
    //TO PRINT THE MAZE
    for(int i=0; i<y_value;i++){
        for(int j=0;j<x_value;j++){
            cout<<setw(3)<<maze[i][j].image;
        }
        cout<<endl;
        
    }
    //DELETING THE USED SPOTS IN MEMORY
    for (int i=0; i<y_value; i++){
        delete [] maze[i];
    }
    delete [] maze;
    cout<<endl;
}
