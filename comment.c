#include"comment.h"
#include<stdlib.h>
#include<string.h>
Comment *createcomment(char *username,char*content)
{
    Comment *newcomment =(Comment *)malloc(sizeof(Comment));
    if (!newcomment) 
    return NULL;
    newcomment->username = strdup(username);
    newcomment->content = strdup(content);
    if(!newcomment->username||!newcomment->content)
    {
        free(newcomment->username);
        free(newcomment->content);
        free(newcomment);
        return NULL;
    }
    return newcomment;
}
void destroycommentdata(Comment *comment)
{
    if(!comment)
    return;
    
        free(comment->username);
        free(comment->content);
        free(comment);
    
}
