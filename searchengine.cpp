/*
//////////////////////////////Term Project Data Structure Lab(CS-210)///////////////////////////////
///////////////////////////Text Search Engine///////////////////////////////////////////////////////
//////////////Algorithm is based on Hash Table Searching//////////////////////////////////////////

Author - Chetan Anand
Roll no- 11010117

*/

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<string>
#include<sstream>
using namespace std;
#define MAX 100000

struct node *ht[MAX]={NULL};
struct node *pht[MAX]={NULL};

const char fn[53][14]={ "file1.txt","file2.txt","file3.txt","file4.txt","file5.txt","file6.txt","file7.txt","file8.txt","file9.txt","file10.txt",
                        "file11.txt","file12.txt","file13.txt","file14.txt","file15.txt","file16.txt","file17.txt","file18.txt","file19.txt","file20.txt",
                        "file21.txt","file22.txt","file23.txt","file24.txt","file25.txt","file26.txt","file27.txt","file28.txt","file29.txt","file30.txt",
                        "file31.txt","file32.txt","file33.txt","file34.txt","file35.txt","file36.txt","file37.txt","file38.txt","file39.txt","file40.txt",
                        "file41.txt","file42.txt","file43.txt","file44.txt","file45.txt","file46.txt","file47.txt","file48.txt","file49.txt","file50.txt",
                        };

///////////////////////////////////////////////////////////////////////////////////////////////
struct node
{
    char hword[200];
    int fileno;
    int lineno;
    int wordno;  //type of data in the node
    struct node *ptr;   //pointer data in the node
};

struct node word1[MAX];
struct node word2[MAX];

///////////////// defining the createnode function which returns the node type adress/////////////////////////
struct node *createnode()
{
    struct node *temp;
    temp=(struct node*)malloc(sizeof(struct node));
    temp->ptr=NULL;
    return temp;
};
//////////////////////////////////////////////////////

int hashfunc(char *a,int size)
{
    int i,count=0;
    for(i=0;i<size;i++)
    {
        count=(count+i*a[i])%100000;
    }
    return count;
}
///////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////
void insert(int hvalue,struct node *temp)
{
    struct node *temp1;
    if(ht[hvalue]==NULL){ht[hvalue]=temp;}
    else
    {
        temp1=ht[hvalue];
        while((temp1->ptr)!=NULL)
        {
            temp1=temp1->ptr;
        }
        temp1->ptr=temp;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////It is the most important function of this programme. It read all the words (neglecting the special charatcters) and extracting the important information like  1.No of lines 2.No of words. 3.Word and line loaction of a particular word.

int index(const char *fname,int fileno)
{
    char ch;
    int i,j,now=0,nol=1,tow=0,hvalue;
    struct node *temp1;
    FILE *ptr=fopen(fname,"r");
    ch=fgetc(ptr);
    while(ch!=EOF)
    {
        //ch=fgetc(ptr);
        if(ch=='\n'){nol++;tow=tow+now;now=0;ch=fgetc(ptr);}
        else if((ch<='z' && ch>='a')||(ch<='Z' && ch>='A'))
        {
            char word[200]={};
            now++;
            for(i=0;(ch<='z' && ch>='a')||(ch<='Z' && ch>='A')||(ch>=0&&ch<=9);i++)
            {
                word[i]=ch;
                ch=fgetc(ptr);
                //if(ch=='\n'){nol++;now=0;}
            }
            //////////////////////////////////////////////////
            temp1=createnode();
            temp1->lineno=nol;
            temp1->wordno=now;
            temp1->fileno=fileno;
            for(j=0;j<i;j++)
            {
                temp1->hword[j]=word[j];
            }
            hvalue=hashfunc(word,i);
            insert(hvalue,temp1);
            //////////////////////////////////////////////////
            /*puts(word);
            printf("its hash value is %d\n",hvalue);
            printf("word size is %d\n",i);
            printf("its word position is %d ",now);
            printf("its line position is %d",nol);
            printf("\n");*/
        }
        else{ch=fgetc(ptr);/*printf("c\n");*/}
    }
    tow=tow+now;
    //printf("Total no of words in the file = %d\n",tow);
    //printf("Total no of lines in the file = %d\n",nol);
    return 1;
}
//////////////////////////////////////////////////////////////
//////////////display all the content in the given bucket of a particular hash value
void display(int hvalue)
{
    struct node *temp;
    temp=ht[hvalue];
    cout<<temp<<endl;
    if(temp!=NULL)
        while(temp!=NULL)
        {
            puts(temp->hword);
            printf("Its file no = %d\n",temp->fileno);
            printf("Its line no = %d\n",temp->lineno);
            printf("Its word no = %d\n",temp->wordno);
            temp=temp->ptr;
        }
    else
    {
        printf("Sorry there is no word in the file which you have typed\n");
    }
}

///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
int searchp(int n)
{
    struct node *temp1;
    struct node *temp2;
    struct node *temp3;
    int i;
    int flag1;int flag2;int cnt=0;
    for(i=1;i<n;i++)
    {
        temp1=pht[0];flag1=0;
        while(temp1!=NULL)
        {
            temp2=pht[i];
            while(temp2!=NULL)
            {
                if((temp1->fileno==temp2->fileno)&&(temp1->lineno==temp2->lineno)&&(temp1->wordno+i==temp1->wordno))
                {
                    temp3=temp1;flag1=1;cnt++;break;
                }
                temp2->ptr=temp2;
            }
            temp1->ptr=temp1;
            if(flag1==1){break;}
        }
    }
    if(cnt==n-1)
    {
        printf("The phrase is found\n");
        printf("Its file no = %d",temp3->fileno);
        printf("Its file no = %d",temp3->lineno);
        printf("Its file no = %d",temp3->wordno);
    }
}

//////////////////////////////////////////////////////////////////////////
void dispword(int hvalue,char *sword)
{
    struct node *temp;
    temp=ht[hvalue];
    if(temp!=NULL)
    {
        while(temp!=NULL)
        {
            if(strncmp(temp->hword,sword,strlen(sword))==0)
            {
                puts(sword);
                printf("Its file no = %d\n",temp->fileno);
                printf("Its line no = %d\n",temp->lineno);
                printf("Its word no = %d\n",temp->wordno);
            }
            temp=temp->ptr;
        }
    }
    else
    {
        printf("There is no such input present in the files\n");
    }

}
//////////////////////////////////////////////////////////////////////////////
void dispphrase(int hvalue,char *sword)
{
    struct node *temp,*temp1;
    temp=pht[hvalue];
    if(temp!=NULL)
    {
        while(temp!=NULL)
        {
            if(strncmp(temp->hword,sword,strlen(sword))==0)
            {
               /* puts(sword);
                printf("Its file no = %d\n",temp->fileno);
                printf("Its line no = %d\n",temp->lineno);
                printf("Its word no = %d\n",temp->wordno);
                if(i==0)
                {
                    word1[j].fileno=temp->fileno;
                    word1[j].lineno=temp->lineno;
                    word1[j].wordno=temp->wordno;
                }
                else
                {
                    word2[j].fileno=temp->fileno;
                    word2[j].lineno=temp->lineno;
                    word2[j].wordno=temp->wordno;
                }
                j++;*/
                temp1=createnode();
                temp1->fileno=temp->fileno;
                temp1->lineno=temp->lineno;
                temp1->wordno=temp->wordno;
                temp1->ptr=temp1;
            }
            temp=temp->ptr;
        }
    }
}

//////////////////reading string from input///////////////////////////////////
void searching()
{
    int hvalue;
    char sword[100],ch='&';
    //s canf("%s",sword);
    int i;
    //int flag=0;
    for(i=0;ch!='\n';i++)
    {
        scanf("%s",sword);
        ch=getchar();
        puts(sword);
        //printf("the word lenth is %d\n",strlen(sword));
        hvalue=hashfunc(sword,strlen(sword));
        //display(hvalue);
        dispword(hvalue,sword);

    }
}

/////////////////////////////////////////////////////////////
/*void searching()
{
    int i,j,k;
    gets(sword);

}*/
///////////////////////////////////////////////////////////////

int initiate()
{
    int i;
    for(i=0;i<9;i++)
    {
        index(fn[i],i+1);
    }
    return 1;
}

////////////////////////////////////////////////////////////
/*
struct *node()
{
    int i;
    int j;
    int k;
    char *a[];
    int temp;
}

temp=malloc(int *)sizeof(* node);

void main()
{
    int i,j,k;
    return 0;
}

*/
/////////////////////////////////////////


int main()
{
    //index();
    //display(3810);


    int i;
    char ch='/';
    //const char fname[53]="text1.txt";
    printf("/////////////////////////////////////////////////\n");
    printf("Welcome to the search engine based on hash table\n");
    printf("press y to index the whole data\n");
    scanf("%c",&ch);
    printf("Indexing Process starts ....................\n");
    if(ch=='y')
    {
        if(initiate())
        {
            printf("Indexing process complete...............\n");
        }
        else{printf("Some error occured while indexing\n");}
    }
    else{return 0;}
    //display(3810);
    printf("Now you can continue with the search.......\n");
    printf("Type the word for searching\n");
    while(ch=='y')
    {
        searching();
        printf("do you want to continue searching (y/n)? ");
        //getchar();
        scanf("%c",&ch);
    }

    return 0;
    /*struct node *temp;
    temp=createnode();
    ht[2]=temp;
    temp->lineno=12;
    temp->ptr=createnode();
    temp=temp->ptr;
    temp->lineno=15;
    for(i=0;i<10;i++)
    {
        cout<<ht[i]<<endl;
        if(ht[i]!=NULL)
        {
            struct node *temp1;
            temp1=ht[i];
            //printf("%d",temp1);
            while(temp1!=NULL)
            {
                //puts((temp->hword));
                printf("%d ",temp1->lineno);
                temp1=temp1->ptr;
            }
            printf("\n");
        }
    }*/

    //return 0;
}

