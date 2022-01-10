
void    move_foward()
{
    if //map[int(player->pos->x + player->dir->x * //move_value)][int(plyaer->pos->y)] == 0: (NO WALL IN FRONT X)
        player->pos->x += player->dir->x * //move_value;
    if //map[int(player->pos->x)][int(plyaer->pos->y + player->dir->y * //move_value)] == 0: (NO WALL IN FRONT Y)
        player->pos->y += player->dir->y * //move_value;
}

void move_backward()
{
    if //map[int(player->pos->x - player->dir->x * //move_value)][int(plyaer->pos->y)] == 0: (NO WALL IN FRONT X)
        player->pos->x -= player->dir->x * //move_value;
    if //map[int(player->pos->x)][int(player->pos->y - player->dir->y * //move_value)] == 0: (NO WALL IN FRONT Y)
        player->pos->y -= player->dir->y * //move_value;  
}

