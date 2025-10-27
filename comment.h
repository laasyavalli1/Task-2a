#ifndef COMMENT_H
#define COMMENT_H
#include<stdbool.h>
typedef struct Comment{
    char *username;
    char*content;
}Comment;
typedef struct Commentnode{
    Comment *data;
    struct Commentnode *next;
}Commentnode;
Comment *createcomment(char *username,char * content);
void destroycommentdata(Comment *comment);

#endif
