#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"
#define MAX_LINE 512
void printcomments(Commentnode *node) 
{
    int count = 1;
    while (node) {
        printf("  comment %d by %s: %s\n", count++, node->data->username, node->data->content);
        node = node->next;
    }
}

int main(void)
{
    char line[MAX_LINE];
    char cmd[50], arg1[100], arg2[400];
    int n;
    createplatform();
    printf("commands:\n");
    printf("  add post <username> \"<caption>\"\n");
    printf("  add comment <username> \"<comment>\"\n");
    printf("  view post <n>\n");
    printf("  delete post <n>\n");
    printf("  delete comment <n>\n");
    printf("  quit\n\n");
    while (1) 
    {
        printf(">> ");
        if (!fgets(line, sizeof(line), stdin))
        break;
        line[strcspn(line, "\n")] = 0;
        if (sscanf(line, "%s", cmd) != 1)
        continue;
        if (strcmp(cmd, "add") == 0)
        {
            if (strstr(line, "add post") != NULL) 
            {
                char *quote = strchr(line, '"');
                if (!quote) 
                { printf("sorry invalid format\n"); 
                continue; 
                }
                char *endq = strchr(quote + 1, '"');
                if (!endq)
                { printf("sorry invalid format\n"); continue; }
                *endq = 0;
                sscanf(line, "%*s %*s %99s", arg1);
                strcpy(arg2, quote + 1);
                if (addpost(arg1, arg2))
                    printf("post added by %s: %s\n", arg1, arg2);
                else
                    printf("there is an error in adding post\n");
            }
            else if (strstr(line, "add comment") != NULL) 
            {
                char *quote = strchr(line, '"');
                if (!quote) { printf("invalid format.\n"); continue; }
                char *endq = strchr(quote + 1, '"');
                if (!endq) { printf("invalid format.\n"); continue; }
                *endq = 0;
                sscanf(line, "%*s %*s %99s", arg1);
                strcpy(arg2, quote + 1);
                if (addcomment(arg1, arg2))
                    printf("comment added by %s: %s\n", arg1, arg2);
                else
                    printf("error in adding comment.\n");
            }
        }
        else if (strcmp(cmd, "view") == 0) 
        {
            if (sscanf(line, "%*s %*s %d", &n) == 1) 
            {
                Post *p = viewpost(n);
                if (p)
                {
                    printf("post %d by %s: %s\n", n, p->username, p->caption);
                    printcomments(p->comments_head);
                } else {
                    printf("post %d not found.\n", n);
                }
            }
        }
        else if (strcmp(cmd, "delete") == 0) 
        {
            if (strstr(line, "post"))
            {
                if (sscanf(line, "%*s %*s %d", &n) == 1) 
                {
                    if (deletepost(n))
                        printf("post %d deleted.\n", n);
                    else
                        printf("error deleting post %d.\n", n);
                }
            }
            else if (strstr(line, "comment")) 
            {
                if (sscanf(line, "%*s %*s %d", &n) == 1) {
                    if (deletecomment(n))
                        printf("comment %d deleted.\n", n);
                    else
                        printf("error deleting comment %d.\n", n);
                }
            }
        }
        else if (strcmp(cmd, "quit") == 0) 
        {
            printf("exiting.\n");
            break;
        }
        else {
            printf("unknown command.\n");
        }
    }
    return 0;
}
