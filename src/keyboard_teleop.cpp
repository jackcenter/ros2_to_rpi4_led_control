#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class KeyboardTeleop : public rclcpp::Node
{
  public:
    KeyboardTeleop()
    : Node("keyboard_teleop")
    {
      publisher_ = this->create_publisher<std_msgs::msg::String>("keyboard_command", 10);
    }

    void run()
    {
      bool running = true;
      while (running && rclcpp::ok())
      {
        RCLCPP_INFO(this->get_logger(), "Enter value between 1 and 100... (type 'done' to finish)");
        std::string user_input;
        std::getline(std::cin, user_input);

        if (user_input.compare("done") == 0)
        {
          running = false;
        }

        auto message = std_msgs::msg::String();
        message.data = user_input;
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        publisher_->publish(message);
      }
    }

  private:    
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  KeyboardTeleop object = KeyboardTeleop();
  object.run();
  // rclcpp::spin(std::make_shared<KeyboardTeleop>());
  rclcpp::shutdown();
  return 0;
}
