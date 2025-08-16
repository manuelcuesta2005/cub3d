void start_position(t_player *player, const char dir)
{
    if (dir == 'S')
    {
        player->visionX = 0;
        player->visionY = 1;
        player->planeX = -0.66;
        player->planeY = 0;
    }
    else if (dir == 'E')
    {
        player->visionX = 1;
        player->visionY = 0;
        player->planeX = 0;
        player->planeY = 0.66;
    }
    else if (dir == 'W')
    {
        player->visionX = -1;
        player->visionY = 0;
        player->planeX = 0;
        player->planeY = -0.66;
    }
}
