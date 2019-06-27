#include <iostream>
#include <string>

#include <stdio.h>
#include <dirent.h>*

#ifndef WIN32
    #include <sys/types.h>
#endif

typedef struct dirent* SDIR;

int main()
{
  std::string actualElt{};
  std::string newElt{};

  std::cout << "Enter the part of the name to change >";
  std::getline(std::cin, actualElt);
  std::cout << "Enter the new name >";
  std::getline(std::cin, newElt);

  std::string path{"D:\\2018 - samuel"};

  DIR* rep = NULL;
  rep = opendir(path.c_str());
  SDIR actualFile = NULL;

  if (rep == NULL) return 1;

  /* We open the directory and read what's inside */
  while ((actualFile = readdir(rep)) != NULL){

    std::cout << actualFile->d_name << std::endl;

    auto findName = static_cast<std::string>(actualFile->d_name).find(actualElt);
    if (findName != std::string::npos){
      std::cout << "First occurrence is " << findName << std::endl;
      std::string newName{};

      // step to create the new name taking into account the other elements
      for(auto i{0}; i<findName; ++i){
        newName += actualFile->d_name[i];
      }
      newName += newElt;
      for(int j{findName + actualElt.size()}; j < static_cast<std::string>(actualFile->d_name).size(); ++j){
        newName += actualFile->d_name[j];
      }

      std::string myString(actualFile->d_name);
      std::string oldPath = path + "\\" + static_cast<std::string>(actualFile->d_name);
      std::string newPath = path + "\\" + newName;

      std::cout << oldPath << " /// " << newPath << std::endl;

      std::cout << newName << std::endl;
      if (rename(oldPath.c_str(), newPath.c_str()) == 0)
        std::cout<< "OK" << std::endl;
      else {
        perror("Error renaming file ");
      }
    }
  }

  if (closedir(rep) == -1) return -1;

  std::cout << "End of the program" << std::endl;
  return 0;
}
