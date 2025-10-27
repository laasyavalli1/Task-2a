#ifndef POST_H
#define POST_H
#include<stdbool.h>
#include "comment.h"
typedef struct Post {
    char *username;
    char * caption;
     Commentnode *comments_head;
}Post;

typedef struct Postnode{
    Post*data;
    struct Postnode*next;
}Postnode;
Post*createpost(char *username,char*caption);
void destroypostdata(Post*post);
#endif
