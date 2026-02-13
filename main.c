#include <ncurses.h>
#include <string.h>
#define max_lines 5


void load_file(char** buffer, char* path){
  FILE* f=fopen(path,"r");
  if (f==NULL)
  {
    for (int i = 0; i < max_lines; i++) {
      buffer[i] = strdup(""); 
    }
    return;
  }

  char line_content[1024];
  int i=0;

  while(fgets(line_content, sizeof(line_content), f) && i < max_lines){
    line_content[strcspn(line_content,"\n")]=0;
    buffer[i]=strdup(line_content);
    i++;
  }

  while(i<max_lines){
    buffer[i]=strdup("");
    i++;
  }
  fclose(f);

}


int main(int argc, char** argv){
  char* buffer[max_lines]={0};
  char* file = argv[1];

  load_file(buffer,argv[1]);


  initscr();
  cbreak();
  noecho();
  curs_set(1);

  int line=0,col=0,ch,i;
  char* mode="normal";


  while(1){
    erase();
    for (i=0;i<max_lines;i++)
    {
      mvprintw(i,0,"%s",buffer[i]);
    }
    mvprintw(LINES - 1, 0, " MODE: %-10s | Ligne: %d, Col: %d ", mode, line, col);
    move(line, col);
    refresh();


    ch = getch();
    
    if (strcmp(mode,"normal")==0){
      if (ch == 'q'){
        break;
      }

      switch (ch){

        //movements
        case 'k':
          if (line>0){
            line --;
          }
          if (col>(int)strlen(buffer[line])-1){ //if current colon < lenght of the line 
            col=(int)strlen(buffer[line])-1; //set current colon to the lenghtof the line
            //used -1 to avoid the \0
          }
          break;

        case 'j':
          if (line<max_lines-1){
            if (strlen(buffer[line+1])>0){ // or strcmp(buffer[line+1]!=0
              line ++;
            }
          }
          if (col>(int)strlen(buffer[line])-1){ //if current colon < lenght of the line 
            col=(int)strlen(buffer[line])-1; //set current colon to the lenghtof the line
          //used -1 to avoid the \0
          }
          break;

        case 'l':
          if (col<(int)strlen(buffer[line])-1){ // or if (strcmp(&buffer[line][col+1],"\0")!=0){
            col ++;
          }
          break;

        case 'h':
          if (col>0){
            col--;
          }
          break;
      
        //mode switch
        case 'i':
          mode = "insert";
          break;

        case 'v':
          mode = "visual";
          break;

      }
    }

    if (strcmp(mode,"insert")==0){
      switch (ch){
        //mode switch
        case 27: //Esc key
          mode = "normal";
          break;
      }
    }
    if (strcmp(mode,"visual")==0){
      switch (ch){
        //mode switch
        case 27: //Esc key
          mode = "normal";
          break;
        }
      }
    }
  endwin();
  return 0;
}
