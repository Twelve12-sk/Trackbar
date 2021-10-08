#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace cv;
using namespace std;
vector<vector<Point>>contours;
vector<Vec4i>hierarchy;
const int max_value_H = 360 / 2;
const int max_value = 255;
int low_H = 0, low_S = 0, low_V = 0;
int high_H = max_value_H, high_S = max_value, high_V = max_value;

String HSVname = "HSV";
Mat clo_HSV, clo_threshold;
Mat element = getStructuringElement(MORPH_RECT, Size(1, 1));

static void on_low_H_thresh_trackbar(int, void*)
{
    low_H = min(high_H - 1, low_H);
    setTrackbarPos("Low H", HSVname, low_H);
}
static void on_high_H_thresh_trackbar(int, void*)
{
    high_H = max(high_H, low_H + 1);
    setTrackbarPos("High H", HSVname, high_H);
}
static void on_low_S_thresh_trackbar(int, void*)
{
    low_S = min(high_S - 1, low_S);
    setTrackbarPos("Low S", HSVname, low_S);
}
static void on_high_S_thresh_trackbar(int, void*)
{
    high_S = max(high_S, low_S + 1);
    setTrackbarPos("High S", HSVname, high_S);
}
static void on_low_V_thresh_trackbar(int, void*)
{
    low_V = min(high_V - 1, low_V);
    setTrackbarPos("Low V", HSVname, low_V);
}
static void on_high_V_thresh_trackbar(int, void*)
{
    high_V = max(high_V, low_V + 1);
    setTrackbarPos("High V", HSVname, high_V);
}


int main(int argc, char* argv[])
{

    VideoCapture capture(2);

    /*
    double width = capture.get(CAP_PROP_FRAME_WIDTH);
    double height = capture.get(CAP_PROP_FRAME_HEIGHT);
    double FPS = capture.get(CAP_PROP_FPS);
    double brightness = capture.get(CAP_PROP_BRIGHTNESS);
    double contrast = capture.get(CAP_PROP_CONTRAST);
    double satuation = capture.get(CAP_PROP_SATURATION);
    double hue = capture.get(CAP_PROP_HUE);
    double exposure = capture.get(CAP_PROP_EXPOSURE);
    width = 1920;
    height = 1080;
    capture.set(CAP_PROP_FRAME_WIDTH, 1920);
    capture.set(CAP_PROP_FRAME_HEIGHT, 1080);
    */
    Mat src;
    /*
    //1920×1080

    cout<<"width:"<<width<<endl;
    cout<<"height:"<<height<<endl;
    cout<<"PFS:"<<FPS<<endl;
    cout<<"brightness:"<<brightness<<endl;
    cout<<"contrast:"<<contrast<<endl;
    cout<<"satuation:"<<satuation<<endl;
    //src.cols = 1080;
    //src.rows = 960;
    */
    0, 130, 183,  138, 156, 242;
    Mat roi;
    while (1)
    {
        capture >> src;
        //namedWindow("thr");
        //Mat hsv, dst;
        //inRange(hsv, Scalar(55, 184, 170), Scalar(89, 245, 255), dst); filter green
        //inRange(hsv, Scalar(55, 183, 50), Scalar(70, 255, 170), dst_green); //filter green2
        //inRange(hsv, Scalar(17, 125, 132), Scalar(32, 245, 255), dst);filter yellow
        //inRange(hsv, Scalar(),Scalar(),dst)filter gray;


        createTrackbar("Low H", HSVname, &low_H, max_value_H, on_low_H_thresh_trackbar);
        createTrackbar("High H", HSVname, &high_H, max_value_H, on_high_H_thresh_trackbar);
        createTrackbar("Low S", HSVname, &low_S, max_value, on_low_S_thresh_trackbar);
        createTrackbar("High S", HSVname, &high_S, max_value, on_high_S_thresh_trackbar);
        createTrackbar("Low V", HSVname, &low_V, max_value, on_low_V_thresh_trackbar);
        createTrackbar("High V", HSVname, &high_V, max_value, on_high_V_thresh_trackbar);

        // Convert from BGR to HSV colorspace
        cvtColor(src, clo_HSV, COLOR_BGR2HSV);
        // Detect the object based on HSV Range Values
        inRange(clo_HSV, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), clo_threshold);
        // Show the frames
        namedWindow("src", WINDOW_GUI_NORMAL);
        namedWindow(HSVname, WINDOW_GUI_NORMAL);


        //int w = src.cols;
        //int h = src.rows;
        //cout<<"cols:"<<src.cols<<endl;//480
        //cout<<"rows:"<<src.rows<<endl;//360
        //cv::Mat combine = cv::Mat::zeros(w, h, src.type());
        //Mat ROI = src(Range(src.rows / 3, (src.rows / 3)*2), Range(src.cols/3, (src.cols/3)*2));
        //cvtColor(ROI, ROI, COLOR_BGR2HSV);
        //inRange(ROI, Scalar(60, 8, 188), Scalar(100, 255, 255), ROI);

        //imshow("roi", ROI);

        //imshow(HSVname, clo_threshold);
        imshow("dst", clo_threshold);

        imshow("capture", src);

        char(key) = (char)waitKey(1);
        if (key == 27)
            break;
    }

    return 0;
}

