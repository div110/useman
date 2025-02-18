#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//TODO all to lower/upper case

char input[21];
int lines=0;
int max_length;
int length=0;
char * search;


void help(){
printf("\nList of availible inputs:\nhelp - show this dialog\nUSE - USE Flag configuration mode\nVIDEO_CARDS - VIDEO_CARDS configuration mode\nMAKEOPTS - MAKEOPTS configuration mode\nACCEPT_LICENSE - ACCEPT_LICENSE configuration mode\nexit - exit program without saving changes\n\n");
}
//mark action
void action(char * name){

	char name_true[strlen(name)+3];
	name_true[0]=' ';
	for(int i=0;i<strlen(name_true);i++)
	{name_true[i+1]=name[i];} //changing name to name_true fixes Xkde bug
	//name_true[strlen(name_true)]=' ';	
	name_true[strlen(name)+1]=' ';
	name_true[strlen(name)+2]='\0';
	

	char * pSubstring=strstr(search,name_true);
	if(pSubstring!=NULL)
		{
			//todo REMOVE CORRECT SPACES, sidequest
			//printf("Found:/%s/\n",name_true);
			for(int j=0;j<strlen(name_true)-1;j++){
			for(int i=0;i<(strlen(search)-(strlen(search)-(strlen(pSubstring))));i++){
			pSubstring[i]=pSubstring[i+1];
			}
		}

		}
	else
		{
			//printf("name_true:%s\n",name_true);
			//for(int i=0;i<strlen(name_true);i++)
			//{
				strcat(search,name_true);
			//}
			//printf("final:%s\n",search);
			
		}
	//printf("now should clense\n");	
	

	//cleaning name_true
	for(int i=0;i<sizeof(name_true);i++){name_true[i]='\0';}
	//printf("after clense:/%s/\n",name_true);
}
 ///////USE////////USE/////////USE/////////USE////////USE/////////USE/////////////////
/////////////////////////////////////////////////////////////////////////////////////
//void list(char category[4],char pcontents[lines][max_length])
//{
//char * search;
//	for(int i=0;i<lines;i++)
//	{
//		search = strstr(pcontents[i],category);
//		if(search!=NULL){break;}
//	}
//search=search+5;
//search[strlen(search)-1]='\0';
//printf("Found at: %p\n", search);
//printf("Dereference: %s\n",search);
//}

//mark use
void use(char pcontents[lines][max_length]){

//char * search;

	for(int i=0;i<lines;i++)
	{
		search = strstr(pcontents[i],"USE");
		if(search!=NULL){break;}
	}

search=search+5;
search[strlen(search)-1]=' ';

do
{
	printf("USEconf: ");
	scanf("%s",input);
	if(strlen(input)>20){printf("BUFFER OVERFLOW\n");exit(1);}
	else if(strcmp(input,"list")==0){printf("\n%s\n\n",search);}
	else if(strcmp(input,"exit")!=0){action(input);printf("\n%s\n",search);}
}
while(strcmp(input,"exit")!=0);
input[1]='\0';
}
 ////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

//mark makeopts
void makeopts(char pcontents[lines][max_length]){

//char * search;
	for(int i=0;i<lines;i++)
	{
		search = strstr(pcontents[i],"MAKEOPTS");
		if(search!=NULL){break;}
	}
if(search!=NULL){search=search+10;
search[strlen(search)-1]=' ';
}

do
{
	printf("MAKEOPTSconf: ");
	scanf("%s",input);
	if(strlen(input)>20){printf("BUFFER OVERFLOW\n");exit(1);}
	else if(strcmp(input, "list")==0){printf("\n%s\n\n",search);}
	else if(strcmp(input,"exit")!=0){action(input);printf("\n%s\n",search);}
}
while(strcmp(input,"exit")!=0);
input[1]='\0';
}

//mark video
void video_cards(char pcontents[lines][max_length]){
for(int i=0;i<lines;i++)
{
search = strstr(pcontents[i],"VIDEO_CARDS");
if(search!=NULL){break;}
}
if(search!=NULL){search=search+13;
search[strlen(search)-1]=' ';
}
do
{
	printf("VIDEO_CARDS: ");
	scanf("%s",input);
	
	if(strlen(input)>20){printf("BUFFER OVERFLOW\n");exit(1);}
	else if(strcmp(input, "list")==0){printf("\n%s\n\n",search);}
	
	else if(strcmp(input,"exit")!=0){
		
		if(strcmp(input,"nvidia")==0){action(input);}
		else if(strcmp(input,"amdgpu")==0){action(input);}
		else if(strcmp(input,"nouveau")==0){action(input);}
		else if(strcmp(input,"radeonsi")==0){action(input);}
		else if(strcmp(input,"intel")==0){action(input);}
		else if(strcmp(input,"vc4")==0){action(input);}
		else if(strcmp(input,"virgl")==0){action(input);}
		else if(strcmp(input, "d3d12")==0){action(input);}
		else{printf("Unrecognized Flag :( \n");}

		printf("\n%s\n\n",search);}
}
while(strcmp(input,"exit")!=0);
input[1]='\0';
}
//mark accept_license()
void accept_license(char pcontents[lines][max_length]){
for(int i=0;i<lines;i++){
search = strstr(pcontents[i],"ACCEPT_LICENSE");
if(search!=NULL){break;}
}
if(search!=NULL){search=search+16;
search[strlen(search)-1]=' ';
}
do
{
	printf("ACCEPT_LICENSE: ");
	scanf("%s",input);
	if(strlen(input)>30){printf("BUFFER OVERFLOW\n");exit(1);}
	else if(strcmp(input,"list")==0){printf("\n%s\n\n",search);}
	else if(strcmp(input,"exit")!=0){
		action(input);
	}
}
while(strcmp(input,"exit")!=0);
input[1]='\0';
}





//mark main
int main(int argc, char* argv[]){

FILE *file;
file = fopen("/etc/portage/make.conf","r");
char buf[100000];
fscanf(file,"%[^#]",buf);
printf("%s\n", buf);

lines=0;
length=0;
max_length=0;
for(int i=0;i<strlen(buf);i++){
	length++;
	if(buf[i]=='\n'){lines++;length=0;}
	if(length>max_length){max_length=length;}
}
max_length = 2 * max_length;
char contents[lines][max_length];


//filling matrix with '\0'
for(int i=0;i<lines;i++){for(int j=0;j<max_length;j++){contents[i][j]='\0';}}


lines=0;
int index=0;
for(int loko=0;loko<strlen(buf);loko++){
if(buf[loko]=='\n'){lines++;index=0;}
else{contents[lines][index]=buf[loko];
index++;
//printf("%c\n",contents[lines][index]);
}
}




//mark loop
do
	{
	printf("tool: ");
	scanf("%s",input);
	if(strlen(input)>20){printf("BUFFER OVERFLOW\n");exit(1);}
	if(strcmp(input,"USE")==0){use(contents);}
	else if(strcmp(input,"VIDEO_CARDS")==0){video_cards(contents);}
	else if(strcmp(input,"MAKEOPTS")==0){makeopts(contents);}
	else if(strcmp(input,"ACCEPT_LICENSE")==0){accept_license(contents);
	}
	else if(strcmp(input,"help")==0||strcmp(input,"h")==0){help();}
	else if(strcmp(input,"exit")!=0){printf("unrecognized; type 'help' to see availible commands\n");}
	}
	while(strcmp(input,"exit")!=0); //this is stupid non-sense




return 0;}
