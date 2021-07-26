#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(void)
{
   int count = 0, n = 11, i = 0, j = 0;

   // n is a total submission file in a directory.

   struct dirent *submition_directory;

   char totalDirectory[n][50];            //directory name are stored in this array.
   int rollNo[n], status[n];              //roll no. and status are stored in this array.
   char correctName[50] = "CP_Lab_01_CE"; // correct name of submission.
   int correctNameLength = strlen(correctName);

   DIR *directory = opendir("./lab_01"); //open directory.

   if (directory == NULL) // if directory not find then run this code.
   {
      printf("Could not open current directory");
      return 0;
   }

   // current directory and parent directory (. and ..) are ignore so count is >1.

   while ((submition_directory = readdir(directory)) != NULL)
   {
      status[i] = 1, j = 0, rollNo[i] = 0; //initialise with 0.

      if (count > 1)
      {

         //copy file name in totalDirectory array.

         strcpy((totalDirectory[i]), (submition_directory->d_name));

         //cheak the file name is wrong or not and cheak status is 0 or 1.

         while (j < correctNameLength)
         {
            if (totalDirectory[i][j] != correctName[j])
            {
               status[i] = 0;
               break;
            }
            j++;
         }

         //Find roll no.

         int str_length = strlen(totalDirectory[i]), l = 0;
         char roll[4];
         for (int k = (str_length - 7); k < (str_length - 4); k++, l++)
         {
            roll[l] = totalDirectory[i][k];
         }
         roll[3] = '\0';
         rollNo[i] = (atoi(roll));

         ++i;
      }
      ++count;
   }

   //print matching and non-matching file name

   for (j = 0; j < n; j++)       //non-matching file name.
   {
      if (status[j] == 0)
      {
         printf("don't match : %s\n", totalDirectory[j]);
      }
   }
   for (j = 0; j < n; j++)       //matching file name.
   {
      if (status[j] == 1)
      {
         printf("match : %s\n", totalDirectory[j]);
      }
   }

   closedir(directory); //close directory.

   //create a file results.txt and store roll no. and status according roll no.

   FILE *result;        //declare a file.
   result=fopen("results.txt","w");       //open a file in write mode.

   //sort data according roll no.

   for ( i = 0; i < n; i++)
   {
      for ( j = 0; j < n-i-1; j++)
      {
         if (rollNo[j]>rollNo[j+1])
         {
            int temp=rollNo[j];
            rollNo[j]=rollNo[j+1];
            rollNo[j+1]=temp;

            temp=status[j];
            status[j]=status[j+1];
            status[j+1]=temp;
         }
         
      }
      
   }

   for ( j = 0; j < n; j++)         //print data in results.txt file.
   {
      fprintf(result,"Roll No : %d  Score : %d\n",rollNo[j],status[j]);
   }

   printf("\ncontents to file written successfully !\n\n");
 
   fclose(result);

   result=fopen("results.txt","r");       //open a file in read mode.

   printf("Reading file\n");

   for ( j = 0; j < n; j++)         //read data in results.txt file.
   {
      fscanf(result,"Roll No : %d  Score : %d\n",&rollNo[j],&status[j]);
      printf("roll_no = %d score = %d\n",rollNo[j],status[j]);
   }

   fclose(result);         //close a file.

   return 0;
}
