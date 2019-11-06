#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/highgui.hpp"
#include <cv_bridge/cv_bridge.h>

using namespace cv;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_pub");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub0 = it.advertise("/stitch", 1);
  image_transport::Publisher pub1 = it.advertise("/distort_cam1", 1);
  cv::Mat image = cv::imread("/home/ryu/catkin_ws/src/FVCD/image_pub/image/add_AC.jpg", CV_LOAD_IMAGE_COLOR);
  cv::waitKey(30);
  sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();

  ros::Rate loop_rate(5);
  while (nh.ok()) {
    pub0.publish(msg);
    pub1.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
}
