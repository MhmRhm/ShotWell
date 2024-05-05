#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[]) try {
  using namespace std;

  rs2::config config{};
  config.enable_stream(RS2_STREAM_DEPTH, RS2_FORMAT_Z16, 30);
  config.enable_stream(RS2_STREAM_INFRARED, RS2_FORMAT_Y8, 30);

  rs2::pipeline p;
  p.start(config);

  cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);

  while (true) {
    rs2::frameset frames = p.wait_for_frames();
    rs2::depth_frame depth_frame = frames.get_depth_frame();
    rs2::frame infrared_frame = frames.get_infrared_frame();

    auto width = depth_frame.get_width();
    auto height = depth_frame.get_height();
    float dist_to_center = depth_frame.get_distance(width / 2, height / 2);

    std::cout << "The camera is facing an object " << dist_to_center
              << " meters away \r";

    cv::Mat infrared_image(cv::Size(width, height), CV_8U,
                           (void *)infrared_frame.get_data(),
                           cv::Mat::AUTO_STEP);

    cv::line(infrared_image, {0, 0}, {width, height}, {255, 255, 255});
    cv::line(infrared_image, {width, 0}, {0, height}, {255, 255, 255});

    cv::imshow("Display Image", infrared_image);

    char c = cv::waitKey(25);
    if (c == 'q')
      break;
  }

  return EXIT_SUCCESS;

} catch (const rs2::error &e) {
  std::cerr << "RealSense error calling " << e.get_failed_function() << "("
            << e.get_failed_args() << "):\n    " << e.what() << std::endl;
  return EXIT_FAILURE;

} catch (const std::exception &e) {
  std::cerr << e.what() << std::endl;
  return EXIT_FAILURE;
}
