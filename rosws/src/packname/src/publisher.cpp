#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
using namespace std::chrono_literals;

class Talker : public rclcpp::Node
{
public:
  Talker() : Node("talker_node")
  {
    // 创建发布者，话题名chatter，消息类型String，队列长度10
    publisher_ = this->create_publisher<std_msgs::msg::String>("chatter", 10);
    // 定时器：500ms执行一次回调
    timer_ = this->create_wall_timer(500ms, std::bind(&Talker::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto msg = std_msgs::msg::String();
    msg.data = "Hello ROS2!";
    RCLCPP_INFO(this->get_logger(), "发布消息: %s", msg.data.c_str());
    publisher_->publish(msg);
  }
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Talker>());
  rclcpp::shutdown();
  return 0;
}
