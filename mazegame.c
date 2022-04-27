//<----MAZE GAME---->
//Aakash Chaudhary 2K20/CO/002
//Akshat Gupta     2K20/CO/047
#include <stdio.h>
#include <stdlib.h>

int length, width;

struct memory
{
    int pr[2], sk[2];
    char direction;
    struct memory *next;
};

struct head
{
    int cnt;
    struct memory *start;
    struct memory *end;
};

typedef struct memory memory;
typedef struct head head;

void record(head *h, int player_position[2], int snake_position[2], char player_move)
{
    memory *node = (memory *)malloc(sizeof(memory));
    if (node == NULL)
        return;
    node->pr[0] = player_position[0];
    node->pr[1] = player_position[1];
    node->sk[0] = snake_position[0];
    node->sk[1] = snake_position[1];
    node->direction = player_move;
    node->next = NULL;
    h->cnt++;
    if (h->start == NULL)
    {
        h->start = h->end = node;
        return;
    }
    h->end->next = node;
    h->end = node;
}

char undo(head *h, int player_position[2], int snake_position[2])
{
    if (h->start == NULL && h->cnt <= 1)
        return '0';
    char ch = h->end->direction;
    player_position[0] = h->end->pr[0];
    player_position[1] = h->end->pr[1];
    snake_position[0] = h->end->sk[0];
    snake_position[1] = h->end->sk[1];
    memory *temp = h->end;
    memory *node = h->start;
    while (node->next != NULL && node->next->next != NULL)
        node = node->next;
    if (node->next == NULL)
        h->start = h->end = NULL;
    else
    {
        node->next = NULL;
        h->end = node;
    }
    h->cnt--;
    free(temp);
    return ch;
}

void print_maze(char maze[length][width])
{
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < width; j++)
            printf("%c", maze[i][j]);
        printf("\n");
    }
}

void move_snake(int snake_position[2], int player_position[2], char maze[length][width])
{
	
	int x = snake_position[0];
    int y = snake_position[1];
	
	maze[x][y] = ' ';
    int num = 0;
    int dist = 1e8;

    // If gamer move up
    if(maze[x-1][y] != 'O' && x-1 > 0){
        int diff = abs(player_position[0] - (x-1)) + abs(player_position[1] - (y));
        if(diff < dist){
            dist = diff;
            num = 1;
        }
    }

    // If gamer move down
    if(maze[x+1][y] != 'O' && x+1 < 10){
        int diff = abs(player_position[0] - (x+1)) + abs(player_position[1] - (y));
        if(diff<dist){
            dist = diff;
            num = 2;
        }
    }

    // If gamer move right
    if(maze[x][y+1] != 'O' && y+1 < 14){
        int diff = abs(player_position[0] - x) + abs(player_position[1] - (y+1));
        if(diff<dist){
            dist = diff;
            num = 3;
        }
    }

    // If gamer move left
    if(maze[x][y-1] != 'O' && y-1 > 0){
        int diff = abs(player_position[0] - x) + abs(player_position[1] - (y-1));
        if(diff<dist){
            dist = diff;
            num = 4;
        }
    }

    if(num == 1){
        snake_position[0]--;
    }else if(num == 2){
        snake_position[0]++;
    }else if(num == 3){
        snake_position[1]++;
    }else{
        snake_position[1]--;
    }
    
    maze[snake_position[0]][snake_position[1]] = '~';
    
}

void play(char maze[length][width], int snake_position[2], int player_position[2], int dst[2])
{
    char ch;
    int win = 0, lose = 0;
    head mem;
    mem.cnt = 0;
    mem.start = mem.end = NULL;
    record(&mem, player_position, snake_position, '^');
    while (!win && !lose)
    {
        system("cls");
        printf("RULES OF GAME\n");
        printf("-------------\n");
        printf("Press \'w\' to move up\n");
        printf("Press \'a\' to move left\n");
        printf("Press \'s\' to move down\n");
        printf("Press \'d\' to move right\n");
        printf("Press \'u\' to undo\n");
        printf("Press \'q\' to quit\n\n");
        print_maze(maze);
        printf("\n");
        fflush(stdin);
        scanf("%c", &ch);
        switch (ch)
        {
        case 'w':
        {
            if (maze[player_position[0] - 1][player_position[1]] == ' ' || maze[player_position[0] - 1][player_position[1]] == 'X')
            {
                if (maze[player_position[0] - 1][player_position[1]] == 'X')
                    win = 1;
                maze[player_position[0]][player_position[1]] = ' ';
                maze[player_position[0] - 1][player_position[1]] = '^';
                player_position[0]--;
                record(&mem, player_position, snake_position, '^');
            }
            break;
        }
        case 'a':
        {
            if (maze[player_position[0]][player_position[1] - 1] == ' ' || maze[player_position[0]][player_position[1] - 1] == 'X')
            {
                if (maze[player_position[0]][player_position[1] - 1] == 'X')
                    win = 1;
                maze[player_position[0]][player_position[1]] = ' ';
                maze[player_position[0]][player_position[1] - 1] = '<';
                player_position[1]--;
                record(&mem, player_position, snake_position, '<');
            }
            break;
        }
        case 's':
        {
            if (maze[player_position[0] + 1][player_position[1]] == ' ' || maze[player_position[0] + 1][player_position[1]] == 'X')
            {
                if (maze[player_position[0] + 1][player_position[1]] == 'X')
                    win = 1;
                maze[player_position[0]][player_position[1]] = ' ';
                maze[player_position[0] + 1][player_position[1]] = 'v';
                player_position[0]++;
                record(&mem, player_position, snake_position, 'v');
            }
            break;
        }
        case 'd':
        {
            if (maze[player_position[0]][player_position[1] + 1] == ' ' || maze[player_position[0]][player_position[1] + 1] == 'X')
            {
                if (maze[player_position[0]][player_position[1] + 1] == 'X')
                    win = 1;
                maze[player_position[0]][player_position[1]] = ' ';
                maze[player_position[0]][player_position[1] + 1] = '>';
                player_position[1]++;
                record(&mem, player_position, snake_position, '>');
            }
            break;
        }
        case 'u':
        {
            int px, py, sx, sy;
            px = player_position[0];
            py = player_position[1];
            sx = snake_position[0];
            sy = snake_position[1];
            char mz_val = undo(&mem, player_position, snake_position);
            if (mz_val != '0')
            {
                maze[px][py] = ' ';
                maze[player_position[0]][player_position[1]] = mz_val;
                maze[sx][sy] = ' ';
                maze[snake_position[0]][snake_position[1]] = '~';
            }
            break;
        }
        case 'q':
        {
            printf("Thank You for Playing our game ...\n");
            del_memory(&mem);
            exit(0);
        }
        default:
        {
            printf("Invalid Choice!!!");
            system("pause");
            break;
        }
        }
        move_snake(snake_position, player_position, maze);
        if (player_position[0] == snake_position[0] && player_position[1] == snake_position[1])
            lose = 1;
    }
    system("cls");
    print_maze(maze);
    del_memory(&mem);
    if (win)
        printf("\nCongratulations You Win...\n");
    else
        printf("\nYou Loose!! Try again\n");
}

void game_start(char *file_name)
{
    //Creating Maze by Reading File
    printf("Enter 1_2_3\n");
    FILE *fp;
    fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        printf("%s FILE UNAVAILABLE!!! \n");
        return;
    }
    int snake_position[2], player_position[2], dst[2];
    int x;
    fscanf(fp, "%d %d %d", &x, &length, &width);
    int obs[x - 3][2], n = 0;
    for (int i = 0; i < x; i++)
    {
        int t1, t2, t3;
        fscanf(fp, "%d %d %d", &t1, &t2, &t3);
        if (t3 == 0)
        {
            player_position[0] = t1;
            player_position[1] = t2;
        }
        else if (t3 == 1)
        {
            snake_position[0] = t1;
            snake_position[1] = t2;
        }
        else if (t3 == 2)
        {
            dst[0] = t1;
            dst[1] = t2;
        }
        else
        {
            obs[n][0] = t1;
            obs[n++][1] = t2;
        }
    }
    fclose(fp);

    //Preparing the Maze for the game
    char maze[length][width];
    maze[0][0] = maze[0][width - 1] = maze[length - 1][0] = maze[length - 1][width - 1] = '#';
    for (int i = 1; i < width - 1; i++)
        maze[0][i] = maze[length - 1][i] = '-';
    for (int i = 1; i < length - 1; i++)
        maze[i][0] = maze[i][width - 1] = '|';
    for (int i = 1; i < length - 1; i++)
        for (int j = 1; j < width - 1; j++)
            maze[i][j] = ' ';
    // positioning obstacles
    for (int i = 0; i < n; i++)
        maze[obs[i][0]][obs[i][1]] = 'O';
    maze[dst[0]][dst[1]] = 'X'; //setting final position
    maze[snake_position[0]][snake_position[1]] = '~'; //setting sanke position
    maze[player_position[0]][player_position[1]] = '^'; //setting player position

    play(maze, snake_position, player_position, dst);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Invalid command!!!\n");
        exit(1);
    }
    game_start(argv[argc - 1]);
    return 0;
}
