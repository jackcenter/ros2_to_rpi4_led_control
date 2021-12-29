#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int8.hpp"
#include "std_msgs/msg/string.hpp"

class LedSetting : public rclcpp::Node
{
  public:
    LedSetting()
    : Node("led_setting")
    {
      publisher_ = this->create_publisher<std_msgs::msg::Int8>("led_brightness", 10);
      subscription_ = this->create_subscription<std_msgs::msg::String>(
        "keyboard_command", 10, std::bind(&LedSetting::keyboard_command_callback, this, 
        std::placeholders::_1)
      );
    }
  
  private:
    void keyboard_command_callback(const std_msgs::msg::String::SharedPtr msg_in) const
    {
      RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg_in->data.c_str());

      // TODO: validate command.
      auto msg_out = std_msgs::msg::Int8();
      msg_out.data = std::stoi(msg_in->data.c_str());
      RCLCPP_INFO(this->get_logger(), "Publishing: %i", msg_out.data);
      publisher_->publish(msg_out);
    }

    rclcpp::Publisher<std_msgs::msg::Int8>::SharedPtr publisher_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<LedSetting>());
  rclcpp::shutdown();
  return 0;
}
