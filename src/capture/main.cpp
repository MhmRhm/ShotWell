#include <librealsense2/rs.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[]) try {
  using namespace std;

  rs2::config config{};
  config.enable_stream(RS2_STREAM_COLOR, RS2_FORMAT_BGR8, 30);

  rs2::pipeline p;
  p.start(config);

  cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);

  while (true) {
    rs2::frameset frames = p.wait_for_frames();
    rs2::video_frame color_frame = frames.get_color_frame();
    cv::Mat color_image(
        cv::Size(color_frame.get_width(), color_frame.get_height()), CV_8UC3,
        (void *)color_frame.get_data(), cv::Mat::AUTO_STEP);

    auto hog{cv::HOGDescriptor{}};
    std::vector<cv::Rect> foundLocations{};
    hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
    hog.detectMultiScale(color_image, foundLocations);

    for (auto &&rect : foundLocations) {
      cv::rectangle(color_image, rect, {255, 255, 255});
    }

    cv::imshow("Display Image", color_image);

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
