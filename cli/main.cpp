#include <iostream>
#include <string>
#include "command_handler.h"

int main() {
  bool keep_running = true;

  std::string website_url;
  std::string platform;
  std::string confirm;

  std::string welcome_message = "Welcome to ILOVENATIVE CLI\nConvert any website to native app";
  std::string ascii_art = R"(
  //               ,--,                                                                          ,----,                               
  //            ,---.'|       ,----..                                  ,--.                    ,/   .`|                               
  //       ,---,|   | :      /   /   \                  ,---,.       ,--.'|   ,---,          ,`   .'  :   ,---,                ,---,. 
  //    ,`--.' |:   : |     /   .     :        ,---.  ,'  .' |   ,--,:  : |  '  .' \       ;    ;     /,`--.' |       ,---.  ,'  .' | 
  //    |   :  :|   ' :    .   /   ;.  \      /__./|,---.'   |,`--.'`|  ' : /  ;    '.   .'___,/    ,' |   :  :      /__./|,---.'   | 
  //    :   |  ';   ; '   .   ;   /  ` ; ,---.;  ; ||   |   .'|   :  :  | |:  :       \  |    :     |  :   |  ' ,---.;  ; ||   |   .' 
  //    |   :  |'   | |__ ;   |  ; \ ; |/___/ \  | |:   :  |-,:   |   \ | ::  |   /\   \ ;    |.';  ;  |   :  |/___/ \  | |:   :  |-, 
  //    '   '  ;|   | :.'||   :  | ; | '\   ;  \ ' |:   |  ;/||   : '  '; ||  :  ' ;.   :`----'  |  |  '   '  ;\   ;  \ ' |:   |  ;/| 
  //    |   |  |'   :    ;.   |  ' ' ' : \   \  \: ||   :   .''   ' ;.    ;|  |  ;/  \   \   '   :  ;  |   |  | \   \  \: ||   :   .' 
  //    '   :  ;|   |  ./ '   ;  \; /  |  ;   \  ' .|   |  |-,|   | | \   |'  :  | \  \ ,'   |   |  '  '   :  ;  ;   \  ' .|   |  |-, 
  //    |   |  ';   : ;    \   \  ',  /    \   \   ''   :  ;/|'   : |  ; .'|  |  '  '--'     '   :  |  |   |  '   \   \   ''   :  ;/| 
  //    '   :  ||   ,/      ;   :    /      \   `  ;|   |    \|   | '`--'  |  :  :           ;   |.'   '   :  |    \   `  ;|   |    \ 
  //    ;   |.' '---'        \   \ .'        :   \ ||   :   .''   : |      |  | ,'           '---'     ;   |.'      :   \ ||   :   .' 
  //    '---'                 `---`           '---" |   | ,'  ;   |.'      `--''                       '---'         '---" |   | ,'   
  //                                                `----'    '---'                                                        `----'     
  //                                                                                                                                  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
  )";

  std::string step_1 = "Enter the website URL";
  std::string step_2 = "Choose target Platform[Win/Mac/Linux]";

  while (keep_running) {
    std::cout<< ascii_art << std::endl;
    std::cout << welcome_message << std::endl;

    while(true){
      std::cout << step_1 << std::endl;
      std::cin >> website_url;
      if(isValidURL(website_url)) break;
      std::cout << "Please enter a valid URL" << std::endl;
    }

    while(true){
      std::cout << step_2 << std::endl;
      std::cin >> platform;
      if(isValidPlatform(platform)) break;
      std::cout << "Please enter a valid platform" << std::endl;
    }
    
    std::cout << "Please confirm the following details[Y/n]:\n"
          << "Website: " << website_url << "\n"
          << "Platform: " << platform << std::endl;
    std::cin >> confirm;

    if (confirm == "Y" || confirm == "y" || confirm.empty()) {
      std::cout << "\nDetails confirmed. Proceeding...\n";
      // invoke api
      command_handler(website_url, platform);
      keep_running = false;
    } else {
        std::cout << "\nRestarting input...\n\n";
      }
    }
  return 0;

}
