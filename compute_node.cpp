#include <iostream>
#include <stddef.h>
#include <stdio.h>
extern "C" {
#include "Compute.h" 
}

#include "rtwtypes.h"
#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64.hpp>
using namespace std::chrono_literals;
using std::placeholders::_1;

void Compute_step(void);
void Compute_initialize(void);
void Compute_terminate(void);

class compute : public rclcpp::Node
{
  public:
    compute()
    : Node("compute")
    {
      subscription_ = this->create_subscription<std_msgs::msg::Float64>(
      "sense/out", 1, std::bind(&compute::topic_callback, this, _1));


      publisher_ = this->create_publisher<std_msgs::msg::Float64>("compute/out", 1);
      timer_ = this->create_wall_timer(
      2000ms, std::bind(&compute::timer_callback, this));
    }

  private:
    void topic_callback(const std_msgs::msg::Float64::SharedPtr msg) const
    {
      Compute_U.in = msg->data;
      Compute_step();
      //RCLCPP_INFO(this->get_logger(), "I heard: '%f'", msg->data);

    }
    void timer_callback()
    {
      auto message = std_msgs::msg::Float64();
      message.data = Compute_Y.out;
      RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", message.data);
      publisher_->publish(message);
    }
    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  Compute_initialize();

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<compute>());
  rclcpp::shutdown();
  
  Compute_terminate();

  return 0;
}
