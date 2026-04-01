#include <stdio.h>
#include <errno.h>
#include "data.h"
#include "score.h"

int score(gameState* game)
{
    int current_score = 0;
    FILE* file = NULL;

    fopen_s(&file, "score.txt", "r");
    fscanf_s(file, "%d", &current_score);
    fclose(file);
    // 如果文件不存在，current_score已经是0

    if (game->score > current_score)
    {
        // 保存新纪录
        fopen_s(&file, "score.txt", "w");
        fprintf(file, "%d", game->score);
        fclose(file);
        printf("恭喜！你打破了记录\n新纪录：%d（原纪录：%d）\n",game->score, current_score);
        return 1;
    }
    else if (game->score == current_score && current_score > 0)
    {
        printf("太可惜了！就差一点就破纪录了\n得分：%d\n", game->score);
        return 2;
    }
    else
    {
        return 0;
    }
}