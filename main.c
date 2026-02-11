#include <ncurses.h>
#include <string.h>
#define max_lines 5


char *buffer[max_lines] = {
    "Bienvenue dans l'interface ncurses.",
    "Ici, le deplacement est fluide.",
    "Utilise h, j, k, l ou les fleches.",
    "Appuie sur 'q' pour quitter.",
    "Fin du buffer."
};

int main(void){
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
    move(line, col);
    refresh();


    ch = getch();

    if (ch == 'q'){
      break;
    }

    switch (ch){
      case 'k':
        if (line>0){
          line --;
        }
        break;

      case 'j':
        if (line<max_lines-1){
          line ++;
        }
        break;

      case 'l':
        if (col<(int)strlen(buffer[line])){
          col ++;
        }
        break;

      case 'h':
        if (col>0){
          col--;
        }
        break;
      
      case 'n':
        if (strcmp(mode, "normal")==0){ //if already on normal mode
          printf("normal mode");
        }
        break;
      
      case 'i':
        if(strcmp(mode, "insert")==0){
          printf("Insert mode");
        }
        break;


    }
  }
  endwin();
  return 0;
}
