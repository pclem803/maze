//
//  block.hpp
//  Maze Game
//
//  Created by Philip Clement on 7/29/19.
//  Copyright © 2019 Philip Clement. All rights reserved.
//

#define MAX 1000

class block {
public:
    char image;
    bool right_wall;
    bool left_wall;
    bool ceiling;
    bool floor;
    bool new_point;
    int x_position;
    int y_position;
    int parent_x;
    int parent_y;
};


class stacknode {
    friend class block;
    friend class stacks;
private:
    block data;
    stacknode* next;
public:
    stacknode(block cell);
};

class stacks {
private:
    stacknode* top;
public:
    stacks();
    ~stacks();
    void push(block cell);
    block pop();
    block peek();
    bool isEmpty();
};





class queuenode{
    friend class queue;
private:
    block data;
    queuenode* next;
public:
    queuenode(block d);
};

class queue{
private:
    queuenode* first;
    queuenode* last;
public:
    queue();
    ~queue();
    void add(block d);
    block remove();
    block peek();
    bool isEmpty();
};
