#include"post.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
Post *createpost(char *username,char*caption)
{
    Post* newpost = (Post*)malloc(sizeof(Post));
    if (!newpost) 
    return NULL;
    newpost->username = strdup(username);
    newpost->caption = strdup(caption);
    if(!newpost->username||!newpost->caption)
    {
        free(newpost->username);
        free(newpost->caption);
        free(newpost);
        return NULL;
    }
    newpost->comments_head=NULL;
    return newpost;
}

void destroypostdata(Post *post)
{
    if (!post) 
    return;
    Commentnode *c = post->comments_head;
    while (c) {
         Commentnode *tmp = c;
        c = c->next;
        destroycommentdata(tmp->data);
       free(tmp);
        }
    free(post->username);
    free(post->caption);
    free(post);
}
