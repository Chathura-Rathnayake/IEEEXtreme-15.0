#include <iostream>
using namespace std;

bool** rotateImage(bool** image, int& width, int& height);
bool** flipImageHorizontal(bool** image, int width, int height);
bool** flipImageVertical(bool** image, int width, int height);
int getSimilarity(bool** image_1, int rows_1, int columns_1, bool** image_2, int rows_2, int columns_2);

int main() {
    ios::sync_with_stdio(false);

    int cases;
    cin >> cases;

    while (cases-- > 0) {
        // Read first image
        int rows_1, columns_1;
        cin >> rows_1 >> columns_1;
        bool** image_1 = new bool*[rows_1];
        for (int i = 0; i < rows_1; i++) {
            bool* row = new bool[columns_1];
            for (int j = 0; j < columns_1; j++) {
                char cell;
                cin >> cell;
                row[j] = (cell == '#');
            }
            image_1[i] = row;
        }

        // Read second image
        int rows_2, columns_2;
        cin >> rows_2 >> columns_2;
        bool** image_2 = new bool*[rows_2];
        for (int i = 0; i < rows_2; i++) {
            bool* row = new bool[columns_2];
            for (int j = 0; j < columns_2; j++) {
                char cell;
                cin >> cell;
                row[j] = (cell == '#');
            }
            image_2[i] = row;
        }

        // Find out which image is smaller
        bool** smallImage = image_1;
        int smallRows = rows_1, smallColumns = columns_1;
        bool** largeImage = image_2;
        int largeRows = rows_2, largeColumns = columns_2;
        if (rows_1 * columns_1 > rows_2 * columns_2) {
            smallImage = image_2;
            smallRows = rows_2;
            smallColumns = columns_2;
            largeImage = image_1;
            largeRows = rows_1;
            largeColumns = columns_1;
        }

        // Compare each transformation of the small image
        int similarity = 0;

        // Flip: none, rotation: 0 deg
        similarity = getSimilarity(smallImage, smallRows, smallColumns, largeImage, largeRows, largeColumns);

        // Flip: none, rotation: 90 deg
        smallImage = rotateImage(smallImage, smallColumns, smallRows);
        similarity = max(similarity, getSimilarity(smallImage, smallRows, smallColumns, largeImage, largeRows, largeColumns));

        // Flip: none, rotation: 180 deg
        smallImage = rotateImage(smallImage, smallColumns, smallRows);
        similarity = max(similarity, getSimilarity(smallImage, smallRows, smallColumns, largeImage, largeRows, largeColumns));

        // Flip: none, rotation: 270 deg
        smallImage = rotateImage(smallImage, smallColumns, smallRows);
        similarity = max(similarity, getSimilarity(smallImage, smallRows, smallColumns, largeImage, largeRows, largeColumns));

        // Flip: horizontal, rotation: 270 deg
        smallImage = flipImageHorizontal(smallImage, smallColumns, smallRows);
        similarity = max(similarity, getSimilarity(smallImage, smallRows, smallColumns, largeImage, largeRows, largeColumns));

        // Flip: horizontal, rotation: 0 deg
        smallImage = rotateImage(smallImage, smallColumns, smallRows);
        similarity = max(similarity, getSimilarity(smallImage, smallRows, smallColumns, largeImage, largeRows, largeColumns));

        // Flip: horizontal, rotation: 90 deg
        smallImage = rotateImage(smallImage, smallColumns, smallRows);
        similarity = max(similarity, getSimilarity(smallImage, smallRows, smallColumns, largeImage, largeRows, largeColumns));

        // Flip: horizontal, rotation: 180 deg
        smallImage = rotateImage(smallImage, smallColumns, smallRows);
        similarity = max(similarity, getSimilarity(smallImage, smallRows, smallColumns, largeImage, largeRows, largeColumns));

        // Flip: horizontal & vertical, rotation: 180 deg
        smallImage = flipImageVertical(smallImage, smallColumns, smallRows);
        similarity = max(similarity, getSimilarity(smallImage, smallRows, smallColumns, largeImage, largeRows, largeColumns));

        // Flip: horizontal & vertical, rotation: 270 deg
        smallImage = rotateImage(smallImage, smallColumns, smallRows);
        similarity = max(similarity, getSimilarity(smallImage, smallRows, smallColumns, largeImage, largeRows, largeColumns));

        // Flip: horizontal & vertical, rotation: 0 deg
        smallImage = rotateImage(smallImage, smallColumns, smallRows);
        similarity = max(similarity, getSimilarity(smallImage, smallRows, smallColumns, largeImage, largeRows, largeColumns));

        // Flip: horizontal & vertical, rotation: 90 deg
        smallImage = rotateImage(smallImage, smallColumns, smallRows);
        similarity = max(similarity, getSimilarity(smallImage, smallRows, smallColumns, largeImage, largeRows, largeColumns));

        // Flip: vertical, rotation: 90 deg
        smallImage = flipImageHorizontal(smallImage, smallColumns, smallRows);
        similarity = max(similarity, getSimilarity(smallImage, smallRows, smallColumns, largeImage, largeRows, largeColumns));

        // Flip: vertical, rotation: 180 deg
        smallImage = rotateImage(smallImage, smallColumns, smallRows);
        similarity = max(similarity, getSimilarity(smallImage, smallRows, smallColumns, largeImage, largeRows, largeColumns));

        // Flip: vertical, rotation: 270 deg
        smallImage = rotateImage(smallImage, smallColumns, smallRows);
        similarity = max(similarity, getSimilarity(smallImage, smallRows, smallColumns, largeImage, largeRows, largeColumns));

        // Flip: vertical, rotation: 0 deg
        smallImage = rotateImage(smallImage, smallColumns, smallRows);
        similarity = max(similarity, getSimilarity(smallImage, smallRows, smallColumns, largeImage, largeRows, largeColumns));

        cout << similarity << "\n";
    }
    return 0;
}

// Rotates image 90 deg clockwise
bool** rotateImage(bool** image, int& width, int& height) {
    bool** result = new bool*[width];
    for (int i = 0; i < width; i++) {
        bool* row = new bool[height];
        for (int j = 0; j < height; j++) {
            row[j] = image[height - j - 1][i];
        }
        result[i] = row;
    }
    swap(width, height);
    return result;
}

// Flips image horizontally
bool** flipImageHorizontal(bool** image, int width, int height) {
    bool** result = new bool*[height];
    for (int i = 0; i < height; i++) {
        bool* row = new bool[width];
        for (int j = 0; j < width; j++) {
            row[j] = image[i][width - j - 1];
        }
        result[i] = row;
    }
    return result;
}

// Flips image vertically
bool** flipImageVertical(bool** image, int width, int height) {
    bool** result = new bool*[height];
    for (int i = 0; i < height; i++) {
        bool* row = new bool[width];
        for (int j = 0; j < width; j++) {
            row[j] = image[height - i - 1][j];
        }
        result[i] = row;
    }
    return result;
}

// Compares image_1 and image_2 and assumes image_1 is smaller
int getSimilarity(bool** image_1, int rows_1, int columns_1, bool** image_2, int rows_2, int columns_2) {
    int similarity = 0;
    for (int i = 1 - rows_1; i < rows_2; i++) {
        for (int j = 1 - columns_1; j < columns_2; j++) {
            int currentSimilarity = 0;
            for (int k = 0; k < rows_1; k++) {
                if (k + i == rows_2) break;
                for (int l = 0; l < columns_1; l++) {
                    if (l + j == columns_2) break;
                    if (k + i >= 0 && l + j >= 0) {
                        if (image_1[k][l] && image_2[k + i][l + j]) currentSimilarity++;
                    }
                }
            }
            similarity = max(similarity, currentSimilarity);
        }
    }
    return similarity;
}
