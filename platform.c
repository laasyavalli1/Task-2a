#include "platform.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Platform *globalplatform = NULL;

Platform *createplatform(void)
{
    if (globalplatform != NULL) return globalplatform;
    Platform *platform = (Platform *)malloc(sizeof(Platform));
    if (!platform) return NULL;
    platform->posts_head = NULL;
    platform->lastviewedpost = NULL;
    globalplatform = platform;
    return platform;
}

bool addpost(char *username, char *caption)
{
    if (!globalplatform) return false;
    Post *newpost = createpost(username, caption);
    if (!newpost) return false;
    Postnode *newnode = (Postnode *)malloc(sizeof(Postnode));
    if (!newnode) {
        destroypostdata(newpost);
        return false;
    }
    newnode->data = newpost;
    newnode->next = globalplatform->posts_head;
    globalplatform->posts_head = newnode;
    globalplatform->lastviewedpost = newnode;
    return true;
}

Post *viewpost(int n)
{
    if (!globalplatform || n <= 0) return NULL;
    Postnode *curr = globalplatform->posts_head;
    for (int i = 1; i < n && curr; i++)
        curr = curr->next;
    if (!curr) return NULL;
    globalplatform->lastviewedpost = curr;
    return curr->data;
}

bool addcomment(char *username, char *content)
{
    if (!globalplatform || !globalplatform->lastviewedpost) return false;

    Post *post = globalplatform->lastviewedpost->data;
    Comment *newcomment = createcomment(username, content);
    if (!newcomment) return false;
    Commentnode *newnode = (Commentnode *)malloc(sizeof(Commentnode));
    if (!newnode) {
        destroycommentdata(newcomment);
        return false;
    }
    newnode->data = newcomment;
    newnode->next = post->comments_head;
    post->comments_head = newnode;
    return true;
}

bool deletepost(int n)
{
    if (!globalplatform || n <= 0)
    return false;
    Postnode *curr = globalplatform->posts_head;
    Postnode *prev = NULL;
    for (int i = 1; i < n && curr; i++) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) return false;
    if (prev)
        prev->next = curr->next;
    else
        globalplatform->posts_head = curr->next;

    if (globalplatform->lastviewedpost == curr)
        globalplatform->lastviewedpost = globalplatform->posts_head;
    destroypostdata(curr->data);
    free(curr);
    return true;
}

bool deletecomment(int n)
{
    if (!globalplatform || !globalplatform->lastviewedpost || n <= 0)
        return false;
    Post *post = globalplatform->lastviewedpost->data;
    Commentnode *curr = post->comments_head;
    Commentnode *prev = NULL;
    for (int i = 1; i < n && curr; i++) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) return false;
    if (prev)
        prev->next = curr->next;
    else
        post->comments_head = curr->next;
    destroycommentdata(curr->data);
    free(curr);
    return true;
}

Commentnode *viewcomments(void)
{
    if (!globalplatform || !globalplatform->lastviewedpost)
        return NULL;

    return globalplatform->lastviewedpost->data->comments_head;
}
