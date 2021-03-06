#pragma once
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/common/time.h>
#include <pcl/console/print.h>
#include <pcl/io/boost.h>
#include <pcl/exceptions.h>
#include <iostream>
#include "libfreenect2\libfreenect2.hpp"
#include "libfreenect2\frame_listener_impl.h"
#include <libfreenect2/threading.h>
#include <libfreenect2/packet_pipeline.h>
#include <pcl\visualization\cloud_viewer.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "registration.h"
class libfreenect2_grabber
{
public:
	libfreenect2_grabber();
	libfreenect2_grabber(const std::string rgb_calibration_file, const std::string depth_calibration_file, const std::string pose_calibration_file);
	~libfreenect2_grabber();
	Eigen::Matrix4d getDepth2World(){
		return depth2world_;
	}

private:
	double rgb_fx_, rgb_fy_, rgb_cx_, rgb_cy_;
	double ir_fx_, ir_fy_, ir_cx_, ir_cy_;
	Eigen::Matrix4d world2rgb_;
	Eigen::Matrix4d depth2world_;
	const int size_x = 512;
	const int size_y = 424;
	float distance_;
	bool init_rototranslation_=false;
	cv::Mat rotation_, translation_, essential_, fundamental_;
	cv::Mat calibrgb_camera_matrix_, calibdepth_camera_matrix_, rgb_camera_matrix_, depth_camera_matrix_, depth_distortion_, rgb_distortion_;
	cv::Size calibsize_depth_, calibsize_rgb_;
	cv::Mat map_x_depth_, map_y_depth_;
	void initRotoTranslation();
	void initSizeAndData();
	void loadCalibration(const std::string rgb_calibration_file, const std::string depth_calibration_file, const std::string pose_calibration_file);
};