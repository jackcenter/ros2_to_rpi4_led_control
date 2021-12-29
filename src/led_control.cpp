#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int8.hpp"

class LedControl : public rclcpp::Node
{
  public:
    LedControl()
    : Node("led_control")
    {
      subscription_ = this->create_subscription<std_msgs::msg::Int8>(
        "led_brightness", 10, std::bind(&LedControl::led_brightness_callback, this, 
        std::placeholders::_1)
      );
    }

  private:
    void led_brightness_callback(const std_msgs::msg::Int8::SharedPtr msg_in) const
    {
      RCLCPP_INFO(this->get_logger(), "I heard: %i", msg_in->data);
    }

    rclcpp::Subscription<std_msgs::msg::Int8>::SharedPtr subscription_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<LedControl>());
  rclcpp::shutdown();
  return 0;
}
