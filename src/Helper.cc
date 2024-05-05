// This is just a helper class which contains the implementation of the line_of_sight function.

#include "../include/Helper.h"

float calculateDistance(float x1, float y1, float x2, float y2)
{
    float dx = x1 - x2;
    float dy = y1 - y2;
    return sqrt(dx * dx + dy * dy);
}

// Simple line of sight to detect if position_x and position_y is visible
// We use Bresenham's line algorithm
float line_of_sight(float target_x, float target_y, float _x, float _y, int scale, Environnement *lab)
{
    int x0 = _x / scale; // Convert to grid coordinates
    int y0 = _y / scale; // Convert to grid coordinates
    int target_grid_x = target_x / scale; 
    int target_grid_y = target_y / scale;

    int delta_x = abs(target_grid_x - x0); // Absolute difference between the x coordinates
    int delta_y = abs(target_grid_y - y0); // Absolute difference between the y coordinates
    int step_x = (x0 < target_grid_x) ? 1 : -1; 
    int step_y = (y0 < target_grid_y) ? 1 : -1;
    int error = delta_x - delta_y;

    char current_position;
    while (true)
    {
        current_position = lab->data(x0, y0);

        // Check if current position is a wall or a box
        if (current_position == VERTICAL_WALL ||
            current_position == HORIZONTAL_WALL ||
            current_position == WALL_CELL ||
            current_position == BOX_CELL)
        {
            // No line of sight
            return -1;
        }

        if (x0 == target_grid_x && y0 == target_grid_y)
        {
            // Line of sight exists
            break;
        }

        int double_error = 2 * error;
        if (double_error > -delta_y)
        {
            error -= delta_y;
            x0 += step_x;
        }
        if (double_error < delta_x)
        {
            error += delta_x;
            y0 += step_y;
        }
    }
    double distance = calculateDistance(_x, _y, target_x, target_y);

    return distance;
}