#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define STDNUM 20
#define MAXNUM 200
#define ID 10
#define NAME 30
#define SUB 100

typedef struct subject{
  char subid[ID];  
  char subname[SUB]; 
  int credit;
  int numofreqsub;
  char **subpre; 
}subject_t;

typedef struct student{
  char stuid[ID]; 
  char stuname[NAME];
  int numofcompsub;
  char **completed; 
}student_t;

// in mang mon hoc vao file
void printSubtoFile(char* fn, subject_t sub[], int size) {
  int i,j;
  FILE* f = fopen(fn,"a+");
  for(j=0;j<size;j++) {
    fprintf(f,"%-10s",sub[j].subid);
    fprintf(f,"%-30s",sub[j].subname);
    fprintf(f,"%-5d",sub[j].credit);
    fprintf(f,"%-5d",sub[j].numofreqsub);
    if(sub[j].numofreqsub > 0) {
      for(i=0;i<sub[j].numofreqsub;i++) {
	fprintf(f,"%-8s",sub[j].subpre[i]);
      }
    }
    fprintf(f,"\n");
  }
  fclose(f);
}
void printSub(subject_t sub[], int size) {
  int i,j;
  fprintf(stdout,"%-10s%-30s%-5s%-30s\n","ID","Name","Cre","Prior Subject");
  for(j=0;j<size;j++) {
    fprintf(stdout,"%-10s",sub[j].subid);
    fprintf(stdout,"%-30s",sub[j].subname);
    fprintf(stdout,"%-5d",sub[j].credit);
    if(sub[j].numofreqsub > 0) {
      for(i=0;i<sub[j].numofreqsub;i++) {
	fputs(sub[j].subpre[i],stdout);
	fprintf(stdout," ");
      }
    } else {
      printf("0");
    }
    printf("\n");
  }
}

//tim 1 mon trong mang
int searchSub(subject_t sub[], char *id, int size) {
  int i;
  for( i=0; i<size; i++) {
    if(strcmp(sub[i].subid, id) == 0)
      return i;
  }
  return -1;
}

// them 1 mon vao mang
void insertSubject(subject_t sub[], int *size) {  
  int i,found;
  sub[*size].subpre = (char**)malloc(sizeof(char*)*SUB);
  fscanf(stdin,"%*c");
  printf("Subject ID: "); fgets(sub[*size].subid,ID,stdin);
  sub[*size].subid[strlen(sub[*size].subid)-1] = '\0';
  found = searchSub(sub,sub[*size].subid,*size);
  if(found != -1) {
    printf("Existed subject!\n");
  } else {  
    printf("Subject's name: "); fgets(sub[*size].subname,SUB,stdin);
    sub[*size].subname[strlen(sub[*size].subname)-1]='\0';
    while(getchar()!='\n') {}
    printf("Number of credit: ");fscanf(stdin,"%d",&sub[*size].credit);
    printf("Number of required subjects: ");fscanf(stdin,"%d",&sub[*size].numofreqsub);
    if(sub[*size].numofreqsub > 0) {
      printf("Required subjects: ");
      for(i=0;i<sub[*size].numofreqsub;i++) {
	sub[*size].subpre[i] = (char*)malloc(sizeof(char)*ID);
	fscanf(stdin,"%s",sub[*size].subpre[i]);
	//  free(stu.stuname[i]);
      }
    }
    printf("\n");
  }
  printf("%s %i %i\n",sub[*size].subname,sub[*size].credit,sub[*size].numofreqsub);
  ++(*size);
}

//xoa du lieu 1 mon
void delete1Subject(subject_t sub[], int x) {
  int i;
  strcpy(sub[x].subid,"");
  strcpy(sub[x].subname,"");
  sub[x].credit = 0;
  for(i=0;i<sub[x].numofreqsub;i++) {
    strcpy(sub[x].subpre[i],"");
  }
  sub[x].numofreqsub = 0;
}

//xoa 1 mon trong mang
void deleteSubject(subject_t sub[],int *size) {
  char *id;
  int found;
  int i;
  id = (char*)malloc(sizeof(char)*ID);
  if(*size > 0) {
    printf("Enter subject ID: ");
    fscanf(stdin,"%*c");
    fgets(id,ID,stdin);
    printf("id %s\n",id);
    id[strlen(id)-1]='\0';
    found = searchSub(sub,id,*size);
    // printf("found %i\n",found);
    if(found != -1 && (*size) != 0) {
      if (found == ((*size)-1)) //Xoa ban ghi cuoi cung
	{
	  delete1Subject(sub, found);
	  --(*size);
	  printf("Ban ghi da duoc xoa.\n");
	}
      else //xoa ban ghi dau tien hoac o giua
	{
	  for (i = found; i < (*size)-1; i++)
	    {
	      sub[i] = sub[i + 1];
	      delete1Subject(sub, *size);
	    }
	  --(*size) ;
	}
    }
    else printf("Ban ghi khong ton tai. Kiem tra ID va thu lai.\n");
  }
  else printf("Khong co ban ghi nao duoc xoa\n");
}
//tim 1 hs trong mang
int searchStu(student_t stu[], char *id, int size) {
  int i;
  for( i=0; i<size; i++) {
    if(strcmp(stu[i].stuid, id) == 0)
      return i;
  }
  return -1;
}

// them 1 hs vao mang
void insertStudent(student_t stu[], int *size) {  
  int i,found;
  stu[*size].completed = (char**)malloc(sizeof(char*)*SUB);
  fscanf(stdin,"%*c");
  printf("Student ID: "); fgets(stu[*size].stuid,ID,stdin);
  stu[*size].stuid[strlen(stu[*size].stuid)-1] = '\0';
  found = searchStu(stu,stu[*size].stuid,*size);
  if(found != -1) {
    printf("Existed student\n");
  } else {  
    printf("Student's name: "); fgets(stu[*size].stuname,SUB,stdin);
    stu[*size].stuname[strlen(stu[*size].stuname)-1]='\0';
    while(getchar()!='\n') {}
    printf("Number of completed subjects: ");fscanf(stdin,"%d",&stu[*size].numofcompsub);
    if(stu[*size].numofcompsub > 0) {
      printf("Completed subjects: ");
      for(i=0;i<stu[*size].numofcompsub;i++) {
	stu[*size].completed[i] = (char*)malloc(sizeof(char)*ID);
	fscanf(stdin,"%s",stu[*size].completed[i]);
      }
    }
    printf("\n");
  }
  ++(*size);
}

//xoa du lieu 1 hs
void delete1Student(student_t stu[], int x) {
  int i;
  strcpy(stu[x].stuid,"");
  strcpy(stu[x].stuname,"");
  for(i=0;i<stu[x].numofcompsub;i++) {
    strcpy(stu[x].completed[i],"");
  }
  stu[x].numofcompsub = 0;
}

//xoa 1 mon trong mang
void deleteStudent(student_t stu[],int *size) {
  char *id;
  int found;
  int i;
  id = (char*)malloc(sizeof(char)*ID);
  if(*size > 0) {
    printf("Enter student ID: ");
    fscanf(stdin,"%*c");
    fgets(id,ID,stdin);
    printf("id %s\n",id);
    id[strlen(id)-1]='\0';
    found = searchStu(stu,id,*size);
    if(found != -1 && (*size) != 0) {
      if (found == ((*size)-1)) //Xoa ban ghi cuoi cung
	{
	  delete1Student(stu, found);
	  --(*size);
	  printf("Ban ghi da duoc xoa.\n");
	}
      else //xoa ban ghi dau tien hoac o giua
	{
	  for (i = found; i < (*size)-1; i++)
	    {
	      stu[i] = stu[i + 1];
	      delete1Student(stu, *size);
	    }
	  --(*size) ;
	}
    }
    else printf("Ban ghi khong ton tai. Kiem tra ID va thu lai.\n");
  }
  else printf("Khong co ban ghi nao duoc xoa\n");
}
void printStu(student_t stu[], int size) {
  int i,j;
  fprintf(stdout,"%-10s%-30s%-80s\n","ID","Name","Completed Subject");
  for(j=0;j<size;j++) {
    fprintf(stdout,"%-10s",stu[j].stuid);
    fprintf(stdout,"%-30s",stu[j].stuname);
    if(stu[j].numofcompsub > 0) {
      for(i=0;i<stu[j].numofcompsub;i++) {
	fputs(stu[j].completed[i],stdout);
	fprintf(stdout," ");
      }
    } else {
      printf("0");
    }
    printf("\n");
  }
}
void printStutoFile(char* fn, student_t stu[], int size) {
  int i,j;
  FILE* f = fopen(fn,"a+");
  for(j=0;j<size;j++) {
    fprintf(f,"%-10s",stu[j].stuid);
    fprintf(f,"%-30s",stu[j].stuname);
    fprintf(f,"%-5d",stu[j].numofcompsub);
    if(stu[j].numofcompsub > 0) {
      for(i=0;i<stu[j].numofcompsub;i++) {
	fprintf(f,"%-8s",stu[j].completed[i]);
      }
    }
    fprintf(f,"\n");
  }
  fclose(f);
}
//main
int main(){
  subject_t sub[MAXNUM];
  student_t stu[MAXNUM];
  int size=0;
  int menu1, menu2, menu3, menu4;;
  char filename1[] = "ctdt.txt";
  char filename2[] = "sinhvien.txt";
  FILE* f1 = fopen(filename1,"a+");
  FILE* f2 = fopen(filename2,"a+");
 
  if(!f1) fprintf( stderr, "File not found\n" );
  else {
    if(!f2) fprintf( stderr, "File not found\n" );
    else {
    
      do {
	printf("Menu\n");
	printf("1 Chuong trinh dao tao\n");
	printf("2 Quan li sinh vien\n");
	printf("3 Thoat\n");
	printf("Your choice: ");scanf("%d",&menu1);

	switch(menu1) {
	case 1:
	  do {
	    printf("Chuong trinh dao tao\n");
	    printf("1 Them 1 mon hoc\n");
	    printf("2 Xoa 1 mon hoc\n");
	    printf("3 Hien thi danh sach mon\n");
	    printf("4 Thoat\n");
	    printf("Your choice: ");scanf("%d",&menu2);

	    switch(menu2) {
	    case 1:
	      insertSubject(sub,&size);
	      break;
	    case 2:
	      deleteSubject(sub,&size);break;
	    case 3:
	       printSub(sub,size);
	       // printSubtoFile(filename1,sub,size);
	      break;
	    case 4:
	      break;
	    default:
	      printf("Invalid choice. Choose again\n");break;
	    }
	  }while(menu2 != 4);
	  break;
	case 2:
	  do {
	    printf("Quan li sinh vien\n");
	    printf("1 Them 1 sinh vien\n");
	    printf("2 Xoa 1 sinh vien\n");
	    printf("3 Hien thi danh sach sinh vien\n");
	    printf("4 Thoat\n");
	    printf("Your choice: ");scanf("%d",&menu3);

	    switch(menu3) {
	    case 1:
	      insertStudent(stu,&size);
	      break;
	    case 2:
	      deleteStudent(stu,&size);
	      break;
	    case 3:
	      //printStu(stu,size);
	      printStutoFile(filename2,stu,size);
	      break;
	    case 4:
	      break;
	    default:
	      printf("Invalid choice. Choose again\n");break;
	    }
	  }while(menu3 != 4);
	  break;
	case 3:
	  break;
	default:
	  printf("Invalid choice. Choose again\n");break;
	}
      }while(menu1 != 3);
    }
  }
  fclose(f1);
  fclose(f2);
  return 0;
}
//printlist(head);
//  char *filename1;
//printf("File ");scanf("%s",filename1);
// createSubjectFile();
/* int i; */
/* stu.stuid = (char*)malloc(sizeof(char)*MAXNUM); */
/* stu.stuname = (char*)malloc(sizeof(char)*MAXNUM); */
/* stu.completed = (subject_t*)malloc(sizeof(subject_t)*MAXNUM); */
  
/* printf("Student ID: "); fscanf(stdin,"%s",stu.stuid); */
/* printf("Student's full name: "); fscanf(stdin,"%s",stu.stuname); */
/* while(getchar()!='\n') {} */
/* char* t = strchr( stu.stuname, '\n' ); */
/* if ( t != NULL ) *t = '\0'; */
/* printf("Number of completed subject: ");fscanf(stdin,"%d",&stu.numofcompsub); */
/* printf("Student's completed subjects: "); */
/* for(i=0;i<stu.numofcompsub;i++) { */
/*   stu.completed[i] = (char*)malloc(sizeof(char)*MAXNUM); */
/*   fscanf(stdin,"%s",stu.completed[i]); */
/*   //  free(stu.stuname[i]); */
/* }	 */
      
/* fprintf(stdout,"%-8s ",stu.stuid);  */
/* fprintf(stdout,"%-20s ",stu.stuname);  */
/* for(i=0;i<stu.numofcompsub;i++) { */
/*   fprintf(stdout,"%s ",stu.completed[i]); */
/* } */
/* printf("\n"); */
// free(stu.stuid);
//  free(stu.stuname);
//  free(stu.completed);
//sub.student = (student_t*)malloc(sizeof(student_t) *MAXNUM);
// sub.student[0] = &stu;
// fprintf(stdout,"%s %s\n",(sub.student[0])->stuid,(sub.student[0])->stuname);
