#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include<conio.h>
#define rmin 1
#define rmax 18
#define cmin 1
#define cmax 38
using namespace std;
struct node
{
    int x,y;
    char data;
    node *next,*prev;
}*start;
struct food
{
    int x;
    int y;
    char value;
}f;
struct poison
{
    int x,y;
    char value;
}f1;
void savegame(struct node *start,struct food f,struct poison f1,int points)
{
     FILE *fp,*fp1,*fp2,*fp3;
   fp=fopen("snake.txt","w");
   fp1=fopen("food.txt","w");
   fp2=fopen("points.txt","w");
   fp3=fopen("poison.txt","w");
   struct node *p1=start;
   while(p1!=NULL)
   {
       putc(p1->x+'0',fp);
       putc(p1->y+'0',fp);
       putc(p1->data,fp);
       putc('\n',fp);
       p1=p1->next;
   }
   putc(f.x+'0',fp1);
   putc(f.y+'0',fp1);
   putc(f.value,fp1);
   putc(points+'0',fp2);
   putc(f1.x+'0',fp3);
   putc(f1.y+'0',fp3);
   putc(f1.value,fp3);
   fclose(fp);
   fclose(fp1);
   fclose(fp2);
}
struct node *insertsavedsnake(struct node *start,int p,int o,char i)
{
    struct node *ptr,*n=new node;
    ptr=start;
    if(start==NULL)
    {
        n->x=p;
        n->y=o;
        n->data=i;
      n->next=NULL;
      n->prev=start;
      start=n;
    }
    else
    {
        while(ptr->next!=NULL)
        {
            ptr=ptr->next;
        }
        n->x=p;
        n->y=o;
        n->data=i;
        ptr->next=n;
        n->next=NULL;
        n->prev=ptr;
    }
    return start;

};
struct node * resumegame(char board[20][40],struct node *start,struct food *f,struct poison *f1,int *points)
{
    FILE *fp,*fp1,*fp2,*fp3;
   fp=fopen("snake.txt","r");
   fp1=fopen("food.txt","r");
   fp2=fopen("points.txt","r");
   fp3=fopen("poison.txt","r");
    int p,o;
    char ch,ch1,ch2,i;
    ch=getc(fp);
   while(ch!=EOF)
   {
       if(ch!='\n')
       {   p=ch-'0';
           ch=getc(fp);
          o=ch-'0';
           ch=getc(fp);
           i=ch;
           start=insertsavedsnake(start,p,o,i);
       }
       ch=getc(fp);
   }
    ch1=getc(fp1);
    while(ch1!=EOF)
    {
    f->x=ch1-'0';
    ch1=getc(fp1);
    f->y=ch1-'0';
    ch1=getc(fp1);
    f->value=ch1;
    board[f->x][f->y]=f->value;
    ch1=getc(fp1);
    }
    ch2=getc(fp2);
    while(ch2!=EOF)
    {
    f1->x=getc(fp3)-'0';
    f1->y=getc(fp3)-'0';
    f1->value=getc(fp3);
    board[f1->x][f1->y]=f1->value;
    ch2=getc(fp2);
    }
    *points=getc(fp2)-'0';
    return start;
}
struct node *insertend(struct node *start)
{

    char value;
    int i,j;
    cout<<"enter snake body :"<<endl;
    cin>>value;
    cout<<"enter snake coordinates :"<<endl;
    cin>>i>>j;
    node *temp;
    temp=new node;

    if(start==NULL)
    {
        temp->x=i;
        temp->y=j;
        temp->data=value;
        temp->prev=NULL;
        temp->next=NULL;
        start=temp;
    }
    else
    {
        node *temp1;
        temp1=start;
        while(temp1->next!=NULL)
        {
            temp1=temp1->next;
        }
        node *temp;
        temp=new node;
        temp->x=i;
        temp->y=j;
        temp->data=value;
        temp->next=NULL;
        temp->prev=temp1;
        temp1->next=temp;

    }

    return start;
}
void eatfood(struct node *start,char x)
{
        node *temp1;
        temp1=start;
        while(temp1->next!=NULL)
        {
            temp1=temp1->next;
        }
        node *temp;
        temp=new node;
        temp->x=temp1->x;
        temp->y=temp1->y-1;
        temp->data=x;
        temp->next=NULL;
        temp->prev=temp1;
        temp1->next=temp;
}
void eatpoison(struct node *start)
{
    node * temp1;
    temp1=start;
    while(temp1->next!=NULL)
    {
        temp1=temp1->next;
    }
    node *temp;
    temp=temp1;
    temp1->prev->next=NULL;
    delete temp;
}

void makefood(char board[20][40])
{
    f.x=(rand()%(rmax-rmin+1))+rmin;
    f.y=(rand()%(cmax-cmin+1))+cmin;
    f.value='*';
    board[f.x][f.y]=f.value;
}
void makepoison(char board[20][40])
{
    f1.x=(rand()%(rmax-rmin+1))+rmin;
    f1.y=(rand()%(cmax-cmin+1))+cmin;
    f1.value='P';
    board[f1.x][f1.y]=f1.value;
}
void display(struct node *start,char board[20][40],int score,int points)
{
    int i,j;
    struct node *ptr=start;
    cout<<"distance ->"<<score<<"       "<<"points ->"<<points<<endl;
    while(ptr!=NULL)
    {
        board[ptr->x][ptr->y]=ptr->data;
        ptr=ptr->next;
    }
    for(i=0;i<20;i++)
    {
        for(j=0;j<40;j++)
        {
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }

}
bool checkfoodonsnake(struct node *start,struct food f)
{
    struct node *ptr=start;
    int flag=0;
    while(ptr!=NULL)
    {
     if(f.x==ptr->x&&f.y==ptr->y)
     {
         return 1;
     }
     ptr=ptr->next;
    }
        return 0;
}
bool checkpoisononsnake(struct node *start,struct poison f1)
{
    struct node *ptr=start;
    int flag=0;
    while(ptr!=NULL)
    {
     if(f1.x==ptr->x&&f1.y==ptr->y)
     {
         return 1;
     }
     ptr=ptr->next;
    }
        return 0;
}
bool checkgameover(struct node *start)
{
    struct node *ptr=start->next;
    int flag=0;
    while(ptr!=NULL)
    {
        if(start->x==ptr->x&&start->y==ptr->y)
        {
            flag=1;
            break;
        }
        ptr=ptr->next;
    }
    if(flag==1)
        return 1;
    else
        return 0;


}
void swap(struct node *start,int row,int col)
{
    if(start->next!=NULL)
    {
    int x1,x2,y1,y2;
   struct node *ptr=start;
   x1=ptr->x;
   y1=ptr->y;
while(ptr->next!=NULL)
{
   ptr=ptr->next;
   x2=ptr->x;
   y2=ptr->y;
    ptr->x=x1;
 ptr->y=y1;
 x1=x2;
 y1=y2;
}
    }
 start->x=row;
 start->y=col;

}
void clearboard(char board[20][40])
{
    int i,j;
      for(i=0;i<20;i++)
    {
        for(j=0;j<40;j++)
        {
            if(i==0 ||i==19 ||j==0 ||j==39){board[i][j]='+';}
             else if(board[i][j]!=f.value&&board[i][j]!=f1.value) board[i][j]=' ';
        }
    }
}

void snakegame(char board[20][40],int option)
{
    int t=2,score=0,points=0;
    struct node *ptr=start;
    if(option==2)
    {
    makefood(board);
    while(checkfoodonsnake(start,f));
    {
        board[f.x][f.y]=' ';
        makefood(board);
    }
       makepoison(board);
       while(checkpoisononsnake(start,f1));
    {
        board[f1.x][f1.y]=' ';
        makepoison(board);
    }

     ptr=insertend(start);
    start=ptr;
    while(t--)
    {
        ptr=insertend(ptr);
    }
    display(start,board,score,points);
    }
    else if(option==1)
    {
        start=resumegame(board,start,&f,&f1,&points);
        display(start,board,score,points);
    }
    while(1)
    {
         cout<<"PRESS w(up),d(right),s(down),a(left)";

        char ch;
        cin>>ch;
         int r,c;
        if(ch=='w')
        {
            ptr=start;
            if(ptr->x==1)
            {
                r=rmax;
                 c=ptr->y;
            }
            else
            {
                r=ptr->x-1;
                c=ptr->y;
            }
            if(r!=start->next->x)
            {
                swap(start,r,c);
                score++;
            }
             if(checkgameover(start))
            {
                cout<<"GAME OVER";
                break;
            }

        }
        else if(ch=='s')
        {
            ptr=start;
            if(ptr->x==rmax)
            {
                r=rmin;
                c=ptr->y;
            }
            else
            {
                r=ptr->x+1;
                c=ptr->y;
            }
            if(r!=start->next->x)
            {
                swap(start,r,c);
                score++;
            }
             if(checkgameover(start))
            {
                cout<<"GAME OVER";
                break;
            }
        }
        else if(ch=='d')
        {
            ptr=start;
            if(ptr->y==cmax)
            {
                r=ptr->x;
                c=cmin;
            }
            else
            {
                r=ptr->x;
                c=ptr->y+1;
            }
            if(c!=start->next->y)
            {
                swap(start,r,c);
                score++;
            }
             if(checkgameover(start))
            {
                cout<<"GAME OVER";
                break;
            }

        }
        else if(ch=='a')
        {
            ptr=start;
            if(ptr->y==cmin)
            {
                r=ptr->x;
                c=cmax;
            }
            else
            {
                r=ptr->x;
                c=ptr->y-1;
            }
            if(c!=start->next->y)
            {
                swap(start,r,c);
                score++;
            }
             if(checkgameover(start))
            {
                cout<<"GAME OVER";
                break;
            }

        }
        else if(ch=='q')
        {
            savegame(start,f,f1,points);
            cout<<"GAME OVER";
            break;
        }
        if(start->x==f.x&&start->y==f.y)
        {
           eatfood(start,start->next->data);
           makefood(board);
           while(checkfoodonsnake(start,f))
           {
               board[f.x][f.y]=' ';
               makefood(board);
           }
           points++;
        }
         if(start->x==f1.x&&start->y==f1.y)
        {
          eatpoison(start);
           makepoison(board);
           while(checkpoisononsnake(start,f1))
           {
               board[f1.x][f1.y]=' ';
               makepoison(board);
           }
           points--;
        }
        clearboard(board);
        system("cls");
        display(start,board,score,points);
    }
}

int main()
{

     cout<<"snake game"<<endl;
    char board[20][40];
    int option;
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<40;j++)
        {
            if(i==0 || i==19 || j==0 || j==39)
            {
                board[i][j]='+';
            }
            else
            {
            board[i][j]=' ';
        }
        }
    }
    cout<<"\tOPTION 1:LOAD GAME "<<endl;
    cout<<"\tOPTION 2:NEW GAME "<<endl;
    cin>>option;
    snakegame(board,option);
}
