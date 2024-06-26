#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 기차열
#define LEN_MIN 15
#define LEN_MAX 50

// 확률
#define PROB_MIN 10
#define PROB_MAX 90

// 어그로
#define AGGRO_MIN 0
#define AGGRO_MAX 5

// 마동석 이동 방향
#define MOVE_LEFT 1
#define MOVE_STAY 0

// 좀비의 공격 대상
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

// 마동석 행동
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2
//스테미나
#define STM_MIN 0
#define STM_MAX 5
int train_length; //기차
int madongseok; //마동석
int zombie, temp_zombie; //좀비
int citizen0, temp_citizen0; //시민
int citizen1, temp_citizen1; //시민1
int citizen2, temp_citizen2; //시민2
int turn = 0; //턴
int percentile_probability; //확률
int temp_aggro0;
int temp_aggro1;
int temp_aggro2; //전 어그
int stamina, temp_stamina; // 스테미나 
int move; //마동석 움직임
int action; //마동석 행동 
int citizen_aggro0 = 1; //시민 어그로 처음에 1로 지정
int citizen_aggro1 = 1;
int citizen_aggro2 = 1;
int ma_aggro = 1; //마동석 어드로 처음에 1로 지정 
int zombie_captured = 0; //좀비가 붙잡혔는지 여부를 나타내는 변수
int remaining_citizens = 3; //남은 시민 수 3명
// 인트로 함수
void print_intro() {
    printf("********************\n");
    printf("**  부산행 게임   **\n");
    printf("********************\n");
    printf("좀비를 피해서 무사히 탈출하세요.\n");
    printf("행운을 빕니다.\n");
    printf("\n");
    printf("게임을 시작합니다\n");
}

// 확률 입력 함수
int input_probability() {
    printf("확률을 입력하세요. (10 ~ 90) >> ");
    scanf_s("%d", &percentile_probability);
    printf("\n");
    //2-2 입력값 처리
    if (percentile_probability < PROB_MIN || percentile_probability > PROB_MAX) {
        input_probability();
    }

    return percentile_probability;
}

// 마동석 스태미나 함수
int madonseok_stamina() {
    printf("\n");
    printf("마동석 스태미나 (0 ~ 5) >> ");
    scanf_s("%d", &stamina);
    printf("\n");

    if (stamina < STM_MIN || stamina > STM_MAX) {
        madonseok_stamina();
    }
    return stamina;
}

// 열차의 길이 입력 함수
void input_train_length() {
    printf("\n");
    printf("열차의 길이를 입력해주세요. (15 ~ 50) >> ");
    scanf_s("%d", &train_length);
    printf("\n");
    //2-2 입력값
    if (train_length < LEN_MIN || train_length > LEN_MAX) {
        input_train_length();
    }

    madongseok = train_length - 2;
    zombie = train_length - 3;
    citizen0 = train_length - 6;
}
void citizen1_2_random() {
    while (1) {
        citizen1 = rand() % (train_length / 2);
        citizen2 = (rand() % (train_length / 2)) + (train_length / 4);
        if (citizen1 != 0 && citizen2 != 0 && citizen1 != citizen2 && citizen0 != citizen1 && citizen0 != citizen2) {
            break;
        }
    }
}

// 열차 상태 출력 함수
void print_train_line(char character, int train_length) {
    for (int i = 0; i < train_length; i++) {
        printf("%c", character);
    }
    printf("\n");
}
//기차
void print_train() {
    print_train_line('#', train_length); // 첫 번째 줄 출력
    for (int i = 0; i < train_length; i++) {
        if (i == citizen0) {
            printf("C");
        } else if (i == citizen1) {
            printf("C");
        } else if (i == citizen2) {
            printf("C");
        } else if (i == madongseok) {
            printf("M");
        } else if (i == zombie) {
            printf("Z");
        } else if (i == 0 || i == train_length - 1) {
            printf("#");
        } else {
            printf(" ");
        }
    }
    printf("\n");
    print_train_line('#', train_length); // 세 번째 줄 출력
}

// 시민 이동 함수
void move_citizen0() {
    temp_citizen0 = citizen0;
    int rcitizen0 = rand() % 101;
    if (100 - percentile_probability >= rcitizen0) {
        citizen0 -= 1; // 시민을 움직임
    }
}
void move_citizen1() {
    temp_citizen1 = citizen1;
    int rcitizen1 = rand() % 101;
    if (100 - percentile_probability >= rcitizen1) {
        citizen1 -= 1; // 시민을 움직임
    }
}
void move_citizen2() {
    temp_citizen2 = citizen2;
    int rcitizen2 = rand() % 101;
    if (100 - percentile_probability >= rcitizen2) {
        citizen2 -= 1; // 시민을 움직임
    }
}
//시민 이동한거 출력
void print_move_citizen0() {
    if (temp_citizen0 == citizen0) {
        temp_aggro0 = citizen_aggro0;
        citizen_aggro0 -= 1;
        if (citizen_aggro0 < AGGRO_MIN) {
            citizen_aggro0 = AGGRO_MIN;
        }
        printf("citizen0: stay %d (aggro %d -> %d)\n", citizen0, temp_aggro0, citizen_aggro0);
    }
    else {
        temp_aggro0 = citizen_aggro0;
        citizen_aggro0 += 1;
        if (citizen_aggro0 > AGGRO_MAX) {
            citizen_aggro0 = AGGRO_MAX;
        }
        printf("citizen0: %d -> %d (aggro: %d -> %d)\n", temp_citizen0, citizen0, temp_aggro0, citizen_aggro0);
    }
}
void print_move_citizen1() {
    if (temp_citizen1 == citizen1) {
        temp_aggro1 = citizen_aggro1;
        citizen_aggro1 -= 1;
        if (citizen_aggro1 < AGGRO_MIN) {
            citizen_aggro1 = AGGRO_MIN;
        }
        printf("citizen1: stay %d (aggro %d -> %d)\n", citizen1, temp_aggro1, citizen_aggro1);
    }
    else {
        temp_aggro1 = citizen_aggro1;
        citizen_aggro1 += 1;
        if (citizen_aggro1 > AGGRO_MAX) {
            citizen_aggro1 = AGGRO_MAX;
        }
        printf("citizen1: %d -> %d (aggro: %d -> %d)\n", temp_citizen1, citizen1, temp_aggro1, citizen_aggro1);
    }
}
void print_move_citizen2() {
    if (temp_citizen2 == citizen2) {
        temp_aggro2 = citizen_aggro2;
        citizen_aggro2 -= 1;
        if (citizen_aggro2 < AGGRO_MIN) {
            citizen_aggro2 = AGGRO_MIN;
        }
        printf("citizen: stay %d (aggro %d -> %d)\n", citizen2, temp_aggro2, citizen_aggro2);
    }
    else {
        temp_aggro2 = citizen_aggro2;
        citizen_aggro2 += 1;
        if (citizen_aggro2 > AGGRO_MAX) {
            citizen_aggro2 = AGGRO_MAX;
        }
        printf("citizen: %d -> %d (aggro: %d -> %d)\n", temp_citizen2, citizen2, temp_aggro2, citizen_aggro2);
    }
}
// 좀비 이동 함수
void move_zombie_citizen0() {
    temp_zombie = zombie;
    // 좀비가 붙잡혀 있으면 턴을 줄임
    if (zombie_captured > 0) {
        zombie_captured--;
        return; // 좀비가 붙잡혀 있으면 이동하지 않음    
    }
    // 홀수 턴일 때만 좀비가 움직임
    if (turn % 2 != 0) {
        // 시민 0이 살아있을 때만 이동
        if (!(madongseok == zombie + 1 && zombie == citizen0 + 1)) {
            if (ma_aggro > citizen_aggro0) {
                zombie += 1;
            } else if (citizen_aggro0 >= ma_aggro) {
                zombie -= 1;       
            } 
            // 좀비가 마동석 쪽으로 이동할 때만 스태미나가 감소
            if (zombie == madongseok - 1) {
                temp_stamina = stamina;
                stamina -= 1;
                printf("stamina: %d -> %d\n", temp_stamina, stamina);            
            }          
            // 좀비가 마동석과 겹치는지 확인
            if (zombie == madongseok) {
                // 겹치지 않도록 원래 위치로 되돌리기
                zombie = temp_zombie;           
            }
        } else {
            zombie = temp_zombie;      
        }
    }
}

void move_zombie_citizen1() {
    // 시민 0이 죽으면 시민 1이 움직임
    if (citizen0 == -1) {
    temp_zombie = zombie;
        // 홀수 턴일 때만 좀비가 움직임
        if (turn % 2 != 0) {
            // 시민 1이 살아있을 때만 이동
            if ((citizen0 = -1) && !(madongseok == zombie + 1 && zombie == citizen1 + 1)) {
                if (ma_aggro > citizen_aggro1) {
                    zombie += 1;
                } else if (citizen_aggro1 >= ma_aggro) {
                    zombie -= 1;       
                } 
                // 좀비가 마동석 쪽으로 이동할 때만 스태미나가 감소
                if (zombie == madongseok - 1) {
                    temp_stamina = stamina;
                    stamina -= 1;
                    printf("stamina: %d -> %d\n", temp_stamina, stamina);            
                }          
                // 좀비가 마동석과 겹치는지 확인
                if (zombie == madongseok) {
                    // 겹치지 않도록 원래 위치로 되돌리기
                    zombie = temp_zombie;           
                }
            } else {
                zombie = temp_zombie;      
            }
        }
    } else {
        // 시민 0이 살아있으면 아무 작업도 하지 않음
        return;
    }
}

void move_zombie_citizen2() {
    // 시민 1이 죽으면 시민 2가 움직임
    if (citizen0 == -1 && citizen1 == -1) {
        temp_zombie = zombie;
        // 홀수 턴일 때만 좀비가 움직임
        if (turn % 2 != 0) {
            // 시민 2가 살아있을 때만 이동
            if ((citizen0 == -1 && citizen1 == -1) && !(madongseok == zombie + 1 && zombie == citizen2 + 1)) {
                if (ma_aggro > citizen_aggro2) {
                    zombie += 1;
                } else if (citizen_aggro2 >= ma_aggro) {
                    zombie -= 1;       
                }
                // 좀비가 마동석 쪽으로 이동할 때만 스태미나가 감소
                if (zombie == madongseok - 1) {
                    temp_stamina = stamina;
                    stamina -= 1;
                    printf("stamina: %d -> %d\n", temp_stamina, stamina);            
                }          
                // 좀비가 마동석과 겹치는지 확인
                if (zombie == madongseok) {
                    // 겹치지 않도록 원래 위치로 되돌리기
                    zombie = temp_zombie;           
                }
            } else {
                zombie = temp_zombie;      
            }
        }
    } else {
        // 시민 1이 살아있으면 아무 작업도 하지 않음
        return;
    }
}


//좀비가 가만히 있거나 움직이는 부분
void print_move_zombie() {
    if (turn % 2 != 0) {
        if (temp_zombie == zombie) {
            printf("zombie: stay %d\n", zombie);
        }
        else {
            printf("zombie: %d -> %d\n", temp_zombie, zombie);
        }
    }
    else {
        printf("zombie: stay %d (cannot move)\n", zombie);
    }
}

// 마동석 이동 함수
void ma_move() {
    int temp_ma = madongseok;
    if (zombie != madongseok - 1) {
        do {
            printf("madongseok move (0: stay, 1: left) >> ");
            scanf_s("%d", &move);
        } while (move != MOVE_STAY && move != MOVE_LEFT);    }
    else {
        do {
            printf("madongseok move (0: stay) >> ");
            scanf_s("%d", &move);
        } while (move != MOVE_STAY);    }
    if (move == MOVE_STAY) {
        temp_ma = madongseok;
    }
    else {
        madongseok -= 1;   }
}


//마동석 이동 출력 함수
void print_ma_move() {
    int temp_aggro = ma_aggro;
    if (move == MOVE_STAY) {
        ma_aggro -= 1;
        if (ma_aggro < AGGRO_MIN) {
            ma_aggro = AGGRO_MIN;
        }
        printf("madongseok: stay %d (aggro: %d -> %d, stamina: %d)\n", madongseok, temp_aggro, ma_aggro, stamina);
    }
    else {
        ma_aggro += 1;
        if (ma_aggro > AGGRO_MAX) {
            ma_aggro = AGGRO_MAX;
        }
        printf("madongseok: left %d (aggro: %d -> %d, stamina: %d)\n", madongseok, temp_aggro, ma_aggro, stamina);
    }
}



// 마동석이 쉴때
void ma_action_rest() {
    if (action == ACTION_REST) {
        int temp_aggro = ma_aggro;
        int temp_stamina = stamina;

        printf("madongseok rests...\n");
        stamina += 1;
        ma_aggro -= 1;
        if (stamina > STM_MAX) stamina = STM_MAX;
        if (ma_aggro < AGGRO_MIN) ma_aggro = AGGRO_MIN;
        printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", madongseok, temp_aggro, ma_aggro, temp_stamina, stamina);
    }
}
//도발할때
void ma_action_provoke() {
    if (action == ACTION_PROVOKE) {
        int temp_aggro = ma_aggro;
        int temp_stamina = stamina;

        printf("madongseok provoked zombie...\n");
        ma_aggro = AGGRO_MAX;
        printf("madongseok: %d (aggro: %d -> %d, stamina: %d)\n", madongseok, temp_aggro, ma_aggro, stamina);
    }
}
//당길때
void ma_action_pull() {
    int temp_aggro = ma_aggro;
    int mar = rand() % 101; 
    int temp_stamina = stamina;
    if (action == ACTION_PULL) {
        printf("madongseok attempts to pull zombie...\n");
        if (100 - percentile_probability > mar) {
            printf("madongseok successfully pulled zombie! Zombie is captured for one turn.\n");
            ma_aggro += 2;
            stamina -= 1;
            zombie_captured = 1;  // 좀비를 한 턴 동안 붙잡음
            if (ma_aggro > AGGRO_MAX) ma_aggro = AGGRO_MAX;
            if (stamina < STM_MIN) stamina = STM_MIN;
            printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", madongseok, temp_aggro, ma_aggro, temp_stamina, stamina);    }
        else {
            printf("madongseok failed to pull zombie.\n");
            ma_aggro += 2;
            stamina -= 1;
            if (ma_aggro > AGGRO_MAX) ma_aggro = AGGRO_MAX;
            if (stamina < STM_MIN) stamina = STM_MIN;
            printf("madongseok: %d (aggro %d -> %d, stamina: %d -> %d)\n", madongseok, temp_aggro, ma_aggro, temp_stamina, stamina);
        }
    }
}
//마동석 행동 입력
void ma_action() {
    int temp_aggro = ma_aggro;
    if (temp_aggro > AGGRO_MAX) {
        temp_aggro = AGGRO_MAX;            }
    if (madongseok == zombie + 1) {
        do {
            printf("madongseok action (0: rest, 1: provoke, 2: pull) >> ");//좀비랑 붙어있을때 pull 뜸
            scanf_s("%d", &action);
        } while (action != ACTION_REST && action != ACTION_PROVOKE && action != ACTION_PULL);    }
    else {
        do {
            printf("madongseok action (0: rest, 1: provoke) >> ");//좀비가 붙어있지 않으면 pull 안뜸
            scanf_s("%d", &action);
        } while (action != ACTION_REST && action != ACTION_PROVOKE);
    }
}

// 시민 탈출 함수
void happy_ending() {
    printf("시민이 탈출했어요!!\n");
    printf("\n");
    printf("********************\n");
    printf("**   Game Clear!  **\n");
    printf("********************\n"); // 아웃트로
    exit(1);
}

// 좀비에게 잡혔을때 나오는 아웃트로 함수
void bad_ending() {
    printf("\n");
    printf("********************\n");
    printf("**   Game Over..  **\n");
    printf("********************\n"); // 아웃트로
    exit(1);
}

// 좀비가 시민을 잡았을 때
void zombie_catch_citizen0() {
    if (citizen0 == zombie - 1) {
        if (madongseok == zombie + 1 && ma_aggro > citizen_aggro0) {
            // 마동석의 어그로가 더 높으면 마동석이 공격받고 게임이 끝나지 않음
            temp_stamina = stamina;
            stamina -= 1;
            printf("Zombie attacked madongseok (aggro %d vs %d, madongseok stamina: %d -> %d)\n", citizen_aggro0, ma_aggro, temp_stamina, stamina);
            if (stamina <= 0) {
                printf("madongseok die...\n");
                bad_ending();
            }
        } else if (!(madongseok == zombie + 1)) {
            // 마동석이 옆에 없는 경우에만 게임이 끝남
            printf("Zombie caught citizen 0\n");
            citizen0 = -1;  // 시민 0을 비활성화
            remaining_citizens--;
            printf("Remaining citizens: %d\n", remaining_citizens);
        }
    }
}
void zombie_catch_citizen1() {
    if (citizen1 == zombie - 1) {
        if (madongseok == zombie + 1 && ma_aggro > citizen_aggro1) {
            // 마동석의 어그로가 더 높으면 마동석이 공격받고 게임이 끝나지 않음
            temp_stamina = stamina;
            stamina -= 1;
            printf("Zombie attacked madongseok (aggro %d vs %d, madongseok stamina: %d -> %d)\n", citizen_aggro1, ma_aggro, temp_stamina, stamina);
            if (stamina <= 0) {
                printf("madongseok die...\n");
                bad_ending();
            }
        } else if (!(madongseok == zombie + 1)) {
            // 마동석이 옆에 없는 경우에만 게임이 끝남
            printf("Zombie caught citizen 0\n");
            citizen1 = -1;  // 시민 0을 비활성화
            remaining_citizens--;
            printf("Remaining citizens: %d\n", remaining_citizens);
        }
    }
}
void zombie_catch_citizen2() {
    if (citizen2 == zombie - 1) {
        if (madongseok == zombie + 1 && ma_aggro > citizen_aggro2) {
            // 마동석의 어그로가 더 높으면 마동석이 공격받고 게임이 끝나지 않음
            temp_stamina = stamina;
            stamina -= 1;
            printf("Zombie attacked madongseok (aggro %d vs %d, madongseok stamina: %d -> %d)\n", citizen_aggro2, ma_aggro, temp_stamina, stamina);
            if (stamina <= 0) {
                printf("madongseok die...\n");
                bad_ending();
            }
        } else if (!(madongseok == zombie + 1)) {
            // 마동석이 옆에 없는 경우에만 게임이 끝남
            printf("Zombie caught citizen 0\n");
            citizen2 = -1;  // 시민 0을 비활성화
            remaining_citizens--;
            printf("Remaining citizens: %d\n", remaining_citizens);
        }
    }
}
// 시민이 탈출했을 때

//결과 출력
void result() {
    if (citizen0 != 1 || citizen1 != 1 || citizen2 !=1) {
        printf("citizen does nothing.");
    }
    if (zombie != madongseok - 1) {
        printf("\nzombie attacked nobody.");
    }
}
//마동석이 좀비한테 물렸을때
void madongseok_catch() {
    if (zombie == madongseok - 1) {
        printf("zombie attacked madongseok.\n");
        temp_stamina = stamina;
        stamina -= 1;
        printf("스태미나: %d -> %d\n", temp_stamina, stamina);
    }
}
//마동석의 스테미나 0
void ma_stamina_zero() {
    if (stamina == 0) {
        printf("madongseok die...");
        bad_ending();
        exit(1);
    }
}
void ending() {
    if (citizen0 == 1 || citizen1 == 1 || citizen2 == 1) {
        happy_ending();
    } else if (citizen0 == -1 && citizen1 == -1 && citizen2 == -1) {
        bad_ending();
    }
}
//메인함수
int main() {
    srand((unsigned int)time(NULL));
    print_intro();
    input_train_length();
    madonseok_stamina();
    input_probability();
    citizen1_2_random();

    // 초기 열차 상태 출력
    print_train();
    printf("\n\n");

    while (1) {
        turn++;

        // 시민과 좀비의 움직임 계산
        move_citizen0(); // 시민의 움직임 계산
        move_citizen1();
        move_citizen2();
        move_zombie_citizen0(); // 좀비의 움직임 계산
        move_zombie_citizen1();
        move_zombie_citizen2();

        // 첫 번째 기차 상태 출력 (시민과 좀비 이동 후)
        print_train(); // 열차 상태 출력
        printf("\n");

        // 시민과 좀비의 이동 상황을 출력
        print_move_citizen0();
        print_move_citizen1();
        print_move_citizen2();
        print_move_zombie(); // 좀비의 이동 상황 출력
        printf("\n");

        // 마동석의 이동 계산을 먼저 수행
        ma_move();

        // 두 번째 기차 상태 출력 (마동석 이동 후)
        print_train(); // 열차 상태 출력
        printf("\n");

        // 마동석의 이동 상황 출력
        print_ma_move();
        printf("\n");

        // 결과 출력
        result();
        printf("\n");

        //마동석이 좀비한테 물렸을때
        madongseok_catch();

        // 마동석의 행동 결정
        ma_action();

        //마동석이 쉴때
        ma_action_rest();

        //마동석이 도발할때
        ma_action_provoke();

        //마동석이 좀비를 당길때
        ma_action_pull();

        // 좀비에게 잡혔는지 확인
        zombie_catch_citizen0();
        zombie_catch_citizen1();
        zombie_catch_citizen2();

        //마동석의 스테미나가 0이 되었을때
        ma_stamina_zero();

        ending();
    }

    return 0;
}
