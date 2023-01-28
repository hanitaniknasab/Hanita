#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct post // structure for saving posts
{
    char* username;
    char* post_id;
    char* text;
    int like; //number of likes
};
struct postNode // structure for post's linked-list
{
    struct post pst;
    struct postNode* next;
};
struct user // structure for saving users
{
    char* username;
    char* password;
    int numberOfPosts;
};
struct userNode // structure for user's linked-lists
{
    struct user usr;
    struct userNode* nextUser;
};
int getCommand(char* command)  // saving input in command
{
    printf("\n");
    char t;

    int len; // length of command

    while(scanf("%c", &t)==1) // saving command while user type inputs
    {

        if(t== '\n')

            break;

        len = strlen(command);

        command= realloc(command,len+1); // dynamic allocation

        *(command+len) = t;

        *(command+len+1) = '\0';

    }
    return len;

}
int signUp(char* command, char* currentUserName, struct user currentUser, struct userNode* users, int len) // sign up function with dynamic allocation
{
    int counter=0 ;
    int i=7;
    while(command[i]!=' ') // count the command before space character
    {
        counter++; // counter= size of username
        i++;
    }
    struct user newuser;
    newuser.username=malloc(counter*sizeof(char)); // dynamic allocation
    int counter2=counter;
    i=0;
    while(i!=counter)
    {
        newuser.username[i]=command[counter2];
        counter2++;
        i++;
    }
    int flagUser=0;
    struct userNode* current = users;
    while(current!=NULL)  // search username in exists usernames
    {
        if(current->usr.username== newuser.username)
        {
            flagUser=1;
        }
        current=current->nextUser;
    }
    if(!flagUser) //username not exist
    {
        counter2++;
        i=0;
        newuser.password=malloc((len-counter)*sizeof(char));
        newuser.numberOfPosts=0;
        while(counter2!=len+1) // save dynamic password
        {
            newuser.password[i]=command[counter2];
            counter2++;
            i++;
        }
        struct userNode *newUserNode = malloc(sizeof(struct userNode));
        newUserNode->usr = newuser;
        newUserNode->nextUser= NULL;
        if(users== NULL)
            users=newUserNode;
        else
        {
            struct userNode* lastNode= users;
            while(lastNode->nextUser!=NULL)
            {
                lastNode=lastNode->nextUser;
            }
            lastNode->nextUser=newUserNode;
        }
        currentUserName = newuser.username;
        currentUser=newuser;
        printf("welcome!\n");

        return 1;
    }
    else // username exists
    {
        printf("this username already exists");
        return 0;
    }

}
int logIn(char* command, char* currentUserName, struct user currentUser, struct userNode* users, int len) //login function
{
    if(currentUserName==NULL) // user not loged in
    {
        int counter=0 ;
        int i=6;
        while(command[i]!=' ')
        {
            counter++;
            i++;
        }
        char* username = malloc(counter*sizeof(char));
        int counter2=counter;
        i=0;
        while(i!=counter) // find the username from command
        {
            username=command[counter2];
            counter2++;
            i++;
        }
        char* password=malloc((len-counter)*sizeof(char));

        counter2++;
        i=0;
        while(counter2!=len+1) //find password from command
        {
            password=command[counter2];
            counter2++;
            i++;
        }
        struct userNode* current = users;
        int flagUser=0;
        int flagPassword=0;
        while(current!=NULL) // search the username
        {
            if(current->usr.username== username)
            {
                flagUser=1;
                if(current->usr.password== password) //check password
                {
                    flagPassword=1;
                    currentUserName=username;
                    currentUser=current->usr;
                }
            }
            current=current->nextUser;
        }
        if( flagPassword && flagUser) // log in
        {
            printf("log in successfully");
            return 1 ;
        }
        else if (!flagPassword && flagUser) // inc pass
        {
            printf("incorrect password!");
            return 0;
        }
        else if(!flagPassword && !flagUser) // inc username
        {
            printf("incorrect userName!");
            return 0;
        }
    }
    else
    {
        printf("you are already logged in!! please logout and try again");
        return 0 ;
    }
}
int logOut( char* currentUserName) // logout function
{
    if(currentUserName!=NULL)
    {
        currentUserName=NULL;
        printf("log out succssefully");
        return 1;
    }
    else
    {
        printf("you are already logged out");
        return 0;
    }
}
int Post(char* command, char* currentUserName, struct postNode* posts,struct userNode* users, int len) // function for saving new post
{
    if(currentUserName==NULL) // check log in
    {
        printf("please login and try again!");
        return 0;
    }
    else
    {
        int i= 5 ;
        struct post newPost ;
        newPost.text= malloc((len-5) * sizeof(char));
        int j=0;
        while(i<=len) //find the text of post in command
        {
            newPost.text[j] = command[i];
            i++;
            j++;
        }
        newPost.like=0;

        struct userNode* current = users;
        while(current!=NULL)
        {
            if(current->usr.username== currentUserName)
            {
                newPost.post_id=current->usr.numberOfPosts+1;
                current->usr.numberOfPosts++;


            }
            current=current->nextUser;
        }
        newPost.username= malloc(sizeof(currentUserName));
        newPost.username=currentUserName;

        struct postNode *newPostNode = malloc(sizeof(struct postNode));
        newPostNode->pst = newPost;
        newPostNode->next= NULL;
        if(posts== NULL)
            posts=newPostNode;
        else
        {
            struct postNode* lastNode= posts;
            while(lastNode->next!=NULL)
            {
                lastNode=lastNode->next;
            }
            lastNode->next=newPostNode;
        }
        return 1;
    }
}
int Info(char* currentUserName, struct user currentUser, struct postNode* posts) //get info function
{
    if(currentUserName==NULL)
    {
        printf("please login and try again!");
        return 0;
    }
    else
    {
        printf("userName:");
        printf(currentUser.username);
        printf("password:");
        printf(currentUser.password);
        struct postNode* lastNode= posts;
        while(lastNode->next!=NULL) // search username
        {
            if(lastNode->pst.username==currentUserName) // username found
            {
                printf(lastNode->pst.post_id);
                printf(lastNode->pst.text);
                printf("\tlikes:");
                printf(lastNode->pst.like);
                printf("\n");

            }
            lastNode=lastNode->next;
        }
        printf("\nDone!!\n");

        return 1;
    }

}

int Like(char* command, char* currentUserName, struct postNode* posts,int len) // function for like a post
{
    if(currentUserName==NULL) // check log in
    {
        printf("please login and try again!");
        return 0;
    }
    else
    {
        int i= 5 ;
        int j=0;
        int counter=0;
        while(command[i]!=' ')
        {
            counter++;
            i++;
        }
        int counter2=counter;
        i=0;
        char* likedUserName = malloc(counter*sizeof(char));
        while(i!=counter) // save the username of account that user liked
        {
            likedUserName[i]=command[counter2];
            counter2++;
            i++;
        }
        char* likedPost = malloc((len-counter2)*sizeof(char));
        while(counter2!=len+1) // find the post id from command
        {
            likedPost[i]=command[counter2];
            counter2++;
            i++;
        }
        int flagPost=0;
        int flagUser=0;
        struct postNode* lastNode= posts;
        while(lastNode->next!=NULL) // search the post
        {
            if(lastNode->pst.username==likedUserName) // username found
            {
                flagUser=1;
                if(lastNode->pst.post_id==likedPost) //post found
                {
                    lastNode->pst.like++;
                    flagPost=1;
                }
            }
            lastNode=lastNode->next;
        }
        if(flagPost && flagUser) // liked
        {
            printf("liked succssefully");
            return 1;
        }
        else if(!flagPost && flagUser) // ing post_id
        {
            printf("post not found");
            return 0;
        }
        else if(!flagUser) // inc username
        {
            printf("user not found");
            return 0;
        }
    }
}
int Delete(char* command, char* currentUserName, struct postNode* posts,int len) // delete a post function
{
    if(currentUserName==NULL)
    {
        printf("please login and try again!");
        return 0;
    }
    else
    {
        char* deletePost= malloc((len-6)*sizeof(char));
        int i=7;
        int j=0;
        while(i<=len)
        {
            deletePost[j]=command[i];
            i++;
            j++;
        }
        int flagPost=0;
        struct postNode* lastNode= posts;
        struct postNode* prevLast= NULL;
        while(lastNode->next!=NULL) //search username and post
        {
            if(lastNode->pst.username==currentUserName) // username found
            {
                if(lastNode->pst.post_id==deletePost) // post found
                {
                    if(lastNode==posts)
                    {
                        struct postNode* temp=posts;
                        posts=posts->next;
                        free(temp);
                    }
                    else
                    {
                        struct postNode* temp = lastNode;
                        prevLast->next=lastNode->next;
                        free(temp);
                    }
                    flagPost=1;
                }
            }
            prevLast= lastNode;
            lastNode=lastNode->next;
        }
        if(flagPost)
        {
            printf("deleted succssefully");
            return 1;
        }
        else if(!flagPost) // inc post_id
        {
            printf("post not found");
            return 0;
        }
    }
}
int Find(char* command, char* currentUserName, struct userNode* users, struct postNode* posts,int len) // find a user function
{
    char* findUserName= malloc((len-9)*sizeof(char));
    int i=10;
    int j=0;
    while(i<=len) // find the username from command
    {
        findUserName[j]=command[i];
        i++;
        j++;
    }
    int flagUser=0;
    struct userNode* lastUser = users;
    while(lastUser->nextUser!=NULL) // username found
    {
        if(lastUser->usr.username==findUserName)
        {
            flagUser=1;
        }
        lastUser=lastUser->nextUser;
    }
    if(!flagUser) // username not found
    {
        printf("username not found!\n");
        return 0;
    }
    else // print user's data
    {
        printf("userName:");
        printf(findUserName);
        struct postNode* lastNode= posts;
        while(lastNode->next!=NULL)
        {
            if(lastNode->pst.username==currentUserName)
            {
                printf(lastNode->pst.post_id);
                printf(lastNode->pst.text);
                printf("\tlikes:");
                printf(lastNode->pst.like);
                printf("\n");

            }
            lastNode=lastNode->next;
        }
        printf("\nDone!!\n");
        return 1;
    }
}
int File_save(struct userNode* users, struct postNode* posts) // function for saving data in file
{
    FILE *faccptr;
    FILE *fpstptr;
    faccptr= fopen("account.txt", "w");
    fpstptr= fopen("posts.txt", "w");
    struct userNode* tempUser = users;
    struct postNode* tempPost = posts;
    while(tempUser!=NULL)
    {
        tempPost=posts; // temp pointer = head (find all posts of any user)
        fprintf(faccptr, "%s ", tempUser->usr.username);
        fprintf(faccptr, "%s ", tempUser->usr.password);
        fprintf(faccptr, "%s", tempUser->usr.numberOfPosts);
        fprintf(faccptr, "\n" );
        while(tempPost!=NULL)
        {
            if(tempPost->pst.username==tempUser->usr.username) // post of current user
            {
                fprintf(fpstptr, "%s ", tempPost->pst.text );
                fprintf(fpstptr, "%s ", tempPost->pst.username );
                fprintf(fpstptr, "%s ", tempPost->pst.like );
                fprintf(fpstptr, "\n" );
            }
            tempPost=tempPost->next;
        }
        tempUser=tempUser->nextUser;
    }
    fclose(faccptr);
    fclose(fpstptr);
    free(tempPost);
    free(tempUser);
    printf("\nDone!!\n");

}
int main()
{

    char* currentUserName = NULL; // save just username of current user
    struct user currentUser ; // save current user as a structure
    struct postNode*  posts = NULL; // head of posts linked-list
    struct userNode*  users = NULL; // head of users linked-list 
    char* command = calloc(1,sizeof(char)); // save the input as a command

    int len = getCommand(command); // length of command
    if(command[0]=='s'&& command[1]=='i' && command[2]=='g' && command[3]=='n' && command[4]=='u' && command[5]=='p' && command[6]==' ') // command start with signup keyword
    {
        signUp(command, currentUserName,currentUser, users, len);
        main();

    }
    else if(command[0]=='l'&& command[1]=='o' && command[2]=='g' && command[3]=='i' && command[4]=='n' && command[5]==' ') // command start with login keyword
    {

        logIn(command, currentUserName, currentUser, users, len) ;
        main();


    }
    else if(command[0]=='l'&& command[1]=='o' && command[2]=='g' && command[3]=='o' && command[4]=='u' && command[5]=='t' && command[6]==' ')// command start with logout keyword
    {
        logOut( currentUserName);
        main();

    }
    else if(command[0]=='p'&& command[1]=='o' && command[2]=='s' && command[3]=='t' && command[4]==' ')// command start with post keyword
    {
        Post(command, currentUserName, posts, users, len);
        main();


    }
    else if(command[0]=='i'&& command[1]=='n' && command[2]=='f' && command[3]=='o')// command start with info keyword
    {
        Info(currentUserName, currentUser, posts);
        main();

    }
    else if(command[0]=='l'&& command[1]=='i' && command[2]=='k' && command[3]=='e' && command[4]==' ')// command start with like keyword
    {
        Like(command, currentUserName, posts, len);
        main();

    }
    else if(command[0]=='d'&& command[1]=='e' && command[2]=='l' && command[3]=='e' && command[4]=='t' && command[5]=='e' && command[6]==' ')// command start with delete keyword
    {
        Delete(command, currentUserName, posts, len);
        main();

    }
    else if(command[0]=='f'&& command[1]=='i' && command[2]=='n' && command[3]=='d' && command[4]=='_' && command[5]=='u' && command[6]=='s' && command[7]=='e' && command[8]=='r' && command[9]==' ')// command start with find_user keyword
    {
        Find(command, currentUserName, users, posts, len);
        main();

    }
    else if(command[0]=='f'&& command[1]=='i' && command[2]=='l' && command[3]=='e' )// command start with file keyword
    {
        File_save(users, posts);
        main();

    }
    else if(command[0]=='e'&& command[1]=='x' && command[2]=='i' && command[3]=='t' )// command start with exit keyword
    {
        free(users);
        free(posts);
        free(users);
        free(currentUserName);
        free(command);
        free(posts);
    }
    else
    {
        printf("incorrect command!\n");
        main();
    }
    return 0;


}
