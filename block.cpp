//
//  block.cpp
//  Maze Game
//
//  Created by Philip Clement on 7/29/19.
//  Copyright © 2019 Philip Clement. All rights reserved.
//

#include "block.hpp"
#include <iostream>

using namespace std;


//----------STACKS---------//


stacknode::stacknode(block cell){
    data=cell;
    next=NULL;
}

stacks::stacks(){
    top=NULL;
}

stacks::~stacks(){
    while (top!=NULL){
        stacknode* temp=top->next;
        delete top;
        top=temp;
    }
}
    
void stacks::push(block cell){
    stacknode* newnode= new stacknode(cell);
    if (top==NULL)
        top=newnode;
    else{
        stacknode* previous_top = top;
        top=newnode;
        top->next=previous_top;
    }
}

block stacks::pop(){ //remove top item
    stacknode* removing_node=top;
    block item = top->data;
    top=top->next;
    delete removing_node;
    return item;
}

block stacks::peek(){//shows top item
    return top->data;
}
bool stacks::isEmpty(){
    if (top==NULL)
        return 1;
    else
        return 0;
}



//----------QUEUES---------//



queuenode::queuenode(block d){
    data=d;
    next=NULL;
}

queue::queue(){
    first=NULL;
    last=NULL;
}

queue::~queue(){
    queuenode* tempnode;
    while (first != last  && first!=NULL){
        tempnode=first->next;
        delete first;
        first=tempnode;
    }
    tempnode=first;
    first=NULL;
    last=NULL;
    delete tempnode;
}


void queue::add(block d){
    queuenode* new_node = new queuenode(d);
    queuenode* temp_node;
    if (first==NULL){ //IF THE QUEUE IS EMPTY
        first=new_node;
        last=new_node;
    }
    else if (first==last && first!=NULL){ //IF THE QUEUE HAS ONLY ONE ELEMENT
        last=new_node;
        first->next=last;
    }
    else {
        temp_node=last;
        last=new_node;
        temp_node->next=last;
    }
}

block queue::remove(){
    block item;
    queuenode* removing_node;
    if(first==last && first!=NULL){
        item=first->data;
        delete first;
        last=NULL;
        first=NULL;
        return item;
    }
    else{
        item=first->data;
        removing_node=first;
        first=first->next;
        delete removing_node;
        return item;
    }
}

block queue::peek(){
    block item= first->data;
    return item;
}

bool queue::isEmpty(){
    if (first==NULL)
        return true;
    else
        return false;
}
