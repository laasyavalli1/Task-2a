#ifndef PLATFORM_H
#define PLATFORM_H
#include"post.h"
#include"comment.h"
#include<stdbool.h>

typedef struct Platform {
    Postnode *posts_head;
    Postnode *lastviewedpost;
}Platform;
Platform* createplatform(void);
bool addpost(char* username, char* caption);
bool deletepost(int n);
bool addcomment(char* username, char* content);
bool deletecomment(int n);
Post* viewpost(int n);
Commentnode* viewcomments(void);

#endif 
