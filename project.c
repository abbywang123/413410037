#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define candidate 5040  //候選組合
#define digits 4  
#define MAX_PLAYERS 100 
#define PLAYER_FILE "players.dat"   //儲存玩家資料的檔案

typedef struct {
    char name[50];  //玩家名稱
    int score;  //玩家分數
} Player;

Player players[MAX_PLAYERS];    //玩家資料的陣列
int player_count = 0;   //當前玩家的數量

//載入玩家資料
void load_players() {
    FILE *file = fopen(PLAYER_FILE, "rb");
    if (file != NULL) {
        fread(&player_count, sizeof(int), 1, file);  //讀取玩家數量
        fread(players, sizeof(Player), player_count, file); //讀取玩家資料
        fclose(file);
    }
}

//儲存玩家資料
void save_players() {
    FILE *file = fopen(PLAYER_FILE, "wb");
    if (file != NULL) {
        fwrite(&player_count, sizeof(int), 1, file);
        fwrite(players, sizeof(Player), player_count, file);
        fclose(file);
    }
}

//重置玩家資料
void reset_players() {
    player_count = 0;   //重設玩家數量為0
    FILE *file = fopen(PLAYER_FILE, "wb");
    if (file != NULL) {
        fwrite(&player_count, sizeof(int), 1, file);
        fclose(file);
    }
    printf("All player data has been reset.\n");
}

//查找玩家資料
int find_player(char *name) {
    for (int i = 0; i < player_count; i++) {
        if (strcmp(players[i].name, name) == 0) {
            return i;
        }   //比對玩家名稱是否有相同
    }
    return -1;
}

//顯示玩家排名
void print_player_ranking(int player_index) {
    for (int i = 0; i < player_count - 1; i++) {
        for (int j = i + 1; j < player_count; j++) {
            if (players[i].score < players[j].score) {
                Player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }   //排序當前玩家的分數

    int rank = 1;   
    for (int i = 0; i < player_count; i++) {
        if (strcmp(players[i].name, players[player_index].name) == 0) {
            break;
        }
        rank++;
    }   //計算當前玩家的遊戲排名
    printf("Your ranking is: %d\n", rank);
}

typedef struct{
    int nums[digits];   //儲存候選組合
}candidates;

candidates possible[5040];  //儲存所有候選可能組合
int candidate_count = candidate;    //當前的候選組合數量

//生成候選組合
void generate_guess(candidates *possible){     
    int index = 0;  //初始化索引
    for(int a=0;a<10;a++){
        for(int b=0;b<10;b++){
            if(b==a){
                continue; 
            }   //確保a跟b不重複
            for(int c=0;c<10;c++){
                if(c==b || c==a){
                    continue;
                }
                for(int d=0;d<10;d++){
                    if(d==c || d==b || d==a){
                        continue;
                    }
                    possible[index].nums[0] = a;    //儲存候選數字
                    possible[index].nums[1] = b;
                    possible[index].nums[2] = c;
                    possible[index].nums[3] = d;
                    index++;
                }
            }
        }
    }
}

//計算A和B的數量
int calculate_feedback(int guess[], int answer[], int *a, int *b) {
    *a = 0; //初始化A的數量
    *b = 0; //初始化B的數量
    for (int i = 0; i < digits; i++) {
        if (guess[i] == answer[i]) {
            (*a)++;
        } else {
            for (int j = 0; j < digits; j++) {
                if (i != j && guess[i] == answer[j]) {
                    (*b)++;
                }
            }
        }
    }
    return 0;
}

//生成四位隨機數字
void generate_digits(int *result){  
    int used[10] = {0}; //標誌數字是否已被使用過
    int count = 0;  //已生成的數字數量
    while(count < digits){
        int digit = rand()%10;  
        if (!used[digit]) {    
            result[count++] = digit; 
            used[digit] = 1;       
        }//數字未被使用，則被存入
    }
}

//檢查數字是否無重複跟是四位數
bool is_valid_number(int number) {
    char str[5];
    snprintf(str, 5, "%04d", number);   //將數字轉為四位數的字串

    int seen[10] = {0}; //檢查數字是否重複
    for (int i = 0; i < digits; i++) {
        int digit = str[i] - '0';
        if (seen[digit] > 0) {
            return false; 
        }
        seen[digit]++;
    }
    return true;
}

int main() {
    char playagain = 'Y';   //判斷玩家是否要再次玩
    char player_name[50];   //儲存玩家名稱
    int player_index;   //玩家在陣列中的索引

    load_players();

    char reset_rankings;    //玩家是否要重置排名(Y/N)
    printf("Do you want to reset all player rankings? (Y/N)\n");
    scanf(" %c", &reset_rankings);
    if (reset_rankings == 'Y') {
        reset_players();
    }

    printf("Enter your name:\n");
    scanf("%s", player_name);

    //檢查玩家名稱是否已存在玩家資料中
    player_index = find_player(player_name);
    if (player_index != -1) {
        char confirm;
        printf("Player name '%s' already exists. Are you sure you are this player? (Y/N)\n", player_name);
        scanf(" %c", &confirm);
        if (confirm == 'N') {
            printf("Please enter a new name:\n");
            scanf("%s", player_name);
            player_index = -1; // Reset player index to indicate a new player
        }
    }

    //名稱不存在，則新增玩家資料
    player_index = find_player(player_name);
    if (player_index == -1) {
        strcpy(players[player_count].name, player_name);
        players[player_count].score = 0;
        player_index = player_count;
        player_count++;
    }

    while (playagain == 'Y') { 
        char mode;  //選擇A和B的模式
        int x, y, attempt = 0, time_limit, score = 0;   //A的數量、B的數量、玩家或電腦的嘗試次數、玩家選擇遊戲時間、分數
        time_t start_time; //紀錄遊戲開始時間

        printf("Enter the time limit in seconds for the game:\n");
        scanf("%d", &time_limit);

        printf("Which mode do you want to play?\n");
        printf("A.Guesser mode B.Questioner mode\n");
        scanf(" %c", &mode);

        if (mode == 'A') {
            generate_guess(possible); // 重新初始化候選數組
            printf("Please come up with a four-digit set of numbers in your mind and the numbers do not repeat.\n");
            sleep(5);   //等待 5 秒，給玩家時間思考
            printf("The computer will now start guessing.\n");

            int guess[digits];  //儲存電腦猜測數字
            srand(time(NULL));

            start_time = time(NULL); 

            while (attempt < 15) {
                if (difftime(time(NULL), start_time) > time_limit) {
                    printf("Time's up! Game over.\n");
                    score -= 20;
                    printf("Your score: %d\n", score);
                    players[player_index].score = score;
                    save_players();
                    print_player_ranking(player_index);
                    break;
                }   //超過遊戲時間

                int guess_index = rand() % candidate_count;
                for (int i = 0; i < digits; i++) {
                    guess[i] = possible[guess_index].nums[i];
                }//從候選組合隨機猜測

                attempt++;
                printf("The computer's guess answer is: %d%d%d%d.\n", guess[0], guess[1], guess[2], guess[3]);
                printf("Please enter how many A and how many B are now (e.g., 1 2):\n");
                scanf("%d %d", &x, &y);

                if (x == 4) {
                    score = 150 - (attempt - 1) * 10;
                    printf("PC WIN\n");
                    printf("Your score: %d\n", score);
                    players[player_index].score = score;
                    save_players();
                    print_player_ranking(player_index);
                    break;
                }

                if (x + y > 4 || x < 0 || y < 0) {
                    printf("YOU CHEAT\n");
                    break; // 結束當前遊戲回合，等待玩家決定是否再玩一次
                }

                int new_count = 0;
                for (int i = 0; i < candidate_count; i++) {
                    int a = 0, b = 0;
                    calculate_feedback(possible[i].nums, guess, &a, &b);
                    if (a == x && b == y) {
                        possible[new_count++] = possible[i];
                    }
                }
                candidate_count = new_count;

                if (candidate_count == 0) {
                    printf("YOU CHEAT\n");
                    break; 
                }//x、y輸入不合理
            }

        }
        else { 
            int result[digits], digit[digits];  //儲存電腦隨機產生的四位數字、儲存玩家猜測的四位數字
            int number;
            srand(time(NULL));
            generate_digits(result);
            start_time = time(NULL);    //記錄遊戲開始時間

            while (1) {
                if (difftime(time(NULL), start_time) > time_limit) {
                    printf("Time's up! Game over.\n");
                    score -= 20;
                    printf("Your score: %d\n", score);
                    players[player_index].score = score;
                    save_players(); 
                    print_player_ranking(player_index); 
                    break;
                }   //超過遊戲時間
                printf("Please enter an ordered set of four different digits\n");
                scanf("%d", &number);
                if (!is_valid_number(number)) {
                    printf("Invalid input! Please enter a 4-digit number with no repeated digits.\n");
                    continue; 
                }   //要求使用者重新輸入正確的數字
                for (int j = 3; j >= 0; j--) {
                    digit[j] = number % 10;
                    number /= 10;
                }
                x = 0;
                y = 0;
                for (int j = 0; j < digits; j++) {
                    for (int k = 0; k < digits; k++) {
                        if (digit[j] == result[k] && j == k) {
                            x++;
                        } else if (digit[j] == result[k]) {
                            y++;
                        }
                    }
                }//計算A和B的數量
                attempt++;
                if (x == 4) {
                    score = 150 - (attempt - 1) * 5;
                    printf("YOU WIN\n");
                    printf("Your score: %d\n", score);
                    players[player_index].score = score;
                    save_players(); 
                    print_player_ranking(player_index);
                    break;
                }//成功猜出數字
                printf("Now it's %dA%dB.\n", x, y);
            }
        }

        printf("Do you want to play again? (Y/N)\n");
        scanf(" %c", &playagain); 
    }

    save_players(); //遊戲結束後保存玩家資料
    print_player_ranking(player_index); //顯示玩家排名
    return 0;
}
