#include <stdio.h>
#include <string.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>


void do_checks(FILE* fp, const int* char_history, int cur_indx){
    printf("-----------%i\n", *(char_history+cur_indx));
    if (*(char_history+cur_indx) == 18 && *(char_history+(cur_indx-1)%6) == 25){
	fprintf(fp, "I passed the Exam!\n");
    }
    if (*(char_history+cur_indx) == 25 && *(char_history+(cur_indx-1)%6) == 30 && *(char_history+(cur_indx-2)%6) == 46){
    	fprintf(fp, "Get some cappuccino!\n");
    }
    if (*(char_history+cur_indx) == 17 && *(char_history+(cur_indx-1)%6) == 35){
	    fprintf(fp, "WEWEWE he-he\n");
    }
}

int main() {
    struct input_event inputEvent;
    ssize_t n;
    int fd;
    
    int char_history[6];
    int current_indx = 0;

    for (int i = 0; i < 6; i++){
        char_history[i] = 0;
    }

    fd = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);
    
    FILE* fp = fopen("ex3.txt", "w");
    fclose(fp);

    while (1){
    	fp = fopen("ex3.txt", "a");
    	
        n = read(fd, &inputEvent, sizeof inputEvent);
        if ((int) inputEvent.code == 0 || (int) inputEvent.code == 4){
            fclose(fp);
            continue;
        }

        switch (inputEvent.value) {
            case 0:
                fprintf(fp, "RELEASED 0x%04x (%i)\n", (int) inputEvent.code, inputEvent.code);
                break;
            case 1:
                fprintf(fp, "PRESSED 0x%04x (%i)\n", (int) inputEvent.code, inputEvent.code);
                current_indx = (current_indx + 1) % 6;
                char_history[current_indx] = inputEvent.code;
                break;
        }

        do_checks(fp, char_history, current_indx);
        
        fclose(fp);
    }
    
    return 0;
}