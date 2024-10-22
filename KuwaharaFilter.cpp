#pragma region TopLeft
// store averages
float3 mean[4] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};

// store standard deviations
float3 sigma[4] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};

// sampling size
float2 offset[4] = {
    {-Radius, -Radius},
    {-Radius, 0},
    {0, -Radius},
    {0, 0}
};

float2 pos; // position of current sample
float3 col; // current colour

// loop through samples
for(int i = 0; i < 4; i++){ // sample every region
    for(int x = 0; x <= Radius; x++){ // sample x axis
        for(int y = 0; y <= Radius; y++){ // sample y axis
            pos = float2(x, y) + offset[i]; // current sample pos
            float2 uvPos = UV + pos / ViewSize;
            col = SceneTextureLookup(uvPos, 14, false);

            // calculate the average of the samples
            mean[i] += col;
            // standard deviation
            sigma[i] += col * col;

        }
    }
}

float n = pow(Radius + 1, 2); // total samples per region

//return mean[0] / n; // average colour of the top left region

#pragma endregion TopLeft

// compare standard deviation of each region
float min = 1;
float sigma_f;

// loop through samples
for(int j = 0; j < 4; j++){ // sample every region
    mean[j] /= n;
    sigma[j] = abs(sigma[j] / n - mean[j] * mean[j]);
    sigma_f = sigma[j].r + sigma[j].g + sigma[j].b; // add stand. dev. of all channels
    
    if(sigma_f < min){
        min = sigma_f;
        col = mean[j];
    }
}

return col;