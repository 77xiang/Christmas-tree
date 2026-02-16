/**
 * @file Christmas tree.c
 * @author 77xiang
 * @brief 基于 Windows Console 的简单动态圣诞树与雪花
 * @version 0.2
 * @date 2026-2-16
 **/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h> 
#define MAX_SLEEP 500
#define MIN_SLEEP 10
#define maxSnow 1000


// 1. 设置光标位置
void gotoxy(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// 2. 设置颜色
enum Color {
    BLACK = 0, BLUE = 1, GREEN = 2, CYAN = 3, RED = 4,
    PURPLE = 5, BROWN = 6, WHITE = 7, YELLOW = 14, BRIGHT_WHITE = 15
};
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 3. 祝福语
void drawGreeting(int y) {
    const char* greetings[] = {
        "           ★ Merry Christmas! ★      ",
        "              圣  诞  快  乐！        ",
        "                    ^_^ ",
        "          ★ Wish you happiness!★    "
    };

    int colors[] = { RED, GREEN, YELLOW, CYAN };

    for (int i = 0; i < 4; i++) {
        gotoxy(20, y + i);
        setColor(colors[i]);
        printf("%s", greetings[i]);
    }
}

// 4. 绘制单个字符
void drawPoint(int x, int y, int color, const char* s) {
    gotoxy(x, y);
    setColor(color);
    printf("%s", s);
}

// 5. 绘制圣诞树主体
void drawTreeBody(int centerX, int baseY) {
    // 定义树的三层结构：{起始Y, 宽度, 高度}
    int layers[3][3] = {
        {baseY - 8, 7, 3},
        {baseY - 5, 11, 4},
        {baseY - 1, 15, 3}
    };

    for (int i = 0; i < 3; i++) {
        int startY = layers[i][0];
        int width = layers[i][1];
        int height = layers[i][2];

        for (int row = 0; row < height; row++) {
            int stars = width - (height - 1 - row) * 2;
            if (stars < 1) stars = 1;
            int startX = centerX - stars / 2;
            for (int col = 0; col < stars; col++) {
                drawPoint(startX + col, startY + row, GREEN, "*");
            }
        }
    }
    // 绘制树干
    for (int i = 0; i < 3; i++) {
        drawPoint(centerX - 1, baseY + 1 + i, BROWN, "|||");
    }
}

//  6. 判断碰撞
int isInTree(int x, int y) {
    int centerX = 40;
    int baseY = 15;

    // 1. 第一层 (y: 7~9)
    if (y >= 7 && y <= 9) {
        int row = y - 7;
        int width = 7 - (3 - 1 - row) * 2;
        int r = width / 2;
        if (x >= centerX - r && x <= centerX + r) return 1;
    }

    // 2. 第二层 (y: 10~13)
    else if (y >= 10 && y <= 13) {
        int row = y - 10;
        int width = 11 - (4 - 1 - row) * 2;
        int r = width / 2;
        if (x >= centerX - r && x <= centerX + r) return 1;
    }

    // 3. 第三层 (y: 14~16) 
    else if (y >= 14 && y <= 16) {
        int row = y - 14;
        int width = 15 - (3 - 1 - row) * 2;
        int r = width / 2;
        if (x >= centerX - r && x <= centerX + r) return 1;
    }

    // 4. 树干部分 (y: 16~18) 
    if (y >= 16 && y <= 18) {
        if (x >= centerX - 1 && x <= centerX + 1) return 1;
    }

    // 5. 星星部分
    if (y = 6 && x == centerX)  return 1;
    return 0;
}


// 7. 绘制彩灯
void drawLights(int centerX, int baseY, int frame) {
    int colors[] = { RED, YELLOW, BLUE, PURPLE, CYAN, BRIGHT_WHITE };
    struct { int x, y; } lights[] = {
        {centerX - 2, baseY - 6}, {centerX + 2, baseY - 6},
        {centerX - 3, baseY - 3}, {centerX, baseY - 3}, {centerX + 3, baseY - 3},
        {centerX - 3, baseY}, {centerX + 3, baseY},
        {centerX - 5, baseY + 1}, {centerX + 5, baseY + 1}
    };
    int numLights = sizeof(lights) / sizeof(lights[0]);

    for (int i = 0; i < numLights; i++) {
        // 使用帧数 frame 和索引 i 配合，实现流水灯效果
        int c = colors[(frame + i) % 6];
        drawPoint(lights[i].x, lights[i].y, c, "*");
    }

    // 树顶星星
    if (frame % 2 == 0) {
        drawPoint(centerX, baseY - 9, YELLOW, "★"); // 使用特殊字符★
    }
    else {
        drawPoint(centerX, baseY - 9, BRIGHT_WHITE, "☆");
    }
}


// 8. 雪花系统
void handleSnow(int snow[][3], int init, int activeSnow) {
    if (init) {
        for (int i = 0; i < maxSnow; i++) { // 初始化时建议初始化全部，防止越界
            do {
                snow[i][0] = rand() % 81;
                snow[i][1] = rand() % 19;
            } while (isInTree(snow[i][0], snow[i][1]));
            snow[i][2] = rand() % 2 + 1;
        }
        return;
    }

    // 处理活跃的雪花
    for (int i = 0; i < activeSnow; i++) {
        // 1. 擦除旧位置（仅当不在树内时擦除）
        if (!isInTree(snow[i][0], snow[i][1])) {
            drawPoint(snow[i][0], snow[i][1], BLACK, " ");
        }

        // 2. 尝试更新位置
        snow[i][1] += snow[i][2];

        // 3. 碰撞检测：如果新位置出界 或 进入了树的区域
        if (snow[i][1] > 18 || isInTree(snow[i][0], snow[i][1])) {
            // 重新在顶部生成，并确保新生成的点也不在树里
            snow[i][1] = 0;
            do {
                snow[i][0] = rand() % 81;
            } while (isInTree(snow[i][0], snow[i][1]));
        }
        else {
            // 4. 绘制新位置
            drawPoint(snow[i][0], snow[i][1], BRIGHT_WHITE, ".");
        }
    }

    // 擦除不再活跃的雪花残留
    for (int j = activeSnow; j < maxSnow; j++) {
        drawPoint(snow[j][0], snow[j][1], BLACK, " ");
    }
}

//9. UI系统
void drawUI(int activeSnow, int sleepTime, int show) {
    if (show) {
        setColor(BRIGHT_WHITE);
        gotoxy(17, 25); printf("╔═════════════ Real-time status (TAB) ═══════════╗");
        gotoxy(17, 26); printf("║ ActiveSnow: %-4d/ 1000 |   FPS: %-4dms / 500   ║", activeSnow, sleepTime);
        gotoxy(17, 27); printf("╚════════════════════════════════════════════════╝");
    }
    else {
        // 擦除 UI 区域，防止字符残留
        for (int i = 25; i <= 27; i++) {
            gotoxy(17, i);
            printf("                                                    ");
        }
    }
}

int main() {
    // 初始化环境
    srand((unsigned int)time(NULL));
    int frame = 0;
    int snowData[maxSnow][3];
    int sleepTime = 120;
    int activeSnow = 200;
    int showUI = 0; // 0 为隐藏，1 为显示
    handleSnow(snowData, 1, activeSnow); // 初始化雪花

    // 隐藏光标，避免屏幕上有个小白块闪来闪去
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cinfo = { 1, FALSE };
    SetConsoleCursorInfo(hOut, &cinfo);

    // 清屏一次作为背景
    system("cls");
    // 绘制地面
    setColor(WHITE);
    gotoxy(0, 19); printf("=================================================================================");
    // 绘制祝福语
    drawGreeting(20);

    // 主循环
    while (1) {
        // 1. 更新并绘制
        handleSnow(snowData, 0, activeSnow);
        drawTreeBody(40, 15);
        drawLights(40, 15, frame);
        drawUI(activeSnow, sleepTime, showUI);


        // 2. 键盘交互
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 27) break;
            if (ch == 'w' || ch == 'W') { if (sleepTime > MIN_SLEEP) sleepTime -= 10; }
            if (ch == 's' || ch == 'S') { if (sleepTime < MAX_SLEEP) sleepTime += 10; }
            if (ch == 'a' || ch == 'A') {
                if (activeSnow > 10) activeSnow -= 10;
            }
            if (ch == 'd' || ch == 'D') {
                if (activeSnow < maxSnow) activeSnow += 10;
            }
            if (ch == '\t') showUI = !showUI;
        }

        // 3. 控制刷新频率
        Sleep(sleepTime);
        frame++;

    }

    // 恢复现场
    cinfo.bVisible = TRUE;
    SetConsoleCursorInfo(hOut, &cinfo);

    system("cls");
    setColor(BRIGHT_WHITE);
    printf("\n\n\t\t程序已安全退出，圣诞快乐！\n\n");
    printf("\t\t按任意键彻底结束...");


    return 0;
}