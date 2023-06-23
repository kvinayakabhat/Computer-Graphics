void shortestpath(int src, int n, int cost[MAX][MAX])
{
    // START OF BELLMAN FORD
    int j, p, q, x1, y1, x2, y2, x, y;
    int d[MAX], parent[MAX];

    int it, flag = 0, child[MAX];

    // INITIALIZE DATA OBJECTS
    for (it = 1; it <= n; ++it)
    {
        d[it] = INFINITY;
        parent[it] = src;
    }
    d[src] = 0;

    // RELAXATION METHOD
    for (int m = 0; m < n; m++) // REPEAT N TIMES
    {
        // RELAX ALL EDGES
        for (it = 1; it <= n; ++it)
        {
            for (j = 1; j <= n; ++j)
            {
                if (d[it] + cost[it][j] < d[j])
                {
                    d[j] = d[it] + cost[it][j];
                    parent[j] = it;
                }
            }
        }
    }

    // CHECK FOR NEGATIVE LOOPS
    for (it = 1; it <= n; ++it)
    {
        for (j = 1; j <= n; ++j)
        {
            if (cost[it][j] == INFINITY)
                continue;
            if (d[it] + cost[it][j] < d[j])
            {
                FILE *file = fopen("output.txt", "w"); // Open the file in write mode
                if (file != NULL)
                {
                    fprintf(file, "\n\nGraph contains a negative-weight cycle\n");
                    fclose(file); // Close the file
                }
                return;
            }
        }
    }

    FILE *file = fopen("output.txt", "w"); // Open the file in write mode
    if (file != NULL)
    {
        // Write the shortest path results to the file
        for (it = 1; it <= n; ++it)
        {
            fprintf(file, "Shortest path from node %d to %d: %d\n", src, it, d[it]);
        }
        fclose(file); // Close the file
    }
}
