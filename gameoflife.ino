#define width 40
#define height 20

byte sparcity = 6;

byte matrix1 [height + 2][width + 2];
byte matrix2 [height + 2][width + 2];

void setup() {
    Serial.begin(500000);
    randomSeed(analogRead(0));
    for (byte x = 0; x < height + 2; x++)
    {
        for (byte y = 0; y < width + 2; y++)
        {
            byte cell = random(sparcity);
            if (cell == 0)
            {
                matrix1[x][y] = 1;
            }
            else
            {
                matrix1[x][y] = 0;
            }
        }
    }
}

// Show the cells in the matrix
void displayMatrix()
{
    for (byte x = 1; x < height + 1; x++)
    {
        for (byte y = 1; y < width + 1; y++)
        {
            if (matrix1[x][y] == 1) Serial.write("O");
            else Serial.write(" ");

        }
       Serial.write(0x0A);
    }
    Serial.write(0x0A);
    Serial.write(0x0A);
}


// Apply Conways rules
void applyRules()
{
    // clear the buffer matrix
    for (byte x = 0; x < height + 2; x++)
    {
        for (byte y = 0; y < width + 2; y++)
        {
            matrix2[x][y] = 0;
        }
    }

    // check number of neighbours
    for (byte x = 1; x < height + 1; x++)
    {
        for (byte y = 1; y < width + 1; y++)
        {
            byte neighbours = 0;

            // count how many neighbours around the cell
            if (matrix1[x - 1][y - 1] == 1) neighbours++;
            if (matrix1[x][y - 1] == 1) neighbours++;
            if (matrix1[x + 1][y - 1] == 1) neighbours++;
            if (matrix1[x - 1][y] == 1) neighbours++;
            if (matrix1[x + 1][y] == 1) neighbours++;
            if (matrix1[x - 1][y + 1] == 1) neighbours++;
            if (matrix1[x][y + 1] == 1) neighbours++;
            if (matrix1[x + 1][y + 1] == 1) neighbours++;

            // apply rules
            if (matrix1[x][y] == 1 && (neighbours == 2 || neighbours == 3)) matrix2[x][y] = 1;
            if (matrix1[x][y] == 0 && neighbours == 3 ) matrix2[x][y] = 1;
        }
    }

    // copy the buffer matrix
    for (byte x = 0; x < height + 2; x++)
    {
        for (byte y = 0; y < width + 2; y++)
        {
            matrix1[x][y] = matrix2[x][y];
        }
    }
}

void loop()
{
    displayMatrix();
    delay(250);
    applyRules();
}
