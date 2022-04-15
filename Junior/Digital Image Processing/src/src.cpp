#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <time.h>

using namespace cv;
using namespace std;

enum SeamDirection { VERTICAL, HORIZONTAL };

bool demo;

Mat createEnergyImage(Mat& image) {
    Mat image_blur, image_gray;
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    Mat grad, energy_image;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    // apply a gaussian blur to reduce noise
    GaussianBlur(image, image_blur, Size(3, 3), 0, 0, BORDER_DEFAULT);

    // convert to grayscale
    cvtColor(image_blur, image_gray, CV_BGR2GRAY);

    // use Scharr to calculate the gradient of the image in the x and y direction
    Scharr(image_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT);
    Scharr(image_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT);

    // convert gradients to abosulte versions of themselves
    convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);

    // total gradient
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

    // convert the default values to double precision
    grad.convertTo(energy_image, CV_64F, 1.0 / 255.0);

    // create and show the newly created energy image
    if (demo) {
        namedWindow("Energy Image", WINDOW_AUTOSIZE);
        imshow("Energy Image", energy_image);
    }

    return energy_image;
}

Mat createCumulativeEnergyMap(Mat& energy_image, SeamDirection direction) {
    double a, b, c;

    // get the numbers of rows and columns in the image
    int rowsize = energy_image.rows;
    int colsize = energy_image.cols;

    // initialize the map with zeros
    Mat cumulative_energy_map = Mat(rowsize, colsize, CV_64F, double(0));

    // copy the first row/col
    if (direction == VERTICAL)
        energy_image.row(0).copyTo(cumulative_energy_map.row(0));
    else if (direction == HORIZONTAL)
        energy_image.col(0).copyTo(cumulative_energy_map.col(0));

    if (direction == VERTICAL) { // part of the DP process which generates a map indicating the minimum cumulative energy needed to reach each pixel from above
        for (int row = 1; row < rowsize; row++) {
            for (int col = 0; col < colsize; col++) {
                a = cumulative_energy_map.at<double>(row - 1, max(col - 1, 0));
                b = cumulative_energy_map.at<double>(row - 1, col);
                c = cumulative_energy_map.at<double>(row - 1, min(col + 1, colsize - 1));

                cumulative_energy_map.at<double>(row, col) = energy_image.at<double>(row, col) + min(a, min(b, c));
            }
        }
    }
    else if (direction == HORIZONTAL) { // part of the DP process which generates a map indicating the minimum cumulative energy needed to reach each pixel from leftside
        for (int col = 1; col < colsize; col++) {
            for (int row = 0; row < rowsize; row++) {
                a = cumulative_energy_map.at<double>(max(row - 1, 0), col - 1);
                b = cumulative_energy_map.at<double>(row, col - 1);
                c = cumulative_energy_map.at<double>(min(row + 1, rowsize - 1), col - 1);

                cumulative_energy_map.at<double>(row, col) = energy_image.at<double>(row, col) + min(a, min(b, c));
            }
        }
    }

    // create and show the newly created cumulative energy map converting map into color
    if (demo) {
        Mat color_cumulative_energy_map;
        double Cmin;
        double Cmax;
        minMaxLoc(cumulative_energy_map, &Cmin, &Cmax);
        float scale = 255.0 / (Cmax - Cmin);
        cumulative_energy_map.convertTo(color_cumulative_energy_map, CV_8UC1, scale);
        applyColorMap(color_cumulative_energy_map, color_cumulative_energy_map, cv::COLORMAP_JET);

        namedWindow("Cumulative Energy Map", WINDOW_AUTOSIZE); imshow("Cumulative Energy Map", color_cumulative_energy_map);
    }

    return cumulative_energy_map;
}

vector<int> findOptimalSeam(Mat& cumulative_energy_map, SeamDirection direction) {
    int offset = 0;
    vector<int> path;
    Mat sortIdxArr;

    int rowsize = cumulative_energy_map.rows;
    int colsize = cumulative_energy_map.cols;

    if (direction == VERTICAL) {
        // find the root of the optimal seam
        Mat row = cumulative_energy_map.row(rowsize - 1);
        sortIdx(row, sortIdxArr, CV_SORT_ASCENDING + CV_SORT_EVERY_ROW);

        // initialize the path vector
        path.resize(rowsize);
        int min_index = sortIdxArr.at<int>(0, 0);;
        path[rowsize - 1] = min_index;

        // starting from the bottom, look at the three adjacent pixels above current pixel, choose the minimum of those and add to the path
        for (int i = rowsize - 2; i >= 0; i--) {
            double a = cumulative_energy_map.at<double>(i, max(min_index - 1, 0));
            double b = cumulative_energy_map.at<double>(i, min_index);
            double c = cumulative_energy_map.at<double>(i, min(min_index + 1, colsize - 1));

            if (min(a, b) > c) {
                offset = 1;
            }
            else if (min(a, c) > b) {
                offset = 0;
            }
            else if (min(b, c) > a) {
                offset = -1;
            }

            min_index += offset;
            min_index = min(max(min_index, 0), colsize - 1); // take care of edge cases
            path[i] = min_index;
        }
    }
    else if (direction == HORIZONTAL) {
        // find the root of the optimal seam
        Mat col = cumulative_energy_map.col(colsize - 1);
        sortIdx(col, sortIdxArr, CV_SORT_ASCENDING + CV_SORT_EVERY_COLUMN);

        // initialize the path vector
        path.resize(colsize);
        int min_index = sortIdxArr.at<int>(0, 0);
        path[colsize - 1] = min_index;

        // starting from the right, look at the three adjacent pixels to the left of current pixel, choose the minimum of those and add to the path
        for (int i = colsize - 2; i >= 0; i--) {
            double a = cumulative_energy_map.at<double>(max(min_index - 1, 0), i);
            double b = cumulative_energy_map.at<double>(min_index, i);
            double c = cumulative_energy_map.at<double>(min(min_index + 1, rowsize - 1), i);

            if (min(a, b) > c) {
                offset = 1;
            }
            else if (min(a, c) > b) {
                offset = 0;
            }
            else if (min(b, c) > a) {
                offset = -1;
            }

            min_index += offset;
            min_index = min(max(min_index, 0), rowsize - 1); // take care of edge cases
            path[i] = min_index;
        }
    }

    return path;
}

void reduce(Mat& image, vector<int> path, SeamDirection direction) {
    int rowsize = image.rows;
    int colsize = image.cols;

    // create a 1x1x3 dummy matrix to add onto the tail of a new row to maintain image dimensions and mark for deletion
    Mat dummy(1, 1, CV_8UC3, Vec3b(0, 0, 0));

    if (direction == VERTICAL) { // reduce width
        for (int i = 0; i < rowsize; i++) {
            // take all pixels to the left and right of marked pixel and store them in appropriate subrow variables
            Mat new_row;
            Mat lower = image.row(i).colRange(0, path[i]);
            Mat upper = image.row(i).colRange(path[i] + 1, colsize);

            // merge the two subrows and dummy matrix/pixel into a full row
            if (!lower.empty() && !upper.empty()) {
                hconcat(lower, upper, new_row);
                hconcat(new_row, dummy, new_row);
            }
            else if (lower.empty()) {
                hconcat(upper, dummy, new_row);
            }
            else if (upper.empty()) {
                hconcat(lower, dummy, new_row);
            }

            // copy the new row to its original place
            new_row.copyTo(image.row(i));
        }
        // clip the right-most side of the image
        image = image.colRange(0, colsize - 1);
    }
    else if (direction == HORIZONTAL) { // reduce height
        for (int i = 0; i < colsize; i++) {
            // take all pixels to the top and bottom of marked pixel and store the in appropriate subcolumn variables
            Mat new_col;
            Mat lower = image.col(i).rowRange(0, path[i]);
            Mat upper = image.col(i).rowRange(path[i] + 1, rowsize);

            // merge the two subcolumns and dummy matrix/pixel into a full col
            if (!lower.empty() && !upper.empty()) {
                vconcat(lower, upper, new_col);
                vconcat(new_col, dummy, new_col);
            }
            else {
                if (lower.empty()) {
                    vconcat(upper, dummy, new_col);
                }
                else if (upper.empty()) {
                    vconcat(lower, dummy, new_col);
                }
            }

            // copy the new col to its original place
            new_col.copyTo(image.col(i));
        }
        // clip the bottom-most side of the image
        image = image.rowRange(0, rowsize - 1);
    }
}

void extend(Mat& image, vector<int> path, SeamDirection direction) {
    int rowsize = image.rows;
    int colsize = image.cols;

    if (direction == VERTICAL) { // extend width
        // extend image width
        Mat dummy(rowsize, 1, CV_8UC3, Vec3b(0, 0, 0));
        hconcat(image, dummy, image);

        for (int i = 0; i < rowsize; i++) {
            Mat new_row;
            Mat new_pixel;

            // generate the new pixel to be added
            Mat left = image.row(i).col(max(0, path[i] - 1));
            Mat right = image.row(i).col(min(colsize - 1, path[i] + 1));
            addWeighted(left, 0.5, right, 0.5, 0, new_pixel);

            // take all pixels to the left and right of marked pixel and store them in appropriate subrow variables
            Mat lower = image.row(i).colRange(0, path[i]);
            Mat upper = image.row(i).colRange(path[i], colsize);

            // merge the two subrows and dummy matrix/pixel into a full row
            if (!lower.empty() && !upper.empty()) {
                hconcat(lower, new_pixel, new_row);
                hconcat(new_row, upper, new_row);
            }
            else if (!lower.empty()) {
                hconcat(lower, new_pixel, new_row);
            }
            else if (!upper.empty()) {
                hconcat(new_pixel, upper, new_row);
            }

            // copy the new row to its original place
            new_row.copyTo(image.row(i));
        }
    }
    else if (direction == HORIZONTAL) { // extend height
        // extend image height
        Mat dummy(1, colsize, CV_8UC3, Vec3b(0, 0, 0));
        vconcat(image, dummy, image);

        for (int i = 0; i < colsize; i++) {
            Mat new_col;
            Mat new_pixel;

            // generate the new pixel to be added
            Mat up = image.row(max(0, path[i] - 1)).col(i);
            Mat down = image.row(min(rowsize - 1, path[i] + 1)).col(i);
            addWeighted(up, 0.5, down, 0.5, 0, new_pixel);

            // take all pixels to the top and bottom of marked pixel and store the in appropriate subcolumn variables
            Mat lower = image.col(i).rowRange(0, path[i]);
            Mat upper = image.col(i).rowRange(path[i], rowsize);

            // merge the two subcolumns and dummy matrix/pixel into a full col
            if (!lower.empty() && !upper.empty()) {
                vconcat(lower, new_pixel, new_col);
                vconcat(new_col, upper, new_col);
            }
            else if (!lower.empty()) {
                vconcat(lower, new_pixel, new_col);
            }
            else if (!upper.empty()) {
                vconcat(new_pixel, upper, new_col);
            }

            // copy the new col to its original place
            new_col.copyTo(image.col(i));
        }
    }
}

void driver(Mat& image, int desiredWidth, int desiredHeight) {
    namedWindow("Original Image", WINDOW_AUTOSIZE);
    imshow("Original Image", image);

    int deltaW = desiredWidth - image.cols;
    int deltaH = desiredHeight - image.rows;
    SeamDirection direction;

    direction = VERTICAL;
    if (deltaW >= 0) { // extend width
        for (int i = 0; i < deltaW; i++) {
            Mat energy_image = createEnergyImage(image);
            Mat cumulative_energy_map = createCumulativeEnergyMap(energy_image, direction);
            vector<int> path = findOptimalSeam(cumulative_energy_map, direction);
            extend(image, path, direction);
        }
    }
    else { // reduce width
        for (int i = 0; i < abs(deltaW); i++) {
            Mat energy_image = createEnergyImage(image);
            Mat cumulative_energy_map = createCumulativeEnergyMap(energy_image, direction);
            vector<int> path = findOptimalSeam(cumulative_energy_map, direction);
            reduce(image, path, direction);
        }
    }

    direction = HORIZONTAL;
    if (deltaH >= 0) { // extend height
        for (int i = 0; i < deltaH; i++) {
            Mat energy_image = createEnergyImage(image);
            Mat cumulative_energy_map = createCumulativeEnergyMap(energy_image, direction);
            vector<int> path = findOptimalSeam(cumulative_energy_map, direction);
            extend(image, path, direction);
        }
    }
    else { // reduce height
        for (int i = 0; i < abs(deltaH); i++) {
            Mat energy_image = createEnergyImage(image);
            Mat cumulative_energy_map = createCumulativeEnergyMap(energy_image, direction);
            vector<int> path = findOptimalSeam(cumulative_energy_map, direction);
            reduce(image, path, direction);
        }
    }

    namedWindow("Resized Image", WINDOW_AUTOSIZE);
    imshow("Resized Image", image);

    waitKey(0);

    imwrite("result.jpg", image);
}

int main() {
    string filename;
    int width, height;

    cout << "Please enter a filename: ";
    cin >> filename;

    Mat image = imread(filename);
    if (image.empty()) {
        cout << "Unable to load image, please try again." << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Please enter desired width: ";
    cin >> width;

    while (width <= 0) {
        cout << "Width should be an integer greater than zero, please enter desired width again: ";
        cin >> width;
    }

    cout << "Please enter desired height: ";
    cin >> height;

    while (height <= 0) {
        cout << "Height should be an integer greater than zero, please enter desired height again: ";
        cin >> height;
    }

    demo = false;

    driver(image, width, height);

    return 0;
}