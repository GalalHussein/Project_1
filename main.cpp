/**
 * Project: [File organizing]
 * Version: 1.0.0
 * Description: [Moving all files into folders that are created according to the type of files]
 *
 * Note:
 *    This project utilizes the "dirent" library for directory traversal and management,
 * allowing it to access and read directory contents effectively across different platforms.
 * Additionally, regular expressions (`regex`) have been employed to validate and filter
 * file types, ensuring accurate categorization and processing of files based on their extensions.
 *
 * Developed by: [Galal Hussein] ,studies at the Faculty of Computers and Artificial Intelligence, Helwan University
 *
 * Date: [2/9/2024]
 */

#include <iostream>
#include <dirent.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include "pattern.h"
#include "colors.h"

using namespace std;

string MAIN_FLD_PATH;

// PROTOTYPES
 int FILE_CATEGORY(string file_name);
 DIR *OPEN_DIR();
 void GET_FILES_NAME(DIR *main_dir);
 void FILTER_CATEGORY(vector<int>categories);
 void CREATE_FLD(string new_fld_name);
  void MOVE_FILES(string File_name, string New_fld_name);

int main()
{
  GET_FILES_NAME(OPEN_DIR());

    return 0;
}


 // OPEND DIRECTOR:
 DIR *OPEN_DIR(){
   DIR *main_dir; // pointer to the main director
   string main_folder_path;
   cout << YELLOW "Enter The Folder path: ";
   do{
      getline(cin, main_folder_path);
      main_dir = opendir(main_folder_path.c_str()); // c_str() to convert string to const *char
      if(main_dir != nullptr){
          MAIN_FLD_PATH = main_folder_path; // Store Path Of the main folder, to use it in two function ( Create fld, move folder)
          cout << GREEN "Successful\n" RESET;
          break;
    }
      cerr << REDD << strerror(errno) << RESET;
      cout << YELLOW " Enter Valid path: ";
  }while(true);
  return main_dir;
}
 // ==================================



 // READ DIRECROTY:
 void GET_FILES_NAME(DIR *main_dir){
  struct dirent *in_files; // pointer to internal files in folder
  vector<int>Categories;
   while(in_files = readdir(main_dir)){
      Categories.push_back(FILE_CATEGORY(in_files->d_name));
  // cout << FILE_CATEGORY(in_files->d_name);
  // cout << endl;
  }
  FILTER_CATEGORY(Categories);
  cout << GREEN "Successful\n" RESET;

  rewinddir(main_dir);

  // Passing files name to move it:
  while(in_files = readdir(main_dir)){
    int temp = FILE_CATEGORY(in_files->d_name);
    switch(temp){
      case IMGS:
        MOVE_FILES(in_files->d_name,"Imgs");
        continue;
      case MEDIA:
         MOVE_FILES(in_files->d_name,"Multimedia");
         continue;
      case IDEAS:
         MOVE_FILES(in_files->d_name,"Ideas");
         continue;
      case DOCS:
         MOVE_FILES(in_files->d_name,"Docs");
         continue;
      case DATA:
         MOVE_FILES(in_files->d_name,"Data");
         continue;
//      case OTHERS:
//         MOVE_FILES(in_files->d_name,"Others");
//         continue;
    }
  }

  closedir(main_dir);
}
 // ===================================



 // File classification by regular expression:
 int FILE_CATEGORY(string file_name){
   if(regex_match(file_name, IMGS_PATTERN))
      return IMGS;
   else if(regex_match(file_name, MEDIA_PATERRN))
      return MEDIA;
   else if(regex_match(file_name, TXT_PATTERN))
      return IDEAS;
   else if(regex_match(file_name, DOCS_PATERRN))
      return DOCS;
   else if(regex_match(file_name, DATA_PATTERN))
      return DATA;
//   else
//      return OTHERS;
 }
 // ===================================


 /* determines the folders needed for creation
    and call function CREATE_FLD */
 void FILTER_CATEGORY(vector<int>categories){

 //Delete duplicate types:
    sort(categories.begin(), categories.end());
    vector<int>::iterator repet = unique(categories.begin(), categories.end());
    categories.erase(repet, categories.end());

    for(int i: categories){
      switch(i){
        case IMGS:
         CREATE_FLD("Imgs"); // goto create folder

         continue;
        case MEDIA:
         CREATE_FLD("Multimedia"); // goto create folder
         continue;
        case IDEAS:
         CREATE_FLD("Ideas"); // goto create folder
         continue;
        case DOCS:
         CREATE_FLD("Docs"); // goto create folder
         continue;
        case DATA:
         CREATE_FLD("Data"); // goto create folder
         continue;
//        case OTHERS:
//         CREATE_FLD("Others"); // goto create folder
//         continue;
      }
    }
 }
 // ================================


 // Create new folder:
 void CREATE_FLD(string new_fld_name){
   string new_fld_path = MAIN_FLD_PATH +"\\"+ new_fld_name;
   mkdir(new_fld_path.c_str());
   // return new_fld_path
 }
 // ================================


 // Moving files into folder:
 void MOVE_FILES(string File_name, string New_fld_name){
    string FROM_PATH = MAIN_FLD_PATH + "\\" + File_name;
    string TO_PATH = MAIN_FLD_PATH + "\\" + New_fld_name +"\\"+ File_name;
  if(rename(FROM_PATH.c_str(),(TO_PATH.c_str())))
     cerr << REDD << strerror(errno);
  else
    cout << GREEN "Complete Successful\n" RESET;
 }



